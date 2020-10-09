#pragma once


#if defined(HAVE_OPENSSL)

#include <openssl/rsa.h>
#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/hmac.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/whrlpool.h>




#include <openssl/ssl.h>


#endif








namespace crypto
{


   CLASS_DECL_APEX void md5(void* ptarget, const void* psource, ::memsize size);
   CLASS_DECL_APEX void sha1(void* ptarget, const void* psource, ::memsize size);
   CLASS_DECL_APEX void sha256(void* ptarget, const void* psource, ::memsize size);
   CLASS_DECL_APEX void nessie(void* ptarget, const void* psource, ::memsize size);


} //   namespace crypto


#include "hasher_algorithm.h"
#include "hasher.h"
#include "rsa.h"








namespace crypto
{


   CLASS_DECL_APEX void md5(void* ptarget, const void* psource, ::memsize size);
   CLASS_DECL_APEX void sha1(void* ptarget, const void* psource, ::memsize size);
   CLASS_DECL_APEX void sha256(void* ptarget, const void* psource, ::memsize size);
   CLASS_DECL_APEX void nessie(void* ptarget, const void* psource, ::memsize size);


} //   namespace crypto


#include "hasher_algorithm.h"
#include "hasher.h"
#include "rsa.h"


