#pragma once


namespace android
{


   class CLASS_DECL_ACME file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual ::estatus initialize(::element * pobjectContext) override;



      virtual ::estatus update_module_path() override;


   };


} // namespace ca2


