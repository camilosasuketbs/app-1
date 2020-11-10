﻿#include "framework.h"
#include "_internal.h"


#define UNZ_FILE_INFO ((unz_file_info *) m_punzfileinfo)


namespace zip
{


   in_file::in_file()
   {

      m_punzfileinfo = new unz_file_info;

   }


   in_file::~in_file()
   {
      if(get_zip_file() != nullptr)
         close();

      delete UNZ_FILE_INFO;
   }




   bool in_file::zip_open(const char * pszFileName,::u32)
   {

      m_filea.remove_all();

      m_infilea.remove_all();

      m_straPath.remove_all();

      m_straPrefix.remove_all();

      string strFile;

      strFile = pszFileName;


      index iFind = -1;

      index iStart = 0;

      while((iFind = ::str::find_file_extension("zip:",pszFileName,iStart)) >= 0)

      {

         m_straPath.add(string(&pszFileName[iStart],iFind + strlen(".zip")));


         iStart = iFind + strlen(".zip:");

      }

      if(::str::ends_ci(pszFileName,".zip"))

      {

         m_straPath.add(string(&pszFileName[iStart]));


      }

      if(m_straPath.get_size() == 0)
      {

         return false;

      }

      m_filea.add(__new(::zip::file()));

      if(!m_filea.last()->zip_open(m_straPath[0]))
      {

         return false;

      }

      string str;

      i32 i;

      for(i = 1; i < m_straPath.get_size(); i++)
      {

         m_infilea.add(__new(::zip::in_file));

         str = m_straPath[i];

         if(!m_infilea.last()->zip_open(m_filea.last_pointer(),str))
         {

            m_filea.remove_all();

            m_infilea.remove_all();

            return false;

         }

         m_filea.add(__new(::zip::file));

         if(!m_filea.last_pointer()->zip_open((file_pointer) m_infilea.last_pointer()))
         {

            m_filea.remove_all();

            m_infilea.remove_all();

            return false;

         }

         m_straPrefix.add(m_straPath[i]);

      }

      if(::str::ends(strFile,":"))
      {

         return true;

      }

      iFind = strFile.reverse_find(L':');

      strFile = strFile.Mid(iFind + 1);

      ::str::begins_eat(strFile,"/");

      ::str::begins_eat(strFile,"\\");

      return true;

   }


   bool in_file::unzip_open(::file::file * pfile, const string_array & straPath, int iBufferLevel, ::file::enum_type * petype)
   {

      m_filea.remove_all();

      m_infilea.remove_all();

      m_straPath = straPath;

      m_straPrefix.remove_all();

      m_filea.add(__new(::zip::file));

      if(!m_filea.last_pointer()->unzip_open(pfile, iBufferLevel))
      {

         return false;

      }

      string str;

      i32 i;

      for(i = 0; i < m_straPath.get_upper_bound(); i++)
      {

         m_infilea.add(__new(::zip::in_file));

         str = m_straPath[i];

         if(!m_infilea.last_pointer()->unzip_open(m_filea.last_pointer(),str))
         {

            m_filea.remove_all();

            m_infilea.remove_all();

            return false;

         }

         m_filea.add(__new(::zip::file()));

         if(!m_filea.last_pointer()->unzip_open((file_pointer)m_infilea.last_pointer()))
         {

            m_filea.remove_all();

            m_infilea.remove_all();

            return false;

         }

         m_straPrefix.add(m_straPath[i]);

      }

      if (i != m_straPath.get_upper_bound())
      {

         return true;

      }

      string strFile = straPath.last();

      index iFind = strFile.reverse_find(L':');

      strFile = strFile.Mid(iFind + 1);

      ::str::begins_eat(strFile,"/");

      ::str::begins_eat(strFile,"\\");

      if (locate(strFile))
      {

         if (::is_set(petype))
         {

            *petype = ::file::type_file;

         }

         return true;

      }
      else if(locate(strFile + "/"))
      {

         if (::is_set(petype))
         {

            *petype = ::file::type_folder;

         }

         return true;

      }

      return false;

   }


   bool in_file::locate(const char * pszFileName)
   {
      string strFile(pszFileName);
      index iFind = strFile.find(":");
      if(iFind >= 0)
         strFile = strFile.Left(iFind);
      strFile.replace("\\","/");
      if(unzLocateFile(get_zip_file()->m_pfUnzip,strFile,0) != UNZ_OK)
      {
         strFile.replace("/","\\");
         if(unzLocateFile(get_zip_file()->m_pfUnzip,strFile,0) != UNZ_OK)
         {
            return false;
         }
      }
      if(unzOpenCurrentFile(get_zip_file()->m_pfUnzip) != UNZ_OK)
         return false;
      if(unzGetCurrentFileInfo(get_zip_file()->m_pfUnzip,
                               UNZ_FILE_INFO,
                               nullptr,
                               0,
                               nullptr,
                               0,
                               nullptr,
                               0) != UNZ_OK)
         return false;

      m_iPosition = 0;
      m_strFileName = strFile;
      return true;
   }


