#include <stddef.h>

#include "include/app_state.h"
#include "include/raylib.h"

// **************************************************
// Public functions implementation.
// **************************************************
AppState *appState_create(void) {
  AppState *state = MemAlloc(sizeof(AppState));
  if (!state) {
    return NULL;
  }

  state->screenWidth = GetScreenWidth();
  state->screenHeight = GetScreenHeight();
  state->shouldUpdateScreen = false;

  return state;
}
void appState_update(AppState *const state) {
  int32_t newWidth = GetScreenWidth();
  int32_t newHeight = GetScreenHeight();
  state->shouldUpdateScreen = false;

  if (state->screenWidth != newWidth || state->screenHeight != newHeight) {
    state->screenWidth = newWidth;
    state->screenHeight = newHeight;
    state->shouldUpdateScreen = true;
  }
}
void appState_destroy(AppState **ptrState) {
  if (ptrState && *ptrState) {
    MemFree(*ptrState);
    *ptrState = NULL;
  }
}
