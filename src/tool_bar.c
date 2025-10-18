
#include "include/app_state.h"
#include "include/bar.h"
#include "include/config.h"
#include "include/package.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const int32_t BAR_WIDTH = 6;

// **************************************************
// Static functions declaration.
// **************************************************
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

void toolBar_update(Bar *const toolBar) {
  // TODO
}

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
  toolBar->size.x = TILE_EDITOR_VIRTUAL_SCREEN_WIDTH;
  toolBar->size.y = BAR_WIDTH;
  toolBar->position.x = 0;
  toolBar->position.y = TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT -
                        (float)TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT / 3;
  toolBar->background = globalPackage->theme.colors[5];
}
