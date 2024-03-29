#ifndef _ELF_LOADER_EXTENSION_H

#include <sys/stat.h>

enum {
  BLOB_PUTS = 0,
  BLOB_STRCMP = 1,
  BLOB_STRLEN = 2,
  BLOB_FOPEN = 3,
  BLOB_FCLOSE = 4,
  BLOB_TIMESPEC_GET = 5,
  BLOB_PRINT_DIFFTIME = 6,
  BLOB_MALLOC = 7,
  BLOB_MEMSET = 8,
  BLOB_FREE = 9,
  BLOB_MEMMOVE = 10,
  BLOB_MEMCPY = 11,
  BLOB_STRSTR = 12,
  BLOB_MEMCMP = 13,
  BLOB_STRTOL = 14,
  BLOB_QSORT = 15,
  BLOB_STRNCPY = 16,
  BLOB_STRRCHR = 17,
  BLOB_STRCAT = 18,
  BLOB_GETENV = 19,
  BLOB_STRNCMP = 20,
  BLOB_STRCPY = 21,
  BLOB_MEMCHR = 22,
  BLOB_REALLOC = 23,
  BLOB_MUNMAP = 24,
  BLOB_OPEN = 25,
  BLOB_FSTAT = 26,
  BLOB_MMAP = 27,
  BLOB_READ = 28,
  BLOB___ERRNO_LOCATION = 29,
  BLOB_REMOVE = 30,
  BLOB_FERROR = 31,
  BLOB_FPUTS = 32,
  BLOB_STRERROR = 33,
  BLOB_FREAD = 34,
  BLOB_FLOOR = 35,
  BLOB_GMTIME = 36,
  BLOB_FREXP = 37,
  BLOB_MODF = 38,
  BLOB_POW = 39,
  BLOB_CLOSE = 40,
  BLOB_FPUTC = 41,
  BLOB_ABORT = 42,
  BLOB_FFLUSH = 43,
  BLOB_ATOF = 44,
  BLOB_FWRITE = 45,
  BLOB__SETJMP = 46,
  BLOB_LONGJMP = 47,
  BLOB_FCNTL = 48,
  BLOB_PRINTF = 49,
  BLOB_SPRINTF = 50,
  BLOB_FPRINTF = 51,
  BLOB_STPCPY = 52,
  BLOB_CALLOC = 53,
  BLOB_STRTOD = 54
};

#endif // _ELF_LOADER_EXTENSION_H
