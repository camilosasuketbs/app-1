#include "framework.h"
#include "aqua/node/uwp/directx.h"
#include "aqua/node/uwp/directx_interaction.h"
#include "aqua/node/uwp/directx_impact.h"
#include "aqua/node/uwp/directx_application.h"


CLASS_DECL_AQUA ::estatus os_application_system_run(::aqua::system * psystem)
{

   //auto estatus = psystem->begin_synch();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   auto source = ::uwp::new_directx_application_source(get_context_system(), psystem->m_strCommandLine);

   ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

   return ::success;

}



