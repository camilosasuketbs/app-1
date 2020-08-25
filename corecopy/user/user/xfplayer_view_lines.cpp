#include "framework.h"


xfplayer_view_linea::xfplayer_view_linea()
{

   defer_create_mutex();
   m_iFirstVisible = -1;
   m_iLastVisible = -1;
   m_pinteraction = nullptr;

}


xfplayer_view_linea::~xfplayer_view_linea()
{

}



void xfplayer_view_linea::OnChildSetVisible(xfplayer_view_line * pline, bool bVisible)
{
   sync_lock sl(mutex());
   index iLineIndex = FindLine(pline);
   index iIndex;

   if (bVisible)
   {
      if (iLineIndex < m_iFirstVisible)
         m_iFirstVisible = iLineIndex;
      else if (iLineIndex > m_iLastVisible)
         m_iLastVisible = iLineIndex;
   }
   else
   {
      iIndex = iLineIndex;
      if (iIndex >= m_iFirstVisible)
      {
         while (!this->line_at(iIndex)->IsVisible())
         {
            iIndex++;
            if (iIndex >= this->line_count())
               break;
         }
      }
      m_iFirstVisible = iIndex;
      iIndex = iLineIndex;
      if (iIndex <= m_iLastVisible)
      {
         while (!this->line_at(iIndex)->IsVisible())
         {
            iIndex--;
            if (iIndex < 0)
               break;
         }
      }
      m_iLastVisible = iIndex;
   }

}

index xfplayer_view_linea::GetFirstVisibleLineIndex()
{
   return m_iFirstVisible;
}

index xfplayer_view_linea::GetLastVisibleLineIndex()
{
   return m_iLastVisible;
}

void xfplayer_view_linea::Prepare()
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->m_pContainer = this;
      this->line_at(i)->m_iIndex = i;
   }
}

void xfplayer_view_linea::Prepare(xfplayer_view_line *pViewLine)

{
   sync_lock sl(mutex());
   pViewLine->m_pContainer = this;

}

void xfplayer_view_linea::set_user_interaction(__pointer(::user::interaction) pinteraction)
{
   
   m_pinteraction = pinteraction;

}


void xfplayer_view_linea::SetEffect(i32 iEffect)
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->SetTextEffect(iEffect);
   }
}

void xfplayer_view_linea::SetRenderWindow(::user::interaction_impl * pwindow)
{
   UNREFERENCED_PARAMETER(pwindow);
}

index xfplayer_view_linea::FindLine(xfplayer_view_line * pline)
{
   sync_lock sl(mutex());
   for (i32 iLine = 0; iLine < this->line_count(); iLine++)
   {
      if (line_at(iLine) == pline)
         return iLine;
   }
   return -1;
}

::user::e_line_hit xfplayer_view_linea::hit_test(const point &pointCursor, index &iLine, strsize &iChar)
{
   sync_lock sl(mutex());
   for (index i = 0; i < this->line_count(); i++)
   {
      ::user::e_line_hit etest = this->line_at(i)->hit_test(pointCursor, iChar);
      if (etest != ::user::line_hit_none)
      {
         iLine = i;
         return  etest;
      }
   }
   return ::user::line_hit_none;

}

void xfplayer_view_linea::install_message_routing(::channel * pchannel)
{
   IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &xfplayer_view_linea::OnMouseMove);
   IGUI_MSG_LINK(WM_SETCURSOR, pchannel, this, &xfplayer_view_linea::OnSetCursor);
   //IGUI_MSG_LINK(WM_TIMER,        pchannel, this, &xfplayer_view_linea::OnTimer);
   IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &xfplayer_view_linea::OnLButtonDown);
   IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &xfplayer_view_linea::OnLButtonUp);
}

void xfplayer_view_linea::OnMouseMove(::message::message * pmessage)
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->m_pContainer = this;
      this->line_at(i)->m_iIndex = i;
      this->line_at(i)->OnMouseMove(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_view_linea::OnLButtonDown(::message::message * pmessage)
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->m_pContainer = this;
      this->line_at(i)->m_iIndex = i;
      this->line_at(i)->OnLButtonDown(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_view_linea::OnLButtonUp(::message::message * pmessage)
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->OnLButtonUp(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_view_linea::_001OnTimer(::timer * ptimer)
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->_001OnTimer(ptimer);
      if (!ptimer->thread_get_run())
         return;
   }
}

void xfplayer_view_linea::OnSetCursor(::message::message * pmessage)
{
   sync_lock sl(mutex());
   for (i32 i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->OnSetCursor(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_view_linea::set_blend(double dBlend)
{
   sync_lock sl(mutex());
   for (i32 iLine = 0; iLine < this->line_count(); iLine++)
   {
      line_at(iLine)->set_blend(dBlend);
   }
}


XfplayerViewLineSelection & xfplayer_view_linea::GetSelection()
{
   return m_selection;
}


void xfplayer_view_linea::get_sel_text(string & strSelText, const char * pszLineSeparator)
{
   sync_lock sl(mutex());
   index iLineStart;
   index iCharStart;
   index iLineEnd;
   index iCharEnd;

   m_selection.GetNormalSelection(iLineStart, iCharStart, iLineEnd, iCharEnd);

   if (iLineEnd >= iLineStart)
   {

      if (iLineStart < 0)
         return;

      if (iLineEnd < 0)
         return;

      if (iLineEnd == iLineStart)
      {

         strSelText = line_at(iLineStart)->m_str.Mid(iCharStart, iCharEnd - iCharStart + 1);

      }
      else
      {

         strSelText = line_at(iLineStart)->m_str.Mid(iCharStart);

         for (index iLine = iLineStart + 1; iLine < iLineEnd; iLine++)
         {

            strSelText += pszLineSeparator;

            strSelText += line_at(iLine)->m_str;

         }

         if (iLineEnd > iLineStart)
         {

            strSelText += pszLineSeparator;

            strSelText += line_at(iLineEnd)->m_str.Mid(0, iCharEnd + 1);

         }
      }

   }

}

string xfplayer_view_linea::get_sel_text(const char * pszLineSeparator)
{

   string strSelText;

   get_sel_text(strSelText, pszLineSeparator);

   return strSelText;

}


void xfplayer_view_linea::get_text(string & strText, const char * pszLineSeparator)
{
   sync_lock sl(mutex());
   if (line_count() > 0)
   {

      strText = line_at(0)->m_str;

   }

   for (i32 iLine = 1; iLine < line_count(); iLine++)
   {

      strText += pszLineSeparator;

      strText += line_at(iLine)->m_str;

   }

}

string xfplayer_view_linea::get_text(const char * pszLineSeparator)
{

   string strText;

   get_text(strText, pszLineSeparator);

   return strText;

}
