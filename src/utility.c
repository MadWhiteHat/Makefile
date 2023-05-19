#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "png.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "interface.h"
#include "utility.h"

#if defined(DYNAMIC)
int
open_libs(
  void
) {

  char* __err = NULL;

  _libfreetype = dlopen(LIBFREETYPE_PATH, RTLD_LAZY);

  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  _libpng = dlopen(LIBPNG_PATH, RTLD_LAZY);

  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }
  return 0;
}

int
func_resolve(
  void
) {
  char* __err = NULL;

  SO_FT_Init_FreeType = dlsym(_libfreetype, "FT_Init_FreeType");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_New_Face = dlsym(_libfreetype, "FT_New_Face");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Done_FreeType = dlsym(_libfreetype, "FT_Done_FreeType");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Set_Pixel_Sizes = dlsym(_libfreetype, "FT_Set_Pixel_Sizes");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Done_Face = dlsym(_libfreetype, "FT_Done_Face");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Load_Char = dlsym(_libfreetype, "FT_Load_Char");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Get_Glyph = dlsym(_libfreetype, "FT_Get_Glyph");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Glyph_To_Bitmap = dlsym(_libfreetype, "FT_Glyph_To_Bitmap");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Done_Glyph = dlsym(_libfreetype, "FT_Done_Glyph");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Get_Char_Index = dlsym(_libfreetype, "FT_Get_Char_Index");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_FT_Get_Kerning = dlsym(_libfreetype, "FT_Get_Kerning");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_create_write_struct = dlsym(_libpng, "png_create_write_struct");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_create_info_struct = dlsym(_libpng, "png_create_info_struct");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_init_io = dlsym(_libpng, "png_init_io");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_set_IHDR = dlsym(_libpng, "png_set_IHDR");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_set_text = dlsym(_libpng, "png_set_text");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_write_row = dlsym(_libpng, "png_write_row");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_write_end = dlsym(_libpng, "png_write_end");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_destroy_write_struct = dlsym(_libpng, "png_destroy_write_struct");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  SO_png_write_info = dlsym(_libpng, "png_write_info");
  if ((__err = dlerror()) != NULL) {
    puts(__err);
    return 1;
  }

  return 0;
}

void
close_libs(
  void
) {
  if (_libpng != NULL) { dlclose(_libpng); }
  if (_libfreetype != NULL) { dlclose(_libfreetype); }
}

#endif // DYNAMIC

FT_Glyph
get_glyph(
  FT_Face __face,
  unsigned int __charcode
) {
  int __status = 0;
  FT_Glyph __glyph = NULL;
  __status = FT_Load_Char(__face, __charcode, FT_LOAD_RENDER);
  if (__status != 0) {
    puts("FT_Load_Char failed");
    return NULL;
  }
  __status = FT_Get_Glyph(__face->glyph, &__glyph);
  if (__status != 0) {
    puts("FT_Get_Glyph failed");
    return NULL;
  }
  if (__glyph->format != FT_GLYPH_FORMAT_BITMAP) {
    __status = FT_Glyph_To_Bitmap(&__glyph, FT_RENDER_MODE_NORMAL, NULL, 1);
    // glyph unchanged, so cannot be parsed as glyph bitmap in further
    if (__status != 0) {
      FT_Done_Glyph(__glyph);
      puts("FT_Glyph_To_Bitmap failed");
      return NULL;
    }
  }
  return __glyph;
}

FT_Pos
get_kerning(
  FT_Face __face,
  unsigned int __left_charcode,
  unsigned int __right_charcode
) {

  int __status = 0;
  FT_UInt __left_idx = FT_Get_Char_Index(__face, __left_charcode);
  FT_UInt __right_idx = FT_Get_Char_Index(__face, __right_charcode);
  FT_Vector __delta;
  __status = FT_Get_Kerning(
    __face,
    __left_idx,
    __right_idx,
    FT_KERNING_DEFAULT,
    &__delta
  );
  return (__status == 0) ? __delta.x : 0;
}

