#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <setjmp.h>
#include <time.h>
#include <resolv.h>

#include "interface.h"

#define DEFAULT_FONT "./fonts/AmaticSC-Regular.ttf"
#define DEFAULT_TEXT "Hello world!"
#define DEFAULT_IMAGE_NAME "hello.png"

#if defined(BLOB)

#include <sys/stat.h>

FILE* stderr;
void** global_funcs;


int puts(const char* __str) {
  typedef int (*puts_type)(const char*);
  return ((puts_type)global_funcs[BLOB_PUTS])(__str);
}

int strcmp(const char* __lhs, const char* __rhs) {
  typedef int (*strcmp_type)(const char*, const char*);
  return ((strcmp_type)global_funcs[BLOB_STRCMP])(__lhs, __rhs);
}

size_t strlen(const char* __str) {
  typedef size_t (*strlen_type)(const char*);
  return ((strlen_type)global_funcs[BLOB_STRLEN])(__str);
}

FILE* fopen(const char* __filename, const char* __mode) {
  typedef FILE* (*fopen_type)(const char*, const char*);
  return ((fopen_type)global_funcs[BLOB_FOPEN])(__filename, __mode);
}

int fclose(FILE* __stream) {
  typedef int (*fclose_type)(FILE*);
  return ((fclose_type)global_funcs[BLOB_FCLOSE])(__stream);
}

int timespec_get(struct timespec* __tm, int __base) {
  typedef int (*timespec_get_type)(struct timespec*, int);
  return ((timespec_get_type)global_funcs[BLOB_TIMESPEC_GET])(__tm, __base);
}

void print_difftime(struct timespec* __start, struct timespec* __finish) {
  typedef void (*print_difftime_type)(struct timespec*, struct timespec*);
  ((print_difftime_type)global_funcs[BLOB_PRINT_DIFFTIME])(__start, __finish);
}

void __stack_chk_fail(void) { }

void* malloc(size_t __size) {
  typedef void* (*malloc_type)(size_t);
  return ((malloc_type)global_funcs[BLOB_MALLOC])(__size);
}

void* memset(void* __dest, int __ch, size_t __size) {
  typedef void* (*memset_type)(void*, int, size_t);
  return ((memset_type)global_funcs[BLOB_MEMSET])(__dest, __ch, __size);
}

void free(void* __ptr) {
  typedef void (*free_type)(void*);
  return ((free_type)global_funcs[BLOB_FREE])(__ptr);
}

void* memmove(void* __dest, const void* __src, size_t __count) {
  typedef void* (*memmove_type)(void*, const void*, size_t);
  return ((memmove_type)global_funcs[BLOB_MEMMOVE])(__dest, __src, __count);
}

void* memcpy(void* __dest, const void* __src, size_t __count) {
  typedef void* (*memcpy_type)(void*, const void*, size_t);
  return ((memcpy_type)global_funcs[BLOB_MEMCPY])(__dest, __src, __count);
}

char* strstr(const char* __str, const char* __substr) {
  typedef char* (*strstr_type)(const char*, const char*);
  return ((strstr_type)global_funcs[BLOB_STRSTR])(__str, __substr);
}

int memcmp(const void* __lhs, const void* __rhs, size_t __count) {
  typedef int (*memcmp_type)(const void*, const void*, size_t);
  return ((memcmp_type)global_funcs[BLOB_MEMCMP])(__lhs, __rhs, __count);
}

long strtol(const char* __str, char** __str_end, int __base) {
  typedef long (*strtol_type)(const char*, char**, int);
  return ((strtol_type)global_funcs[BLOB_STRTOL])(__str, __str_end, __base);
}

void
qsort(
  void* __ptr,
  size_t __count,
  size_t __size,
  int(*__comp)(const void*, const void*)
) {
  typedef void (*qsort_type)(void*, size_t, size_t,
      int (*)(const void*, const void*)
  );
  return ((qsort_type)global_funcs[BLOB_QSORT])(__ptr, __count, __size, __comp);
}

char* strncpy(char* __dest, const char* __src, size_t __count) {
  typedef char* (*strncpy_type)(char*, const char*, size_t);
  return ((strncpy_type)global_funcs[BLOB_STRNCPY])(__dest, __src, __count);
}

