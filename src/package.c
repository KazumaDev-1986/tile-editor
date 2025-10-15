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
  // Candy Castle Palette.
  // theme->colors[0] = TILE_EDITOR_COLOR_CANDY_CASTLE_0;
  // theme->colors[1] = TILE_EDITOR_COLOR_CANDY_CASTLE_1;
  // theme->colors[2] = TILE_EDITOR_COLOR_CANDY_CASTLE_2;
  // theme->colors[3] = TILE_EDITOR_COLOR_CANDY_CASTLE_3;
  // theme->colors[4] = TILE_EDITOR_COLOR_CANDY_CASTLE_4;
  // theme->colors[5] = TILE_EDITOR_COLOR_CANDY_CASTLE_5;
  // theme->colors[6] = TILE_EDITOR_COLOR_CANDY_CASTLE_6;
  // theme->colors[7] = TILE_EDITOR_COLOR_CANDY_CASTLE_7;

  // Retrotronic DX Palette.
  theme->colors[0] = TILE_EDITOR_COLOR_RETROTRONIC_DX_0;
  theme->colors[1] = TILE_EDITOR_COLOR_RETROTRONIC_DX_1;
  theme->colors[2] = TILE_EDITOR_COLOR_RETROTRONIC_DX_2;
  theme->colors[3] = TILE_EDITOR_COLOR_RETROTRONIC_DX_3;
  theme->colors[4] = TILE_EDITOR_COLOR_RETROTRONIC_DX_4;
  theme->colors[5] = TILE_EDITOR_COLOR_RETROTRONIC_DX_5;
  theme->colors[6] = TILE_EDITOR_COLOR_RETROTRONIC_DX_6;
  theme->colors[7] = TILE_EDITOR_COLOR_RETROTRONIC_DX_7;

  // // Funky Future Palette.
  // theme->colors[0] = TILE_EDITOR_COLOR_FUNKY_FUTURE_0;
  // theme->colors[1] = TILE_EDITOR_COLOR_FUNKY_FUTURE_1;
  // theme->colors[2] = TILE_EDITOR_COLOR_FUNKY_FUTURE_2;
  // theme->colors[3] = TILE_EDITOR_COLOR_FUNKY_FUTURE_3;
  // theme->colors[4] = TILE_EDITOR_COLOR_FUNKY_FUTURE_4;
  // theme->colors[5] = TILE_EDITOR_COLOR_FUNKY_FUTURE_5;
  // theme->colors[6] = TILE_EDITOR_COLOR_FUNKY_FUTURE_6;
  // theme->colors[7] = TILE_EDITOR_COLOR_FUNKY_FUTURE_7;
}
