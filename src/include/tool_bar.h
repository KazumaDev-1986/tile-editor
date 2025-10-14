
#ifndef TILE_EDITOR_TOOL_BAR_H
#define TILE_EDITOR_TOOL_BAR_H

#include "config.h"

TILE_EDITOR typedef struct {
  Vector2 position;
  Vector2 size;
  Color background;
} ToolBar;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR ToolBar *toolBar_create(void);

TILE_EDITOR void toolBar_update(ToolBar *const toolBar);

TILE_EDITOR void toolBar_draw(const ToolBar *const toolBar);

TILE_EDITOR void toolBar_destroy(ToolBar **ptrToolBar);

#if defined(__cplusplus)
}
#endif

#endif  // TILE_EDITOR_TOOL_BAR_H
