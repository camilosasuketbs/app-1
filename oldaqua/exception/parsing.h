#pragma once


class CLASS_DECL_AQUA parsing_exception:
   public ::exception::exception
{
public:


   parsing_exception(const char * pszMessage);
   virtual ~parsing_exception();


};


CLASS_DECL_AQUA bool get_avoid_parsing_exception();
CLASS_DECL_AQUA bool throw_parsing_exception(const string & strMessage);


class CLASS_DECL_AQUA avoid_parsing_exception
{
public:

   
   iptr m_iBefore;


   var & m_varAvoidParsingException;


   avoid_parsing_exception();
   virtual ~avoid_parsing_exception();
   

};



class json_parsing_exception :
   public ::parsing_exception
{
public:

   json_parsing_exception(const char * pszMessage = nullptr);
   virtual ~json_parsing_exception();

};


CLASS_DECL_AQUA bool throw_json_parsing_exception(const string & strMessage);