#include <stddef.h>

#include "../include/custom_camera.h"
#include "../include/grid.h"
#include "../include/raylib.h"
#include "../include/screen.h"

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;
static Grid *__grid = NULL;
static CustomCamera *__customCamera = NULL;

// **************************************************
// Static function declaration.
// **************************************************
static void _reset_static_variables(void);

// **************************************************
// Public functions implementation.
// **************************************************
Screen *canvas_create(void) {
  Screen *screen = MemAlloc(sizeof(Screen));
  if (!screen) {
    return NULL;
  }
  _reset_static_variables();
  screen->type = SCREEN_TYPE_CANVAS;
  __customCamera = customCamera_create();
  if (!__customCamera) {
    canvas_destroy(&screen);
    return NULL;
  }

  // TODO: I need to change this.
  __grid = grid_create(8, 8, 16, __customCamera);
  if (!__grid) {
    canvas_destroy(&screen);
    return NULL;
  }

  return screen;
}

void canvas_update(Screen *const screen) {
  customCamera_update(__customCamera);
  grid_update(__grid);
}

void canvas_draw(const Screen *const screen) {
  ClearBackground(TILE_EDITOR_COLOR_GRAY_LIGHT);
  BeginMode2D(__customCamera->camera);
  grid_draw(__grid);
  EndMode2D();
}

ScreenType canvas_next_screen(void) { return __nextScreenType; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    grid_destroy(&__grid);
    customCamera_destroy(&__customCamera);
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}

// **************************************************
// Static function declaration.
// **************************************************
static void _reset_static_variables(void) {
  __nextScreenType = SCREEN_TYPE_UNDEFINED;
  __grid = NULL;
  __customCamera = NULL;
}
