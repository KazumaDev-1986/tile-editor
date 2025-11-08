#include "include/tile_map.h"
#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"

extern Package *globalPackage;
extern AppState *globalAppState;
// **************************************************
// Static variables declaration.
// **************************************************
static const size_t __VELOCITY = 8;

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_tileMap(TileMap *tileMap);
static void _initialize_tile(Tile *const tile, size_t tx, size_t ty);
static void _draw_tileMap(const TileMap *const tileMap);
static void _draw_tile(const Tile *const tile, Offset offset);
static void _keyboatd_events(TileMap *const tileMap);

// **************************************************
// Public functions implementation.
// **************************************************
TileMap *tileMap_create(void) {
  TileMap *tileMap = MemAlloc(sizeof(TileMap));
  if (!tileMap) {
    return NULL;
  }

  _initialize_tileMap(tileMap);
  return tileMap;
}

void tileMap_update(TileMap *const tileMap) { _keyboatd_events(tileMap); }

void tileMap_draw(const TileMap *const tileMap) { _draw_tileMap(tileMap); }

void tileMap_destroy(TileMap **const ptrTileMap) {
  if (ptrTileMap && *ptrTileMap) {
    MemFree(*ptrTileMap);
    *ptrTileMap = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_tileMap(TileMap *tileMap) {
  tileMap->offset.x = 0;
  tileMap->offset.y = 0;
  tileMap->width = TILE_EDITOR_TILE_MAP_TILE_LIST_WIDTH;
  tileMap->height = TILE_EDITOR_TILE_MAP_TILE_LIST_HEIGHT;

  for (size_t ty = 0; ty < tileMap->height; ++ty) {
    for (size_t tx = 0; tx < tileMap->width; ++tx) {
      Tile *tile = &tileMap->tiles[ty * tileMap->width + tx];
      _initialize_tile(tile, tx, ty + 1);
    }
  }
}

static void _initialize_tile(Tile *const tile, size_t tx, size_t ty) {
  tile->width = TILE_EDITOR_TILE_MAP_PIXEL_LIST_WIDTH;
  tile->height = TILE_EDITOR_TILE_MAP_PIXEL_LIST_HEIGHT;

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
    for (size_t tx = 0; tx < tileMap->width; ++tx) {
      size_t index = ty * tileMap->width + tx;
      const Tile *const tile = &tileMap->tiles[index];
      _draw_tile(tile, tileMap->offset);
    }
  }
}

static void _draw_tile(const Tile *const tile, Offset offset) {
  ZoomLevel zoom = globalAppState->zoom;

  for (size_t py = 0; py < tile->height; ++py) {
    for (size_t px = 0; px < tile->width; ++px) {
      size_t index = py * tile->width + px;
      const Pixel *const pixel = &tile->pixels[index];

      float x = (pixel->x - offset.x) * zoom;
      float y = (pixel->y - offset.y) * zoom;
      if ((pixel->x == 0 || (pixel->x != 0 && 8 % pixel->x == 1)) ||
          (pixel->y == 0 || (pixel->y != 0 && 8 % pixel->y == 1))) {
        DrawRectangle(x, y, zoom, zoom, pixel->color);
      }
      // DrawRectangle(x, y, zoom, zoom, pixel->color);
    }
  }
}
static void _keyboatd_events(TileMap *const tileMap) {
  if (IsKeyPressed(KEY_UP)) {
    tileMap->offset.y += __VELOCITY;
  }
  if (IsKeyPressed(KEY_RIGHT)) {
    tileMap->offset.x -= __VELOCITY;
  }
  if (IsKeyPressed(KEY_DOWN)) {
    tileMap->offset.y -= __VELOCITY;
  }
  if (IsKeyPressed(KEY_LEFT)) {
    tileMap->offset.x += __VELOCITY;
  }
}