char* strrchr(const char* __str, int __ch) {
  typedef char* (*strrchr_type)(const char*, int);
  return ((strrchr_type)global_funcs[BLOB_STRRCHR])(__str, __ch);
}

char* strcat(char* __dest, const char* __src) {
  typedef char* (*strcat_type)(char*, const char*);
  return ((strcat_type)global_funcs[BLOB_STRCAT])(__dest, __src);
}

char* getenv(const char* __name) {
  typedef char* (*getenv_type)(const char*);
  return ((getenv_type)global_funcs[BLOB_GETENV])(__name);
}

int strncmp(const char* __lhs, const char* __rhs, size_t __size) {
  typedef int (*strncmp_type)(const char*, const char*, size_t);
  return ((strncmp_type)global_funcs[BLOB_STRNCMP])(__lhs, __rhs, __size);
}

char* strcpy(char* __dest, const char* __src) {
  typedef char* (*strcpy_type)(char*, const char*);
  return ((strcpy_type)global_funcs[BLOB_STRCPY])(__dest, __src);
}

void* memchr(const void* __ptr, int __ch, size_t __count) {
  typedef void* (*memchr_type)(const void*, int, size_t);
  return ((memchr_type)global_funcs[BLOB_MEMCHR])(__ptr, __ch, __count);
}

void* realloc(void* __ptr, size_t __new_size) {
  typedef void* (*realloc_type)(void*, size_t);
  return ((realloc_type)global_funcs[BLOB_REALLOC])(__ptr, __new_size);
}

int munmap(void* __start, size_t __length) {
  typedef int (*munmap_type)(void*, size_t);
  return ((munmap_type)global_funcs[BLOB_MUNMAP])(__start, __length);
}

int open(const char* __pathname, int __flags) {
  typedef int (*open_type)(const char*, int);
  return ((open_type)global_funcs[BLOB_OPEN])(__pathname, __flags);
}

int fstat(int __fd, struct stat* __buff) {
  typedef int (*fstat_type)(int, struct stat*);
  return ((fstat_type)global_funcs[BLOB_FSTAT])(__fd, __buff);
}

void*
mmap(
  void* __addr,
  size_t __length,
  int __prot,
  int __flags,
  int __fd,
  off_t __offset
) {
  typedef void* (*mmap_type)(void*, size_t, int, int, int, off_t);
  return ((mmap_type)global_funcs[BLOB_MMAP])(
    __addr,
    __length,
    __prot,
    __flags,
    __fd,
    __offset
  );
}

ssize_t read(int __fd, void* __buff, size_t __count) {
  typedef ssize_t (*read_type)(int, void*, size_t);
  return ((read_type)global_funcs[BLOB_READ])(__fd, __buff, __count);
}

int* __errno_location(void) {
  typedef int* (*__errno_location_type)(void);
  return ((__errno_location_type)global_funcs[BLOB___ERRNO_LOCATION])();
}

int remove(const char* __filename) {
  typedef int (*remove_type)(const char*);
  return ((remove_type)global_funcs[BLOB_REMOVE])(__filename);
}

int ferror(FILE* __stream) {
  typedef int (*ferror_type)(FILE*);
  return ((ferror_type)global_funcs[BLOB_FERROR])(__stream);
}

int fputs(const char* __str, FILE* __stream) {
  typedef int (*fputs_type)(const char*, FILE*);
  return ((fputs_type)global_funcs[BLOB_FPUTS])(__str, __stream);
}

char* strerror(int __errnum) {
  typedef char* (*strerror_type)(int);
  return ((strerror_type)global_funcs[BLOB_STRERROR])(__errnum);
}

size_t fread(void* __buffer, size_t __size, size_t __count, FILE* __stream) {
  typedef size_t (*fread_type)(void*, size_t, size_t, FILE*);
  return ((fread_type)global_funcs[BLOB_FREAD])(
    __buffer,
    __size,
    __count,
    __stream
  );
}

double floor(double __arg) {
  typedef double (*floor_type)(double);
  return ((floor_type)global_funcs[BLOB_FLOOR])(__arg);
}

