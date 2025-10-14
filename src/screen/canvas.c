#include <stddef.h>

#include "../include/app_state.h"
#include "../include/bar.h"
#include "../include/custom_camera.h"
#include "../include/grid.h"
#include "../include/raylib.h"
#include "../include/screen.h"

extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;
static Grid *__grid = NULL;
static CustomCamera *__customCamera = NULL;
static Bar *__toolBar = NULL;

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

  __grid = grid_create(32, 32, 16, __customCamera);
  if (!__grid) {
    canvas_destroy(&screen);
    return NULL;
  }

  __toolBar = toolBar_create();
  if (!__toolBar) {
    canvas_destroy(&screen);
    return NULL;
  }

  return screen;
}

void canvas_update(Screen *const screen) {
  customCamera_update(__customCamera);
  grid_update(__grid);
  toolBar_update(__toolBar);
}

void canvas_draw(const Screen *const screen) {
  ClearBackground(TILE_EDITOR_COLOR_PURPLE_DARK);
  BeginMode2D(__customCamera->camera);
  grid_draw(__grid);
  EndMode2D();

  float posY =
      globalAppState->screenHeight - (float)globalAppState->screenHeight / 3;
  DrawRectangle(0, posY, globalAppState->screenWidth,
                globalAppState->screenHeight, TILE_EDITOR_COLOR_PURPLE_DARK);
  toolBar_draw(__toolBar);
}

ScreenType canvas_next_screen(void) { return __nextScreenType; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    grid_destroy(&__grid);
    toolBar_destroy(&__toolBar);
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
  __toolBar = NULL;
}
