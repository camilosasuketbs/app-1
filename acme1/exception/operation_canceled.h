#pragma once


class CLASS_DECL_ACME operation_canceled_exception :
   public ::exception::exception
{
public:


   operation_canceled_exception(const char * pszMessage = nullptr);
   virtual ~operation_canceled_exception();


};

