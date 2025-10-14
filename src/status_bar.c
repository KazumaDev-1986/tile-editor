#include "include/app_state.h"
#include "include/status_bar.h"

extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const int32_t BAR_WIDTH = 24;

// **************************************************
// Static functions declaration.
// **************************************************
static void _check_resize_screen(StatusBar *const statusBar);
static void _initialize_variables(StatusBar *const statusBar);

// **************************************************
// Public functions implementation.
// **************************************************
StatusBar *statusBar_create(void) {
  StatusBar *statusBar = MemAlloc(sizeof(StatusBar));
  if (!statusBar) {
    return NULL;
  }

  _initialize_variables(statusBar);
  return statusBar;
}

void statusBar_update(StatusBar *const statusBar) {
  _check_resize_screen(statusBar);
}

void statusBar_draw(const StatusBar *const statusBar) {
  DrawRectangleRec(
      (Rectangle){
          statusBar->position.x,
          statusBar->position.y,
          statusBar->size.x,
          statusBar->size.y,
      },
      statusBar->background);
}

void statusBar_destroy(StatusBar **ptrStatusBar) {
  if (ptrStatusBar && *ptrStatusBar) {
    MemFree(*ptrStatusBar);
    *ptrStatusBar = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_variables(StatusBar *const statusBar) {
  statusBar->size.x = globalAppState->screenWidth;
  statusBar->size.y = BAR_WIDTH * globalAppState->zoom;
  statusBar->position.x = 0;
  statusBar->position.y = globalAppState->screenHeight - statusBar->size.y;
  statusBar->background = TILE_EDITOR_COLOR_BLUE_DARK;
}

static void _check_resize_screen(StatusBar *const statusBar) {
  if (globalAppState->shouldUpdateScreen) {
    _initialize_variables(statusBar);
  }
}
