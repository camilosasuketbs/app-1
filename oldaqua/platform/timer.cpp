﻿#include "framework.h"
#include "aqua/const/id.h"

#define THREADED_TIMER


timer::timer(::aqua::timer_array * ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void * pvoidData, class sync * pmutex) :
   ::object(ptimera)
{

   m_bRunning = false;

   initialize(ptimera);

   __refer(m_ptimera, ptimera);

   if(m_ptimera)
   {

      // m_ptimera->children_add(this);

      m_ptimera->m_map[uiTimer] = this;

      impl_init();

   }

   m_bHandling = false;

   m_nIDEvent = uiTimer;

   m_pfnTimer = pfnTimer;

   m_pvoidData = pvoidData;

   //set_mutex(pmutex);

   m_pcallback = nullptr;

   m_puserinteraction = nullptr;

}


timer::~timer()
{

}


bool timer::start(int millis, bool bPeriodic)
{

   sync_lock sl(mutex());

   if (::is_set(m_pcallback) && !m_pcallback->timer_is_ok())
   {

      return false;

   }

   set_ok();

   m_bPeriodic = bPeriodic;

   m_dwMillis = millis;

   try
   {

      m_bRunning = true;

      if(!impl_start())
      {

         return false;

      }

   }
   catch(...)
   {

      m_bRunning = false;

      return false;

   }

   //this->children_add(this);

   //Application.thread_add(this);

   return true;

}



void timer::call_on_timer()
{

   sync_lock sl(mutex());

   __keep_true(m_bHandling);

   if (!is_timer_ok())
   {

      return;

   }

   m_bDupHandle = false;

   //SetCurrentHandles();

   set_current_handles();

   ::set_thread(this);

   bool bRepeat = true;

   ::thread_set(id_thread_is_timer);

   try
   {

      if(!thread_get_run())
      {

         bRepeat = false;

      }

   }
   catch(...)
   {

      bRepeat = false;

   }

   if(bRepeat)
   {

      m_bTemporary = true;

      sl.unlock();

      try
      {

         if(!on_timer())
         {

            bRepeat = false;

         }

      }
      catch(...)
      {

      }

      sl.lock();

   }

   if(bRepeat)
   {

      try
      {

         if (m_bPeriodic)
         {

            if(!impl_restart())
            {

               bRepeat = false;

            }

         }
         else
         {

             bRepeat = false;

         }

      }
      catch (...)
      {

         bRepeat = false;

      }

   }
   else
   {

      try
      {

      }
      catch (...)
      {

      }

   }

   if(!bRepeat)
   {

      try
      {

         m_bRunning = false;

      }
      catch (...)
      {

      }

      try
      {

//         if(m_bPeriodic)
//         {
//
//            impl_stop();
//
//         }

         //finalize();

         //impl_term();

         //set_os_int(0);

         //set_os_data(nullptr);



      }
      catch(...)
      {

      }

   }
   else
   {

      //set_os_int(0);

      //set_os_data(nullptr);

   }

}


bool timer::on_timer()
{

   m_bRet = false;

   if (m_pfnTimer != nullptr)
   {

      m_pfnTimer(this);

      return true;

   }

   if (m_pcallback != nullptr)
   {

      return m_pcallback->on_timer(this);

   }

   return true;

}

void timer::term_thread()
{

   {

   sync_lock sl(mutex());

   try
   {

      m_ptimera->remove_timer(this);

   }
   catch (...)
   {

   }

}

   ::thread::term_thread();

}

//void timer::finalize()
//{
//
//
////   Application.thread_remove(this);
//
//
//   {
//
//      sync_lock sl(mutex());
//
//  //    if(m_bPeriodic)
//      //{
//
//      //   try
//      //   {
//
//      //      impl_stop();
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
////      try
////      {
////
////         m_bHandling = false;
////
////         impl_term();
////
////         try
////         {
////
////            if (m_bRunThisThread)
////            {
////
////               m_bRunThisThread = false;
////
////            }
////
////         }
////         catch (...)
////         {
////
////         }
////
////      }
////      catch (...)
////      {
////
////      }
//
//   ::thread::finalize();
//
//
//   }
//
//}


bool timer::thread_active() const
{

   return m_bRunning && ::thread::thread_active();

}





#ifdef THREADED_TIMER





//#if defined(LINUX) || defined(ANDROID)

//void aura_timer_handler(sigval sigval);


void timer::impl_init()
{

   //xxf_zero(m_sev);

   // m_timerid = nullptr;

   // m_sev.sigev_notify = SIGEV_THREAD;

   // m_sev.sigev_signo = 0;

   // m_sev.sigev_value.sival_ptr = this;

   // m_sev.sigev_notify_function = aura_timer_handler;

   //m_bInit = !timer_create(CLOCK_REALTIME, &m_sev, &m_timerid);

   //if (timer_create(CLOCK_REALTIME, &m_sev, &m_timerid) == -1)
   //{

   //   __throw(::exception::exception("timer_create failed"));

   //}

   m_bInit = true;

}


bool timer::impl_start()
{

   if (!m_bInit)
   {

      return false;

   }

   //itimerspec & its = m_its;

   //its.it_value.tv_sec = m_dwMillis / 1000;

   //its.it_value.tv_nsec = (m_dwMillis * 1000 * 1000) % (1000 * 1000 * 1000);


   begin();

   //   if (m_bPeriodic)
   //   {
   //
   //      its.it_interval = its.it_value;
   //
   //      if (timer_settime(m_timerid, 0, &its, nullptr) == -1)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //   }
   //   else
   ////   {
   //
   //      its.it_interval.tv_nsec = 0;
   //      its.it_interval.tv_sec = 0;
   //
   //      if (timer_settime(m_timerid, 0, &its, nullptr) == -1)
   //      {
   //
   //         return false;
   //
   //      }

      //}


   return true;

}


void timer::impl_term()
{

   if (m_bInit)
   {

      m_bInit = false;
      //
      //      timer_delete(m_timerid);

            //m_timerid = nullptr;

   }

}


void timer::impl_stop()
{

   set_finish();

   //   if (m_bInit)
   //   {
   //
   //      itimerspec its;
   //
   //      its.it_value.tv_nsec = 0;
   //      its.it_value.tv_sec = 0;
   //      its.it_interval.tv_nsec = 0;
   //      its.it_interval.tv_sec = 0;
   //
   //      if(timer_settime(m_timerid, 0, &its, nullptr) == -1)
   //      {
   //
   //         printf("Failed to stop the timer.");
   //
   //      }
   //
   //   }

}


bool timer::impl_restart()
{

   if (!m_bInit)
   {

      return false;

   }
   //
   //   if (!thread_get_run())
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   impl_stop();
   //
   //   if (timer_settime(m_timerid, 0, &m_its, nullptr) == -1)
   //   {
   //
   //      return false;
   //
   //   }
   //
   return true;

}

::estatus timer::run()
{

   while (thread_sleep(::millis((::i64) m_dwMillis)))
   {

      try
      {

         on_timer();

      }
      catch (...)
      {

      }

      if (!m_bPeriodic)
      {

         break;

      }

   }

   return m_estatus;

}
//void aura_timer_handler(sigval sigval)
//{
//
//   ::timer * ptimer = (::timer *) sigval.sival_ptr;
//
//   try
//   {
//
//      ptimer->call_on_timer();
//
//   }
//   catch (...)
//   {
//
//   }
//
//}

//#endif



#endif // THREADED_TIMER