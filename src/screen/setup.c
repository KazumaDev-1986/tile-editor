#include <stdint.h>

#include "../include/screen.h"
#include "../include/package.h"

extern Package *globalPackage;

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;

// **************************************************
// Static functions declaration.
// **************************************************
static void _reset_static_variables(void);

// **************************************************
// Public functions implementation.
// **************************************************
Screen *setup_create(void) {
  _reset_static_variables();
  Screen *screen = MemAlloc(sizeof(Screen));
  if (!screen) {
    return NULL;
  }

  screen->type = SCREEN_TYPE_SETUP;
  return screen;
}

void setup_update(Screen *const screen) {
  // TODO
}

void setup_draw(const Screen *const screen) {
  ClearBackground(globalPackage->theme.colors[0]);

  int32_t middleWidth = GetScreenWidth() / 2;
  int32_t middleHeight = GetScreenHeight() / 2;

  DrawLine(-100 + middleWidth, middleHeight, 100 + middleWidth, middleHeight,
           RED);
  DrawLine(middleWidth, -100 + middleHeight, middleWidth, middleHeight + 100,
           GREEN);
}

ScreenType setup_next_screen(void) { return __nextScreenType; }

void setup_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _reset_static_variables(void) {
  __nextScreenType = SCREEN_TYPE_UNDEFINED;
}
