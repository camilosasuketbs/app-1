/* Copyright 2012 William Woodall and John Harrison
 *
 * Additional Contributors: Christopher Baker @bakercp
 */

#include "framework.h"

 //#include <sstream>

#if !defined(_WIN32)

#include <stdio.h>
#include <string.h>
//#include <sstream>
#undef USE_MISC

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <errno.h>
#include <paths.h>
#include <sysexits.h>
#include <termios.h>
#include <sys/param.h>
#include <pthread.h>

#if defined(__linux__)
# include <linux/serial.h>
#endif

#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#ifdef __MACH__
#include <AvailabilityMacros.h>
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "serial.h"

#ifndef TIOCINQ
#ifdef FIONREAD
#define TIOCINQ FIONREAD
#else
#define TIOCINQ 0x541B
#endif
#endif

#if defined(MAC_OS_X_VERSION_10_3) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_3)
#include <IOKit/serial/ioss.h>
#endif

using serial::MillisecondTimer;
using serial::Serial;
using serial::SerialException;
using serial::PortNotOpenedException;
using serial::IOException;


MillisecondTimer::MillisecondTimer(const u32 millis)
   : expiry(timespec_now())
{
   i64 tv_nsec = expiry.tv_nsec + (millis * 1e6);
   if (tv_nsec >= 1e9)
   {
      i64 sec_diff = tv_nsec / static_cast<int> (1e9);
      expiry.tv_nsec = tv_nsec % static_cast<int>(1e9);
      expiry.tv_sec += sec_diff;
   }
   else
   {
      expiry.tv_nsec = tv_nsec;
   }
}

i64
MillisecondTimer::remaining()
{
   timespec now(timespec_now());
   i64 millis = (expiry.tv_sec - now.tv_sec) * 1e3;
   millis += (expiry.tv_nsec - now.tv_nsec) / 1e6;
   return millis;
}

timespec
MillisecondTimer::timespec_now()
{
   timespec time;
# ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
   clock_serv_t cclock;
   mach_timespec_t mts;
   host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   time.tv_sec = mts.tv_sec;
   time.tv_nsec = mts.tv_nsec;
# else
   clock_gettime(CLOCK_MONOTONIC, &time);
# endif
   return time;
}

timespec
timespec_from_ms(const u32 millis)
{
   timespec time;
   time.tv_sec = millis / 1e3;
   time.tv_nsec = (millis - (time.tv_sec * 1e3)) * 1e6;
   return time;
}

Serial::SerialImpl::SerialImpl(::element * pobject, const string & port, unsigned long baudrate,
   bytesize_t bytesize,
   parity_t parity, stopbits_t stopbits,
   flowcontrol_t flowcontrol)
   : element(pobject), m_strPort(port), m_iFd(-1), m_bOpened(false), m_bXonXoff(false), m_bRtsCts(false),
   m_ulBaudrate(baudrate), m_parity(parity),
   m_bytesize(bytesize), m_stopbits(stopbits), m_flowcontrol(flowcontrol)
{
   pthread_mutex_init(&this->m_mutexRead, nullptr);
   pthread_mutex_init(&this->m_mutexWrite, nullptr);
   if (m_strPort.empty() == false)
      open();
}

Serial::SerialImpl::~SerialImpl()
{
   close();
   pthread_mutex_destroy(&this->m_mutexRead);
   pthread_mutex_destroy(&this->m_mutexWrite);
}

void
Serial::SerialImpl::open()
{
   if (m_strPort.empty())
   {
      __throw(invalid_argument_exception("Empty port is invalid."));
   }
   if (m_bOpened == true)
   {
      __throw(SerialException("Serial port already open."));
   }

   m_iFd = ::open(m_strPort.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);

   if (m_iFd == -1)
   {
      switch (errno)
      {
      case EINTR:
         // Recurse because this is a recoverable error.
         open();
         return;
      case ENFILE:
      case EMFILE:
         THROW(IOException, "Too many file handles open.");
      default:
         THROW(IOException, errno);
      }
   }

   reconfigurePort();
   m_bOpened = true;
}

