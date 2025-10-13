#include <stdint.h>

#include "../include/form_setup.h"
#include "../include/raygui.h"
#include "../include/screen.h"

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;
static FormSetup *__formSetup = NULL;

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

  // TODO: Find a way to improve this.
  int32_t width = 368;
  int32_t height = 256;
  int32_t middleWidth = GetScreenWidth() / 2;
  int32_t middleHeight = GetScreenHeight() / 2;
  int32_t posX = middleWidth - width / 2;
  int32_t posY = middleHeight - height / 2;
  
  __formSetup = formSetup_create((Vector2){posX, posY}, (Vector2){width, height});
  if (!__formSetup) {
    setup_destroy(&screen);
    return NULL;
  }
  screen->type = SCREEN_TYPE_SETUP;
  return screen;
}

void setup_update(Screen *const screen) { formSetup_update(__formSetup); }

void setup_draw(const Screen *const screen) {
  ClearBackground(TILE_EDITOR_COLOR_GRAY_LIGHT);

  formSetup_draw(__formSetup);

  int32_t width = 250;
  int32_t height = 200;
  int32_t middleWidth = GetScreenWidth() / 2;
  int32_t middleHeight = GetScreenHeight() / 2;
  int32_t posX = middleWidth - width / 2;
  int32_t posY = middleHeight - height / 2;
  
  DrawLine(-100 + middleWidth, middleHeight, 100 + middleWidth, middleHeight,
           RED);
  DrawLine(middleWidth, -100 + middleHeight, middleWidth, middleHeight + 100,
           GREEN);
}

ScreenType setup_next_screen(void) { return __nextScreenType; }

void setup_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    formSetup_destroy(&__formSetup);
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _reset_static_variables(void) {
  __nextScreenType = SCREEN_TYPE_UNDEFINED;
  __formSetup = NULL;
}
