#ifndef TILE_EDITOR_TILE_MAP_H
#define TILE_EDITOR_TILE_MAP_H

#include "config.h"

TILE_EDITOR typedef struct {
  uint32_t x;
  uint32_t y;
  Color color;
} Pixel;

TILE_EDITOR typedef struct {
  size_t width;
  size_t height;
  Pixel pixels[TILE_EDITOR_TILE_MAP_PIXEL_LIST_WIDTH * TILE_EDITOR_TILE_MAP_PIXEL_LIST_HEIGHT];
} Tile;

TILE_EDITOR typedef struct {
  int32_t x;
  int32_t y;
} Offset;

TILE_EDITOR typedef struct {
  size_t width;
  size_t height;
  Tile tiles[TILE_EDITOR_TILE_MAP_TILE_LIST_WIDTH *
             TILE_EDITOR_TILE_MAP_TILE_LIST_HEIGHT];
  Offset offset;
} TileMap;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR TileMap *tileMap_create(void);

TILE_EDITOR void tileMap_update(TileMap *const tileMap);

TILE_EDITOR void tileMap_draw(const TileMap *const tileMap);

TILE_EDITOR void tileMap_destroy(TileMap **const ptrTileMap);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_TILE_MAP_H
