#include <math.h>
#include <stddef.h>

#include "include/app_state.h"
#include "include/config.h"
#include "include/custom_camera.h"
#include "include/raylib.h"
#include "include/raymath.h"

// screen = (world - target) * zoom + offset

extern AppState *globalAppState;

// **************************************************
// Static functions declaration.
// **************************************************
static void _update_resize_camera(CustomCamera *const customCamera);
static void _keyboard_event(CustomCamera *const customCamera);
static Vector2 _get_direction(void);
static void _mouse_event(CustomCamera *const customCamera);

// **************************************************
// Public functions implementation.
// **************************************************
CustomCamera *customCamera_create(void) {
  CustomCamera *customCamera = MemAlloc(sizeof(CustomCamera));
  if (!customCamera) {
    return NULL;
  }

  customCamera->camera = (Camera2D){0};
  customCamera->camera.offset = (Vector2){
      .x = (float)globalAppState->screenWidth / 2,
      .y = (float)globalAppState->screenHeight / 2,
  };
  customCamera->camera.target = (Vector2){0};
  customCamera->camera.rotation = 0;
  customCamera->camera.zoom = 1;

  return customCamera;
}

void customCamera_update(CustomCamera *const customCamera) {
  if (customCamera) {
    _update_resize_camera(customCamera);
    _mouse_event(customCamera);
    _keyboard_event(customCamera);
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
static void _update_resize_camera(CustomCamera *const customCamera) {
  if (globalAppState->shouldUpdateScreen) {
    float screenWidth = (float)globalAppState->screenWidth;
    float screenHeight = (float)globalAppState->screenHeight;

    float scale = fminf(screenWidth / TILE_EDITOR_SCREEN_WIDTH,
                        screenHeight / TILE_EDITOR_SCREEN_HEIGHT);

    customCamera->camera.zoom = scale;
    customCamera->camera.offset = (Vector2){
        .x = (float)globalAppState->screenWidth / 2,
        .y = (float)globalAppState->screenHeight / 2,
    };
  }
}

static void _keyboard_event(CustomCamera *const customCamera) {
  Vector2 dir = _get_direction();
  float deltaTime = GetFrameTime();

  customCamera->camera.target.x +=
      dir.x * TILE_EDITOR_CAMERA_MOVE_SPEED * deltaTime;
  customCamera->camera.target.y +=
      dir.y * TILE_EDITOR_CAMERA_MOVE_SPEED * deltaTime;
}

static Vector2 _get_direction(void) {
  Vector2 dir = {0, 0};

  if (IsKeyDown(KEY_UP)) dir.y -= 1;
  if (IsKeyDown(KEY_DOWN)) dir.y += 1;
  if (IsKeyDown(KEY_LEFT)) dir.x -= 1;
  if (IsKeyDown(KEY_RIGHT)) dir.x += 1;

  if (dir.x != 0 || dir.y != 0) {
    dir = Vector2Normalize(dir);
  }

  return dir;
}

static void _mouse_event(CustomCamera *const customCamera) {
  if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
    Vector2 mouseDelta = GetMouseDelta();
    float zoom = customCamera->camera.zoom;

    customCamera->camera.target.x -= mouseDelta.x / zoom;
    customCamera->camera.target.y -= mouseDelta.y / zoom;
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    customCamera->camera.zoom += wheel * TILE_EDITOR_CAMERA_ZOOM_WHEEL_DIFF;
    if (customCamera->camera.zoom < TILE_EDITOR_CAMERA_ZOOM_MIN) {
      customCamera->camera.zoom = TILE_EDITOR_CAMERA_ZOOM_MIN;
    }
    if (customCamera->camera.zoom > TILE_EDITOR_CAMERA_ZOOM_MAX) {
      customCamera->camera.zoom = TILE_EDITOR_CAMERA_ZOOM_MAX;
    }
  }
}
