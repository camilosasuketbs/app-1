#pragma once

//
//class CLASS_DECL_APEX message_box
//{
//public:
//
//   __pointer(::user::primitive)     m_puserprimitive;
//   string                           m_strMessage;
//   string                           m_strTitle;
//   ::emessagebox                    m_emessagebox;
//   ::duration                       m_durationTimeout;
//   callback                         m_callback;
//
//
//   message_box();
//   message_box(const payload & payload);
//   virtual ~message_box();
//
//
//   ::estatus show(::object* pobject);
//
//
//};
//
//
//
//
//inline payload operator + (payload payload, const ::enum_message_box& emessagebox)
//{
//
//   if (payload.get_type() != type_propset)
//   {
//
//      payload["message"] = payload.get_string();
//
//   }
//
//   payload["flags"] = (::i64) emessagebox;
//
//   return payload;
//
//}
//
//
//template < typename TYPE_CHAR >
//inline payload operator +(const string_base < TYPE_CHAR >& str, const enum_message_box& e)
//{
//
//   return payload(str) + e;
//
//}
//
//
//
//
//inline payload operator + (const char* psz, const ::enum_message_box& emessagebox)
//{
//
//   return payload(psz) + emessagebox;
//
//}
//
//
//
//
//CLASS_DECL_APEX ::estatus os_message_box(oswindow oswindow, const char* pszText, const char* pszTitle = nullptr, ::emessagebox emessagebox = e_message_box_ok, ::callback callback = ::callback());
//CLASS_DECL_APEX ::estatus message_box(::user::primitive * puiOwner, const char* pszText, const char* pszTitle = nullptr, ::emessagebox emessagebox = e_message_box_ok, ::callback callback = ::callback());
//
//
//inline ::estatus os_message_box(const char* pszText, const char* pszTitle = nullptr, ::emessagebox emessagebox = e_message_box_ok, ::callback callback = ::callback())
//{
//
//   return os_message_box(nullptr, pszText, pszTitle, emessagebox, callback);
//
//}
//
//
//inline ::estatus message_box(const char* pszText, const char* pszTitle = nullptr, ::emessagebox emessagebox = e_message_box_ok, ::callback callback = ::callback())
//{
//
//   return message_box(nullptr, pszText, pszTitle, emessagebox, callback);
//
//}
//
//
//
