#include "framework.h"


CLASS_DECL_AURA void thread_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_AURA void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_AURA int32_t thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);

CLASS_DECL_AURA int32_t process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, sync_object * * pobjectptra, DWORD tickTimeout, DWORD dwWakeMask, DWORD dwFlags)
{

   DWORD start = 0;

   if(tickTimeout != (DWORD) INFINITE)
   {

      start = ::get_tick();

   }

   __pointer(mq) pmq;

   if(dwWakeMask > 0)
   {

      pmq = __get_mq(GetCurrentThreadId(), false);

   }

   int_bool bWaitForAll        = dwFlags & MWMO_WAITALL;

   timespec delay;

   delay.tv_sec = 0;

   delay.tv_nsec = 1000000;

   if(bWaitForAll)
   {

      while(true)
      {

         int32_t i;

         int32_t j;

         i = 0;

         for(; comparison::lt(i, dwSize);)
         {

            if(pmq != nullptr)
            {

               sync_lock sl(&pmq->m_mutex);

               if(pmq->ma.get_count() > 0)
               {

                  return WAIT_OBJECT_0 + dwSize;

               }

            }

            if(tickTimeout != (DWORD) INFINITE && start.elapsed() >= tickTimeout)
            {

               for(j = 0; j < i; j++)
               {

                  pobjectptra[j]->unlock();

               }

               return WAIT_TIMEOUT;

            }

            if(pobjectptra[i]->lock(millis(1)))
            {

               i++;

            }
            else
            {

               nanosleep(&delay, nullptr);

            }

         }

         return WAIT_OBJECT_0;

      }

   }
   else
   {

      int32_t i;

      while(true)
      {

         for(i = 0; comparison::lt(i, dwSize); i++)
         {

            if(pmq != nullptr)
            {

               sync_lock sl(&pmq->m_mutex);

               if(pmq->ma.get_count() > 0)
               {

                  return WAIT_OBJECT_0 + dwSize;

               }

            }

            if(tickTimeout != (DWORD) INFINITE && start.elapsed() >= tickTimeout)
            {

               return WAIT_TIMEOUT;

            }

            if(pobjectptra[i]->lock(millis(0)))
            {

               return WAIT_OBJECT_0 + i;

            }

         }

         nanosleep(&delay, nullptr);

      }

   }

}


DWORD MsgWaitForMultipleObjects(DWORD dwSize, sync_object ** pobjectptra, WINBOOL bWaitForAll, DWORD tickTimeout, DWORD dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pobjectptra, tickTimeout, dwWakeMask, (bWaitForAll ?  MWMO_WAITALL : 0));

}


DWORD WaitForMultipleObjectsEx(DWORD dwSize, sync_object ** pobjectptra, WINBOOL bWaitForAll, DWORD tickTimeout, WINBOOL bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pobjectptra, tickTimeout, 0, (bWaitForAll ?  MWMO_WAITALL : 0) | (bAlertable ?  MWMO_ALERTABLE : 0));

}


DWORD WaitForMultipleObjects(DWORD dwSize, sync_object ** pobjectptra, WINBOOL bWaitForAll, DWORD tickTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, pobjectptra, bWaitForAll, tickTimeout, FALSE);

}


DWORD WaitForSingleObjectEx(sync_object * pobject, DWORD tickTimeout, WINBOOL bAlertable)
{

   return WaitForMultipleObjectsEx(1, &pobject, TRUE, tickTimeout, bAlertable);

}


DWORD WaitForSingleObject(sync_object * pobject, DWORD tickTimeout)
{

   return WaitForSingleObjectEx(pobject, tickTimeout, FALSE);

}


thread_data::thread_data()
{

   pthread_key_create(&m_key, nullptr);

}


thread_data::~thread_data()
{

}

void * thread_data::get()
{

   return pthread_getspecific(m_key);

}


void thread_data::set(void * p)
{

   pthread_setspecific(m_key,p);

}


CLASS_DECL_AURA HTHREAD get_current_hthread()
{

   return ::GetCurrentThread();

}


CLASS_DECL_AURA ITHREAD get_current_ithread()
{

   return ::GetCurrentThreadId();

}


