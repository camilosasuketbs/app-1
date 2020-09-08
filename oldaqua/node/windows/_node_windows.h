﻿#pragma once




//#include "exception.h"

string get_error_message(DWORD dwError);


CLASS_DECL_AQUA bool __initialize();


//#include "system_dir.h"
//#include "system_file.h"
//
//#include "folder_watch.h"
//#include "factory_exchange.h"
//#include "uac_tools.h"
//#include "thread.h"
//#include "file.h"
//#include "crypto.h"
//#include "ip_enum.h"


#define NODE_THREAD(pthread) (dynamic_cast < ::windows::thread * > (dynamic_cast < thread * >(pthread)))


//
//#include "command.h"



void CLASS_DECL_AQUA __cdecl _ca2_purecall();
void CLASS_DECL_AQUA __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);
bool CLASS_DECL_AQUA __windows_init();
i32 CLASS_DECL_AQUA __windows_main(::aqua::system * psystem, ::create * pmaininitdata);






//#include "file_find.h"
//#include "file.h"
//#include "shell.h"
//#include "stdio_file.h"
//#include "registry.h"
//#include "os.h"


// Sanity checks for ATOMs
CLASS_DECL_AQUA bool __is_valid_atom(ATOM nAtom);
//CLASS_DECL_AQUA bool __is_valid_atom(const char * psz);
CLASS_DECL_AQUA bool __is_valid_atom(const wchar_t * psz);


/////////////////////////////////////////////////////////////////////////////
// locale-invariant comparison helpers till CRT gets that support
inline i32 __invariant_stricmp(const char *pszLeft,const char *pszRight)
{
#ifdef WINDOWS_DESKTOP
   return ::CompareStringA(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                           NORM_IGNORECASE,
                           pszLeft,
                           -1,
                           pszRight,
                           -1) - CSTR_EQUAL;
#else
   return ansi_compare_ci(pszLeft,pszRight);
#endif
}

inline i32 __invariant_stricmp(const unichar *pwszLeft,const unichar *pwszRight)
{
#ifdef WINDOWS_DESKTOP
   return ::CompareStringW(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                           NORM_IGNORECASE,
                           pwszLeft,
                           -1,
                           pwszRight,
                           -1) - CSTR_EQUAL;
#else
   return wide_compare_case_insensitive(pwszLeft,pwszRight);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Portability abstractions

#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((UINT)(WORD)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((UINT)(WORD)oswindow->GetDlgCtrlId())


//#include "pipe.h"
//#include "process.h"










namespace windows
{


   class thread;

   class windows
   {
      i32 function();
   };

   CLASS_DECL_AQUA HINSTANCE   load_library(const char * psz);

   CLASS_DECL_AQUA bool        shell_get_special_folder_path(oswindow oswindow,::file::path &str,i32 csidl,bool fCreate);
   CLASS_DECL_AQUA ::file::path  shell_get_special_folder_path(i32 csidl, bool fCreate = true, oswindow oswindow = nullptr);
   CLASS_DECL_AQUA DWORD       get_file_attributes(const char * pFileName);

   CLASS_DECL_AQUA DWORD       get_current_directory(string & str);
   CLASS_DECL_AQUA DWORD       get_temp_path(string & str);
   CLASS_DECL_AQUA LONG        reg_query_value(HKEY hkey,const char * pszSubKey,string & str);

   CLASS_DECL_AQUA HICON       extract_icon(HINSTANCE hInst,const char * pszExeFileName,UINT nIconIndex);

   CLASS_DECL_AQUA bool        delete_file(const char * pFileName);

   CLASS_DECL_AQUA i32     get_menu_string(HMENU hMenu,UINT uIDItem,string & str,UINT flags);
   CLASS_DECL_AQUA void        time_to_filetime(::object * pobject,const ::datetime::time& time,LPFILETIME pFileTime);


} // namespace windows





CLASS_DECL_AQUA LONG delete_registry_tree_helper(HKEY hParentKey,const string & strKeyName);


CLASS_DECL_AQUA __pointer(::aqua::application) __get_app();
CLASS_DECL_AQUA HINSTANCE __get_resource_handle();
CLASS_DECL_AQUA void __set_resource_handle(HINSTANCE hInstResource);

CLASS_DECL_AQUA HINSTANCE __get_resource_handle();
CLASS_DECL_AQUA HINSTANCE __find_string_resource_handle(UINT nID);



CLASS_DECL_AQUA i32 app_main(::aqua::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, ::edisplay edisplay);




//#include "tts_speaker.h"




