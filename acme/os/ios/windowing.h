//
//  ios_windowing.hpp
//  ios_acme
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


#ifndef __OBJC__

struct UIWindow;

#endif

UIWindow * __uiwindow(oswindow oswindow);


int GetMainScreenRect(LPRECT lprect);

int GetScreenRect(LPRECT lprect, int iMonitor);

int GetScreenCount();

int GetWkspaceRect(LPRECT lprect, int iMonitor);

int GetWkspaceCount();


//
//  ios_window.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//


oswindow get_capture();
oswindow set_capture(oswindow window);
WINBOOL release_capture();
oswindow set_focus(oswindow window);
oswindow get_focus();
oswindow get_active_window();
oswindow set_active_window(oswindow window);


//void GetMainScreenRect(LPRECT lprect);

WINBOOL SetForegroundWindow(oswindow window);
WINBOOL BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);






#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA


void deactivate_window(oswindow window);


oswindow get_window(oswindow window, int iParentHood);



