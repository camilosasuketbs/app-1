#pragma once


namespace message
{


   class CLASS_DECL_APEX id :
      public ::id
   {
      public:


         ::message::e_type         m_emessagetype;


         id(::message::e_type etype = ::message::type_null)
         {

            m_emessagetype = etype;

         }


         id(::i64 i)
         {

            m_emessagetype = type_message;

            ::id::operator = ((::i32) i);

         }



         id(const ::id id)
         {

            if (id.is_integer())
            {

               m_emessagetype = type_message;

            }
            else
            {

               m_emessagetype = type_command;

            }

            ::id::operator = (id);

         }

         id(const id & id)
         {

            m_emessagetype = id.m_emessagetype;
            ::id::operator = (id);

         }

         id(::id id, ::message::e_type etype)
         {

            m_emessagetype = etype;
            ::id::operator = (id);

         }

         
         bool operator == (::i64 i) const
         {

            return is_integer() && m_i == i;

         }


         bool operator == (::i32 i) const
         {

            return is_integer() && m_i == i;

         }


         bool operator == (const string & str) const
         {

            return is_text() && str.compare(m_psz) == 0;

         }


         bool operator == (const char * psz) const
         {

            return is_text() && !strcmp(m_psz, psz);

         }

         bool operator == (const id & id) const
         {

            return m_emessagetype == id.m_emessagetype && ::id::operator==(id);

         }

         id & operator = (const id & id)
         {

            if (this != &id)
            {

               m_emessagetype = id.m_emessagetype;

               ::id::operator = (id);

            }

            return *this;

         }


         id & operator = (::message::e_type etype)
         {

            m_emessagetype = etype;

            return *this;

         }

   };



} // namespace




template <  >
inline uptr uptr_hash < const ::message::id & >(const ::message::id & key)
{

   return (UINT) (((i64)key.m_emessagetype) ^ uptr_hash < const ::id & >((const ::id &) key));

}