void
Serial::SerialImpl::reconfigurePort()
{
   if (m_iFd == -1)
   {
      // Can only operate on a valid file descriptor
      THROW(IOException, "Invalid file descriptor, is the serial port open?");
   }

   struct termios options; // The options for the file descriptor

   if (tcgetattr(m_iFd, &options) == -1)
   {
      THROW(IOException, "::tcgetattr");
   }

   // set up raw mode / no echo / binary
   options.c_cflag |= (tcflag_t)(CLOCAL | CREAD);
   options.c_lflag &= (tcflag_t)~(ICANON | ECHO | ECHOE | ECHOK | ECHONL |
      ISIG | IEXTEN); //|ECHOPRT

   options.c_oflag &= (tcflag_t)~(OPOST);
   options.c_iflag &= (tcflag_t)~(INLCR | IGNCR | ICRNL | IGNBRK);
#ifdef IUCLC
   options.c_iflag &= (tcflag_t)~IUCLC;
#endif
#ifdef PARMRK
   options.c_iflag &= (tcflag_t)~PARMRK;
#endif

   // setup baud rate
   bool custom_baud = false;
   speed_t baud;
   switch (m_ulBaudrate)
   {
#ifdef B0
   case 0: baud = B0; break;
#endif
#ifdef B50
   case 50: baud = B50; break;
#endif
#ifdef B75
   case 75: baud = B75; break;
#endif
#ifdef B110
   case 110: baud = B110; break;
#endif
#ifdef B134
   case 134: baud = B134; break;
#endif
#ifdef B150
   case 150: baud = B150; break;
#endif
#ifdef B200
   case 200: baud = B200; break;
#endif
#ifdef B300
   case 300: baud = B300; break;
#endif
#ifdef B600
   case 600: baud = B600; break;
#endif
#ifdef B1200
   case 1200: baud = B1200; break;
#endif
#ifdef B1800
   case 1800: baud = B1800; break;
#endif
#ifdef B2400
   case 2400: baud = B2400; break;
#endif
#ifdef B4800
   case 4800: baud = B4800; break;
#endif
#ifdef B7200
   case 7200: baud = B7200; break;
#endif
#ifdef B9600
   case 9600: baud = B9600; break;
#endif
#ifdef B14400
   case 14400: baud = B14400; break;
#endif
#ifdef B19200
   case 19200: baud = B19200; break;
#endif
#ifdef B28800
   case 28800: baud = B28800; break;
#endif
#ifdef B57600
   case 57600: baud = B57600; break;
#endif
#ifdef B76800
   case 76800: baud = B76800; break;
#endif
#ifdef B38400
   case 38400: baud = B38400; break;
#endif
#ifdef B115200
   case 115200: baud = B115200; break;
#endif
#ifdef B128000
   case 128000: baud = B128000; break;
#endif
#ifdef B153600
   case 153600: baud = B153600; break;
#endif
#ifdef B230400
   case 230400: baud = B230400; break;
#endif
#ifdef B256000
   case 256000: baud = B256000; break;
#endif
#ifdef B460800
   case 460800: baud = B460800; break;
#endif
#ifdef B576000
   case 576000: baud = B576000; break;
#endif
#ifdef B921600
   case 921600: baud = B921600; break;
#endif
#ifdef B1000000
   case 1000000: baud = B1000000; break;
#endif
#ifdef B1152000
   case 1152000: baud = B1152000; break;
#endif
#ifdef B1500000
   case 1500000: baud = B1500000; break;
#endif
#ifdef B2000000
   case 2000000: baud = B2000000; break;
#endif
#ifdef B2500000
   case 2500000: baud = B2500000; break;
#endif
#ifdef B3000000
   case 3000000: baud = B3000000; break;
#endif
#ifdef B3500000
   case 3500000: baud = B3500000; break;
#endif
#ifdef B4000000
   case 4000000: baud = B4000000; break;
#endif
   default:
      custom_baud = true;
      // OS X support
#if defined(MAC_OS_X_VERSION_10_4) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_4)
      // Starting with Tiger, the IOSSIOSPEED ioctl can be used to set arbitrary baud rates
      // other than those specified by POSIX. The driver for the underlying serial hardware
      // ultimately determines which baud rates can be used. This ioctl sets both the input
      // and output speed.
      speed_t new_baud = static_cast<speed_t> (m_ulBaudrate);
      if (-1 == ioctl(m_iFd, IOSSIOSPEED, &new_baud, 1))
      {
         THROW(IOException, errno);
      }
      // Linux Support
#elif defined(__linux__) && defined (TIOCSSERIAL)
      struct serial_struct ser;

      if (-1 == ioctl(m_iFd, TIOCGSERIAL, &ser))
      {
         THROW(IOException, errno);
      }

      // set custom divisor
      ser.custom_divisor = ser.baud_base / static_cast<int> (m_ulBaudrate);
      // update flags
      ser.flags &= ~ASYNC_SPD_MASK;
      ser.flags |= ASYNC_SPD_CUST;

      if (-1 == ioctl(m_iFd, TIOCSSERIAL, &ser))
      {
         THROW(IOException, errno);
      }
#else
      __throw(invalid_argument("OS does not currently support custom bauds"));
#endif
   }
   if (custom_baud == false)
   {
#ifdef _BSD_SOURCE
      ::cfsetspeed(&options, baud);
#else
      ::cfsetispeed(&options, baud);
      ::cfsetospeed(&options, baud);
#endif
   }

   // setup char len
   options.c_cflag &= (tcflag_t)~CSIZE;
   if (m_bytesize == eightbits)
      options.c_cflag |= CS8;
   else if (m_bytesize == sevenbits)
      options.c_cflag |= CS7;
   else if (m_bytesize == sixbits)
      options.c_cflag |= CS6;
   else if (m_bytesize == fivebits)
      options.c_cflag |= CS5;
   else
      __throw(invalid_argument_exception("invalid char len"));
   // setup stopbits
   if (m_stopbits == stopbits_one)
      options.c_cflag &= (tcflag_t)~(CSTOPB);
   else if (m_stopbits == stopbits_one_point_five)
      // ONE POINT FIVE same as TWO.. there is no POSIX support for 1.5
      options.c_cflag |= (CSTOPB);
   else if (m_stopbits == stopbits_two)
      options.c_cflag |= (CSTOPB);
   else
      __throw(invalid_argument_exception("invalid stop bit"));
   // setup parity
   options.c_iflag &= (tcflag_t)~(INPCK | ISTRIP);
   if (m_parity == parity_none)
   {
      options.c_cflag &= (tcflag_t)~(PARENB | PARODD);
   }
   else if (m_parity == parity_even)
   {
      options.c_cflag &= (tcflag_t)~(PARODD);
      options.c_cflag |= (PARENB);
   }
   else if (m_parity == parity_odd)
   {
      options.c_cflag |= (PARENB | PARODD);
   }
#ifdef CMSPAR
   else if (m_parity == parity_mark)
   {
      options.c_cflag |= (PARENB | CMSPAR | PARODD);
   }
   else if (m_parity == parity_space)
   {
      options.c_cflag |= (PARENB | CMSPAR);
      options.c_cflag &= (tcflag_t)~(PARODD);
   }
#else
   // CMSPAR is not defined on OSX. So do not support mark or space parity.
   else if (m_parity == parity_mark || m_parity == parity_space)
   {
      __throw(invalid_argument_exception("OS does not support mark or space parity"));
   }
#endif  // ifdef CMSPAR
   else
   {
      __throw(invalid_argument_exception("invalid parity"));
   }
   // setup flow control
   if (m_flowcontrol == flowcontrol_none)
   {
      m_bXonXoff = false;
      m_bRtsCts = false;
   }
   if (m_flowcontrol == flowcontrol_software)
   {
      m_bXonXoff = true;
      m_bRtsCts = false;
   }
   if (m_flowcontrol == flowcontrol_hardware)
   {
      m_bXonXoff = false;
      m_bRtsCts = true;
   }
   // xonxoff
#ifdef IXANY
   if (m_bXonXoff)
      options.c_iflag |= (IXON | IXOFF); //|IXANY)
   else
      options.c_iflag &= (tcflag_t)~(IXON | IXOFF | IXANY);
#else
   if (m_bXonXoff)
      options.c_iflag |= (IXON | IXOFF);
   else
      options.c_iflag &= (tcflag_t)~(IXON | IXOFF);
#endif
   // rtscts
#ifdef CRTSCTS
   if (m_bRtsCts)
      options.c_cflag |= (CRTSCTS);
   else
      options.c_cflag &= (unsigned long)~(CRTSCTS);
#elif defined CNEW_RTSCTS
   if (m_bRtsCts)
      options.c_cflag |= (CNEW_RTSCTS);
   else
      options.c_cflag &= (unsigned long)~(CNEW_RTSCTS);
#else
#error "OS Support seems wrong."
#endif

   // http://www.unixwiz.net/techtips/termios-vmin-vtime.html
   // this basically sets the read call up to be a polling read,
   // but we are using select to ensure there is data available
   // to read before each call, so we should never needlessly poll
   options.c_cc[VMIN] = 0;
   options.c_cc[VTIME] = 0;

   // activate settings
   ::tcsetattr(m_iFd, TCSANOW, &options);

   // Update byte_time_ based on the new settings.
   u32 bit_time_ns = 1e9 / m_ulBaudrate;
   m_uiByteTimeNs = bit_time_ns * (1 + m_bytesize + m_parity + m_stopbits);

   // Compensate for the stopbits_one_point_five enum being equal to int 3,
   // and not 1.5.
   if (m_stopbits == stopbits_one_point_five)
   {
      m_uiByteTimeNs += ((1.5 - stopbits_one_point_five) * bit_time_ns);
   }
}

