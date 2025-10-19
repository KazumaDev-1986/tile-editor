#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"
#include "include/tile_map.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_tileMap(TileMap *tileMap);
static void _initialize_tile(Tile *const tile, size_t tx, size_t ty);

static void _draw_tileMap(const TileMap *const tileMap);
static void _draw_tile(const Tile *const tile);

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
  _draw_tileMap(tileMap);

  // float posX = 0;
  // float posY = 0;
  // for (size_t ty = 0; ty < tileMap->height; ++ty) {
  //   for (size_t tx = 0; tx < tileMap->width; ++tx) {
  //     DrawRectangleLines(posX, posY, 8, 8, RED);
  //     posX += 8;
  //   }
  //   posX = 0;
  //   posY += 8;
  // }

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
  tileMap->width = 2;
  tileMap->height = 2;

  for (size_t ty = 0; ty < tileMap->height; ++ty) {
    for (size_t tx = 0; tx < tileMap->width; ++tx) {
      Tile *tile = &tileMap->tiles[ty * tileMap->width + tx];
      _initialize_tile(tile, tx, ty);
    }
  }
}

static void _initialize_tile(Tile *const tile, size_t tx, size_t ty) {
  tile->width = 8;
  tile->height = 8;

  for (size_t py = 0; py < tile->height; ++py) {
    for (size_t px = 0; px < tile->width; ++px) {
      size_t index = py * tile->width + px;
      tile->pixels[index].x = tx * tile->width + px;
      tile->pixels[index].y = ty * tile->height + py;
      tile->pixels[index].color = globalPackage->theme.colors[7];
    }
  }
}

static void _draw_tileMap(const TileMap *const tileMap) {
  for (size_t ty = 0; ty < tileMap->height; ++ty) {
    for (size_t tx = 0; tx < tileMap->height; ++tx) {
      size_t index = ty * tileMap->width + tx;
      const Tile *const tile = &tileMap->tiles[index];
      _draw_tile(tile);
    }
  }
}

static void _draw_tile(const Tile *const tile) {
  ZoomLevel zoom = globalAppState->zoom;

  for (size_t py = 0; py < tile->height; ++py) {
    for (size_t px = 0; px < tile->height; ++px) {
      size_t index = py * tile->width + px;
      const Pixel *const pixel = &tile->pixels[index];
      DrawRectangle(pixel->x, pixel->y, zoom, zoom, pixel->color);
    }
  }
}
