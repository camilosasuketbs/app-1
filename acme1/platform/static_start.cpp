#include "framework.h"
#include "static_start.h"
//#include "acme/net/sockets/_.h"
#include "acme/memory/plex_heap1.h"
#include "acme/memory/plex_heap_impl1.h"
//#include "acme/platform/app_core.h"
#include "acme/primitive/primitive/malloc.h"
#include "acme/astr.h"
#include "acme/os/_os.h"

//#include <sqlite3.h>

#ifdef RASPBIAN
#define PLATFORM_NAMESPACE linux
#endif

#if defined(__APPLE__)
#include <xlocale.h>
#else
#include <locale.h>
#endif

#ifdef LINUX
#include <glib.h> // sudo apt-get install libglib2.0-dev
#endif




void trace_category_static_init();
void trace_category_static_term();


//extern thread_local __pointer(::thread) t_pthread;


#undef new


#ifdef LINUX
static void
log_handler (const gchar   *log_domain,
             GLogLevelFlags log_level,
             const gchar   *message,
             gpointer       user_data)
{
   g_log_default_handler (log_domain, log_level, message, user_data);

   g_on_error_query (nullptr);
}


#endif


namespace acme
{


#ifdef WINDOWS_DESKTOP

   HINSTANCE      g_hinstance = nullptr;

#endif



#if OBJ_TYP_CTR

   map < const char*, const char*, ::i64, ::i64 >* g_pmapObjTypCtr;

#endif


   //critical_section* g_pcsRefDbg;
   bool g_bace;


#if OBJ_TYP_CTR

   int g_iObjTypCtrInit;

#endif

   CLASS_DECL_ACME critical_section* g_pcsFont = nullptr;

   CLASS_DECL_ACME string_to_string * g_pmapFontFaceName = nullptr;

   ::mutex* g_pmutexChildren;
   ::mutex* g_pmutexThreadWaitClose;
   //string_map < __pointer(::acme::library) >* g_pmapLibrary;
   //string_map < PFN_NEW_ace_LIBRARY >* g_pmapNewaceLibrary;


#if !defined(WINDOWS)

//void windows10_init();
//#ifdef WINDOWS

//
//   void set_simple_output_debug_string_a();
//
//   void set_extended_output_debug_string_a();
//
//   void set_simple_output_debug_string_w();
//
//   void set_extended_output_debug_string_w();
//
//
//   //#endif
//
//#else

   DWORD_PTR g_tlsindexLastError;
   char* g_pszDemangle;
   critical_section* g_pcsDemangle;

#endif


   //::mutex * &::get_context_system()->g_mutexLibrary;

   __LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;

   ::mutex* g_pmutexGlobals;

   critical_section* g_pcsGlobal;

   bool g_bOutputDebugString;

   critical_section* g_pcsTrace;

   ::generic* g_ptrace;

   simple_trace* g_psimpletrace;

#ifdef __APPLE__

   // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
   // http://stackoverflow.com/users/346736/jbenet

   //#include <mach/clock.h>
   //#include <mach/mach.h>
#include <mach/mach_time.h>

//clock_serv_t   g_cclock;
   double g_machtime_conversion_factor;
   //   clock_get_time(cclock, &mts);

#endif


   ::mutex* g_pmutexCred;


   class ::exception_engine* g_pexceptionengine;

   ::mutex* g_pmutexMessageDispatch;


   array < generic* >* g_paace;


   ::map < ::id, const ::id&, ::id, const ::id& >* g_pmapRTL;

   plex_heap_alloc_array* g_pheap;

   critical_section* g_pmutexSystemHeap;

#if defined(WINDOWS)

   _locale_t g_localeC;

#else

   locale_t g_localeC;

#endif

   //map < ITHREAD, ITHREAD, ITHREAD, ITHREAD > * g_pmapThreadOn;

#ifdef WINDOWS

   LARGE_INTEGER g_largeintegerFrequency;

#endif

   i64 g_iFirstNano;

   //plex_heap_alloc_array * g_pplexheapallocarray;

   int g_iMemoryCountersStartable;
   //mutex * g_pmutexTrait;
   //::mutex * g_pmutexFactory;

   ::mutex* g_pmutexUiDestroyed;

#ifdef ANDROID

   ::mutex* g_pmutexOutputDebugStringA;

#endif

   //acme commented
   //CLASS_DECL_ACME ace_str_pool* g_pacestrpool;

   // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   // ::mutex * g_pmutexMq;

