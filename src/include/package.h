#ifndef TILE_EDITOR_PACKAGE_H
#define TILE_EDITOR_PACKAGE_H

#include "config.h"

TILE_EDITOR typedef struct {
  Color colors[TILE_EDITOR_COLOR_PALETTE_SIZE];
} Theme;

TILE_EDITOR typedef struct {
  Font fonts[TILE_EDITOR_PACKAGE_FONT_SIZE];
  Theme theme;
} Package;

#if defined(__cplusplsu)
extern "C" {
#endif

TILE_EDITOR Package *package_create(void);

TILE_EDITOR void package_destroy(Package **ptrPackage);

#if defined(__cplusplsu)
}
#endif

#endif // TILE_EDITOR_PACKAGE_H
