﻿#pragma once


#undef System
#undef Platform
#undef Application
#undef Session


CLASS_DECL_AQUA bool __initialize(bool bDLL, DWORD dwVersion);

CLASS_DECL_AQUA uptr keycode_to_char(uptr n);

CLASS_DECL_AQUA uptr virtualkey_to_char(::Windows::System::VirtualKey e);

CLASS_DECL_AQUA::user::e_key virtualkey_to_userkey(::Windows::System::VirtualKey e, bool& bSpecialKey);

CLASS_DECL_AQUA uptr virtualkey_to_code(::Windows::System::VirtualKey e);



