#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <stdio.h>

#if defined(DYNAMIC)
int
open_libs(
  void
);

int
func_resolve(
  void
);

void
close_libs(
  void
);

#endif // DYNAMIC

float*
text_to_float(
  int* __width,
  int* __height,
  const char* __font,
  const char* __text
);

void
create_image(
  const char* __image_name,
  int __width,
  int __height,
  float* __image_buff,
  const char* __image_title
);

#endif // _INTERFACE_H
