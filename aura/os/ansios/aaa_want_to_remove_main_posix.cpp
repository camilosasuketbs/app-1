#include "framework.h"
#include "aura/inline/_console.h"


extern "C"
typedef  void  AURA_MAIN();
typedef AURA_MAIN* PFN_AURA_MAIN;


int main_posix(int argc, char* argv[])
{

   console console(argc, argv);

   HMODULE hmodule = ::GetModuleHandle(NULL);

   PFN_AURA_MAIN pauramain = (PFN_AURA_MAIN) ::GetProcAddress(hmodule, "aura_main");

   if (!pauramain)
   {

      message_box("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + message_box_icon_error);

      return -1;

   }

   Application.m_estatus = ::undefined;

   (*pauramain)();

   int iStatus = (int)Application.m_estatus;

   int iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      if (::get_context_system()->command_value_is_true("show_application_information"))
      {

         printf("return code is %d", iStatus);

      }

   }

   return iError;

}

