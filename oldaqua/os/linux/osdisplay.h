


class CLASS_DECL_AQUA osdisplay_data
{
public:


   critical_section *      m_pcsOsDisplayData;
   Display *               m_pdisplay;
   Atom                    m_atomLongType;
   Atom                    m_atomLongStyle;
   Atom                    m_atomLongStyleEx;
   Atom                    m_atomWmState;
   Atom                    m_atomNetWmState;
   ATOM                    m_atomaNetWmState[net_wm_state_count];
   iptr                    m_countReference;
   //array < MESSAGE >     m_messsageaInput;
   //::mutex *               m_pmutexInput;

   static osdisplay_dataptra * s_pdataptra;
   static ::mutex * s_pmutex;

   osdisplay_data();
   ~osdisplay_data();

   Display * display()
   {
      return ::is_null(this) ? nullptr : m_pdisplay;
   }

   Display * display() const
   {
      return ::is_null(this) ? nullptr : m_pdisplay;
   }

   Atom atom_long_type()
   {
      return ::is_null(this) ? 0 : m_atomLongType;
   }

   Atom atom_long_style()
   {
      return ::is_null(this) ? 0 : m_atomLongStyle;
   }

   Atom atom_long_style_ex()
   {
      return ::is_null(this) ? 0 : m_atomLongStyleEx;
   }

   bool is_null() const
   {
      return ::is_null(this);
   }

   Atom get_window_long_atom(i32 nIndex);


   Atom intern_atom(const char * pszAtomName, bool bCreate);

   Atom intern_atom(e_net_wm_state estate, bool bCreate);

   Atom net_wm_state_atom(bool bCreate);




   inline i64 get_ref_count()
   {

      return m_countReference;

   }


   inline i64 add_ref(OBJ_REF_DBG_PARAMS)
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference,1);

#endif

   }


   inline i64 dec_ref(OBJ_REF_DBG_PARAMS)
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference,1);

#endif

   }


   inline i64 release(OBJ_REF_DBG_PARAMS)
   {

      i64 i = dec_ref(OBJ_REF_DBG_ARGS);

      if(i == 0)
      {

         osdisplay_remove(m_pdisplay);

      }

      return i;

   }


   Window default_root_window();


};




typedef osdisplay_data * osdisplay;


inline xdisplay::operator Display *()
{

   return m_pdata->m_pdisplay;

}

inline bool xdisplay::is_null()
{

   return m_pdata == nullptr;

}


inline bool xdisplay::is_set()
{

   return m_pdata != nullptr;

}





class osdisplay_dataptra :
   public ::raw_array < osdisplay_data * >
{
public:

   virtual ~osdisplay_dataptra()
   {

      remove_all();

   }

   void remove_all()
   {

      for(auto point : *this)
      {

         delete point;

      }

      raw_array < osdisplay_data * >::remove_all();
   }

};