   bool in_file::unzip_open(::zip::file * pzfile,const char * pcszFileName)

   {

      ASSERT(__is_valid_string(pcszFileName));


      m_filea.add(pzfile);

      if(!locate(pcszFileName))

      {

         return false;

      }

      return true;

   }


   bool in_file::zip_open(::zip::file * pzfile,const char * pcszFileName)

   {

      ASSERT(__is_valid_string(pcszFileName));


      m_filea.add(pzfile);

      m_strZipFile = pcszFileName;

      return TRUE;
   }

   bool in_file::dump(file_pointer  pfile)
   {
      if(m_strFileName.is_empty())
         return false;
      byte buf[1024];
      memsize iRead;
      while((iRead = read(buf,sizeof(buf))) > 0)
      {
         pfile->write(buf,iRead);
      }
      return true;
   }


   bool in_file::dump(memory & m)
   {

      byte buf[1024];

      memsize iRead;

      while((iRead = read(buf,sizeof(buf))) > 0)
      {

         m.append(buf, iRead);

      }

      return true;

   }


   memsize in_file::read(void * pdata,memsize nCount)

   {
      //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != nullptr);

      if(nCount == 0)
         return 0;   // avoid Win32 "nullptr-read"

      ASSERT(pdata != nullptr);

      ASSERT(__is_valid_address(pdata,(uptr)nCount));

      auto iRead = unzReadCurrentFile(get_zip_file()->m_pfUnzip,pdata,(u32)nCount);

      m_iPosition += iRead;

      return (::u32)iRead;
   }

   void in_file::write(const void * pdata,memsize nCount)

   {
      UNREFERENCED_PARAMETER(pdata);

      UNREFERENCED_PARAMETER(nCount);
      //ASSERT_VALID(this);
      ASSERT(get_zip_file() != nullptr);

      ASSERT(FALSE);
   }

   filesize in_file::seek(filesize lOff,::file::e_seek nFrom)
   {
      //   ASSERT_VALID(this);
      //ASSERT(get_zip_file() != nullptr);
      //ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      //ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);


      u64 iNewPos;
      if(nFrom == ::file::seek_begin)
      {
         iNewPos = lOff;
      }
      else if(nFrom == ::file::seek_end)
      {
         iNewPos = UNZ_FILE_INFO->uncompressed_size - lOff;
      }
      else if(nFrom == ::file::seek_current)
      {
         iNewPos = m_iPosition + lOff;
      }
      else
      {
         __throw(invalid_argument_exception("zip::in_file::seek invalid seek option"));
      }

      if(iNewPos < m_iPosition)
      {
         if(unzCloseCurrentFile(get_zip_file()->m_pfUnzip) != UNZ_OK)
            return ::numeric_info < filesize >::allset();
         if(unzOpenCurrentFile(get_zip_file()->m_pfUnzip) != UNZ_OK)
            return ::numeric_info < filesize >::allset();
         m_iPosition = 0;
      }

      if(iNewPos > m_iPosition)
      {
         i64 iRemain = iNewPos - m_iPosition;
         i64 iGet;
         i32 iRead;
         byte pbBuf[1024];

         while(iRemain > 0)
         {
            iGet = min(iRemain,1024);
            iRead = unzReadCurrentFile(get_zip_file()->m_pfUnzip,pbBuf,(u32)iGet);

            iRemain -= iRead;
            if(iRead < iGet)
               break;
         }
         iNewPos -= iRemain;
      }

      m_iPosition = iNewPos;

      return iNewPos;
   }

   filesize in_file::get_position() const
   {
      return m_iPosition;
   }

   void in_file::flush()
   {
      //   ASSERT_VALID(this);

   }

   void in_file::close()
   {
      //   ASSERT_VALID(this);
      //ASSERT(get_zip_file() != nullptr);

      bool bError = FALSE;
      /*if(get_zip_file() != nullptr)
      {
      unzCloseCurrentFile(get_zip_file()->m_pf);
      }*/

      m_filea.remove_all();
      m_infilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();
      m_strFileName.Empty();

      if(bError)
         __throw(::exception::exception(0));
   }


   //void in_file::lock(filesize dwPos,filesize dwCount)
   //{
   //   UNREFERENCED_PARAMETER(dwPos);
   //   UNREFERENCED_PARAMETER(dwCount);
   //}


   //void in_file::unlock(filesize dwPos,filesize dwCount)
   //{
   //   UNREFERENCED_PARAMETER(dwPos);
   //   UNREFERENCED_PARAMETER(dwCount);
   //}

   
   void in_file::set_size(filesize dwNewLen)
   {
      
      __throw(not_supported_exception());

   }