void
Serial::SerialImpl::close()
{
   if (m_bOpened == true)
   {
      if (m_iFd != -1)
      {
         int ret;
         ret = ::close(m_iFd);
         if (ret == 0)
         {
            m_iFd = -1;
         }
         else
         {
            THROW(IOException, errno);
         }
      }
      m_bOpened = false;
   }
}

bool
Serial::SerialImpl::isOpen() const
{
   return m_bOpened;
}

size_t
Serial::SerialImpl::available()
{
   if (!m_bOpened)
   {
      return 0;
   }
   int count = 0;
   if (-1 == ioctl(m_iFd, TIOCINQ, &count))
   {
      THROW(IOException, errno);
   }
   else
   {
      return static_cast<size_t> (count);
   }
}

bool
Serial::SerialImpl::waitReadable(u32 timeout)
{
   // Setup a select call to block for serial data or a timeout
   fd_set readfds;
   FD_ZERO(&readfds);
   FD_SET(m_iFd, &readfds);
   timespec timeout_ts(timespec_from_ms(timeout));
   int r = pselect(m_iFd + 1, &readfds, nullptr, nullptr, &timeout_ts, nullptr);

   if (r < 0)
   {
      // Select was interrupted
      if (errno == EINTR)
      {
         return false;
      }
      // Otherwise there was some error
      THROW(IOException, errno);
   }
   // Timeout occurred
   if (r == 0)
   {
      return false;
   }
   // This shouldn't happen, if r > 0 our fd has to be in the list!
   if (!FD_ISSET(m_iFd, &readfds))
   {
      THROW(IOException, "select reports ready to read, but our fd isn't"
         " in the list, this shouldn't happen!");
   }
   // Data available to read.
   return true;
}