   // #endif

#if defined(LINUX) || defined(__APPLE__) || defined(_UWP) || defined(ANDROID)

//::mutex * g_pmutexThreadIdHandleLock;

//::mutex * g_pmutexThreadIdLock;

//#if !defined(_UWP)

//::mutex * g_pmutexPendingThreadsLock;

//#endif

//::mutex * g_pmutexTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(_UWP)


#if defined(LINUX) || defined(__APPLE__)


   ::mutex* g_pmutexTz;

   ::mutex* g_pmutexThreadHandleLock;


#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


   ::mutex* g_pmutexCvt;


#endif


   critical_section g_csRefDbg;



   void acme::construct()
   {

      g_bace = 0;

#if OBJ_TYP_CTR

      g_pmapObjTypCtr = nullptr;

#endif

      g_bace = false;

#if OBJ_TYP_CTR

      g_iObjTypCtrInit = 0;

#endif

      g_pmutexChildren = nullptr;

      g_pmutexThreadWaitClose = nullptr;

#if !defined(WINDOWS)

      g_tlsindexLastError = 0;

      g_pszDemangle = nullptr;

      g_pcsDemangle = nullptr;

#endif

      g_main_deferred_run = nullptr;

      g_pmutexGlobals = nullptr;

      g_pcsGlobal = nullptr;

      g_bOutputDebugString = true;

      g_pcsTrace = nullptr;

      g_ptrace = nullptr;

      g_psimpletrace = nullptr;

#ifdef __APPLE__

      // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
      // http://stackoverflow.com/users/346736/jbenet

      //#include <mach/clock.h>
      //#include <mach/mach.h>
#include <mach/mach_time.h>

//clock_serv_t   g_cclock;
      g_machtime_conversion_factor = 0.0;
      //   clock_get_time(cclock, &mts);

#endif

      g_pmutexCred = nullptr;

      g_pexceptionengine = nullptr;
      g_pmutexMessageDispatch = nullptr;

      g_paace = nullptr;

      g_pmapRTL = nullptr;

      //::map < void *, void *,::acme::application *, ::acme::application * > * g_pmapace;

      //string_map < __pointer(::acme::library) > * g_pmapLibCall;

      g_pheap = nullptr;

      g_pmutexSystemHeap = nullptr;

      //::mutex * g_pmutexThreadOn;

#if defined(WINDOWS)

      g_localeC = 0;

#else

      g_localeC = 0;

#endif

      //map < ITHREAD, ITHREAD, ITHREAD, ITHREAD > * g_pmapThreadOn;

#ifdef WINDOWS

      g_largeintegerFrequency = {};

#endif

      g_iFirstNano = 0;

      //plex_heap_alloc_array * g_pplexheapallocarray = nullptr;

      g_iMemoryCountersStartable = 0;
      //mutex * g_pmutexTrait;
      //::mutex * g_pmutexFactory;

      g_pmutexUiDestroyed = 0;

#ifdef ANDROID

      g_pmutexOutputDebugStringA = 0;

#endif
      //acme commented
      //g_pacestrpool = nullptr;

      // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      // ::mutex * g_pmutexMq;

      // #endif

#if defined(LINUX) || defined(__APPLE__) || defined(_UWP) || defined(ANDROID)

//::mutex * g_pmutexThreadIdHandleLock;

//::mutex * g_pmutexThreadIdLock;

//#if !defined(_UWP)

//::mutex * g_pmutexPendingThreadsLock;

//#endif

//::mutex * g_pmutexTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(_UWP)

#if defined(LINUX) || defined(__APPLE__)

      g_pmutexTz = nullptr;

      g_pmutexThreadHandleLock = nullptr;

#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


      g_pmutexCvt = nullptr;


#endif

      g_pcsFont = nullptr;

      g_pmapFontFaceName = nullptr;



   }


