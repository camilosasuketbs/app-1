#pragma once


class CLASS_DECL_AQUA invalid_index_exception :
   public invalid_argument_exception
{
public:


   invalid_index_exception(const char * pszMessage = nullptr);
   virtual ~invalid_index_exception();


};

