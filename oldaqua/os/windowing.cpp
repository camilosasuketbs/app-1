#include "framework.h"
#include "_os.h"
#include <stdio.h>

#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)



static oswindow g_oswindowSplash = nullptr;


void set_splash(oswindow oswindow)
{

   g_oswindowSplash = oswindow;

}


oswindow get_splash()
{

   return g_oswindowSplash;

}



bool g_bWindowingOutputDebugString = false;


void windowing_output_debug_string(const char * pszDebugString)
{

   if(g_bWindowingOutputDebugString)
   {

      output_debug_string(pszDebugString);

      fflush(stdout);

   }

}



//CLASS_DECL_AQUA void update_application_session_cursor(void * pvoidApp, const point & pointCursor)
//{
//
//   ::aqua::application * papp = (::aqua::application *) pvoidApp;
//
//   if(::is_set(papp) && ::is_set(papp->get_context_session()))
//   {
//
//      Sess(papp).m_pointCursor = pointCursor;
//
//   }
//
//}



::user::interaction* oswindow_interaction(oswindow oswindow)
{

   auto pimpl = oswindow_interaction_impl(oswindow);

   if (::is_null(pimpl))
   {

      return nullptr;

   }

   return pimpl->m_puserinteraction;

}





::user::interaction_impl * oswindow_interaction_impl(oswindow oswindow)
{

   if (::is_null(oswindow))
   {

      return nullptr;

   }

#ifndef WINDOWS_DESKTOP

   if (::is_set(oswindow->m_pimpl))
   {

      return oswindow->m_pimpl;

   }

#endif

   auto psystem = ::get_context_system();

   sync_lock slSystem(psystem->mutex());

   auto pmap = psystem->m_pwindowmap;

   if (!pmap)
   {

      return nullptr;

   }

   //sync_lock slMap(pmap->mutex());

   ::user::primitive * pbase;

   if (!pmap->m_map.lookup(oswindow, pbase))
   {

      auto pimpl = thread_value("wnd_init").cast < ::user::interaction_impl >();

      if (::is_set(pimpl))
      {

         thread_value("wnd_init") = nullptr;

         pimpl->attach(oswindow);

         return oswindow_interaction_impl(oswindow);

      }

      return nullptr;

   }

   return dynamic_cast <::user::interaction_impl *>(pbase);

}



CLASS_DECL_AQUA string message_box_result_to_string(int iResult)
{

   string strResult;

   if (iResult == IDNO)
   {

      strResult = "no";

   }
   else if (iResult == IDYES)
   {

      strResult = "yes";

   }
   else if (iResult == IDCANCEL)
   {

      strResult = "cancel";

   }
   else if (iResult == IDOK)
   {

      strResult = "ok";

   }
   else if (iResult == IDTRYAGAIN)
   {

      strResult = "tryagain";

   }
   else if (iResult == IDABORT)
   {

      strResult = "abort";

   }
   else if (iResult == IDRETRY)
   {

      strResult = "retry";

   }
   else if (iResult == IDCONTINUE)
   {

      strResult = "continue";

   }

   else if (iResult == IDIGNORE)
   {

      strResult = "retry";

   }

   return strResult;
}


CLASS_DECL_AQUA color get_simple_ui_color(::user::e_element eelement, ::user::estate estate)
{

   ::color color;

   if(eelement == ::user::element_background)
   {

      if (::user::is_app_dark_mode())
      {

         color = ARGB(255, 0x50, 0x50, 0x58);

      }
      else
      {

         color = ARGB(255, 0xcd, 0xcd, 0xc8);

      }

   }
   else
   {

      if (::user::is_app_dark_mode())
      {

         color = ARGB(255, 255, 255, 255);

      }
      else
      {

         color = ARGB(255, 49, 50, 42);

      }

   }

   return color;

}



