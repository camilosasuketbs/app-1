#include "framework.h" 
#include "aura/const/id.h" 


CLASS_DECL_AQUA void thread_touch_sockets()
{

   thread_value(id_thread_using_sockets) = true;

}


CLASS_DECL_AQUA int thread_has_sockets()
{

   return (int) (iptr)thread_value(id_thread_using_sockets);

}



