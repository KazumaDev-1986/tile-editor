#include <stddef.h>

#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"

// **************************************************
// Static functions declaration.
// **************************************************
static bool _load_fonts(Font *fonts);
static void _unload_fonts(Font *fonts);
static bool _load_font(Font *font, const char *fileName);
static void _load_theme(Theme *theme);

// **************************************************
// Public functions implementation.
// **************************************************
Package *package_create(void) {
  Package *package = MemAlloc(sizeof(Package));
  if (!package) {
    return NULL;
  }

  if (_load_fonts(package->fonts)) {
    package_destroy(&package);
    return NULL;
  }

  _load_theme(&package->theme);
  return package;
}

void package_destroy(Package **ptrPackage) {
  if (ptrPackage && *ptrPackage) {
    _unload_fonts((*ptrPackage)->fonts);
    MemFree(*ptrPackage);
    *ptrPackage = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static bool _load_fonts(Font *fonts) {
  bool hasError = false;

  const char *fileNameList[] = {
      TILE_EDITOR_PACKAGE_FONT_04b_03,
      TILE_EDITOR_PACKAGE_FONT_BM_MINI,
  };

  for (size_t i = 0; !hasError && i < TILE_EDITOR_PACKAGE_FONT_SIZE; ++i) {
    const char *fileName = fileNameList[i];
    hasError = _load_font(&fonts[i], fileName);
  }

  return hasError;
}

static bool _load_font(Font *font, const char *fileName) {
  bool hasError = false;

  if (FileExists(fileName)) {
    *font = LoadFont(fileName);
  } else {
    hasError = true;
  }

  return hasError;
}

static void _unload_fonts(Font *fonts) {
  for (size_t i = 0; i < TILE_EDITOR_PACKAGE_FONT_SIZE; ++i) {
    if (fonts[i].texture.id != 0) {
      UnloadFont(fonts[i]);
      fonts[i].texture.id = 0;
    }
  }
}

static void _load_theme(Theme *theme) {
  theme->colors[0] = TILE_EDITOR_COLOR_PICO8_0;
  theme->colors[1] = TILE_EDITOR_COLOR_PICO8_1;
  theme->colors[2] = TILE_EDITOR_COLOR_PICO8_2;
  theme->colors[3] = TILE_EDITOR_COLOR_PICO8_3;
  theme->colors[4] = TILE_EDITOR_COLOR_PICO8_4;
  theme->colors[5] = TILE_EDITOR_COLOR_PICO8_5;
  theme->colors[6] = TILE_EDITOR_COLOR_PICO8_6;
  theme->colors[7] = TILE_EDITOR_COLOR_PICO8_7;
  theme->colors[8] = TILE_EDITOR_COLOR_PICO8_8;
  theme->colors[9] = TILE_EDITOR_COLOR_PICO8_9;
  theme->colors[10] = TILE_EDITOR_COLOR_PICO8_10;
  theme->colors[11] = TILE_EDITOR_COLOR_PICO8_11;
  theme->colors[12] = TILE_EDITOR_COLOR_PICO8_12;
  theme->colors[13] = TILE_EDITOR_COLOR_PICO8_13;
  theme->colors[14] = TILE_EDITOR_COLOR_PICO8_14;
  theme->colors[15] = TILE_EDITOR_COLOR_PICO8_15;
}
