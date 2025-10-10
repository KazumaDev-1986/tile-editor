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
  }

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
