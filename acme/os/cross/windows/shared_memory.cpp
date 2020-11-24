#include "framework.h"
#include "acme/os/_c.h"
#include "acme/os/_.h"

#ifndef _UWP

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#undef USE_MISC



#ifdef LINUX

#include <unistd.h>

extern "C" int mkostemps64 (char *__template, int __suffixlen, int __flags);
#define mkostemps mkostemps64
#endif

#ifdef ANDROID
/*

@deftypefn Replacement int mkstemps (char *@payload{pattern}, int @payload{suffix_len})

Generate a unique temporary file name from @payload{pattern}.
@payload{pattern} has the form:

@example
@payload{path}/ccXXXXXX@payload{suffix}
@end example

@payload{suffix_len} tells us how long @payload{suffix} is (it can be zero
length).  The last six characters of @payload{pattern} before @payload{suffix}
must be @samp{XXXXXX}; they are replaced with a string that makes the
filename unique.  Returns a file descriptor open on the file for
reading and writing.

@end deftypefn

*/


int
mkstemps(char *pattern, int suffix_len)
{
   static const char letters[]
      = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   static u64 value;
//#ifdef HAVE_GETTIMEOFDAY
   struct timeval tv;
//#endif
   char *XXXXXX;
   size_t len;
   int count;

   len = strlen(pattern);

   if ((int)len < 6 + suffix_len
         || ansi_count_compare(&pattern[len - 6 - suffix_len], "XXXXXX", 6))
   {
      return -1;
   }

   XXXXXX = &pattern[len - 6 - suffix_len];

//#ifdef HAVE_GETTIMEOFDAY
   /* Get some more or less random data.  */
   gettimeofday(&tv, nullptr);
   value += ((u64)tv.tv_usec << 16) ^ tv.tv_sec ^ getpid();
//#else
//   value += getpid();
//#endif

   for (count = 0; count < TMP_MAX; ++count)
   {
      u64 v = value;
      int fd;

      /* Fill in the random bits.  */
      XXXXXX[0] = letters[v % 62];
      v /= 62;
      XXXXXX[1] = letters[v % 62];
      v /= 62;
      XXXXXX[2] = letters[v % 62];
      v /= 62;
      XXXXXX[3] = letters[v % 62];
      v /= 62;
      XXXXXX[4] = letters[v % 62];
      v /= 62;
      XXXXXX[5] = letters[v % 62];

      fd = open(pattern, O_BINARY | O_RDWR | O_CREAT | O_EXCL, 0600);
      if (fd >= 0)
         /* The file does not exist.  */
         return fd;
      if (errno != EEXIST
#ifdef EISDIR
            && errno != EISDIR
#endif
         )
         /* Fatal error (EPERM, ENOSPC etc).  Doesn't make sense to loop.  */
         break;

      /* This is a random value.  It is only necessary that the next
      TMP_MAX values generated by adding 7777 to VALUE are different
      with (module 2^32).  */
      value += 7777;
   }

   /* We return the null string if we can't find a unique file name.  */
   pattern[0] = '\0';
   return -1;
}

#endif


HGLOBAL WINAPI GlobalAlloc(::u32 uFlags, SIZE_T dwBytes)
{

   i32 result;


   HGLOBAL hglobal = new struct hglobal();

   strcpy(hglobal->m_szFile, "/ca2/time/global_alloc/XXXXXX.mmap");

#if defined(__APPLE__) || defined(ANDROID)

   hglobal->m_fd = mkstemps(hglobal->m_szFile, 5);

#else

   hglobal->m_fd = mkostemps(hglobal->m_szFile, 5, O_RDWR | O_CREAT | O_TRUNC);

#endif

   /* Open a file for writing.
    *  - Creating the file if it doesn't exist.
    *  - Truncating it to 0 size if it already exists. (not really needed)
    *
    * Note: "O_WRONLY" mode is not sufficient when mmaping.
    */
//    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
   if(hglobal->m_fd == -1)
   {
      //perror("Error opening file for writing");
      //exit(EXIT_FAILURE);
      delete hglobal;
      return nullptr;
   }

   /* Stretch the file size to the size of the (mmapped) array of ints
    */
   result = ftruncate(hglobal->m_fd, dwBytes);
   if(result == -1)
   {
      close(hglobal->m_fd);
      //perror("Error calling lseek() to 'stretch' the file");
      //exit(EXIT_FAILURE);
      delete hglobal;
      return nullptr;
   }

   /* Something needs to be written at the end of the file to
    * have the file actually have the new size.
    * Just writing an empty string at the current file position will do.
    *
    * Note:
    *  - The current position in the file is at the end of the stretched
    *    file due to the call to lseek().
    *  - An empty string is actually a single '\0' character, so a zero-byte
    *    will be written at the last byte of the file.
    */
   /*result = write(hglobal->m_fd, "", 1);
   if(result != 1)
   {
      close(hglobal->m_fd);
   //    perror("Error writing last byte of the file");
    //  exit(EXIT_FAILURE);
      delete hglobal;
      return nullptr;
   } */

   hglobal->m_map = nullptr;

   return hglobal;

}


HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hglobal, SIZE_T dwBytes, ::u32 uFlags)
{

   i32 result = ftruncate(hglobal->m_fd, dwBytes);
   if(result == -1)
   {
      close(hglobal->m_fd);
      //perror("Error calling lseek() to 'stretch' the file");
      //exit(EXIT_FAILURE);
      delete hglobal;
      return nullptr;
   }

   return hglobal;

}


HGLOBAL WINAPI GlobalFree(HGLOBAL hglobal)
{

   close(hglobal->m_fd);
   unlink(hglobal->m_szFile);
   delete hglobal;

   return nullptr;

}


LPVOID WINAPI GlobalLock(HGLOBAL hglobal)
{

   if(hglobal->m_map != nullptr)
      return hglobal->m_map;

   /* Now the file is ready to be mmapped.
     */
   hglobal->m_map = mmap(0, ::get_file_size(hglobal->m_fd), PROT_READ | PROT_WRITE, MAP_SHARED, hglobal->m_fd, 0);

   if(hglobal->m_map == MAP_FAILED)
   {
      //perror("Error mmapping the file");
      //exit(EXIT_FAILURE);
      return nullptr;
   }

   return hglobal->m_map;

}


SIZE_T WINAPI GlobalSize(HGLOBAL hglobal)
{

   struct stat st;

   fstat(hglobal->m_fd, &st);

   return st.st_size;

}


int_bool WINAPI GlobalUnlock(HGLOBAL hglobal)
{

   if(hglobal->m_map == nullptr)
      return FALSE;

   if (munmap(hglobal->m_map, ::get_file_size(hglobal->m_fd)) == -1)
   {
      //perror("Error un-mmapping the file");
      /* Decide here whether to close(fd) and exit() or not. Depends... */
      return FALSE;
   }

   return TRUE;

}




#endif


