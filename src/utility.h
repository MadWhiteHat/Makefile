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
(*SO_FT_Init_FreeType)(
  FT_Library*
);

FT_EXPORT(FT_Error)
(*SO_FT_New_Face)(
    FT_Library,
    const char*,
    FT_Long,
    FT_Face*
);

FT_EXPORT(FT_Error)
(*SO_FT_Done_FreeType)(
  FT_Library
);

FT_EXPORT(FT_Error)
(*SO_FT_Set_Pixel_Sizes)(
  FT_Face,
  FT_UInt,
  FT_UInt
);

FT_EXPORT(FT_Error)
(*SO_FT_Done_Face)(
  FT_Face
);

FT_EXPORT(FT_Error)
(*SO_FT_Load_Char)(
  FT_Face,
  FT_ULong,
  FT_Int32
);

FT_EXPORT(FT_Error)
(*SO_FT_Get_Glyph)(
  FT_GlyphSlot,
  FT_Glyph
);

FT_EXPORT(FT_Error)
(*SO_FT_Glyph_To_Bitmap)(
  FT_Glyph*,
  FT_Render_Mode,
  const FT_Vector*,
  FT_Bool
);

FT_EXPORT(FT_Error)
(*SO_FT_Done_Glyph)(
  FT_Glyph
);

FT_EXPORT(FT_Error)
(*SO_FT_Get_Char_Index)(
  FT_Face,
  FT_ULong
);

FT_EXPORT(FT_Error)
(*SO_FT_Get_Kerning)(
  FT_Face,
  FT_UInt,
  FT_UInt,
  FT_UInt,
  FT_Vector*
);

#define FT_Init_FreeType SO_FT_Init_FreeType
#define FT_New_Face SO_FT_New_Face
#define FT_Done_FreeType SO_FT_Done_FreeType
#define FT_Done_Face SO_FT_Done_Face
#define FT_Set_Pixel_Sizes SO_FT_Set_Pixel_Sizes
#define FT_Load_Char SO_FT_Load_Char
#define FT_Get_Glyph SO_FT_Get_Glyph
#define FT_Glyph_To_Bitmap SO_FT_Glyph_To_Bitmap
#define FT_Done_Glyph SO_FT_Done_Glyph
#define FT_Get_Char_Index SO_FT_Get_Char_Index
#define FT_Get_Kerning SO_FT_Get_Kerning

png_structp
(*SO_png_create_write_struct)(
  png_const_charp,
  png_voidp,
  png_error_ptr,
  png_error_ptr
);

png_infop
(*SO_png_create_info_struct)(
  png_structp
);

void
(*SO_png_destroy_write_struct)(
  png_structpp,
  png_infopp
);

void
(*SO_png_init_io)(
  png_structp,
  png_FILE_p
);

void
(*SO_png_set_IHDR)(
  png_structp,
  png_infop,
  png_unit_32,
  png_unit_32,
  int,
  int,
  int,
  int,
  int
);

void
(*SO_png_set_text)(
  png_structp,
  png_infop,
  png_textp,
  int
);

void
(*SO_png_write_info)(
  png_structp,
  png_infop
);

void
(*SO_png_write_row)(
  png_structp,
  png_bytep
);

void
(*SO_png_write_end)(
  png_structp,
  png_infop
);

#define png_create_write_struct SO_png_create_write_struct
#define png_create_info_struct SO_png_create_info_struct
#define png_destroy_write_struct SO_png_destroy_write_struct
#define png_init_io SO_png_init_io
#define png_set_IHDR SO_png_set_IHDR
#define png_set_text SO_png_set_text
#define png_write_info SO_png_write_info
#define png_write_row SO_png_write_row
#define png_write_end SO_png_write_end

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
