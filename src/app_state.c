#include <stddef.h>

#include "include/app_state.h"
#include "include/config.h"
#include "include/raylib.h"

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_view(AppState *const state);
static void _keyboard_events(AppState *const state);
static ZoomLevel _getZoomLevelByNumber(int32_t value);
static void _check_resize_screen(AppState *const state);

// **************************************************
// Public functions implementation.
// **************************************************
AppState *appState_create(void) {
  AppState *state = MemAlloc(sizeof(AppState));
  if (!state) {
    return NULL;
  }

  state->zoom = ZOOM_LEVEL_ONE;
  state->baseAspect = (float)TILE_EDITOR_VIRTUAL_SCREEN_WIDTH /
                      (float)TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT;
  _initialize_view(state);

  return state;
}
void appState_update(AppState *const state) {
  _keyboard_events(state);
  _check_resize_screen(state);
}

void appState_destroy(AppState **const ptrState) {
  if (ptrState && *ptrState) {
    MemFree(*ptrState);
    *ptrState = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_view(AppState *const state) {
  state->screenWidth = GetScreenWidth();
  state->screenHeight = GetScreenHeight();
  state->view = (View){0};

  float currentAspect = (float)state->screenWidth / (float)state->screenHeight;

  state->view.width = state->screenWidth;
  state->view.height = state->screenHeight;

  if (currentAspect > state->baseAspect) {
    state->view.width = state->screenHeight * state->baseAspect;
    state->view.x = (state->screenWidth - state->view.width) / 2;
  } else if (currentAspect < state->baseAspect) {
    state->view.height = state->screenWidth / state->baseAspect;
    state->view.y = (state->screenHeight - state->view.height) / 2;
  }
}

static void _keyboard_events(AppState *const state) {
  if (IsKeyPressed(KEY_K)) {
    state->zoom = _getZoomLevelByNumber(state->zoom + 1);
  } else if (IsKeyPressed(KEY_J)) {
    state->zoom = _getZoomLevelByNumber(state->zoom - 1);
  }
}

static ZoomLevel _getZoomLevelByNumber(int32_t value) {
  if (value < ZOOM_LEVEL_ONE) {
    return ZOOM_LEVEL_ONE;
  }

  if (value > ZOOM_LEVEL_FOUR) {
    return ZOOM_LEVEL_FOUR;
  }

  return (ZoomLevel)value;
}
static void _check_resize_screen(AppState *const state) {
  bool isScreenWidthChanged = state->screenWidth != GetScreenWidth();
  bool isScreenHeightChanged = state->screenHeight != GetScreenHeight();

  if (isScreenWidthChanged || isScreenHeightChanged) {
    _initialize_view(state);
  }
}
