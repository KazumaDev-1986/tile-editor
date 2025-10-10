#ifndef TILE_EDITOR_SCREEN_H
#define TILE_EDITOR_SCREEN_H

#include "config.h"

TILE_EDITOR typedef enum {
  SCREEN_TYPE_UNDEFINED = 0,
  SCREEN_TYPE_CANVAS,
} ScreenType;

TILE_EDITOR typedef struct {
  ScreenType type;
} Screen;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR Screen *canvas_create(void);

TILE_EDITOR void canvas_update(Screen *const screen);

TILE_EDITOR void canvas_draw(const Screen *const screen);

TILE_EDITOR ScreenType canvas_next_screen(void);

TILE_EDITOR void canvas_destroy(Screen **ptrScreen);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_SCREEN_H