   acme::acme()
   {

      m_bRef = false;

      construct();

      //g_pcsRefDbg = nullptr;


#if defined(WINDOWS)

      g_localeC = _wcreate_locale(LC_ALL, L"C");

#elif defined(__APPLE__)

      g_localeC = newlocale(LC_ALL, "C", NULL);

#else

      g_localeC = newlocale(LC_ALL_MASK, "C", NULL);

#endif

#ifndef WINDOWS

      g_pcsDemangle = new critical_section;

#endif

      g_pcsTrace = new critical_section;

#ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

      SetThreadLocale(65001);

      ::SetConsoleOutputCP(65001);

#endif

      ::QueryPerformanceFrequency(&g_largeintegerFrequency);

#elif defined(__APPLE__)

      {

         mach_timebase_info_data_t timebase;

         mach_timebase_info(&timebase);

         g_machtime_conversion_factor = (double)timebase.numer / (double)timebase.denom;

      }

#endif

      g_iFirstNano = get_nanos();

      //xxdebug_box("acme.dll base_static_start (0)", "box", MB_OK);

      g_pexceptionengine = new ::PLATFORM_NAMESPACE::exception_engine();

      g_pmutexGlobals = new ::mutex();

      g_pmutexChildren = new ::mutex();

      g_pcsGlobal = new critical_section();

#ifndef __MCRTDBG

      g_pheap = new plex_heap_alloc_array();

#endif

      ::id_space::s_pidspace = new id_space();

      init_id_pool();

#ifdef ANDROID

      g_pmutexOutputDebugStringA = new ::mutex();

#endif

#if OBJ_TYP_CTR

      g_pmapObjTypCtr = new map < const char*, const char*, ::i64, ::i64 >;

#endif

      trace_category_static_init();

      g_psimpletrace = new simple_trace;

      g_ptrace = g_psimpletrace;

      //acme commented
//#ifdef BSD_STYLE_SOCKETS
//
//      ::sockets::base_socket::s_pmutex = new ::mutex();
//
//#endif


#ifdef __APPLE__

      g_pmutexCvt = new ::mutex();

#endif

      g_pmutexThreadWaitClose = new ::mutex();

      //g_pmutexThreadOn = new ::mutex();

      //g_pmapThreadOn = new ::map < ITHREAD, ITHREAD, ITHREAD, ITHREAD >;

      g_pmutexSystemHeap = new critical_section();

#if MEMDLEAK

      memdleak_init();

#endif

      ::factory::factory_init();

      g_paace = new array < generic * >;

      //g_pmapace =new ::map < void *,void *,::acme::application *,::acme::application * >;

      g_pmutexUiDestroyed = new ::mutex();

      g_pmutexMessageDispatch = new ::mutex();

      g_pmutexCred = new ::mutex();

#if defined(LINUX) || defined(__APPLE__)

      g_pmutexTz = new ::mutex();

#endif // defined(LINUX) || defined(__APPLE__)

      g_pmapRTL = nullptr;

      //&::get_context_system()->g_mutexLibrary = new ::mutex;

      //g_pmapLibrary = new string_map < __pointer(::acme::library) >();

      //g_pmapNewaceLibrary = new string_map < PFN_NEW_ace_LIBRARY >();

#ifndef _UWP

      br_init(nullptr);

#endif

      // Only draw2d implementations needing "big" synch should init_draw2d_mutex();
      // init_draw2d_mutex();

#ifdef MACOS

      //mach_port_deallocate(mach_task_self(), g_cclock);

#endif

#ifdef PRIMITIVE_DEBUG

      ace_auto_debug_teste();

#endif

      //g_pmapLibCall = new string_map < __pointer(::acme::library) >();

#ifdef MEMORY_COUNTERS

      g_iMemoryCountersStartable = 1;

#else

      g_iMemoryCountersStartable = 0;

#endif

      //sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

      //acme commented
      //__construct_new(::channel::s_pmutexChannel);

#ifdef LINUX

      ::user::initialize_edesktop();

#endif

      //acme commented
      //g_pacestrpool = new ace_str_pool();

      //acme commented
      //::user::init_windowing();

      //g_pcsRefDbg = new critical_section();

      g_bace = 1;

      //::thread::g_pmutex = new mutex();

      //::thread::g_pthreadmap = new ::thread_map();

      // acme commented
//      create_factory < ::context >();


#if OBJ_TYP_CTR
      g_iObjTypCtrInit = 1;
#endif

      g_pcsFont = new critical_section();

      g_pmapFontFaceName = new string_to_string();

      init();

   }