struct tm* gmtime(const time_t* __timer) {
  typedef struct tm* (*gmtime_type)(const time_t*);
  return ((gmtime_type)global_funcs[BLOB_GMTIME])(__timer);
}

double frexp(double __arg, int* __exp) {
  typedef double (*frexp_type)(double, int*);
  return ((frexp_type)global_funcs[BLOB_FREXP])(__arg, __exp);
}

double modf(double __arg, double* __iptr) {
  typedef double (*modf_type)(double, double*);
  return ((modf_type)global_funcs[BLOB_MODF])(__arg, __iptr);
}

double pow(double __base, double __exp) {
  typedef double (*pow_type)(double, double);
  return ((pow_type)global_funcs[BLOB_POW])(__base, __exp);
}

int close(int __fd) {
  typedef int (*close_type)(int);
  return ((close_type)global_funcs[BLOB_CLOSE])(__fd);
}

int fputc(int __ch, FILE* __stream) {
  typedef int (*fputc_type)(int, FILE*);
  return ((fputc_type)global_funcs[BLOB_FPUTC])(__ch, __stream);
}

_Noreturn void abort(void) {
  typedef _Noreturn void (*abort_type)(void);
  ((abort_type)global_funcs[BLOB_ABORT])();
}

int fflush(FILE* __stream) {
  typedef int (*fflush_type)(FILE*);
  return ((fflush_type)global_funcs[BLOB_FFLUSH])(__stream);
}

double atof(const char* __str) {
  typedef double (*atof_type)(const char*);
  return ((atof_type)global_funcs[BLOB_ATOF])(__str);
}

size_t
fwrite(
  const void* __buff,
  size_t __size,
  size_t __count,
  FILE* __stream
) {
  typedef size_t (*fwrite_type)(const void*, size_t, size_t, FILE*);
  return ((fwrite_type)global_funcs[BLOB_FWRITE])(
    __buff,
    __size,
    __count,
    __stream
  );
}

int _setjmp(struct __jmp_buf_tag __env[1]) {
  typedef int (*_setjmp_type)(struct __jmp_buf_tag[1]);
  return ((_setjmp_type)global_funcs[BLOB__SETJMP])(__env);
}

_Noreturn void longjmp(struct __jmp_buf_tag __env[1], int __status) {
  typedef _Noreturn void (*longjmp_type)(struct __jmp_buf_tag[1], int);
  ((longjmp_type)global_funcs[BLOB_LONGJMP])(__env, __status);
}

int fcntl(int __fd, int __cmd, ...) {
  typedef int (*fcntl_type)(int, int, ...);
  int __res;
  va_list __args;
  va_start(__args, __cmd);
  __res = ((fcntl_type)global_funcs[BLOB_FCNTL])(__fd, __cmd, __args);
  va_end(__args);
  return __res;
}

int printf(const char* __fmt, ...) {
  typedef int (*printf_type)(const char*, ...);
  int __res;
  va_list __args;
  va_start(__args, __fmt);
  __res = ((printf_type)global_funcs[BLOB_PRINTF])(__fmt, __args);
  va_end(__args);
  return __res;
}

int sprintf(char* __buffer, const char* __fmt, ...) {
  typedef int (*sprintf_type)(char*, const char*, ...);
  int __res;
  va_list __args;
  va_start(__args, __fmt);
  __res = ((sprintf_type)global_funcs[BLOB_SPRINTF])(__buffer, __fmt, __args);
  va_end(__args);
  return __res;
}

int fprintf(FILE* __stream, const char* __fmt, ...) {
  typedef int (*fprintf_type)(FILE*, const char*, ...);
  int __res;
  va_list __args;
  va_start(__args, __fmt);
  __res = ((fprintf_type)global_funcs[BLOB_FPRINTF])(__stream, __fmt, __args);
  va_end(__args);
  return __res;
}

char* stpcpy(char* restrict __dest, const char* restrict __src) {
  typedef char* (*stpcpy_type)(char*, const char*);
  return ((stpcpy_type)global_funcs[BLOB_STPCPY])(__dest, __src);
}

void* calloc(size_t __num, size_t __size) {
  typedef void* (*calloc_type)(size_t, size_t);
  return ((calloc_type)global_funcs[BLOB_CALLOC])(__num, __size);
}

