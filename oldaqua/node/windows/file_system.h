#pragma once


namespace windows
{


   class CLASS_DECL_AQUA file_system:
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual ::estatus init_system() override;


      virtual ::estatus update_module_path() override;


   };


} // namespace windows



