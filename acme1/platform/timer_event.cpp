#include "framework.h"


timer_event::timer_event(::acme::timer_array * ptimera, int iTimer) :
   ::generic(ptimera),
   timer(ptimera, iTimer)
{

}


timer_event::~timer_event()
{


}

bool timer_event::wait(int millis)
{

   start(millis,false);

   m_ev.wait();

   return true;
}


bool timer_event::on_timer()
{

   m_ev.SetEvent();

   return true;

}



