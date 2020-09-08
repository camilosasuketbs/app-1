#include "framework.h"
#include "aqua/filesystem/fs/_fs.h"


namespace fs
{


   fs::fs()
   {

   }


   fs::~fs()
   {

   }


   ::estatus fs::initialize(::object * pobjectContext)
   {

      auto estatus = ::aqua::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }
//
//      if(get_context_application()->is_system())
//      {
//
///*       
//         create_factory <main_view > ();
//         create_factory <tree > ();
//         create_factory <list > ();
//*/
//
//      }

      return estatus;

   }
 


} // namespace fs



