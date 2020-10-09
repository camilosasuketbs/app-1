﻿#pragma once


template < class T >
class pointer_array :
   public pointer_array_process < comparable_array < ___pointer < T > >, T >
{
public:

   using BASE_ARRAY = pointer_array_process < comparable_array < ___pointer < T > >, T >;

   using ARRAY_BASE = typename BASE_ARRAY::ARRAY_BASE;


   //using ref_iterator = typename ARRAY_BASE::ref_iterator;
   ///using ref_iterator_range = typename ARRAY_BASE::ref_iterator_range;

   using comparable_array < ___pointer < T > >::operator &=;
   using comparable_array < ___pointer < T > >::operator -=;
   using comparable_array < ___pointer < T > >::operator |=;
   using comparable_array < ___pointer < T > >::operator -;
   using comparable_array < ___pointer < T > >::operator ==;
   using comparable_array < ___pointer < T > >::operator !=;

   pointer_array()
   {

   }


   explicit pointer_array(std::nullptr_t)
   {

   }


   virtual ~pointer_array()
   {

      this->remove_all();

   }


   pointer_array(const pointer_array & a) : BASE_ARRAY(a) { }

   pointer_array(pointer_array && a) : BASE_ARRAY(::move(a)) { }


   pointer_array(const std::initializer_list < T * > & list)
   {

      for(auto & point : list)
      {

         add(point);

      }

   }


   template < typename OBJECT >
   __pointer(T) & add_new(OBJECT * pobjectContext)
   {

      __pointer(T) & p = comparable_array < ___pointer < T > >::add_new();

      p.create();

      if (::is_set(pobjectContext))
      {

         p->initialize(pobjectContext);

      }

      return p;

   }


   ::count set_size(::count nNewSize, ::count nGrowBy = -1)
   {

      return comparable_array < ___pointer < T > > :: set_size(nNewSize);

   }

   template < TEMPLATE_TYPE >
   ::count set_size_create(::count nNewSize, ::count nGrowBy = -1, TEMPLATE_ARG)
   {

      ::index i = this->get_size();

      comparable_array < ___pointer < T > > :: set_size(nNewSize);

      ::count c = this->get_size();

      for(; i < c; i++)
      {

         this->element_at(i).create();

      }

      return c;

   }


   template < class DERIVED >
   __pointer(DERIVED) get(::index iStart = 0)
   {

      __pointer(DERIVED) pderived;

      for(::index i = iStart; i < this->get_count(); i++)
      {

         try
         {

            pderived = this->element_at(i);

         }
         catch(...)
         {

         }

         if (pderived.is_set())
         {

            return pderived;

         }

      }

      return nullptr;

   }

   template < class DERIVED >
   __pointer(DERIVED) typed_ptr_at(::index iIndex)
   {

      return this->element_at(iIndex);

   }


   ::index add(const comparable_array < ___pointer < T > > & a)
   {

      return comparable_array < ___pointer < T > >::add(a);

   }


   ::index add(T * p)
   {

      return comparable_array < ___pointer < T > >::add(p);

   }


   bool add_unique(T * p)
   {

      if(contains(p))
         return false;

      this->add(p);

      return true;

   }

   template < typename TYPE >
   __pointer(TYPE) find_first() const
   {

      for (auto & pointer : this->ptra())
      {

         __pointer(TYPE) ptype = pointer;

         if(ptype)
         {

            return ptype;

         }

      }

      return nullptr;

   }

   template < typename TYPE >
   bool contains() const
   {

      return find_first < TYPE >();

   }


   template < typename TYPE >
   bool has() const
   {

      return contains < TYPE >();

   }

   ::count add_unique(const pointer_array & a)
   {

      ::count c = 0;

      for (::index i = 0; i < a.get_count(); i++)
      {

         if (add_unique((T *) a[i]))
            c++;

      }

      return c;

   }

   bool contains(const T * point, ::index iStart = 0, ::count nCount = -1) const
   {

      return find_first(point, iStart, nCount) >= 0;

   }


   ::index find_first(const T * point, ::index iStart = 0, ::count inCountLastOut = -1) const
   {

      this->prepare_first_in_count_last_out(iStart, inCountLastOut);

      for(::index i = iStart; i <= inCountLastOut; i++)
      {

         if (this->operator[]((iptr_cast) i).m_p == point)
         {

            return i;

         }

      }

      return -1;

   }


   ::index comp_find_first(const T & t, ::index (* pfnCompare)(const T *, const T *), ::index iStart = 0, ::count nCount = -1) const
   {

      return this->comp_find_first(&t, pfnCompare, iStart, nCount);

   }


   ::index comp_find_first(const T * point, ::index (* pfnCompare)(const T *, const T *), ::index iStart = 0, ::count inCountLastOut = -1) const
   {

      this->prepare_first_in_count_last_out(iStart, inCountLastOut);

      for(::index i = iStart; i <= inCountLastOut; i++)
      {

         if (pfnCompare(this->operator[](i).m_p, point) == 0)
         {

            return i;

         }

      }

      return -1;

   }


   template < class DERIVED >
   pointer_array & operator -= (DERIVED * point)
   {

      this->remove(dynamic_cast < T * > (point));

      return *this;

   }

   ::count remove(T * point)
   {

      ::count ca = 0;

      ::index iFind = 0;

      while((iFind = this->find_first(point, iFind)) >= 0)
      {

         ca++;

         this->remove_at(iFind);

      }

      return ca;

   }


   //inline const pointer < T > & operator[](::index i) const { return ARRAY_BASE::operator[](i); }
   //inline pointer < T > & operator[](::index i) { return ARRAY_BASE::operator[](i); }


   template < typename TYPE >
   ::count remove_type(TYPE *)
   {

      ::count c = 0;

      for (::index i = this->get_upper_bound(); i >= 0; i--)
      {

         if (typeid(*this->element_at(i).m_p) == typeid(TYPE))
         {

            this->remove_at(i);

            c++;

         }

      }

      return c;

   }



   template < typename PRED >
   __pointer(T) pred_remove_first(PRED pred, ::index iStart = 0)
   {

      for (::index i = iStart; i < this->get_count(); i++)
      {

         if (pred(this->m_pData[i]))
         {

            __pointer(T) sp = this->m_pData[i];

            this->remove_at(i);

            return sp;

         }

      }

      return nullptr;

   }


   template < typename PRED >
   __pointer(T) pred_remove_all_get_first(PRED pred, ::index iStart = 0, ::index iEnd = -1)
   {

      __pointer(T) sp;

      if (iEnd < 0)
      {

         iEnd += this->get_count();

      }

      if (iEnd >= this->get_count())
      {

         iEnd = this->get_count() - 1;

      }


      for (::index i = iStart; i <= iEnd;)
      {

         if (pred(this->m_pData[i]))
         {

            if (sp.is_null())
            {

               sp = this->m_pData[i];

            }

            this->remove_at(i);

         }
         else
         {

            i++;

         }

      }

      return sp;

   }



   const ___pointer < T > & sp_at(::index nIndex) const
   {

      return this->comparable_array < ___pointer < T > >::element_at(nIndex);

   }


   ___pointer < T > & sp_at(::index nIndex)
   {

      return this->comparable_array < ___pointer < T > >::element_at(nIndex);

   }


   T * ptr_at(::index nIndex) const
   {

      return this->sp_at(nIndex);

   }


   T * ptr_at(::index nIndex)
   {

      return this->sp_at(nIndex);

   }


   T & at(::index nIndex) const
   {

      return *this->ptr_at(nIndex);

   }


   T & at(::index nIndex)
   {

      return *this->ptr_at(nIndex);

   }

   T * get_first_pointer(::index n = 0) const
   {

      return this->is_empty() ? nullptr : this->comparable_array < ___pointer < T > >::first(n);

   }


   ___pointer < T > & first_pointer(::index n = 0)
   {

      return this->comparable_array < ___pointer < T > >::first(n);

   }


   T * first_ptr(::index n = 0) const
   {

      if (this->is_empty())
      {

         return nullptr;

      }

      return this->get_first_pointer(n);

   }


   T * first_ptr(::index n = 0)
   {

      return this->first_pointer(n);

   }


   T * get_last_pointer(::index n = -1) const
   {

      return this->is_empty() ? nullptr : this->comparable_array < ___pointer < T > >::last(n);

   }


   ___pointer < T > & last_pointer(::index n = -1)
   {

      return this->comparable_array < ___pointer < T > >::last(n);

   }


   T * last_ptr(::index n = -1) const
   {

      return this->get_last_pointer(n);

   }


   T * last_ptr(::index n = -1)
   {

      return this->last_pointer(n);

   }


   const T & operator() (::index nIndex) const
   {

      return *this->sp_at(nIndex);

   }


   T & operator() (::index nIndex)
   {

      return *this->sp_at(nIndex);

   }



   template < typename PRED >
   T * pred_ptr_first(PRED pred)
   {

      ::index i = this->pred_find_first(pred);

      if(i < 0)
         return nullptr;

      return this->ptr_at(i);

   }



   template < class ARRAY >
   pointer_array & append(const ARRAY * pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(::index i = 0; i < c; i++)
      {
         this->add(pa->element_at(i));
      }

      return *this;

   }

   template < class ARRAY >
   pointer_array & append(const __pointer(ARRAY) & pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(::index i = 0; i < c; i++)
      {
         this->add(pa->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   pointer_array & append(const ARRAY & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(::index i = 0; i < c; i++)
      {
         this->add(a.element_at(i));
      }

      return *this;

   }


   pointer_array & append(const pointer_array & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(::index i = 0; i < c; i++)
      {

         this->add(a.sp_at(i));

      }

      return *this;

   }


   template < class ARRAY >
   pointer_array & append_ptra(const ARRAY * pptra)
   {

      ::count c = pptra->get_count(); // allow to append to itself one time

      for(::index i = 0; i < c; i++)
      {
         this->add(*pptra->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   pointer_array & copy(const ARRAY * pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   pointer_array & copy(const __pointer(ARRAY) & pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   pointer_array & copy(const ARRAY & a)
   {

      if (&a == dynamic_cast <ARRAY*> (this))
      {

         return *this;

      }

      this->remove_all();

      this->append(a);

      return *this;

   }

   pointer_array & copy(const pointer_array & a)
   {

      if(&a == this)
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   template < class ARRAY >
   pointer_array & copy_ptra(const ARRAY * pptra)
   {

      if(pptra == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pptra);

      return *this;

   }



   inline pointer_array & operator = (const pointer_array & a)
   {

      copy(a);

      return *this;

   }


   inline pointer_array & operator = (pointer_array && a)
   {

      comparable_array < ___pointer < T > >::operator = (::move(a));

      return *this;

   }

};


//
//
//
//// Range-based for loop support
//// smart_pointer_range2 indirect/interpreted contribution from
///**
//* pugixml parser - version 1.5
//* --------------------------------------------------------
//* Copyright (C) 2006-2014, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
//* Report bugs and download new versions at http://pugixml.org/
//*
//* This library is distributed under the MIT License. See notice at the end
//* of this file.
//*
//* This work is based on the pugxml parser, which is:
//* Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
//*/
//
//template < typename Iterator > class smart_pointer_range2
//{
//public:
//
//   Iterator m_beg;
//   Iterator m_end;
//
//   smart_pointer_range2(Iterator beg,Iterator end): m_beg(beg),m_end(end)
//   {
//   }
//
//   Iterator begin()  const { return m_beg; }
//   Iterator end()    const { return m_end; }
//
//private:
//
//};
//
//
//template < class T >
//class smart_pointer_array2:
//   public comparable_array < pointer < T > >
//{
//public:
//
//
//   class ref_iterator
//   {
//   public:
//
//      typedef T BASE_TYPE;
//      typedef const T & BASE_ARG_TYPE;
//      typedef smart_pointer_array2 BASE_ARRAY;
//
//      ::index            m_i;
//      BASE_ARRAY *     m_parray;
//
//      ref_iterator()
//      {
//         m_i = 0;
//         m_parray = nullptr;
//      }
//
//      ref_iterator(::index i,BASE_ARRAY * parray)
//      {
//         m_i = i;
//         m_parray = parray;
//      }
//
//      ref_iterator(const ref_iterator & it)
//      {
//         operator = (it);
//      }
//
//
//      ref_iterator & operator = (const ref_iterator & it)
//      {
//         if(this != &it)
//         {
//            m_i         = it.m_i;
//            m_parray    = it.m_parray;
//         }
//         return *this;
//      }
//
//      bool operator == (const ref_iterator & it)
//      {
//         if(this == &it)
//            return true;
//         if(m_parray != it.m_parray)
//            return false;
//         if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
//            return true;
//         if(m_i <= 0 && it.m_i <= 0)
//            return true;
//         return m_i == it.m_i;
//      }
//
//      bool operator != (const ref_iterator & it)
//      {
//         return !operator==(it);
//      }
//
//      ref_iterator operator ++(int)
//      {
//         ref_iterator it = *this;
//         operator ++();
//         return it;
//      }
//
//      ref_iterator operator --(int)
//      {
//         ref_iterator it = *this;
//         operator --();
//         return it;
//      }
//
//      ref_iterator & operator ++()
//      {
//         m_i++;
//         if(m_i >= m_parray->get_size())
//            m_i = m_parray->get_size();
//         return *this;
//      }
//
//      ref_iterator & operator +(::index i)
//      {
//         m_i += i;
//         if(m_i >= m_parray->get_size())
//            m_i = m_parray->get_size();
//         return *this;
//      }
//
//      ref_iterator & operator --()
//      {
//         m_i--;
//         if(m_i < 0)
//            m_i = 0;
//         return *this;
//      }
//
//      ref_iterator mid(const ref_iterator & i) const
//      {
//         return ref_iterator((m_i + i.m_i + 1) / 2,m_parray);
//      }
//
//      ref_iterator & operator -(::count c)
//      {
//         m_i-=c;
//         if(m_i < 0)
//            m_i = 0;
//         return *this;
//      }
//
//      bool operator < (const ref_iterator & i) const
//      {
//
//         return m_i < i.m_i;
//
//      }
//
//      ::count get_count() const
//      {
//         return m_parray->get_count();
//      }
//
//
//      T & operator * ()
//      {
//         return m_parray->at(m_i);
//      }
//
//      const T & operator * () const
//      {
//         return m_parray->at(m_i);
//      }
//
//
//   };
//
//   typedef smart_pointer_range2 < ref_iterator > ref_range;
//
//
//   smart_pointer_array2()
//   {
//
//   }
//
//   virtual ~smart_pointer_array2()
//   {
//
//      this->remove_all();
//
//   }
//
//#if defined(MOVE_SEMANTICS)
//
//   smart_pointer_array2(smart_pointer_array2 && a)
//   {
//
//      comparable_array < pointer < T > >::operator = (a);
//
//   }
//
//   inline smart_pointer_array2 & operator = (smart_pointer_array2 && a)
//   {
//
//      comparable_array < pointer < T > >::operator = (a);
//
//      return *this;
//
//   }
//
//#endif
//
//   smart_pointer_array2(const smart_pointer_array2 & a):
//      comparable_array < pointer < T > >(a)
//   {
//
//      comparable_array < pointer < T > >::operator = (a);
//
//   }
//
//   inline smart_pointer_array2 & operator = (const smart_pointer_array2 & a)
//   {
//
//      copy(a);
//
//      return *this;
//
//   }
//
//
//   smart_pointer_array2(::element * pobjectContext):
//      ::element(pobjectContext),
//      comparable_array < pointer < T > >(pobjectContext)
//   {
//   }
//
//   __pointer(T) & add_new()
//   {
//
//      __pointer(T) & sp = comparable_array < pointer < T > >::add_new();
//
//      sp.alloc(this->create_new, this);
//
//      return sp;
//
//   }
//
//
//   ::count set_size(::count nNewSize,::count nGrowBy = -1)
//   {
//
//      return comparable_array < pointer < T > > :: set_size(nNewSize);
//
//   }
//
//   ::count set_size_create(::count nNewSize,::count nGrowBy = -1)
//   {
//      ::index i = this->get_size();
//      comparable_array < pointer < T > > :: set_size(nNewSize);
//      ::count ca = this->get_size();
//      for(; i < ca; i++)
//      {
//         this->element_at(i).alloc(this->create_new, this);
//      }
//      return ca;
//   }
//
//
//   template < class DERIVED >
//   DERIVED * get(::index iStart = 0)
//   {
//
//      DERIVED * pderived = nullptr;
//
//      for(::index i = iStart; i < this->get_count(); i++)
//      {
//
//         try
//         {
//
//            pderived = dynamic_cast < DERIVED * > (this->element_at(i).m_p);
//
//         }
//         catch(...)
//         {
//
//         }
//
//         if(pderived != nullptr)
//            return pderived;
//
//      }
//
//      return nullptr;
//
//   }
//
//   template < class DERIVED >
//   DERIVED * typed_ptr_at(::index iIndex)
//   {
//
//      return dynamic_cast < DERIVED * > (this->element_at(iIndex).m_p);
//
//   }
//
//   pointer < T > & add(T * point)
//   {
//
//      return comparable_array < pointer < T > >::add_new() = point;
//
//   }
//
//
//   bool add_unique(T * point)
//   {
//
//      if(contains(point))
//         return false;
//
//      this->add(point);
//
//      return true;
//
//   }
//
//   ::count add_unique(const smart_pointer_array2 & a)
//   {
//
//      ::count c = 0;
//
//      for(::index i = 0; i < a.get_count(); i++)
//      {
//
//         if(add_unique((T *)a[i]))
//            c++;
//
//      }
//
//      return c;
//
//   }
//
//   bool contains(const T * point,::index iStart = 0,::count nCount = -1) const
//   {
//
//      return find_first(point,iStart,nCount) >= 0;
//
//   }
//
//   ::index find_first(const T * point,::index iStart = 0,::count nCount = -1) const
//   {
//
//      ::index iEnd;
//
//      if(nCount < 0)
//         iEnd = this->get_upper_bound(nCount);
//      else
//         iEnd = iStart + nCount - 1;
//
//      for(::index i = iStart; i <= iEnd; i++)
//      {
//
//         if(this->operator[](i).m_p == point)
//            return i;
//
//      }
//
//      return -1;
//
//   }
//
//
//   ::index find_first(const T & t,::index(* pfnCompare)(const T *,const T *),::index iStart = 0,::count nCount = -1) const
//
//   {
//
//      return this->find_first(&t,pfnCompare,iStart,nCount);
//
//
//   }
//
//
//   ::index find_first(const T * point,::index(* pfnCompare)(const T *,const T *),::index iStart = 0,::count nCount = -1) const
//
//   {
//
//      ::index iEnd;
//
//      if(nCount < 0)
//         iEnd = this->get_upper_bound(nCount);
//      else
//         iEnd = iStart + nCount - 1;
//
//      for(::index i = iStart; i <= iEnd; i++)
//      {
//
//         if(pfnCompare(this->operator[](i).m_p,point) == 0)
//
//            return i;
//
//      }
//
//      return -1;
//
//   }
//
//   template < class DERIVED >
//   smart_pointer_array2 & operator -= (DERIVED * point)
//   {
//
//      this->remove(dynamic_cast < T * > (point));
//
//      return *this;
//
//   }
//
//   ::count remove(T * point)
//   {
//
//      ::count ca = 0;
//
//      ::index iFind = 0;
//
//      while((iFind = this->find_first(point,iFind)) >= 0)
//      {
//
//         ca++;
//
//         this->remove_at(iFind);
//
//      }
//
//      return ca;
//
//   }
//
//
//   template < typename TYPE >
//   ::count remove_type(TYPE *)
//   {
//
//      ::count c = 0;
//
//      for(::index i = this->get_upper_bound(); i >= 0; i--)
//      {
//
//         if(typeid(*this->element_at(i).m_p) == typeid(TYPE))
//         {
//
//            this->remove_at(i);
//
//            c++;
//
//         }
//
//      }
//
//      return c;
//
//   }
//
//   // overloaded operator helpers
//   T  & operator[](::index nIndex) const
//   {
//
//      return *this->comparable_array < pointer < T > >::operator[](nIndex).m_p;
//
//   }
//
//   T  & operator[](::index nIndex)
//   {
//
//      return *this->comparable_array < pointer < T > >::operator[](nIndex).m_p;
//
//   }
//
//   const pointer < T > & sp_at(::index nIndex) const
//   {
//
//      return this->comparable_array < pointer < T > >::element_at(nIndex);
//
//   }
//
//
//   pointer < T > & sp_at(::index nIndex)
//   {
//
//      return this->comparable_array < pointer < T > >::element_at(nIndex);
//
//   }
//
//
//   T * ptr_at(::index nIndex) const
//   {
//
//      return this->sp_at(nIndex);
//
//   }
//
//
//   T * ptr_at(::index nIndex)
//   {
//
//      return this->sp_at(nIndex);
//
//   }
//
//
//   T & at(::index nIndex) const
//   {
//
//      return *this->ptr_at(nIndex);
//
//   }
//
//
//   T & at(::index nIndex)
//   {
//
//      return *this->ptr_at(nIndex);
//
//   }
//
//   const pointer < T > & first_pointer(::index n = 0) const
//   {
//
//      return this->comparable_array < pointer < T > >::first(n);
//
//   }
//
//
//   pointer < T > & first_pointer(::index n = 0)
//   {
//
//      return this->comparable_array < pointer < T > >::first(n);
//
//   }
//
//
//   T * first_ptr(::index n = 0) const
//   {
//
//      return this->first_pointer(n);
//
//   }
//
//
//   T * first_ptr(::index n = 0)
//   {
//
//      return this->first_pointer(n);
//
//   }
//
//
//   T & first(::index n = 0) const
//   {
//
//      return *this->first_ptr(n);
//
//   }
//
//
//   T & first(::index n = 0)
//   {
//
//      return *this->first_ptr(n);
//
//   }
//
//
//   T * last_pointer(::index n = -1) const
//   {
//
//      return this->comparable_array < pointer < T > >::last(n);
//
//   }
//
//
//   pointer < T > & last_pointer(::index n = -1)
//   {
//
//      return this->comparable_array < pointer < T > >::last(n);
//
//   }
//
//
//   T * last_ptr(::index n = -1) const
//   {
//
//      return this->last_pointer(n);
//
//   }
//
//
//   T * last_ptr(::index n = -1)
//   {
//
//      return this->last_pointer(n);
//
//   }
//
//
//   T & last(::index n = -1) const
//   {
//
//      return *last_ptr(n);
//
//   }
//
//
//   T & last(::index n = -1)
//   {
//
//      return *this->last_ptr(n);
//
//   }
//
//
//   const T & operator() (::index nIndex) const
//   {
//
//      return *this->sp_at(nIndex);
//
//   }
//
//
//   T & operator() (::index nIndex)
//   {
//
//      return *this->sp_at(nIndex);
//
//   }
//
//
//   template < class ARRAY >
//   smart_pointer_array2 & append(const ARRAY * pa)
//   {
//
//      ::count c = pa->get_count(); // allow to append to itself one time
//
//      for(::index i = 0; i < c; i++)
//      {
//         this->add(pa->element_at(i));
//      }
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & append(const __pointer(ARRAY) & pa)
//   {
//
//      ::count c = pa->get_count(); // allow to append to itself one time
//
//      for(::index i = 0; i < c; i++)
//      {
//         this->add(pa->operator[](i));
//      }
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & append(const ARRAY & a)
//   {
//
//      ::count c = a.get_count(); // allow to append to itself one time
//
//      for(::index i = 0; i < c; i++)
//      {
//         this->add(a.element_at(i));
//      }
//
//      return *this;
//
//   }
//
//
//   smart_pointer_array2 & append(const smart_pointer_array2 & a)
//   {
//
//      ::count c = a.get_count(); // allow to append to itself one time
//
//      for(::index i = 0; i < c; i++)
//      {
//
//         this->add(a.sp_at(i));
//
//      }
//
//      return *this;
//
//   }
//
//
//   template < class ARRAY >
//   smart_pointer_array2 & append_ptra(const ARRAY * pptra)
//   {
//
//      ::count c = pptra->get_count(); // allow to append to itself one time
//
//      for(::index i = 0; i < c; i++)
//      {
//         this->add(*pptra->operator[](i));
//      }
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy(const ARRAY * pa)
//   {
//
//      if(pa == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->remove_all();
//
//      this->append(pa);
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy(const __pointer(ARRAY) & pa)
//   {
//
//      if(pa == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->remove_all();
//
//      this->append(pa);
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy(const ARRAY & a)
//   {
//
//      if(&a == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->remove_all();
//
//      this->append(a);
//
//      return *this;
//
//   }
//
//   smart_pointer_array2 & copy(const smart_pointer_array2 & a)
//   {
//
//      if(&a == this)
//         return *this;
//
//      this->remove_all();
//
//      this->append(a);
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy_ptra(const ARRAY * pptra)
//   {
//
//      if(pptra == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->remove_all();
//
//      this->append(pptra);
//
//      return *this;
//
//   }
//
//   ref_iterator ref_it(::index iStart) { return ref_iterator(iStart,this); }
//   ref_iterator ref_it(::index iStart,::count cCount) { return ref_iterator(iStart + (cCount < 0 ? this->get_count() + cCount + 1 : cCount),this); }
//
//   ref_range refa(::index iStart = 0,::count cCount = -1) { return smart_pointer_range2 < ref_iterator >(ref_it(iStart),ref_it(iStart,cCount)); }
//
//};

//#define sspa(TYPE) array_base < __pointer(TYPE) >
//#define spa2(TYPE) ::smart_pointer_array2 < TYPE >
///#define __xmlspa(TYPE) ::pointer_array < TYPE >

typedef __pointer_array(element) object_pointera;

typedef __pointer_array(element) simple_object_pointera;