   acme::~acme()
   {

      term();

      ::acme::del(g_pmapFontFaceName);

      ::acme::del(g_pcsFont);

#if OBJ_TYP_CTR
      g_iObjTypCtrInit = 0;
#endif

      //acme commented
      //::release(t_pthread);

      // if(g_pmapace)
      // {

      //    try
      //    {

      //       g_pmapace->remove_all();

      //    }
      //    catch(...)
      //    {

      //    }

      // }

      //try
      //{

      //   sync_lock sl(&::get_context_system()->g_mutexLibrary);

      //   g_pmapLibCall->remove_all();


      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   sync_lock sl(&::get_context_system()->g_mutexLibrary);

      //   &::get_context_system()->g_mapLibrary.remove_all();

      //}
      //catch (...)
      //{

      //}

      if(g_pmapRTL)
      {

         try
         {

            g_pmapRTL->remove_all();

         }
         catch(...)
         {

         }

      }

      if(g_pmapRTL)
      {

         try
         {

            g_pmapRTL->remove_all();

         }
         catch(...)
         {

         }

      }

      try
      {

         ::factory::factory_close();

      }
      catch (...)
      {

      }

      //::acme::del(::thread::g_pmutex);

      //::acme::del(::thread::g_pthreadmap);

      //acme commented
      //::user::term_windowing();

      g_bace = 0;

      //acme commented
      //::acme::del(g_pacestrpool);

      //acme commented
      //::channel::s_pmutexChannel.release();

      g_ptrace = g_psimpletrace;

      del(g_pmapRTL);

#if defined(LINUX) || defined(__APPLE__)

      del(g_pmutexTz);

#endif // defined(LINUX) || defined(__APPLE__)

      del(g_pmutexCred);

      del(g_pmutexMessageDispatch);

      del(g_pmutexUiDestroyed);

      //del(g_pmapace);

      if (g_paace != nullptr)
      {

         for (auto* po : *g_paace)
         {

            try
            {

               del(po);

            }
            catch (...)
            {

            }

         }

         del(g_paace);

      }

      try
      {

         ::factory::factory_term();

      }
      catch (...)
      {

      }

      //del(g_pmapLibCall);

      //del(g_pmapLibrary);

      //del(g_pmapNewaceLibrary);

      //del(&::get_context_system()->g_mutexLibrary);

      trace_category_static_term();

#if OBJ_TYP_CTR

      ::acme::del(g_pmapObjTypCtr);

#endif

#if MEMDLEAK

      memdleak_term();

#endif

      del(g_pmutexSystemHeap);

      //del(g_pmutexThreadOn);

      //del(g_pmapThreadOn);

      del(g_pmutexThreadWaitClose);

#ifdef __APPLE__

      del(g_pmutexCvt);

#endif

      //acme commented
//#ifdef BSD_STYLE_SOCKETS
//
//      del(::sockets::base_socket::s_pmutex);
//
//#endif

      ::acme::del(g_psimpletrace);

      ::acme::del(g_pcsTrace);

      trace_category_static_term();

#ifdef ANDROID

      del(g_pmutexOutputDebugStringA);

#endif

      term_id_pool();

      del(::id_space::s_pidspace);

#if !defined(__MCRTDBG) && !MEMDLEAK

      auto pheap = g_pheap;

      g_pheap = nullptr;

      del(pheap);

#endif

      del(g_pcsGlobal);

      del(g_pmutexChildren);

      del(g_pmutexGlobals);

#if MEMDLEAK

      ::set_thread(nullptr);

#ifdef __USE_BFD

      init_resolve_addr_file_func_line();

#endif

      memdleak_dump();

#endif

#ifndef WINDOWS

      ::acme::free(g_pszDemangle);

#endif

#ifndef WINDOWS

      ::acme::del(g_pcsDemangle);

#endif

#ifdef WINDOWS
      _free_locale(g_localeC);
#elif defined(ANDROID)
      //_freelocale(g_localeC);
#else
      freelocale(g_localeC);
#endif

   }


   void acme::this_ref()
   {

      m_bRef = true;
      //printf()

   }


   //::acme::system * ace_create_system(app_core * pappcore)
   //{

   //   auto psystem = new ::acme::system();

   //   psystem->initialize(nullptr);

   //   return psystem;

   //}



   ::estatus acme::init()
   {

      //::acme::static_start::init();

      if (!__node_ace_pre_init())
      {

         return ::error_failed;

      }

      ::multithreading::init_multithreading();

      if (!__node_ace_pos_init())
      {

         return ::error_failed;

      }

#ifdef WINDOWS

      set_extended_output_debug_string_a();

      set_extended_output_debug_string_w();

#endif

      //g_pfn_create_system = &ace_create_ace_system;

      return true;

   }


   ::estatus acme::term()
   {

      //::multithreading::wait_threads(1_min);

      if (g_axisontermthread)
      {

         g_axisontermthread();

      }

      on_term_thread();

      ::multithreading::term_multithreading();

      __node_ace_pre_term();

#ifdef WINDOWS

      set_simple_output_debug_string_a();

      set_simple_output_debug_string_w();

#endif

      processor_cache_oriented_destroy_all_memory_pools();

      __node_ace_pos_term();

      //::acme::static_start::term();

      //return true;

      return ::success;

   }


//} // namespace static_start


} // namespace acme


//static ::mutex * s_pmutexDraw2d = nullptr;
//
//CLASS_DECL_ACME ::mutex * draw2d_mutex()
//{
//
//   return s_pmutexDraw2d;
//
//}


//CLASS_DECL_ACME void init_draw2d_mutex()
//{
//
//   s_pmutexDraw2d = new ::mutex();
//
//}