void
Serial::SerialImpl::waitByteTimes(size_t count)
{
   timespec wait_time = { 0, static_cast<long>(m_uiByteTimeNs * count) };
   pselect(0, nullptr, nullptr, nullptr, &wait_time, nullptr);
}

size_t
Serial::SerialImpl::read(u8 * buf, size_t size)
{
   // If the port is not open, __throw(new
   if (!m_bOpened)
   {
      __throw(PortNotOpenedException("Serial::read"));
   }
   size_t bytes_read = 0;

   // Calculate total timeout in milliseconds t_c + (t_m * N)
   long total_timeout_ms = m_timeout.read_timeout_constant;
   total_timeout_ms += m_timeout.read_timeout_multiplier * static_cast<long> (size);
   MillisecondTimer total_timeout((u32)total_timeout_ms);

   // Pre-fill buffer with available bytes
   {
      ssize_t bytes_read_now = ::read(m_iFd, buf, size);
      if (bytes_read_now > 0)
      {
         bytes_read = bytes_read_now;
      }
   }

   while (bytes_read < size)
   {
      i64 timeout_remaining_ms = total_timeout.remaining();
      if (timeout_remaining_ms <= 0)
      {
         // Timed out
         break;
      }
      // Timeout for the next select is whichever is less of the remaining
      // total read timeout and the inter-byte timeout.
      u32 timeout = min(static_cast<u32> (timeout_remaining_ms),
         m_timeout.inter_byte_timeout);
      // Wait for the device to be readable, and then attempt to read.
      if (waitReadable(timeout))
      {
         // If it's a fixed-length multi-byte read, insert a wait here so that
         // we can attempt to grab the whole thing in a single IO call. Skip
         // this wait if a non-max inter_byte_timeout is specified.
         if (size > 1 && m_timeout.inter_byte_timeout == Timeout::max())
         {
            size_t bytes_available = available();
            if (bytes_available + bytes_read < size)
            {
               waitByteTimes(size - (bytes_available + bytes_read));
            }
         }
         // This should be non-blocking returning only what is available now
         //  Then returning so that select can block again.
         ssize_t bytes_read_now =
            ::read(m_iFd, buf + bytes_read, size - bytes_read);
         // read should always return some data as select reported it was
         // ready to read when we get to this point.
         if (bytes_read_now < 1)
         {
            // Disconnected devices, at least on Linux, show the
            // behavior that they are always ready to read immediately
            // but reading returns nothing.
            __throw( SerialException("device reports readiness to read but returned no data (device disconnected?)"));
         }
         // Update bytes_read
         bytes_read += static_cast<size_t> (bytes_read_now);
         // If bytes_read == size then we have read everything we need
         if (bytes_read == size)
         {
            break;
         }
         // If bytes_read < size then we have more to read
         if (bytes_read < size)
         {
            continue;
         }
         // If bytes_read > size then we have over read, which shouldn't happen
         if (bytes_read > size)
         {
            __throw( SerialException("read over read, too many bytes where "
               "read, this shouldn't happen, might be "
               "a logical error!"));
         }
      }
   }
   return bytes_read;
}

