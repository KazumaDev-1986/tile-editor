#include <math.h>
#include <stddef.h>

#include "include/app_state.h"
#include "include/config.h"
#include "include/custom_camera.h"
#include "include/raylib.h"
#include "include/raymath.h"

extern AppState *globalAppState;

// **************************************************
// Static functions declaration.
// **************************************************
static float __speed = 400.f;

static void _update_zoom(CustomCamera *const customCamera);
static void _move(CustomCamera *const customCamera);
static Vector2 _get_direction(void);

// **************************************************
// Public functions implementation.
// **************************************************
CustomCamera *customCamera_create(void) {
  CustomCamera *customCamera = MemAlloc(sizeof(CustomCamera));
  if (!customCamera) {
    return NULL;
  }

  customCamera->camera = (Camera2D){0};
  customCamera->camera.offset = (Vector2){0};
  customCamera->camera.target = (Vector2){0};
  customCamera->camera.rotation = 0;
  customCamera->camera.zoom = 1;

  return customCamera;
}

void customCamera_update(CustomCamera *const customCamera) {
  if (customCamera) {
    _update_zoom(customCamera);
    _move(customCamera);
  }
}

void customCamera_destroy(CustomCamera **ptrCustomCamera) {
  if (ptrCustomCamera && *ptrCustomCamera) {
    MemFree(*ptrCustomCamera);
    *ptrCustomCamera = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _update_zoom(CustomCamera *const customCamera) {
  if (globalAppState->shouldUpdateScreen) {
    float screenWidth = (float)globalAppState->screenWidth;
    float screenHeight = (float)globalAppState->screenHeight;

    float scale = fminf(screenWidth / TILE_EDITOR_SCREEN_WIDTH,
                        screenHeight / TILE_EDITOR_SCREEN_HEIGHT);

    customCamera->camera.zoom = scale;
    customCamera->camera.offset.x =
        (screenWidth - TILE_EDITOR_SCREEN_WIDTH) / 2;
    customCamera->camera.offset.y =
        (screenHeight - TILE_EDITOR_SCREEN_HEIGHT) / 2;
  }
}

static void _move(CustomCamera *const customCamera) {
  Vector2 dir = _get_direction();
  float deltaTime = GetFrameTime();

  customCamera->camera.offset.x += dir.x * __speed * deltaTime;
  customCamera->camera.offset.y += dir.y * __speed * deltaTime;
}

static Vector2 _get_direction(void) {
  Vector2 dir = {0, 0};

  if (IsKeyDown(KEY_UP))
    dir.y += 1;
  if (IsKeyDown(KEY_DOWN))
    dir.y -= 1;
  if (IsKeyDown(KEY_LEFT))
    dir.x += 1;
  if (IsKeyDown(KEY_RIGHT))
    dir.x -= 1;

  if (dir.x != 0 || dir.y != 0) {
    dir = Vector2Normalize(dir);
  }

  return dir;
}
