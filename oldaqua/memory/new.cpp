//
//  new.cpp
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 26/07/20.
//

#include "framework.h"


#if !defined(NO_AURA_MEMORY_MANAGEMENT)


void MEMORY_DECL operator delete(void * p, size_t n) del_throw_spec
{

   ::operator delete(p);

}


#endif


