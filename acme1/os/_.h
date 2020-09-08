//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once

CLASS_DECL_ACME string get_command_line_dup();

#if defined(MACOS)

#include "acme/os/ansios/_.h"
#include "acme/os/apple/_.h"
#include "acme/os/macos/_.h"

#elif defined(APPLE_IOS)

#include "acme/os/ansios/_.h"
#include "acme/os/apple/_.h"
#include "acme/os/ios/_.h"

#elif defined(LINUX)

#include "acme/os/cairo/_.h"
#include "acme/os/ansios/_.h"
#include "acme/os/linux/_.h"

#elif defined(_UWP)

#include "acme/os/ansios/_.h"
#include "acme/os/windows_common/_.h"
#include "acme/os/uwp/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/os/ansios/_.h"
#include "acme/os/windows_common/_.h"
#include "acme/os/windows/_.h"

#elif defined(ANDROID)

#include "acme/os/ansios/_.h"
#include "acme/os/android/_.h"

#elif defined(SOLARIS)

#include "acme/os/ansios/_.h"
#include "acme/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif


//void adapt_font_name(string & str);


namespace str
{

   string CLASS_DECL_ACME get_window_text_timeout(oswindow oswindow, tick tickTimeout = 1000);

} // namespace str


CLASS_DECL_ACME void defer_dock_application(int_bool bDock);


CLASS_DECL_ACME string get_current_login_name();


#if defined(WINDOWS)


CLASS_DECL_ACME _locale_t get_c_locale();


#else


CLASS_DECL_ACME locale_t get_c_locale();

#endif



#include "time.h"


