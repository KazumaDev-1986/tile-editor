#ifndef TILE_EDITOR_SCREEN_H
#define TILE_EDITOR_SCREEN_H

#include "config.h"

TILE_EDITOR typedef enum {
  SCREEN_TYPE_UNDEFINED = 0,
  SCREEN_TYPE_SETUP,
  SCREEN_TYPE_CANVAS,
} ScreenType;

TILE_EDITOR typedef struct {
  ScreenType type;
} Screen;

#if defined(__cplusplus)
extern "C" {
#endif

// Setup Screen.
TILE_EDITOR Screen *setup_create(void);
TILE_EDITOR void setup_update(Screen *const screen);
TILE_EDITOR void setup_draw(const Screen *const screen);
TILE_EDITOR ScreenType setup_next_screen(void);
TILE_EDITOR void setup_destroy(Screen **ptrScreen);

// Canvas Screen.
TILE_EDITOR Screen *canvas_create(void);
TILE_EDITOR void canvas_update(Screen *const screen);
TILE_EDITOR void canvas_draw(const Screen *const screen);
TILE_EDITOR ScreenType canvas_next_screen(void);
TILE_EDITOR void canvas_destroy(Screen **ptrScreen);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_SCREEN_H
