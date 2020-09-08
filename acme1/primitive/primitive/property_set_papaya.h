#pragma once


namespace papaya
{


   namespace property_set
   {


      inline string get_string(const ::property_set & set, const string & strKey)
      {

         return set[strKey].get_string();

      }


      //inline string get_string(const ::generic_object & generic_object, const string & strKey)
      //{

      //   return generic_object.property_set_get_string(strKey);

      //}


      //inline bool get_string(string & strResult, const ::context_object& context_object, const string& strKey)
      //{

      //   return context_object.property_set_get_string(strResult, strKey);

      //}


      inline bool get_string(string& strResult, const ::property_set & set, const string& strKey)
      {

         auto pproperty = set.find_property(strKey);

         if (::is_null(pproperty))
         {

            return false;

         }

         strResult = pproperty->get_string();

         return true;

      }


      inline bool get_evaluation(string & strResult, const ::property_set & set, const string & strExpression)
      {

         auto pproperty = set.find_property(strExpression);

         if (::is_null(pproperty))
         {

            return false;

         }

         strResult = pproperty->get_string();

         return true;

      }


      //inline string get_evaluation(const ::context_object& context_object, const string & strExpression)
      //{

      //   return context_object.property_set_get_evaluation(strExpression);

      //}

      //inline bool get_evaluation(string & strResult, const ::context_object& context_object, const string& strExpression)
      //{

      //   return context_object.property_set_get_evaluation(strResult, strExpression);

      //}

      // ::property_set set;
      //
      // set["var5"] = "searching value";
      //
      // str = "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = '$var5'"
      //
      // real-ization: "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = 'searching value'"
      inline string evaluate(const ::property_set & set, const string & strSource)
      {

         string str(strSource);

         strsize iPos;

         char ch;

         char chNext;

         for (iPos = 0; iPos < str.get_length(); iPos++)
         {

            ch = str[iPos];

            if (iPos + 1 < str.get_length())
            {

               chNext = str[iPos + 1];

            }
            else
            {

               chNext = '\0';

            }

            if (ch == '\\')
            {

               iPos++;

               continue;

            }
            else if (ch == '{' && chNext == '$')
            {

               strsize iEnd = str.find('}', iPos + 1);

               if (iEnd < 0)
               {

                  //error

                  break;

               }

               string strKey = str.Mid(iPos + 2, iEnd - iPos - 2);

               string strEval;

               if (get_string(strEval, set, strKey))
               {

                  str = str.Left(iPos) + strEval + str.Mid(iEnd + 1);

                  iPos += strEval.get_length() - 1;

               }
               else
               {

                  iPos = iEnd;

               }


            }
            else if (ch == '$')
            {

               if (!(ansi_char_is_alphabetic(chNext) || chNext == '_'))
               {

                  // error

                  break;

               }

               strsize iStart = iPos;

               strsize iEnd = iStart + 2;

               for (; iEnd < str.get_length(); iEnd++)
               {

                  ch = str[iEnd];

                  if (!(ansi_char_is_alphabetic(ch) || ch == '_' || ansi_char_is_digit(ch)))
                  {

                     break;

                  }

               }

               string strExpression = str.Mid(iStart, iEnd - iStart);

               string strEval;

               if (get_evaluation(strEval, set, strExpression))
               {

                  str = str.Left(iPos) + strEval + str.Mid(iEnd);

                  iPos += strEval.get_length() - 1;

               }
               else
               {

                  iPos = iEnd;

               }

            }

         }

         return str;

      }




   } // namespace property_set


} // namespace papaya



