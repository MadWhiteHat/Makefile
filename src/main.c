#include <stdio.h>
#include <time.h>

#include "utility.h"

#define DEFAULT_FONT "./fonts/AmaticSC-Regular.ttf"
#define DEFAULT_TEXT "Hello world!"
#define DEFAULT_IMAGE_NAME "hello.png"

void usage(void) {
  printf("Usage: text2png.out"
    " [--font FONT_FILE_PATH]"
    " [--out OUTPUT_PNG_PATH]"
    " [--text INPUT_TEXT]");
  printf("\n");
}

int main(const int argc, const char** argv) {
  clock_t __start = clock();

  const char* __font = DEFAULT_FONT;
  const char* __text = DEFAULT_TEXT;
  const char* __image_name = DEFAULT_IMAGE_NAME;
  
  if (argc > 7 || argc % 2 == 0) {
    usage();
    return -1;
  }

#if defined(DYNAMIC)
  func_resolve();
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
    printf("Font file doesn't exist\n");
    return -1;
  }

  fclose(__fd);

  int __width = 0;
  int __height = 0;

  float* __buff = text_to_float(&__width, &__height, __font, __text);

  if (__buff == NULL) {
    printf("Failed to convert text to bitmap");
    return -1;
  }

  create_image(__image_name, __width, __height, __buff, "Created image");

  clock_t __finish = clock();
  double __runtime = ((double)__finish - __start) / CLOCKS_PER_SEC;
  printf("Time elapsed: %.4f\n", __runtime);

  return 0;
}
