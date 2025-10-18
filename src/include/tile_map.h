#ifndef TILE_EDITOR_TILE_MAP_H
#define TILE_EDITOR_TILE_MAP_H

#include "config.h"

TILE_EDITOR typedef struct {
  uint32_t x;
  uint32_t y;
  Color color;
} Pixel;

TILE_EDITOR typedef struct {
  Pixel pixels[TILE_EDITOR_PIXEL_TOTAL];
} Tile;

TILE_EDITOR typedef struct {
  Tile tiles[TILE_EDITOR_TILE_TOTAL];
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
