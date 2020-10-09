#pragma once


class CLASS_DECL_APEX file_context :
   virtual public object
{
public:


   file_context();
   virtual ~file_context();

   
   virtual ::estatus initialize(::layered * pobjectContext) override;




   virtual ::estatus init_system();
   virtual ::estatus init_context();
   
   virtual ::estatus update_module_path();


   virtual ::status::result copy(var varTarget, var varSource, bool bFailIfExists = false, e_extract eextract = extract_first);
   virtual ::status::result move(const ::file::path & pszNew, const ::file::path & psz);
   virtual ::status::result del(const ::file::path & psz);
   virtual ::file::path duplicate(const ::file::path & psz);
   virtual ::file::path paste(const ::file::path & pszLocation, const ::file::path & path);
   virtual ::status::result rename(const ::file::path & pszNew, const ::file::path & psz);

   virtual void trash_that_is_not_trash(const ::file::path & psz);
   virtual void trash_that_is_not_trash(::file::patha & stra);

   virtual bool get_status(const ::file::path & path, ::file::file_status & status);
   virtual ::status::result set_status(const ::file::path & path, const ::file::file_status & status);

   virtual ::status::result replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);

   //virtual bool exists(::file::path path);

   virtual bool is_file_or_dir(const ::file::path & path, var * pvarQuery, ::file::e_type * petype);
   virtual bool is_file_or_dir(const ::file::path & pszPath, ::file::e_type * petype = nullptr);


   virtual var length(const ::file::path & path);

   virtual var length(const ::file::path & path, var * pvarQuery);

   virtual ::file::path module();

   virtual ::file::path ca2module();

   ::file::path time(const ::file::path & pszBasePath, i32 iDepth = 0, const string & pszPrefix = nullptr, const string & pszSuffix = nullptr, bool bTryDelete = false);
   ::file::path time_square(const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);
   ::file::path time_log(const string & pszId);

   virtual file_pointer time_square_file(const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);
   virtual file_pointer get(const ::file::path & name);


   template < class T >
   string time_square(T * p, bool (T:: * pfnOutput)(::stream &, const ::file::path &), const ::file::path & pszSource)
   {

      string strTime = time_square(p);

      if (strTime.has_char())
      {

         if (!output(strTime, p, pfnOutput, pszSource))
         {

            return "";

         }

      }

      return strTime;

   }


   template < typename TYPE >
   inline ::estatus binary_get(const ::var & varFile, TYPE & t)
   {

      auto preader = get_reader(varFile);

      if (!preader)
      {

         return preader.m_estatus;

      }

      binary_stream stream(preader);

      stream.defer_set_loading();

      stream.exchange(::id::type_null, t);

      return stream.fail() ? ::error_failed : ::success;

   }

   template < typename TYPE >
   inline ::estatus binary_set(const ::var & varFile, const TYPE & t)
   {

      auto pwriter = get_writer(varFile);

      if (!pwriter)
      {

         return pwriter.m_estatus;

      }

      binary_stream stream(pwriter);

      stream.defer_set_storing();

      stream.exchange(::id::type_null, t);

      return stream.fail() ? ::error_failed : ::success;

   }


   virtual i32 filterex_time_square(const char * pszPrefix, ::file::patha & stra);
   virtual bool try_create_file(const ::file::path & path, bool bTryDelete);

   virtual var as_json(const var & varFile);
   virtual string as_string(const var & varFile);
   virtual bool as_memory(const var & varFile, memory_base & mem);

   virtual void lines(string_array & stra, const var & varFile);
   virtual void put_lines(const var & varFile, const string_array & stra);
   virtual void put_lines_utf8(const var & varFile, const string_array & stra);
   virtual void _put_lines(::file::file * pfile, const string_array & stra);

   virtual bool put_contents(const var & varFile, const void * pvoidContents, ::count count);
   virtual bool put_contents(const var & varFile, const char * pcszContents);

   virtual bool put_contents(const var & varFile, ::file::file * pfile);
   virtual bool put_contents(const var & varFile, memory & mem);
   virtual bool put_contents_utf8(const var & varFile, const char * pcszContents);


   virtual bool add_contents(const var & varFile, const void * pvoidContents, ::count count);
   virtual bool add_contents(const var & varFile, const char * pcszContents);


   virtual bool is_read_only(const ::file::path & psz);

   virtual ::file::path sys_temp(const ::file::path & lpszName, const char * pszExtension);
   virtual ::file::path sys_temp_unique(const ::file::path & lpszName);


   virtual ::file::path replace_extension(const ::file::path & pszFile, const char * pszExtension);
   virtual void set_extension(::file::path & str, const char * pszExtension);


   virtual void normalize(string & str);
   virtual i32 cmp(const ::file::path & psz1, const ::file::path & psz2);

   virtual string get_hash(const var& varFile, enum_hash ehash);

   //virtual string md5(::file::file * pfile);
   virtual string md5(const var & varFile);

   //virtual string nessie(::file::file * pfile);
   virtual string nessie(const var & varFile);

   virtual bool resolve_link(::file::path & pathTarget, const string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr);

   virtual bool is_link(string strPath);

   virtual bool get_last_write_time(FILETIME * pfiletime, const string & strFilename);

   //virtual void dtf(const ::file::path & pszFile, const ::file::path & pszDir);

   //virtual void dtf(const ::file::path & pszFile, ::file::patha & stra);

   //virtual void ftd(const ::file::path & pszDir, const ::file::path & pszFile);

   // 'n' (natural) terminated ascii number, example: 245765487n
   // pmd5ctx = openssl/md5.h's MD5_CTX
   //virtual void write_n_number(::file::file * pfile, void * pmd5ctx, i64 iNumber);
   //virtual void read_n_number(::file::file * pfile, void * pmd5ctx, i64 & iNumber);

   //virtual void write_gen_string(::file::file * pfile, void * pmd5ctx, string & str);
   //virtual void read_gen_string(::file::file * pfile, void * pmd5ctx, string & str);

   virtual ::file_result file_get_file(::file::path path, const efileopen & eopen);

   virtual ::file_result data_get_file(string strData, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

   virtual ::file_result zip_get_file(::file::file * pfile, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

   virtual ::file_result http_get_file(const var & varFile, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

   virtual ::file_result get_file(const var & varFile, const efileopen & eopen);

   virtual ::file_result get_reader(const var & varFile, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

   virtual ::file_result shared_reader(const var & varFile, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

   virtual ::file_result get_writer(const var & varFile, const efileopen & eopen = ::file::mode_write | ::file::mode_create | ::file::mode_no_truncate | ::file::defer_create_directory | ::file::type_binary);

   virtual bool post_output(::file::path pathOut, ::file::path pathDownloading);

   template < typename T >
   bool output(::file::file * pfileOut, T * p, bool (T:: * pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn);

   virtual bool transfer(::file::file * pfileOut, ::file::file * pfileIn);

   virtual ::file::path dropbox_info_json();


   virtual ::file::path onedrive_global_ini();
   virtual ::file::path onedrive_cid_ini();

//   virtual ::status::result copy(var varTarget, var varSource, bool bFailIfExists = false, e_extract eextract = extract_first);
   //virtual ::status::result move(const ::file::path & pszNew, const ::file::path & psz);
   //virtual ::status::result del(const ::file::path & psz);
   //virtual ::status::result rename(const ::file::path & pszNew, const ::file::path & psz);


   //virtual void trash_that_is_not_trash(const ::file::path & psz);
   //virtual void trash_that_is_not_trash(::file::patha & stra);


   //virtual ::status::result replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);

  virtual bool exists(const ::file::path & pszPath);


  // virtual var length(const ::file::path & pszPath);


   //::file::path time(const ::file::path & pszBasePath, i32 iDepth = 1, const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);


   //virtual file_pointer time_square_file(const char * pszPrefix = nullptr, const char * pszSuffix = nullptr);
   //virtual file_pointer get(const ::file::path & name);



   inline ::memory as_primitive_memory(const var & varFile) { ::memory m; as_memory(varFile, m); return m; }
   inline ::memory as_memory(const var & varFile) { return as_primitive_memory(varFile); }


   template < class OBJECT >
   ::estatus put(const var & varFile, OBJECT & a)
   {

      auto writer = get_writer(varFile);

      *writer << a;

      return writer.m_estatus;

   }


   template < class OBJECT >
   ::estatus as(OBJECT & a, const var & varFile)
   {

      auto reader = get_reader(varFile);

      *reader >> a;

      return reader.m_estatus;

   }


   template < class ARRAY >
   bool to_array(ARRAY & a, const var & varFile)
   {

      auto pfile = get_reader(varFile);

      ::binary_stream s(pfile);

      __exchange_array(a, s);

      return !s.fail();

   }


   //virtual void lines(string_array & stra, const var & varFile);
   //virtual void put_lines(const var & varFile, const string_array & stra);

   //virtual bool put_contents(const var & varFile, const void * pvoidContents, ::count count);
   //virtual bool put_contents(const var & varFile, const char * pcszContents);

   //virtual bool copy?(const var & varFile, const ::stream & stream);
   //virtual bool put_contents(const var & varFile, memory & mem);
   //virtual bool put_contents_utf8(const var & varFile, const char * pcszContents);


   //virtual bool add_contents(const var & varFile, const char * pcszContents);


   string sys_temp(const char * lpszName, const char * pszExtension);


   //virtual ::file_result get_file(const var & varFile, UINT nOpenFlags);


   //virtual bool is_read_only(const ::file::path & psz);

   inline auto open_for_reading(const var & varFile, UINT nOpenFlags = ::file::type_binary)
   {

      return get_file(varFile, nOpenFlags | ::file::mode_read);

   }

   inline auto create_for_writing(const var & varFile, UINT nOpenFlags = ::file::type_binary | ::file::defer_create_directory)
   {

      return get_file(varFile, nOpenFlags | ::file::mode_create | ::file::mode_write);

   }


   // get a file and if there are exceptions, should show end user friendly messages
   virtual rp(::file::file) friendly_get_file(const var & varFile, UINT nOpenFlags);


   //void dtf(const ::file::path & pszFile, const ::file::path & pszDir);
   void dtf(const ::file::path & pszFile, ::file::patha & stra, ::file::patha & straRelative);
   //void ftd(const ::file::path & pszDir, const ::file::path & pszFile);


   virtual bool crypto_set(const var & varFile, const char * pszData, const char * pszSalt);
   virtual bool crypto_get(const var & varFile, string & str, const char * pszSalt);


   template < typename TYPE >
   bool save(const var & varFile, const TYPE & o)
   {

      return put(varFile, o);
   }


   template < typename TYPE >
   inline bool load(TYPE & o, const var & varFile)
   {

      return as(o, varFile);

   }


   virtual bool save_lines(const var & varFile, string_array & stra);
   virtual bool load_lines(string_array & stra, const var & varFile);



   virtual bool touch(const ::file::path & path);

   //virtual string md5(const var & varFile);

   //virtual string nessie(const var & varFile);

   //virtual ::file::path dropbox_info_json();

   //virtual ::file::path onedrive_global_ini();

   //virtual ::file::path onedrive_cid_ini();


};



