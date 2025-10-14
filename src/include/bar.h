#ifndef TILE_EDITOR_BAR_H
#define TILE_EDITOR_BAR_H

#include "config.h"

TILE_EDITOR typedef struct {
  Vector2 position;
  Vector2 size;
  Color background;
} Bar;

#if defined(__cplusplus)
extern "C" {
#endif
// Menubar declaration.
// -------------------------------------------------------------
TILE_EDITOR Bar *menuBar_create(void);
TILE_EDITOR void menuBar_update(Bar *const menuBar);
TILE_EDITOR void menuBar_draw(const Bar *const menuBar);
TILE_EDITOR void menuBar_destroy(Bar **ptrMenuBar);

// ToolBar declaration.
// -------------------------------------------------------------
TILE_EDITOR Bar *toolBar_create(void);
TILE_EDITOR void toolBar_update(Bar *const toolBar);
TILE_EDITOR void toolBar_draw(const Bar *const toolBar);
TILE_EDITOR void toolBar_destroy(Bar **ptrToolBar);

// StatusBar declaration.
// -------------------------------------------------------------
TILE_EDITOR Bar *statusBar_create(void);
TILE_EDITOR void statusBar_update(Bar *const statusBar);
TILE_EDITOR void statusBar_draw(const Bar *const statusBar);
TILE_EDITOR void statusBar_destroy(Bar **ptrStatusBar);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_BAR_H
