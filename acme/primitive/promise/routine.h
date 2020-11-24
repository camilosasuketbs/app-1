#pragma once


namespace promise
{


   class CLASS_DECL_ACME routine :
           public ::function_pointer
   {
   public:


      using ::function_pointer::function_pointer;


      inline ::estatus operator()() const;

      inline bool should_run_async() const;


   };


} // namespace promise