double strtod(const char* restrict __str, char** restrict __str_end) {
  typedef double (*strtod_type)(const char* restrict, char** restrict);
  return ((strtod_type)global_funcs[BLOB_STRTOD])(__str, __str_end);
}

#endif // BLOB


void usage(void) {
  printf("Usage: text2png.out"
    " [--font FONT_FILE_PATH]"
    " [--out OUTPUT_PNG_PATH]"
    " [--text INPUT_TEXT]\n");
}

#if defined(BLOB)

int blob_entry(
    const int argc,
    const char** argv,
    void** funcs,
    struct timespec* start_time
) {

  global_funcs = funcs;

#else

int main(const int argc, const char** argv) {

#endif // BLOB

  struct timespec __start;
  struct timespec __finish;

#if defined(BLOB)

  __start.tv_sec = start_time->tv_sec;
  __start.tv_nsec = start_time->tv_nsec;

#else

  timespec_get(&__start, TIME_UTC);

#endif

  const char* __font = DEFAULT_FONT;
  const char* __text = DEFAULT_TEXT;
  const char* __image_name = DEFAULT_IMAGE_NAME;
  
  if (argc > 7 || argc % 2 == 0) {
    usage();
    return -1;
  }

#if defined(DYNAMIC)
  if (open_libs()) {
    puts("Failed to open libs");
    close_libs();
    return 0;
  }
  if (func_resolve()) {
    puts("Failed to resolve functions");
    close_libs();
    return 0;
  }
  
  timespec_get(&__finish, TIME_UTC);
  puts("Dynamic symbols resolved");
  print_difftime(&__start, &__finish);

#endif // DYNAMIC

  for (int i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], "--font")) {
      __font = argv[++i];
      const char* __ext = ".ttf";
      int __extlen = strlen(__ext);
      int __filename_len = strlen(__font);
      // filename must be *.ttf
      if (!(__filename_len > __extlen
          && !strcmp(__font + __filename_len - __extlen, __ext))) {
        __font = DEFAULT_FONT;
      }
    } else if (!strcmp(argv[i], "--out")) {
      __image_name = argv[++i];
      const char* __ext = ".png";
      int __extlen = strlen(__ext);
      int __filename_len = strlen(__image_name);
      // filename must be *.png
      if (!(__filename_len > __extlen
          && !strcmp(__image_name + __filename_len - __extlen, __ext))) {
        __image_name = DEFAULT_IMAGE_NAME;
      }
    } else if (!strcmp(argv[i], "--text")) {
      __text = argv[++i];
      if (strlen(__text) == 0) { __text = DEFAULT_TEXT; }
    } else {
      usage();
      return -1;
    }
  }

  FILE* __fd = fopen(__font, "rb");

  if (__fd == NULL) {
    puts("Font file doesn't exist");
    return -1;
  }

  fclose(__fd);

  timespec_get(&__finish, TIME_UTC);
  puts("Arguments parsed");
  printf("Font: ");
  puts(__font);
  printf("Text: ");
  puts(__text);
  printf("Output filename: ");
  puts(__image_name);
  print_difftime(&__start, &__finish);

  int __width = 0;
  int __height = 0;
  printf("width %p\nheight %p\nfont %p\ntext %p\n", (void*)&__width, (void*)&__height, (void*)__font, (void*)__text);

  float* __buff = text_to_float(&__width, &__height, __font, __text);

  if (__buff == NULL) {
    puts("Failed to convert text to bitmap");
    return -1;
  }

  timespec_get(&__finish, TIME_UTC);
  puts("Text has been converted to bitmap");
  print_difftime(&__start, &__finish);


  if(!create_image(__image_name, __width, __height, __buff, "Created image")) {
    puts("Failed to create image from bitmap");
  } else {
    timespec_get(&__finish, TIME_UTC);
    puts("Image has been created from bitmap");
    print_difftime(&__start, &__finish);
  }
#ifdef DYNAMIC
  close_libs();
#endif // DYNAMIC

  timespec_get(&__finish, TIME_UTC);
  puts("Finishing execution");
  print_difftime(&__start, &__finish);
  return 0;
}
