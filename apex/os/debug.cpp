#include "framework.h"


CLASS_DECL_APEX void __simple_tracev(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
CLASS_DECL_APEX void __simple_tracea(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char *pszFileName, i32 iLine, const char * psz);
CLASS_DECL_APEX void __simple_tracev(element* pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
CLASS_DECL_APEX void __simple_tracea(element* pobject, e_trace_level elevel, const char * pszFunction, const char *pszFileName, i32 iLine, const char * psz);




//char os_trace_level_char(e_trace_level elevel)
//{
//
//   switch (elevel)
//   {
//   case level_info:
//      return 'I';
//   case level_warning:
//      return 'W';
//   case level_error:
//      return 'E';
//   default:
//      return 'D';
//   }
//
//}



//CLASS_DECL_APEX void __tracea(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
//{
//
//   if (::is_null(::get_context_system()))
//   {
//
//      __simple_tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);
//
//      return;
//
//   }
//
//   ::get_context_system()->__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);
//
//}
//
//CLASS_DECL_APEX void __tracef(::element* pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
//{
//
//   va_list list;
//
//   va_start(list, pszFormat);
//
//   try
//   {
//
//      __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, list);
//
//   }
//   catch (...)
//   {
//
//   }
//
//   va_end(list);
//
//}
//
//
//CLASS_DECL_APEX void __tracev(::element* pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
//{
//
//   if (::is_null(::get_context_system()))
//   {
//
//      __simple_tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//      return;
//
//   }
//
//   ::get_context_system()->__tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//}
//
//
//
//
//
//
