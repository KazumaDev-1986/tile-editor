

#include "include/app_state.h"
#include "include/bar.h"
#include "include/package.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const int32_t BAR_WIDTH = 8;

// **************************************************
// Static functions declaration.
// **************************************************
static void _check_resize_screen(Bar *const menuBar);
static void _initialize_variables(Bar *const menuBar);

// **************************************************
// Public functions implementation.
// **************************************************
Bar *menuBar_create(void) {
  Bar *menuBar = MemAlloc(sizeof(Bar));
  if (!menuBar) {
    return NULL;
  }

  _initialize_variables(menuBar);
  return menuBar;
}

void menuBar_update(Bar *const menuBar) { _check_resize_screen(menuBar); }

void menuBar_draw(const Bar *const menuBar) {
  DrawRectangleRec(
      (Rectangle){
          menuBar->position.x,
          menuBar->position.y,
          menuBar->size.x,
          menuBar->size.y,
      },
      menuBar->background);
}

void menuBar_destroy(Bar **ptrMenuBar) {
  if (ptrMenuBar && *ptrMenuBar) {
    MemFree(*ptrMenuBar);
    *ptrMenuBar = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_variables(Bar *const menuBar) {
  menuBar->size.x = globalAppState->screenWidth;
  menuBar->size.y = BAR_WIDTH;
  menuBar->position.x = 0;
  menuBar->position.y = 0;
  menuBar->background = globalPackage->theme.colors[8];
}

static void _check_resize_screen(Bar *const menuBar) {
  if (globalAppState->shouldUpdateScreen) {
    _initialize_variables(menuBar);
  }
}
