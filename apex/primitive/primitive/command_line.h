#pragma once


namespace fs
{


   class item_array;


} // namespace fs


class CLASS_DECL_APEX command_line :
   virtual public ::context_object
{
public:

   
   enum enum_command
   {
      command_none,
      command_application_start,
      command_file_new,
      command_file_open,
      command_file_print,
      command_file_print_to,
      command_file_dde,
      command_app_unregister,
      command_file_nothing = -1
   };


   enum_command                     m_ecommand;
   bool                             m_bShowSplash;
   bool                             m_bRunEmbedded;
   bool                             m_bRunAutomated;
   i32                              m_nCmdShow;

   // not valid for file_new
   payload                              m_varFile;

   // valid only for file_print_to
   string                           m_strPrinterName;
   string                           m_strDriverName;
   string                           m_strPortName;

   payload                              m_varQuery;
   ::file::item_array *             m_pitema;

   __pointer(::apex::application)   m_pappFork;
   string                           m_strExe;
   string                           m_strApp;
   string                           m_strAppType;
   ::user::primitive *              m_puserinteractionParent;
   index                            m_iEdge;
   manual_reset_event               m_eventReady;
   ::create *                       m_pcreate;
   string                           m_strCommandLine;


   command_line();
   virtual ~command_line();


   void common_construct();


   virtual ::estatus initialize_command_line(const string& strCommandLine);


   //command_line & operator = (const command_line & commandline);


   virtual void ParseParam(const string & strParam,bool bFlag,bool bLast);
   virtual void ParseParamFlag(const string & strParam);
   virtual void ParseParamNotFlag(const string & strParam);
   virtual void ParseLast(bool bLast);


   virtual void _001ParseCommandLine(const string & strCommandLine);
   virtual void _001ParseCommandLineUri(const string & strCommandLine);

   virtual void _001ParseCommandFork(const string & strCommandFork);
   virtual void _001ParseCommandForkUri(const string & strCommandFork);


};



