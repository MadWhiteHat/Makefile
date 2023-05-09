#ifndef _UTILITY_H
#define _UTILITY_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#if defined(STATIC)
#if defined(DYNAMIC) || defined(BLOB)
static_assert(0, "Multiple mutial exclusive definitions");
#endif // DYNAMIC || BLOB
#elif defined(DYNAMIC)
#if defined(STATIC) || defined(DYNAMIC)
static_assert(0, "Multiple mutial exclusive definitions");
#endif // STATIC || DYNAMIC
#elif defined(BLOB)
#if defined(STATIC) || defined(DYNAMIC)
static_assert(0, "Multiple mutial exclusive definitions");
#endif // STATIC || DYNAMIC
#endif


#if defined(DYNAMIC)
#if !defined(LIBPNG_PATH)
static_assert(0, "libpng path not specified");
#endif // !LIBPNG_PATH
#if !defined(LIBFREETYPE_PATH)
static_assert(0, "libfreetype path not specified");
#endif // !LIBFREETYPE_PATH
#endif // DYNAMIC

#include "png.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#if defined(DYNAMIC)
#include <dlfcn.h>
#endif // DYNAMIC

#ifndef MAX_SYMBOLS
#define MAX_SYMBOLS 2048
#endif // MAX_SYMBOLS

#define MAX_SYMBOLS_TO_ALLOC 8192
#define HEIGHT_SHIFT 50
#define WIDTH_SHIFT 50

#define MIN(A, B) (((A) > (B)) ? (B) : (A))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))

#if defined(DYNAMIC)

FT_EXPORT(FT_Error)
(*SO_FT_Init_FreeType)(FT_Library*);
FT_EXPORT(FT_Error)
(*SO_FT_New_Face)(FT_Library, const char*, FT_Long, FT_Long);
FT_EXPORT(FT_Error)
(*SO_FT_Set_Pixel_Sizes)(FT_Face, FT_UInt, FT_UInt);

#define FT_Init_FreeType SO_FT_Init_FreeType
#define FT_New_Face SO_FT_New_Face
#define FT_Set_Pixel_Sizes SO_FT_Set_Pixel_Sizes

#endif // DYNAMIC

typedef struct _my_symbol {
  int _pos_x;
  int _pos_y;
  int _width;
  int _height;
  FT_Glyph _glyph;
} my_symbol;

#if defined(DYNAMIC)
int
func_resolve(
  void
);
#endif

FT_Glyph
get_glyph(
  FT_Face __ft__face,
  unsigned int __charcode
);

FT_Pos
get_kerning(
  FT_Face __ft_face,
  unsigned int __left_charcode,
  unsigned int __right_charcode
);

float*
text_to_float(
  int* __width,
  int* __height,
  const char* __font,
  const char* __text
);

void
set_rgb(
  png_bytep __image_row,
  float __val
);

void
create_image(
  const char* __image_name,
  int __width,
  int __height,
  float* __image_buff,
  const char* __image_title
);

#endif // !_UTILITY_H
