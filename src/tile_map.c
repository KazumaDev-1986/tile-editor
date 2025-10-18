#include "include/tile_map.h"
#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_tileMap(TileMap *tileMap);

static void _initialize_tile(Tile *const tile, size_t tx, size_t ty);

// **************************************************
// Public functions implementation.
// **************************************************
TILE_EDITOR TileMap *tileMap_create(void) {
  TileMap *tileMap = MemAlloc(sizeof(TileMap));
  if (!tileMap) {
    return NULL;
  }

  _initialize_tileMap(tileMap);
  return tileMap;
}

TILE_EDITOR void tileMap_update(TileMap *const tileMap) {
  // TODO
}

TILE_EDITOR void tileMap_draw(const TileMap *const tileMap) {
  for (size_t ty = 0; ty < TILE_EDITOR_TILE_HEIGHT; ++ty) {
    for (size_t tx = 0; tx < TILE_EDITOR_TILE_WIDTH; ++tx) {

      const Tile *const tile =
          &tileMap->tiles[ty * TILE_EDITOR_TILE_WIDTH + tx];
      for (size_t py = 0; py < TILE_EDITOR_PIXEL_HEIGHT; ++py) {
        for (size_t px = 0; px < TILE_EDITOR_PIXEL_WIDTH; ++px) {
          const Pixel *const pixel =
              &tile->pixels[py * TILE_EDITOR_PIXEL_WIDTH + px];

          DrawRectangle(pixel->x, pixel->y, globalAppState->zoom,
                        globalAppState->zoom, pixel->color);
        }
      }
    }
  }
}

TILE_EDITOR void tileMap_destroy(TileMap **const ptrTileMap) {
  if (ptrTileMap && *ptrTileMap) {
    MemFree(*ptrTileMap);
    *ptrTileMap = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_tileMap(TileMap *tileMap) {
  for (size_t ty = 0; ty < TILE_EDITOR_TILE_HEIGHT; ++ty) {
    for (size_t tx = 0; tx < TILE_EDITOR_TILE_WIDTH; ++tx) {

      Tile *tile = &tileMap->tiles[ty * TILE_EDITOR_TILE_WIDTH + tx];
      _initialize_tile(tile, tx, ty);
    }
  }
}

static void _initialize_tile(Tile *const tile, size_t tx, size_t ty) {
  for (size_t py = 0; py < TILE_EDITOR_PIXEL_HEIGHT; ++py) {
    for (size_t px = 0; px < TILE_EDITOR_PIXEL_WIDTH; ++px) {

      Pixel *const pixel = &tile->pixels[py * TILE_EDITOR_PIXEL_WIDTH + px];
      pixel->x = tx * TILE_EDITOR_PIXEL_HEIGHT + px;
      pixel->y = ty * TILE_EDITOR_PIXEL_WIDTH + py;
      pixel->color = globalPackage->theme.colors[0];
    }
  }
}
