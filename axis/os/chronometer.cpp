//////////////////////////////////////////////////////////////////////////////
// chronometer.cpp
// =========
// High Resolution chronometer.
// This chronometer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (ca) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////
#include "framework.h"




namespace axis
{

   ///////////////////////////////////////////////////////////////////////////////
   // constructor
   ///////////////////////////////////////////////////////////////////////////////
   chronometer::chronometer()
   {

      m_bStopped = false;
      m_beg = 0;
      m_end = 0;

   }



   ///////////////////////////////////////////////////////////////////////////////
   // distructor
   ///////////////////////////////////////////////////////////////////////////////
   chronometer::~chronometer()
   {
   }



   ///////////////////////////////////////////////////////////////////////////////
   // start chronometer.
   // startCount will be set at this point.
   ///////////////////////////////////////////////////////////////////////////////
   void chronometer::start()
   {
      
      m_bStopped = false; // reset stop flag

      m_beg = get_nanos();

   }



   ///////////////////////////////////////////////////////////////////////////////
   // stop the chronometer.
   // endCount will be set at this point.
   ///////////////////////////////////////////////////////////////////////////////
   void chronometer::stop()
   {
      
      m_bStopped = true; // set chronometer stopped flag

      m_end = get_nanos();

   }



   ///////////////////////////////////////////////////////////////////////////////
   // compute elapsed time in micro-second resolution.
   // other getElapsedTime will call this first, then convert to correspond resolution.
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getElapsedTimeInMicroSec()
   {

      if (!m_bStopped)
         m_end = get_nanos();

      return (m_end - m_beg) / 1000.0;

   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide elapsedTimeInMicroSec by 1000
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getElapsedTimeInMilliSec()
   {
      return this->getElapsedTimeInMicroSec() * 0.001;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide elapsedTimeInMicroSec by 1000000
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getElapsedTimeInSec()
   {
      return this->getElapsedTimeInMicroSec() * 0.000001;
   }


   ///////////////////////////////////////////////////////////////////////////////
   // compute time in micro-second resolution.
   // other getElapsedTime will call this first, then convert to correspond resolution.
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getTimeInMicroSec()
   {

      return get_nanos() / 1000.0;

   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide TimeInMicroSec by 1000
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getTimeInMilliSec()
   {
      return this->getTimeInMicroSec() * 0.001;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide TimeInMicroSec by 1000000
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getTimeInSec()
   {
      return this->getTimeInMicroSec() * 0.000001;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // same as getElapsedTimeInSec()
   ///////////////////////////////////////////////////////////////////////////////
   double chronometer::getElapsedTime()
   {
      return this->getElapsedTimeInSec();
   }


} // namespace axis