size_t
Serial::SerialImpl::write(const u8 * data, size_t length)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::write"));
   }
   fd_set writefds;
   size_t bytes_written = 0;

   // Calculate total timeout in milliseconds t_c + (t_m * N)
   long total_timeout_ms = m_timeout.write_timeout_constant;
   total_timeout_ms += m_timeout.write_timeout_multiplier * static_cast<long> (length);
   MillisecondTimer total_timeout((u32)total_timeout_ms);

   bool first_iteration = true;
   while (bytes_written < length)
   {
      i64 timeout_remaining_ms = total_timeout.remaining();
      // Only consider the timeout if it's not the first iteration of the loop
      // otherwise a timeout of 0 won't be allowed through
      if (!first_iteration && (timeout_remaining_ms <= 0))
      {
         // Timed out
         break;
      }
      first_iteration = false;

      timespec timeout(timespec_from_ms((u32)timeout_remaining_ms));

      FD_ZERO(&writefds);
      FD_SET(m_iFd, &writefds);

      // Do the select
      int r = pselect(m_iFd + 1, nullptr, &writefds, nullptr, &timeout, nullptr);

      // Figure out what happened by looking at select's response 'r'
      /** Error **/
      if (r < 0)
      {
         // Select was interrupted, try again
         if (errno == EINTR)
         {
            continue;
         }
         // Otherwise there was some error
         THROW(IOException, errno);
      }
      /** Timeout **/
      if (r == 0)
      {
         break;
      }
      /** Port ready to write **/
      if (r > 0)
      {
         // Make sure our file descriptor is in the ready to write list
         if (FD_ISSET(m_iFd, &writefds))
         {
            // This will write some
            ssize_t bytes_written_now =
               ::write(m_iFd, data + bytes_written, length - bytes_written);
            // write should always return some data as select reported it was
            // ready to write when we get to this point.
            if (bytes_written_now < 1)
            {
               // Disconnected devices, at least on Linux, show the
               // behavior that they are always ready to write immediately
               // but writing returns nothing.
               __throw( SerialException("device reports readiness to write but "
                  "returned no data (device disconnected?)"));
            }
            // Update bytes_written
            bytes_written += static_cast<size_t> (bytes_written_now);
            // If bytes_written == size then we have written everything we need to
            if (bytes_written == length)
            {
               break;
            }
            // If bytes_written < size then we have more to write
            if (bytes_written < length)
            {
               continue;
            }
            // If bytes_written > size then we have over written, which shouldn't happen
            if (bytes_written > length)
            {
               __throw( SerialException("write over wrote, too many bytes where "
                  "written, this shouldn't happen, might be "
                  "a logical error!"));
            }
         }
         // This shouldn't happen, if r > 0 our fd has to be in the list!
         THROW(IOException, "select reports ready to write, but our fd isn't"
            " in the list, this shouldn't happen!");
      }
   }
   return bytes_written;
}

