
#include "include/app_state.h"
#include "include/bar.h"
#include "include/package.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const int32_t BAR_WIDTH = 32;

// **************************************************
// Static functions declaration.
// **************************************************
static void _check_resize_screen(Bar *const toolBar);
static void _initialize_variables(Bar *const toolBar);

// **************************************************
// Public functions implementation.
// **************************************************
Bar *toolBar_create(void) {
  Bar *toolBar = MemAlloc(sizeof(Bar));
  if (!toolBar) {
    return NULL;
  }

  _initialize_variables(toolBar);
  return toolBar;
}

void toolBar_update(Bar *const toolBar) { _check_resize_screen(toolBar); }

void toolBar_draw(const Bar *const toolBar) {
  DrawRectangleRec(
      (Rectangle){
          toolBar->position.x,
          toolBar->position.y,
          toolBar->size.x,
          toolBar->size.y,
      },
      toolBar->background);
}

void toolBar_destroy(Bar **ptrToolBar) {
  if (ptrToolBar && *ptrToolBar) {
    MemFree(*ptrToolBar);
    *ptrToolBar = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_variables(Bar *const toolBar) {
  toolBar->size.x = globalAppState->screenWidth;
  toolBar->size.y = BAR_WIDTH * globalAppState->zoom;
  toolBar->position.x = 0;
  toolBar->position.y =
      globalAppState->screenHeight - (float)globalAppState->screenHeight / 3;
  toolBar->background = globalPackage->theme.colors[5];
}

static void _check_resize_screen(Bar *const toolBar) {
  if (globalAppState->shouldUpdateScreen) {
    _initialize_variables(toolBar);
  }
}
