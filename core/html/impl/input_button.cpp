#include "framework.h"
#include "_impl.h"


namespace html
{


   namespace impl
   {


      input_button::input_button()
      {

         m_iFont = -1;

      }


      input_button::~input_button()
      {

         try
         {

            if(m_pbutton->is_window())
            {

               m_pbutton->DestroyWindow();

            }

         }
         catch(...)
         {

         }

         try
         {

            //m_pbutton.release();

         }
         catch(...)
         {

         }

      }


      void input_button::implement_phase1(html_data * pdata, ::html::elemental * pelemental)
      {

         m_bHasChar = true;

         __defer_compose_new(m_pbutton);

         m_pbutton->m_id = pelemental->m_pbase->get_tag()->get_attr_value("id");

         if (m_pbutton->m_id.is_empty())
         {

            m_pbutton->m_id = pelemental->m_pbase->get_tag()->get_attr_value("name");

         }

         if(!m_pbutton->is_window())
         {

            m_pbutton->create_window(pdata->m_pcoredata->m_puserinteraction, m_pbutton->m_id);

            pdata->on_create_interaction(m_pbutton);

         }

         elemental::implement_phase1(pdata, pelemental);

         auto value = pelemental->m_pbase->get_tag()->get_attr_value("value");

         m_pbutton->set_window_text(value);

         m_cxMax = 200;

         m_cxMin = 200;

      }


      bool input_button::layout_phase1(html_data * pdata)
      {

         m_pbutton->resize_to_fit(pdata->m_pcoredata->m_pgraphics);

         auto size = m_pbutton->layout().sketch().size();

         m_box.set_size(size);

         return true;

      }


      void input_button::layout_phase3(html_data * pdata)
      {

         elemental::layout_phase3(pdata);

         m_pbutton->place(m_box);

         m_pbutton->display(::display_normal);

      }


      void input_button::_001OnDraw(html_data * pdata)
      {

         ::draw2d::graphics_pointer & pgraphics = pdata->m_pcoredata->m_pgraphics;

         //::rect rectWindow;
         //m_pbutton->get_window_rect(rectWindow);
         //m_pbutton->GetWindow()->_001ScreenToClient(rectWindow);
         //auto pointPreviousViewportOrg = pgraphics->GetViewportOrg();
         //pgraphics->OffsetViewportOrg((i32) m_box.left, (i32) m_box.top);
         m_pbutton->_000CallOnDraw1(pgraphics);
         //pgraphics->SetViewportOrg(pointPreviousViewportOrg);

      }


      void input_button::on_change_layout(html_data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

         m_pbutton->place(m_box);

      }


   } // namespace impl


} // namespace html





