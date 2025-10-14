#ifndef TILE_EDITOR_STATUS_BAR_H
#define TILE_EDITOR_STATUS_BAR_H

#include "config.h"

TILE_EDITOR typedef struct {
  Vector2 position;
  Vector2 size;
  Color background;
} StatusBar;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR StatusBar *statusBar_create(void);

TILE_EDITOR void statusBar_update(StatusBar *const statusBar);

TILE_EDITOR void statusBar_draw(const StatusBar *const statusBar);

TILE_EDITOR void statusBar_destroy(StatusBar **ptrStatusBar);

#if defined(__cplusplus)
}
#endif

#endif  // TILE_EDITOR_STATUS_BAR_H
