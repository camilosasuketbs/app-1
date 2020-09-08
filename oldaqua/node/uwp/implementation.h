#pragma once

//#define __defer_register_class(fClass) __end_defer_register_class(fClass)

//CLASS_DECL_AQUA bool __end_defer_register_class(LONG fToRegister, const char ** ppszClass);


// Temporary ::map management (locks temp ::map on current thread)
//CLASS_DECL_AQUA void ::ca2::LockTempMaps(::object * pobject);
//CLASS_DECL_AQUA bool ::ca2::UnlockTempMaps(::object * pobject, bool bDeleteTemps = TRUE);



// from wincore.cpp
extern CLASS_DECL_AQUA const char gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_AQUA const char gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_AQUA const char gen_WndMDIFrame[];
extern CLASS_DECL_AQUA const char gen_WndFrameOrView[];
extern CLASS_DECL_AQUA const char gen_WndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_AQUA void __cancel_modes(oswindow hWndRcvr);
CLASS_DECL_AQUA bool __help_enabled();  // determine if ID_HELP handler exists
CLASS_DECL_AQUA bool __custom_log_font(UINT nIDS, LOGFONT* pLogFont);
CLASS_DECL_AQUA bool __get_prop_sheet_font(string & strFace, WORD& wSize, bool bWizard);

CLASS_DECL_AQUA bool __is_combo_box_control(oswindow hWnd, UINT nStyle);
CLASS_DECL_AQUA bool __check_center_dialog(const char * lpszResource);
CLASS_DECL_AQUA bool __compare_class_name(oswindow hWnd, const char * lpszClassName);
CLASS_DECL_AQUA oswindow __child_window_from_point(oswindow, POINT);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    MAKELONG(0, 4)
#define VERSION_IE3             MAKELONG(70, 4)
#define VERSION_IE4             MAKELONG(71, 4)
#define VERSION_IE401   MAKELONG(72, 4)
#define VERSION_6      MAKELONG(0, 6)
extern int gen_ComCtlVersion;
DWORD __get_common_controls_version();
