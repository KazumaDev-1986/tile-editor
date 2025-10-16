#include "include/app_state.h"
#include "include/bar.h"
#include "include/config.h"
#include "include/package.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const int32_t BAR_HEIGHT = 8;

// **************************************************
// Static functions declaration.
// **************************************************
static void _check_resize_screen(Bar *const statusBar);
static void _initialize_variables(Bar *const statusBar);

// **************************************************
// Public functions implementation.
// **************************************************
Bar *statusBar_create(void) {
  Bar *statusBar = MemAlloc(sizeof(Bar));
  if (!statusBar) {
    return NULL;
  }

  _initialize_variables(statusBar);
  return statusBar;
}

void statusBar_update(Bar *const statusBar) { _check_resize_screen(statusBar); }

void statusBar_draw(const Bar *const statusBar) {
  DrawRectangleRec(
      (Rectangle){
          statusBar->position.x,
          statusBar->position.y,
          statusBar->size.x,
          statusBar->size.y,
      },
      statusBar->background);
}

void statusBar_destroy(Bar **ptrStatusBar) {
  if (ptrStatusBar && *ptrStatusBar) {
    MemFree(*ptrStatusBar);
    *ptrStatusBar = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_variables(Bar *const statusBar) {
  statusBar->size.x = TILE_EDITOR_VIRTUAL_SCREEN_WIDTH;
  statusBar->size.y = BAR_HEIGHT;
  statusBar->position.x = 0;
  statusBar->position.y = TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT - statusBar->size.y;
  statusBar->background = globalPackage->theme.colors[8];
}

static void _check_resize_screen(Bar *const statusBar) {
  if (globalAppState->shouldUpdateScreen) {
    _initialize_variables(statusBar);
  }
}