void
Serial::SerialImpl::setPort(const string & port)
{
   m_strPort = port;
}

string
Serial::SerialImpl::getPort() const
{
   return m_strPort;
}

void
Serial::SerialImpl::setTimeout(serial::Timeout & timeout)
{
   m_timeout = timeout;
}

serial::Timeout
Serial::SerialImpl::getTimeout() const
{
   return m_timeout;
}

void
Serial::SerialImpl::setBaudrate(unsigned long baudrate)
{
   m_ulBaudrate = baudrate;
   if (m_bOpened)
      reconfigurePort();
}

unsigned long
Serial::SerialImpl::getBaudrate() const
{
   return m_ulBaudrate;
}

void
Serial::SerialImpl::setBytesize(serial::bytesize_t bytesize)
{
   m_bytesize = bytesize;
   if (m_bOpened)
      reconfigurePort();
}

serial::bytesize_t
Serial::SerialImpl::getBytesize() const
{
   return m_bytesize;
}

void
Serial::SerialImpl::setParity(serial::parity_t parity)
{
   m_parity = parity;
   if (m_bOpened)
      reconfigurePort();
}

serial::parity_t
Serial::SerialImpl::getParity() const
{
   return m_parity;
}

void
Serial::SerialImpl::setStopbits(serial::stopbits_t stopbits)
{
   m_stopbits = stopbits;
   if (m_bOpened)
      reconfigurePort();
}

serial::stopbits_t
Serial::SerialImpl::getStopbits() const
{
   return m_stopbits;
}

void
Serial::SerialImpl::setFlowcontrol(serial::flowcontrol_t flowcontrol)
{
   m_flowcontrol = flowcontrol;
   if (m_bOpened)
      reconfigurePort();
}

serial::flowcontrol_t
Serial::SerialImpl::getFlowcontrol() const
{
   return m_flowcontrol;
}

void
Serial::SerialImpl::flush()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::flush"));
   }
   tcdrain(m_iFd);
}

void
Serial::SerialImpl::flushInput()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::flushInput"));
   }
   tcflush(m_iFd, TCIFLUSH);
}

void
Serial::SerialImpl::flushOutput()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::flushOutput"));
   }
   tcflush(m_iFd, TCOFLUSH);
}

void
Serial::SerialImpl::sendBreak(int duration)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::sendBreak"));
   }
   tcsendbreak(m_iFd, static_cast<int> (duration / 4));
}

void
Serial::SerialImpl::setBreak(bool level)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::setBreak"));
   }

   if (level)
   {
      if (-1 == ioctl(m_iFd, TIOCSBRK))
      {
         string str;
         str.Format("setBreak failed on a call to ioctl(TIOCSBRK): %d %s", errno, strerror(errno));
         __throw(SerialException(str));
      }
   }
   else
   {
      if (-1 == ioctl(m_iFd, TIOCCBRK))
      {
         string ss;
         ss.Format("setBreak failed on a call to ioctl(TIOCCBRK): %d %s", errno, strerror(errno));
         __throw(SerialException(ss));
      }
   }
}

