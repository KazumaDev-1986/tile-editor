#include <stddef.h>

#include "../include/app_state.h"
#include "../include/bar.h"
#include "../include/custom_camera.h"
#include "../include/grid.h"
#include "../include/package.h"
#include "../include/raylib.h"
#include "../include/screen.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;
static Grid *__grid = NULL;
static CustomCamera *__customCamera = NULL;
static Bar *__menuBar = NULL;
static Bar *__toolBar = NULL;
static Bar *__statusBar = NULL;

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

  __grid = grid_create(4, 4, 8, __customCamera);
  if (!__grid) {
    canvas_destroy(&screen);
    return NULL;
  }

  __menuBar = menuBar_create();
  if (!__menuBar) {
    canvas_destroy(&screen);
    return NULL;
  }

  __toolBar = toolBar_create();
  if (!__toolBar) {
    canvas_destroy(&screen);
    return NULL;
  }

  __statusBar = statusBar_create();
  if (!__statusBar) {
    canvas_destroy(&screen);
    return NULL;
  }

  return screen;
}

void canvas_update(Screen *const screen) {
  customCamera_update(__customCamera);
  grid_update(__grid);
  menuBar_update(__menuBar);
  toolBar_update(__toolBar);
  statusBar_update(__statusBar);
}

void canvas_draw(const Screen *const screen) {
  ClearBackground(globalPackage->theme.colors[0]);
  BeginMode2D(__customCamera->camera);
  grid_draw(__grid);
  EndMode2D();

  float posY = TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT -
               (float)TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT / 3;
  DrawRectangle(0, posY, TILE_EDITOR_VIRTUAL_SCREEN_WIDTH, 40,
                globalPackage->theme.colors[1]);
  menuBar_draw(__menuBar);
  toolBar_draw(__toolBar);
  statusBar_draw(__statusBar);
}

ScreenType canvas_next_screen(void) { return __nextScreenType; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    grid_destroy(&__grid);
    menuBar_destroy(&__menuBar);
    toolBar_destroy(&__toolBar);
    statusBar_destroy(&__statusBar);
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
  __menuBar = NULL;
  __toolBar = NULL;
  __statusBar = NULL;
}
