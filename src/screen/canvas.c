#include <stddef.h>

#include "../include/grid.h"
#include "../include/raylib.h"
#include "../include/screen.h"

// **************************************************
// Static variables & functions implementation.
// **************************************************
static ScreenType __nextScreen = SCREEN_TYPE_UNDEFINED;
static Grid *__grid = NULL;

// **************************************************
// Public functions implementation.
// **************************************************
Screen *canvas_create(void) {
  Screen *screen = MemAlloc(sizeof(Screen));
  if (!screen) {
    return NULL;
  }
  screen->type = SCREEN_TYPE_CANVAS;
  // TODO: I need to change this.
  __grid = grid_create(8, 8, 16);
  if (!__grid) {
    canvas_destroy(&screen);
    return NULL;
  }

  return screen;
}

void canvas_update(Screen *const screen) { grid_update(__grid); }

void canvas_draw(const Screen *const screen) {
  ClearBackground(TILE_EDITOR_COLOR_GRAY_LIGHT);
  grid_draw(__grid);
}

ScreenType canvas_next_screen(void) { return __nextScreen; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    grid_destroy(&__grid);
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}