float*
text_to_float(
  int* __width,
  int* __height,
  const char* __font,
  const char* __text
) {

  int __status = 0;
  FT_Library __lib = NULL;
  FT_Face __face = NULL;
  float* __img = NULL;

  FT_Init_FreeType(&__lib);

  if (__lib == NULL) {
    puts("FT_Init_FreeType failed");
    return NULL;
  }

  *__width = 0;
  *__height = 0;
  __status = FT_New_Face(__lib, __font, 0, &__face);

  if (__status != 0) {
    puts("FT_New_Face failed");
    FT_Done_FreeType(__lib);
    return NULL;
  }

  __status = FT_Set_Pixel_Sizes(__face, 100, 0);

  if (__status != 0) {
    puts("FT_Set_Pixel_Size failed");
    FT_Done_Face(__face);
    FT_Done_FreeType(__lib);
    return NULL;
  }

  static_assert(MAX_SYMBOLS < MAX_SYMBOLS_TO_ALLOC);

  int __text_len = strlen(__text);

  if (__text_len >= MAX_SYMBOLS) {
    puts("Input string is too large.");
    FT_Done_Face(__face);
    FT_Done_FreeType(__lib);
    return NULL;
  }

  my_symbol* __symbols = (my_symbol*)malloc(MAX_SYMBOLS * sizeof(my_symbol));

  if (__symbols == NULL) {
    puts("Memory allocation failed");
    FT_Done_Face(__face);
    FT_Done_FreeType(__lib);
    return NULL;
  }

  int __total_symbols = 0;
  int __left = INT_MAX;
  int __top = INT_MAX;
  int __bottom = INT_MIN;
  unsigned int __prev_charcode = 0;
  int __pos_x = 0;
  
  for (int i = 0; i < __text_len; ++i) {
    const unsigned int __charcode = (const unsigned int) __text[i];
    FT_Glyph __glyph = get_glyph(__face, __charcode);
    if (__glyph == NULL) { continue; }

    if (__prev_charcode != 0) {
      __pos_x += get_kerning(__face, __prev_charcode, __charcode);
    }
    __prev_charcode = __charcode;

    my_symbol* __sym = &(__symbols[__total_symbols++]);
    FT_BitmapGlyph __bitmap_glyph = (FT_BitmapGlyph)__glyph;
    __sym->_pos_x = (__pos_x >> 6) + __bitmap_glyph->left;
    __sym->_pos_y = -__bitmap_glyph->top;
    __sym->_width = __bitmap_glyph->bitmap.width;
    __sym->_height = __bitmap_glyph->bitmap.rows;
    __sym->_glyph = __glyph;
    __pos_x += (__glyph->advance.x >> 10);
    __left = MIN(__left, __sym->_pos_x);
    __top = MIN(__top, __sym->_pos_y);
    __bottom = MAX(__bottom, __sym->_pos_y + __sym->_height);
  }

  for (int i = 0; i < __total_symbols; ++i) { __symbols[i]._pos_x -= __left; }

  const my_symbol* __last_sym = &(__symbols[__total_symbols - 1]);
  const int __image_width = __last_sym->_pos_x + __last_sym->_width + 2 * WIDTH_SHIFT;
  const int __image_height = __bottom - __top + 2 * HEIGHT_SHIFT;
  __img = (float*)malloc(__image_width * __image_height * sizeof(float));
  memset(__img, 0x00, __image_width * __image_height * sizeof(float));

  if (__img != NULL) {
    for (int i = 0; i < __total_symbols; ++i) {
      my_symbol* __sym = &(__symbols[i]);
      FT_BitmapGlyph __bitmap_glyph = (FT_BitmapGlyph)__sym->_glyph;
      FT_Bitmap __bitmap = __bitmap_glyph->bitmap;
      for (int src_y = 0; src_y < __sym->_height; ++src_y) {
        const int dest_y = __sym->_pos_y + src_y - __top + HEIGHT_SHIFT;
        for (int src_x = 0; src_x < __sym->_width; ++src_x) {
          float __byte = __bitmap.buffer[src_x + src_y * __bitmap.pitch];
          if (__byte == 0.0f) { continue; }
          __byte /= 255.f;
          int dest_x = __sym->_pos_x + src_x + WIDTH_SHIFT;
          __img[dest_x + dest_y * __image_width] = __byte * dest_y / 255.f + .1f;
        }
      }
    }
  }
  // cleanup
  for (int i = 0; i < __total_symbols; ++i) {
    FT_Done_Glyph(__symbols[i]._glyph);
  }
  free(__symbols);
  *__width = __image_width;
  *__height = __image_height;
  if (__face != NULL) { FT_Done_Face(__face); }
  if (__lib != NULL) { FT_Done_FreeType(__lib); }

  return __img;
}

void
set_rgb(
  png_bytep __image_row,
  float __val
) {
  int __value = (int)(__val * 767);
  __value = MAX(__value, 0);
  __value = MIN(__value, 767);
  int __offset = __value % 256;
  if (__offset > 0) {
    __image_row[0] = 0x34;
    __image_row[1] = 0x91;
    __image_row[2] = 0x6b;
  } else {
    __image_row[0] = __image_row[1] = __image_row[2] = 0;
  }

}

int
create_image(
  const char* __image_name,
  int __width,
  int __height,
  float* __image_buff,
  const char* __image_title
) {
  FILE* __fd = NULL;
  png_structp __image = NULL;
  png_infop __image_info = NULL;
  png_bytep __image_row = NULL;

  __fd = fopen(__image_name, "wb");
  if (__fd == NULL) {
    puts("Failed to open image file for writing");
    return 0;
  }
  __image = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (__image == NULL) {
    puts("png_create_write_struct failed");
    fclose(__fd);
    return 0;
  }
  __image_info = png_create_info_struct(__image);
  if (__image_info == NULL) {
    puts("png_create_info_struct failed");
    png_destroy_write_struct(&__image, (png_infopp)NULL);
    return 0;
  }
  png_init_io(__image, __fd);

  png_set_IHDR(
    __image,
    __image_info,
    __width,
    __height,
    8,
    PNG_COLOR_TYPE_RGB,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE,
    PNG_FILTER_TYPE_BASE
  );

  if (__image_title != NULL) {
    png_text __title_text;
    __title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    __title_text.key = (char*)"Title";
    __title_text.text = (char*)__image_title;
    png_set_text(__image, __image_info, &__title_text, 1);
  }

  png_write_info(__image, __image_info);
  // Alloc memory for row RGB = 3 bytes per pixel

  __image_row = (png_bytep)malloc(3 * __width * sizeof(png_byte));
  // Write data to image
  int x = 0;
  int y = 0;
  for (y = 0; y < __height; ++y) {
    for (x = 0; x < __width; ++x) {
      set_rgb(&(__image_row[x * 3]), __image_buff[y * __width + x]);
    }
    png_write_row(__image, __image_row);
  }
  png_write_end(__image, NULL);

  free(__image_row);
  png_destroy_write_struct(&__image, &__image_info);
  fclose(__fd);
  return 1;
}

#if !defined(BLOB)

void
print_difftime(
  struct timespec* __start,
  struct timespec* __finish
) {
  double __time_finish = __finish->tv_sec * 1000
    + (double)__finish->tv_nsec / 1000000;
  double __time_start = __start->tv_sec * 1000
    + (double)__start->tv_nsec / 1000000;
  printf("Time elapsed: %lf millisecond(s)\n", __time_finish - __time_start);
}

#endif // !BLOB