void __node_init_multithreading()
{

   __node_init_cross_windows_threading();

}


void __node_term_multithreading()
{

   __node_term_cross_windows_threading();

}


#if defined(LINUX) // || defined(ANDROID)

bool (* g_pfn_defer_process_x_message)(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek) = nullptr;

bool aura_defer_process_x_message(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek)
{

   if(g_pfn_defer_process_x_message == nullptr)
      return false;

   return (*g_pfn_defer_process_x_message)(hthread, lpMsg, oswindow, bPeek);

}

void set_defer_process_x_message(bool (* pfn)(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek))
{

   g_pfn_defer_process_x_message = pfn;

}

#endif


extern "C"
void * os_thread_thread_proc(LPVOID lpparameter);


int_bool WINAPI SetThreadPriority(HTHREAD hThread,int32_t nCa2Priority)
{

   int32_t iPolicy;

   sched_param schedparam;

   thread_get_os_priority(&iPolicy,&schedparam,nCa2Priority);

   pthread_setschedparam((pthread_t) hThread,iPolicy,&schedparam);

   return TRUE;

}


int32_t WINAPI GetThreadPriority(HTHREAD  hthread)
{

   int iOsPolicy = SCHED_OTHER;

   sched_param schedparam;

   schedparam.sched_priority = 0;

   pthread_getschedparam((ITHREAD) hthread,&iOsPolicy,&schedparam);

   return thread_get_scheduling_priority(iOsPolicy,&schedparam);

}


static HTHREAD g_hMainThread = nullptr;

static ITHREAD g_iMainThread = (ITHREAD) -1;


CLASS_DECL_AURA void set_main_thread(HTHREAD hThread)
{

   g_hMainThread = hThread;

}


CLASS_DECL_AURA void set_main_thread_id(ITHREAD uiThread)
{

   g_iMainThread = uiThread;

}


CLASS_DECL_AURA HTHREAD get_main_thread()
{

   return g_hMainThread;

}


CLASS_DECL_AURA ITHREAD get_main_thread_id()
{

   return g_iMainThread;

}


CLASS_DECL_AURA void attach_thread_input_to_main_thread(bool bAttach)
{

}


// LPVOID WINAPI thread_get_data(HTHREAD hthread,DWORD dwIndex);

// int_bool WINAPI thread_set_data(HTHREAD hthread,DWORD dwIndex,LPVOID lpTlsValue);

DWORD g_dwDebug_post_thread_msg_time;

int g_iDebug_post_thread_msg_time;

CLASS_DECL_AURA int_bool WINAPI PostThreadMessage(ITHREAD iThreadId,UINT Msg,WPARAM wParam,LPARAM lParam)
{

   __pointer(mq) pmq = __get_mq(iThreadId);

   if(pmq == nullptr)
   {

      return FALSE;

   }

   sync_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   if(Msg == WM_QUIT)
   {

      ::output_debug_string("\n\n\nWM_QUIT posted to thread " + __str((uint64_t)iThreadId) + "\n\n\n");

   }

   msg.message = Msg;
   msg.wParam  = wParam;
   msg.lParam  = lParam;
   msg.pt.x    = 0x80000000;
   msg.pt.y    = 0x80000000;
   msg.hwnd    = nullptr;

   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}


CLASS_DECL_AURA HTHREAD GetCurrentThread()
{

   return pthread_self();

}


CLASS_DECL_AURA ITHREAD GetCurrentThreadId()
{

   return pthread_self();

}


namespace multithreading
{


   CLASS_DECL_AURA bool set_priority(::e_priority epriority)
   {

      return (::SetThreadPriority(::GetCurrentThread(),priority) != 0);

   }


   CLASS_DECL_AURA int32_t priority()
   {

      return ::GetThreadPriority(::GetCurrentThread());

   }


} // namespace aura


bool on_init_thread()
{

   if(!__os_init_thread())
   {

      return false;

   }

   return true;

}


bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}


CLASS_DECL_AURA DWORD_PTR translate_processor_affinity(int iOrder)
{

   return 1 << iOrder;

}



