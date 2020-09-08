#pragma once

//#include "file_stream.h"

namespace file
{

   class exception;
   class file;

} // namespace

enum e_set_version
{

   set_version,

};


//class CLASS_DECL_AQUA stream :
//   virtual public stream
//{
//public:
//
//
//   bool              m_b64bit;
//
//
//   stream(stream & stream);
//   stream(e_set_version = set_version, index iVersion = FIRST_VERSION);
//   stream(::file::file * pfile, index iVersion = FIRST_VERSION);
//   stream(e_create_new, ::object * pobject, index iVersion = FIRST_VERSION);
//   virtual ~stream();
//
//
//   //stream & operator = (const stream & stream);
//
//   virtual bool is_stream_null();
//   virtual bool is_stream_set();
//
//   virtual void close();
//
//   virtual filesize get_position() const;
//
////      void read(i32 & i);
////      void read(u32 & ui);
////      void read(i64 & i);
////      void read(u64 & ui);
//
//   using stream::read;
//   virtual stream & read (bool & b) override;
//   virtual stream & read (char & ch) override;
//   virtual stream & read (unsigned char & uch) override;
//#ifdef WINDOWS
//   virtual stream & read (unichar & wch) override;
//#endif
//   virtual stream & read(i8 & I) override;
//   virtual stream & read (i16 & sh) override;
//   virtual stream & read (u16 & ui) override;
//   virtual stream & read (i32 & i) override;
//   virtual stream & read (u32 & ui) override;
//   virtual stream & read (i64 & i) override;
//   virtual stream & read (u64 & ui) override;
//   virtual stream & read (float & f) override;
//   virtual stream & read (double & d) override;
//   virtual stream & read(POINT * ppoint) ;
//   virtual stream & read(SIZE * psize) ;
//   virtual stream & read (RECT * prect) ;
//
//   virtual stream & read (string & str) override;
//
//   virtual string get_location() const;
//
//   void full_load(string & str);
//
//   using stream::write;
//   virtual stream & write(char ch) override;
//   virtual stream & write(uchar uch) override;
//   virtual stream & write(i8 i) override;
//   virtual stream & write (i16 sh) override;
//   virtual stream & write (u16 ui) override;
//#ifdef WINDOWS
//   virtual stream & write (unichar wch) override;
//#endif
//   virtual stream & write (bool b) override;
//   virtual stream & write (i32 i) override;
//   virtual stream & write (u32 ui) override;
//   virtual stream & write (i64 i) override;
//   virtual stream & write (u64 ui) override;
//   virtual stream & write (float f) override;
//   virtual stream & write (double d) override;
//   virtual stream & write(const POINT * ppoint);
//   virtual stream & write(const SIZE * psize) ;
//   virtual stream & write (const RECT * prect) ;
//   virtual stream & write (const char * psz) override;
//   virtual stream & write (const string & str) override;
//
//   virtual void write_from_hex(const char * psz, strsize iLen = -1);
//   virtual void write_from_hex(const string & str);
//
//};








//class CLASS_DECL_AQUA reader :
//   virtual public stream
//{
//public:
//
//
//   reader(reader && reader);
//   reader(::object * pobject, index iVersion = FIRST_VERSION);
//   reader(::file::file * pfile, index iVersion = FIRST_VERSION);
//   virtual ~reader();
//
//
//   virtual bool is_storing();
//
//
//};
//
//
//class CLASS_DECL_AQUA writer :
//   virtual public stream
//{
//public:
//
//
//   writer(writer && writer);
//   writer(::object * pobject, index iVersion = FIRST_VERSION);
//   writer(::file::file * pfile, index iVersion = FIRST_VERSION);
//   virtual ~writer();
//
//
//   virtual bool is_storing();
//
//
//};


//class CLASS_DECL_AQUA memory_reader :
//   virtual public reader
//{
//public:
//
//
//   memory_reader(memory_reader && reader);
//   memory_reader(::object * pobject, index iVersion = FIRST_VERSION);
//   virtual ~memory_reader();
//
//
//   memory & get_memory();
//
//
//};


//class CLASS_DECL_AQUA memory_writer :
//   virtual public writer
//{
//public:
//
//
//   memory_writer(memory_writer && writer);
//   memory_writer(::object * pobject, index iVersion = FIRST_VERSION);
//   virtual ~memory_writer();
//
//
//   memory & get_memory();
//
//
//};

