#ifndef TILE_EDITOR_APP_STATE_H
#define TILE_EDITOR_APP_STATE_H

#include <stdint.h>

#include "config.h"

TILE_EDITOR typedef enum {
  ZOOM_LEVEL_ONE = 1,
  ZOOM_LEVEL_TWO = 2,
  ZOOM_LEVEL_THREE = 3,
  ZOOM_LEVEL_FOUR = 4,
} ZoomLevel;

TILE_EDITOR typedef struct {
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
} View;

TILE_EDITOR typedef struct {
  View view;
  int32_t screenWidth;
  int32_t screenHeight;
  float baseAspect;
  ZoomLevel zoom;
} AppState;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR AppState *appState_create(void);

TILE_EDITOR void appState_update(AppState *const state);

TILE_EDITOR void appState_destroy(AppState **const ptrState);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_APP_STATE_H