   filesize in_file::get_size() const
   {

      return UNZ_FILE_INFO->uncompressed_size;

   }


   void in_file::assert_valid() const
   {
      //matter::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void in_file::dump(dump_context & dumpcontext) const
   {
      //   matter::dump(dumpcontext);

      dumpcontext << "with handle " << (uptr)get_zip_file();
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
   }

   /////////////////////////////////////////////////////////////////////////////
   // FileException helpers

   /* Error Codes */
#ifndef LINUX

#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#ifndef __APPLE__
#define EAGAIN          11
#endif
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34


#ifdef WINDOWS

#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

#endif




   /*
    * Support EDEADLOCK for compatibiity with older MS-C versions.
    */
#define EDEADLOCK       EDEADLK

#endif


   bool in_file::is_opened() const
   {

      return get_zip_file() != nullptr;

   }


   ::zip::file * in_file::get_zip_file()
   {

      if (m_filea.get_count() <= 0)
      {

         return nullptr;

      }

      return m_filea.last_pointer();

   }


   const ::zip::file * in_file::get_zip_file() const
   {

      return m_filea.get_last_pointer();

   }


   void in_file::add_file(const ::file::path & pszRelative, ::file::file * pfile)
   {

      //::file::path strPath(pszDir / pszRelative);

      ::file::file_status status;

      pfile->get_status(status);

      zip_fileinfo zipfi;

      __memset(&zipfi,0,sizeof(zipfi));

      zipfi.tmz_date.tm_hour = status.m_ctime.GetGmtHour();
      zipfi.tmz_date.tm_sec  = status.m_ctime.GetGmtSecond();
      zipfi.tmz_date.tm_min  = status.m_ctime.GetGmtMinute();
      zipfi.tmz_date.tm_year = status.m_ctime.GetGmtYear();
      zipfi.tmz_date.tm_mon  = status.m_ctime.GetGmtMonth();
      zipfi.tmz_date.tm_mday = status.m_ctime.GetGmtDay();

      zipOpenNewFileInZip(get_zip_file()->m_pfZip,pszRelative,&zipfi,nullptr,0,nullptr,0,nullptr,Z_DEFLATED,Z_DEFAULT_COMPRESSION);

      memory mem;

      mem.set_size(256 * 1024);

      memsize uRead;

      while((uRead = pfile->read(mem,mem.get_size())) > 0)
      {

         zipWriteInFileInZip(get_zip_file()->m_pfZip,mem.get_data(),(u32)uRead);

      }

      zipCloseFileInZip(get_zip_file()->m_pfZip);

   }


   ::file::listing & in_file::ls(::file::listing & listing)
   {

      in_file infile = *this;

      unzFile pf = infile.get_zip_file()->m_pfUnzip;
      string str;
      string wstrFolder;
      string_array wstraFolder;

      unz_file_info fi;

      if(pf != nullptr)
      {

         while(true)
         {

            char szTitle[_MAX_PATH];

            unzGetCurrentFileInfo(
            pf,
            &fi,
            szTitle,
            _MAX_PATH,
            nullptr, // extra Field
            0,
            nullptr, // comment
            0);
            
            string strTitle(szTitle);

            if(listing.m_bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
            {

               listing.add(::file::path(strTitle));

               listing.last().m_iDir = ::str::ends(szTitle,"/") || ::str::ends(szTitle,"\\") || ::str::ends(szTitle,".zip");

               listing.last().m_iSize = fi.uncompressed_size;

            }

            if(unzGoToNextFile(pf) != UNZ_OK)
            {

               break;

            }

         }

      }

      return listing;

   }


   ::file::listing & in_file::ls_relative_name(::file::listing & listing)
   {

      in_file infile = *this;

      unzFile pf = infile.get_zip_file()->m_pfUnzip;
      string str;
      string wstrFolder;
      string_array wstraFolder;

      unz_file_info fi;

      if (pf != nullptr)
      {

         while (true)
         {

            char szTitle[_MAX_PATH];

            unzGetCurrentFileInfo(
            pf,
            &fi,
            szTitle,
            _MAX_PATH,
            nullptr, // extra Field
            0,
            nullptr, // comment
            0);
            
            string strTitle(szTitle);

            if (listing.m_bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
            {

               listing.add(::file::path(strTitle));

               listing.last().m_iDir = ::str::ends(szTitle, "/") || ::str::ends(szTitle, "\\") || ::str::ends(szTitle, ".zip");

               listing.last().m_iSize = fi.uncompressed_size;

            }

            if (unzGoToNextFile(pf) != UNZ_OK)
            {

               break;

            }

         }

      }

      return listing;

   }


   ::file::listing & in_file::perform_file_listing(::file::listing & listing)
   {

      return ls(listing);

   }

   ::file::listing & in_file::perform_file_relative_name_listing(::file::listing & listing)
   {

      return ls_relative_name(listing);

   }


} // namespace zip