void
Serial::SerialImpl::setRTS(bool level)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::setRTS"));
   }

   int command = TIOCM_RTS;

   if (level)
   {
      if (-1 == ioctl(m_iFd, TIOCMBIS, &command))
      {
         text_stream ss;
         ss << "setRTS failed on a call to ioctl(TIOCMBIS): " << errno << " " << strerror(errno);
         __throw(SerialException(ss.str().c_str()));
      }
   }
   else
   {
      if (-1 == ioctl(m_iFd, TIOCMBIC, &command))
      {
         text_stream ss;
         ss << "setRTS failed on a call to ioctl(TIOCMBIC): " << errno << " " << strerror(errno);
         __throw(SerialException(ss.str().c_str()));
      }
   }
}

void
Serial::SerialImpl::setDTR(bool level)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::setDTR"));
   }

   int command = TIOCM_DTR;

   if (level)
   {
      if (-1 == ioctl(m_iFd, TIOCMBIS, &command))
      {
         text_stream ss;
         ss << "setDTR failed on a call to ioctl(TIOCMBIS): " << errno << " " << strerror(errno);
         __throw(SerialException(ss.str().c_str()));
      }
   }
   else
   {
      if (-1 == ioctl(m_iFd, TIOCMBIC, &command))
      {
         text_stream ss;
         ss << "setDTR failed on a call to ioctl(TIOCMBIC): " << errno << " " << strerror(errno);
         __throw(SerialException(ss.str().c_str()));
      }
   }
}

bool
Serial::SerialImpl::waitForChange()
{
#ifndef TIOCMIWAIT

   while (m_bOpened == true)
   {

      int status;

      if (-1 == ioctl(m_iFd, TIOCMGET, &status))
      {
         text_stream ss;
         ss << "waitForChange failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
         __throw(SerialException(ss.str().c_str()));
      }
      else
      {
         if (0 != (status & TIOCM_CTS)
            || 0 != (status & TIOCM_DSR)
            || 0 != (status & TIOCM_RI)
            || 0 != (status & TIOCM_CD))
         {
            return true;
         }
      }

      usleep(1000);
   }

   return false;
#else
   int command = (TIOCM_CD | TIOCM_DSR | TIOCM_RI | TIOCM_CTS);

   if (-1 == ioctl(m_iFd, TIOCMIWAIT, &command))
   {
      string ss;
      ss.Format("waitForDSR failed on a call to ioctl(TIOCMIWAIT): %d %s", errno, strerror(errno));
      __throw(SerialException(ss.str().c_str()));
   }
   return true;
#endif
}

bool
Serial::SerialImpl::getCTS()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::getCTS"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getCTS failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      __throw(SerialException(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_CTS);
   }
}

bool
Serial::SerialImpl::getDSR()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::getDSR"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getDSR failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      __throw(SerialException(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_DSR);
   }
}

bool
Serial::SerialImpl::getRI()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::getRI"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getRI failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      __throw(SerialException(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_RI);
   }
}

bool
Serial::SerialImpl::getCD()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException("Serial::getCD"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getCD failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      __throw(SerialException(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_CD);
   }
}

void
Serial::SerialImpl::readLock()
{
   int result = pthread_mutex_lock(&this->m_mutexRead);
   if (result)
   {
      THROW(IOException, result);
   }
}

void
Serial::SerialImpl::readUnlock()
{
   int result = pthread_mutex_unlock(&this->m_mutexRead);
   if (result)
   {
      THROW(IOException, result);
   }
}

void
Serial::SerialImpl::writeLock()
{
   int result = pthread_mutex_lock(&this->m_mutexWrite);
   if (result)
   {
      THROW(IOException, result);
   }
}

void
Serial::SerialImpl::writeUnlock()
{
   int result = pthread_mutex_unlock(&this->m_mutexWrite);
   if (result)
   {
      THROW(IOException, result);
   }
}

#endif // !defined(_WIN32)
