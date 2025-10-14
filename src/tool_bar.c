
#include "include/app_state.h"
#include "include/tool_bar.h"

extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const int32_t BAR_WIDTH = 24;

// **************************************************
// Static functions declaration.
// **************************************************
static void _check_resize_screen(ToolBar *const toolBar);
static void _initialize_variables(ToolBar *const toolBar);

// **************************************************
// Public functions implementation.
// **************************************************
ToolBar *toolBar_create(void) {
  ToolBar *toolBar = MemAlloc(sizeof(ToolBar));
  if (!toolBar) {
    return NULL;
  }

  _initialize_variables(toolBar);
  return toolBar;
}

void toolBar_update(ToolBar *const toolBar) {
  _check_resize_screen(toolBar);
}

void toolBar_draw(const ToolBar *const toolBar) {
  DrawRectangleRec(
      (Rectangle){
          toolBar->position.x,
          toolBar->position.y,
          toolBar->size.x,
          toolBar->size.y,
      },
      toolBar->background);
}

void toolBar_destroy(ToolBar **ptrToolBar) {
  if (ptrToolBar && *ptrToolBar) {
    MemFree(*ptrToolBar);
    *ptrToolBar = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_variables(ToolBar *const toolBar) {
  toolBar->size.x = globalAppState->screenWidth;
  toolBar->size.y = BAR_WIDTH * globalAppState->zoom;
  toolBar->position.x = 0;
  toolBar->position.y = 0;
  toolBar->background = TILE_EDITOR_COLOR_BLUE_DARK;
}

static void _check_resize_screen(ToolBar *const toolBar) {
  if (globalAppState->shouldUpdateScreen) {
    _initialize_variables(toolBar);
  }
}
