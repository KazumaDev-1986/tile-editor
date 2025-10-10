#include <stddef.h>

#include "../include/raylib.h"
#include "../include/screen.h"

// **************************************************
// Static variables & functions implementation.
// **************************************************
static ScreenType __nextScreen = SCREEN_TYPE_UNDEFINED;

// **************************************************
// Public functions implementation.
// **************************************************
Screen *canvas_create(void) {
  Screen *screen = MemAlloc(sizeof(Screen));
  if (!screen) {
    return NULL;
  }
  screen->type = SCREEN_TYPE_CANVAS;
  return screen;
}

void canvas_update(Screen *const screen) {
  // TODO
}

void canvas_draw(const Screen *const screen) { ClearBackground(RED); }

ScreenType canvas_next_screen(void) { return __nextScreen; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}
