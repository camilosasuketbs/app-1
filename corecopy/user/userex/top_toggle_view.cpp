#include "framework.h"
#include "core/user/userex/_userex.h"


namespace userex
{


   top_toggle_view::top_toggle_view()
   {

      m_ptopview = nullptr;

   }


   top_toggle_view::~top_toggle_view()
   {


   }


   void top_toggle_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void top_toggle_view::update(::update * pupdate)
   {

      ::user::impact::update(pupdate);

   }


   bool top_toggle_view::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable();

   }


} // namespace userex



