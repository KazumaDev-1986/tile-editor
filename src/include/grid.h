#ifndef TILE_EDITOR_GRID_H
#define TILE_EDITOR_GRID_H

#include <stdint.h>

#include "config.h"
#include "raylib.h"

TILE_EDITOR typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t value;
} Square;

TILE_EDITOR typedef struct {
  uint8_t width;
  uint8_t height;
  uint8_t side;
  Square *buffer;

  RenderTexture2D canvas;
} Grid;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR Grid *grid_create(uint8_t width, uint8_t height, uint8_t side);

TILE_EDITOR void grid_update(Grid *const grid);

TILE_EDITOR void grid_draw(const Grid *const grid);

TILE_EDITOR void grid_destroy(Grid **ptrGrid);

#if defined(__cplusplus)
}
#endif

#endif  // TILE_EDITOR_GRID_H
