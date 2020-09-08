#pragma once


#define MSG_TYPE_LINK(emessagetype, pchannel, preceiver, phandler) \
   pchannel->add_route(preceiver, phandler, ::message::id((::message::e_type)(emessagetype)))

#define IGUI_MSG_LINK(int_message, pchannel, preceiver, phandler) \
   pchannel->add_route(preceiver, phandler, ::message::id(::id((index) (int_message)), ::message::type_message))

#define ON_TYPED_MESSAGE(id, MESSAGE, name) \
   this->get_typed_route < typename ::remove_reference < decltype(*this) >::TYPE, MESSAGE >(id, this) = [this](MESSAGE * p ## name)

#define ON_MESSAGE(id) \
   ON_TYPED_MESSAGE(id, ::message::message, message)

#define ON_WM_SHOWWINDOW \
   ON_TYPED_MESSAGE(WM_SHOWWINDOW, ::message::show_window, showwindow)

#define ON_WM_LBUTTONDOWN \
   ON_TYPED_MESSAGE(WM_LBUTTONDOWN, ::message::mouse, mouse)

#define ON_WM_LBUTTONUP \
   ON_TYPED_MESSAGE(WM_LBUTTONUP, ::message::mouse, mouse)

#define ON_WM_MBUTTONDOWN \
   ON_TYPED_MESSAGE(WM_MBUTTONDOWN, ::message::mouse, mouse)

#define ON_WM_MBUTTONUP \
   ON_TYPED_MESSAGE(WM_MBUTTONUP, ::message::mouse, mouse)

#define ON_WM_RBUTTONDOWN \
   ON_TYPED_MESSAGE(WM_RBUTTONDOWN, ::message::mouse, mouse)

#define ON_WM_RBUTTONUP \
   ON_TYPED_MESSAGE(WM_RBUTTONUP, ::message::mouse, mouse)

#define ON_WM_MOUSEMOVE \
   ON_TYPED_MESSAGE(WM_MOUSEMOVE, ::message::mouse, mouse)

/*

#define USER_MESSAGE_LINK(emessageenum, pchannel, preceiver, phandler) \
   IGUI_MSG_LINK(::message::emessageenum, pchannel, preceiver, phandler)

*/

#define SCAST_MSG(tcast) \
   ::message::tcast * p##tcast = dynamic_cast < ::message::tcast * > (pmessage);



