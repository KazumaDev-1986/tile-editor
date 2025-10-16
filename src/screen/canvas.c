#include <stddef.h>

#include "../include/app_state.h"
#include "../include/bar.h"
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
static Bar *__menuBar = NULL;
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

  __grid = grid_create(4, 4, 8);
  if (!__grid) {
    canvas_destroy(&screen);
    return NULL;
  }

  __menuBar = menuBar_create();
  if (!__menuBar) {
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
  grid_update(__grid);
  menuBar_update(__menuBar);
  // toolBar_update(__toolBar);
  statusBar_update(__statusBar);
}

void canvas_draw(const Screen *const screen) {
  ClearBackground(globalPackage->theme.colors[0]);
  grid_draw(__grid);
  menuBar_draw(__menuBar);
  statusBar_draw(__statusBar);
}

ScreenType canvas_next_screen(void) { return __nextScreenType; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    grid_destroy(&__grid);
    menuBar_destroy(&__menuBar);
    statusBar_destroy(&__statusBar);
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
  __menuBar = NULL;
  __statusBar = NULL;
}
