#ifndef __GNUC__
#pragma once
#endif


#ifdef __cplusplus

#ifdef __OBJC__

#include "acme/include/objcpp.h"

#else

#include "acme/_.h"
#include "acme/platform/_platform.h"
#if !defined(BROAD_PRECOMPILED_HEADER)
#define BROAD_PRECOMPILED_HEADER 1
#endif
//#include "acme/user/_user.h"
#if BROAD_PRECOMPILED_HEADER
//#include "acme/user/simple/_simple.h"
//#include "acme/user/rich_text/_rich_text.h"
//#include "acme/filesystem/filemanager/_filemanager.h"
//#include "acme/filesystem/filehandler/_filehandler.h"
//#include "acme/user/userex/_userex.h"
//#include "acme/user/experience/_experience.h"
//#include "acme/user/databaseuser/_databaseuser.h"
#endif
//#include "acme/crypto/crypto_openssl.h"
#include "acme/_defer.h"



#endif

#else

#ifdef __OBJC__

#include "acme/include/objc.h"

#else

#include "acme/_.h"

#endif

#endif



