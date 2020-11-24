#include "framework.h"


namespace promise
{


   context::context()
   {

      m_iUpdateSerial = -1;
      m_bFork = false;

   }


   context::~context()
   {

   }


   ::estatus context::start_task()
   {

      return ::success_none;

   }


   void context::set_up_to_date(::promise::handler *phandler)
   {

      m_iUpdateSerial = phandler->m_iUpdateSerial;

   }


} // namespace promise



