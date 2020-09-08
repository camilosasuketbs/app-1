#include "framework.h"



namespace message
{


   //base::base(::object * pobjectContext) :
   //   ::message::message(psignal)
   //{

   //   m_lresult = 0;
   //   m_bDestroyed = false;
   //   m_puserinteraction = nullptr;
   //   m_plresult = &m_lresult;
   //   m_bDoSystemDefault = true;

   //}


   base::base()
   {

      m_uiMessageFlags     = 0;
      m_puserinteraction       = nullptr;
      m_lresult            = 0;
      m_bDestroyed         = false;
      m_bDoSystemDefault   = true;

   }


   base::base(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam)
   {

      m_uiMessageFlags     = 0;
      m_puserinteraction               = nullptr;
      m_lresult            = 0;
      m_bDestroyed         = false;
      m_bDoSystemDefault   = true;
      set(pwnd,uiMessage,wparam,lparam);


      //Application.tellme_destroyed(pwnd, &m_bDestroyed);

   }


   base::base(const base & base)
   {

      m_uiMessageFlags     = base.m_uiMessageFlags;
      m_puserinteraction               = base.m_puserinteraction;
      m_id                 = base.m_id;
      m_wparam             = base.m_wparam;
      m_lparam             = base.m_lparam;
      m_bConditional       = base.m_bConditional;
      m_bReflect           = base.m_bReflect;
      m_bDoSystemDefault   = base.m_bDoSystemDefault;
      m_bDestroyed         = false;

      //Application.tellme_destroyed(m_puserinteraction, &m_bDestroyed);

   }

   base::~base()
   {

      //if(m_puserinteraction != nullptr)
      //{

      //   sync_lock sl(get_ui_destroyed_mutex());

      //   if(m_bDestroyed)
      //   {

      //      debug_print("Window Already Destroyed");

      //   }
      //   else
      //   {

      //      Application.tellme_destroyed(m_puserinteraction, &m_bDestroyed, false);

      //   }

      //}

   }


   void base::set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam)
   {

      ::message::message::set(pwnd, uiMessage, wparam, lparam);

      m_puserinteraction            = pwnd;

   }


   //base & base::operator = (const base & base)
   //{

   //   if (this != &base)
   //   {

   //      copy_this(base);

   //   }

   //   return *this;

   //}


   //void base::copy_this(const base & base)
   //{

   //   m_puserinteraction = base.m_puserinteraction;
   //   m_bConditional = base.m_bConditional;
   //   m_bReflect = base.m_bReflect;
   //   m_bDestroyed = base.m_bDestroyed;
   //   m_bDoSystemDefault = base.m_bDoSystemDefault;
   //   m_plresult = base.m_plresult;
   //   m_lresult = base.m_lresult;

   //}


   void timer::set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,::lparam lparam)
   {

      base::set(pwnd,uiMessage,wparam,lparam);

      m_nIDEvent = static_cast<UINT>(wparam);

   }



} // namespace message








#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

#define IMPLEMENT_SIGNAL_OBJECT_FIXED_ALLOC(class_name) IMPLEMENT_FIXED_ALLOC(class_name, ROUND4(sizeof(class_name) * 32))