//CLASS_DECL_ACME void terg_draw2d_mutex()
//{
//
//   ::acme::del(s_pmutexDraw2d);
//
//}



CLASS_DECL_ACME ::mutex * get_cred_mutex()
{

   return ::acme::g_pmutexCred;

}







//level * ace_level::s_plevel = nullptr;

//ace_level acelevelace(::ace_level::level_ace, &defer_ace_init);



CLASS_DECL_ACME COLORREF dk_red() // <3 tbs
{
   return ARGB(255, 200, 16, 46);
}


//thread_int_ptr < ::estatus    > t_estatus;

thread_local ::estatus t_estatus;


CLASS_DECL_ACME void set_last_status(const ::estatus & estatus)
{

   t_estatus = estatus;

}


CLASS_DECL_ACME ::estatus  get_last_status()
{

   return t_estatus;

}




//ace_level acelevelAxis(::ace_level::level_axis, &defer_axis_init);
//
//namespace acme
//{
//
//
//   namespace static_start
//   {
//
//
//      CLASS_DECL_ACME void init()
//      {
//
//         xxdebug_box("acme.dll axis_static_start (0)", "box", MB_OK);

//         sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

//#if defined(LINUX)
//
//         //         set_defer_process_x_message(&axis_defer_process_x_message);
//
//         //         set_TranslateMessage(&axis_TranslateMessage);
//         //
//         //         set_DispatchMessage(&axis_DispatchMessage);
//         //
//         //         oswindow_data::s_pdataptra = new oswindow_dataptra;
//         //
//         //         oswindow_data::s_pmutex = new ::mutex;
//         //
//         //         osdisplay_data::s_pdataptra = new osdisplay_dataptra;
//         //
//         //         osdisplay_data::s_pmutex = new ::mutex;
//
//#endif // defined(LINUX)
//
//
//
//      }
//
//
//








































//
//
//
//      CLASS_DECL_ACME void term()
//      {
//
//         //#if defined(LINUX)
//         //
//         //         delete osdisplay_data::s_pmutex;
//         //
//         //         osdisplay_data::s_pmutex = nullptr;
//         //
//         //         delete osdisplay_data::s_pdataptra;
//         //
//         //         osdisplay_data::s_pdataptra = nullptr;
//         //
//         //         delete oswindow_data::s_pmutex;
//         //
//         //         oswindow_data::s_pmutex = nullptr;
//         //
//         //         delete oswindow_data::s_pdataptra;
//         //
//         //         oswindow_data::s_pdataptra = nullptr;
//         //
//         //#endif // defined(LINUX)
//
//
//
//
//      }
//
//
//
//   } // namespace static_start
//
//
//} // namespace acme
//
//
//
//
//

#ifdef WINDOWS
_locale_t get_c_locale()
#else
locale_t get_c_locale()
#endif
{

   return ::acme::g_localeC;

}




// ace_level acelevelCore(::ace_level::level_core, &defer_ace_init);


//#ifdef ANDROID
//
//
//struct lconv* g_plconv = nullptr;
//
//
//#endif
//
//
//namespace acme
//{
//
//
//
//   namespace static_start
//   {
//
////
////      CLASS_DECL_ACME void init()
////      {
////
////         xxdebug_box("acme.dll base_static_start (0)", "box", MB_OK);
////
////         //#ifdef ANDROID
////         //
////         //
////         //         g_plconv = new lconv;
////         //
////         //         g_plconv->decimal_point = strdup(".");
////         //
////         //         //oswindow_data::s_pdataptra = new oswindow_dataptra;
////         //
////         //         //oswindow_data::s_pmutex = new ::mutex;
////         //
////         //#endif
////
////         //#if defined(APPLEOS)
////         //
////         //         g_poswindowdataptra = new oswindow_dataptra;
////         //
////         //         g_poswindowdataptra->defer_create_mutex();
////         //
////         //#endif // defined(APPLEOS)
////
////#ifdef LINUX
////
////
////         ::user::initialize_edesktop();
////
////
////#endif
////
////
////      }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//










//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//      CLASS_DECL_ACME void term()
//      {
//
//
//         //#if defined(APPLEOS)
//         //
//         //         delete g_poswindowdataptra;
//         //
//         //         g_poswindowdataptra = nullptr;
//         //
//         //#endif // defined(APPLEOS)
//
//
//
//
//
//
//      }
//
//
//
//   } // namespace static_start
//
//
//} // namespace acme
//
//
//
//
//



void ace_ref()
{

   ::acme::acme::g_ace.this_ref();

}



