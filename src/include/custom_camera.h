#ifndef TILE_EDITOR_CUSTOM_CAMERA_H
#define TILE_EDITOR_CUSTOM_CAMERA_H

#include "config.h"
#include "raylib.h"

TILE_EDITOR typedef struct {
  Camera2D camera;
} CustomCamera;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR CustomCamera *customCamera_create(void);

TILE_EDITOR void customCamera_update(CustomCamera *const customCamera);

TILE_EDITOR void customCamera_destroy(CustomCamera **ptrCustomCamera);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_CUSTOM_CAMERA_H
