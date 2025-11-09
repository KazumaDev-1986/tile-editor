#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"
#include "include/tile_map.h"

extern Package *globalPackage;
extern AppState *globalAppState;
// **************************************************
// Static variables declaration.
// **************************************************
static const size_t __VELOCITY = 8;
static bool __showGrid = false;
static Vector2 __mousePosition = (Vector2){0};

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_tileMap(TileMap *tileMap);
static void _initialize_tile(Tile *const tile, size_t tx, size_t ty);
static void _draw_tileMap(const TileMap *const tileMap);
static void _draw_tile(const Tile *const tile, Offset offset, size_t spaceX,
                       size_t spaceY);
static void _keyboatd_events(TileMap *const tileMap);
static void _get_mouse_position(void);
static void _reset_static_variables(void);

// **************************************************
// Public functions implementation.
// **************************************************
TileMap *tileMap_create(void) {
  TileMap *tileMap = MemAlloc(sizeof(TileMap));
  if (!tileMap) {
    return NULL;
  }
  _reset_static_variables();
  _initialize_tileMap(tileMap);
  return tileMap;
}

void tileMap_update(TileMap *const tileMap) {
  _keyboatd_events(tileMap);
  _get_mouse_position();
}

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
static void _reset_static_variables(void) {
  __showGrid = false;
  __mousePosition = (Vector2){0};
}

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
      _draw_tile(tile, tileMap->offset, tx, ty);
    }
  }
}

static void _draw_tile(const Tile *const tile, Offset offset, size_t spaceX,
                       size_t spaceY) {
  ZoomLevel zoom = globalAppState->zoom;
  size_t diffX = __showGrid ? spaceX : 0;
  size_t diffY = __showGrid ? spaceY : 0;

  Color color = WHITE;
  Rectangle rec = (Rectangle){(tile->pixels[0].x - offset.x + diffX) * zoom,
                              (tile->pixels[0].y - offset.y + diffY) * zoom,
                              TILE_EDITOR_TILE_MAP_PIXEL_LIST_WIDTH * zoom,
                              TILE_EDITOR_TILE_MAP_PIXEL_LIST_HEIGHT * zoom};

  if (CheckCollisionPointRec(__mousePosition, rec)) {
    color = RED;
  }

  for (size_t py = 0; py < tile->height; ++py) {
    for (size_t px = 0; px < tile->width; ++px) {
      size_t index = py * tile->width + px;
      const Pixel *const pixel = &tile->pixels[index];

      size_t x = (pixel->x - offset.x + diffX) * zoom;
      size_t y = (pixel->y - offset.y + diffY) * zoom;
      DrawRectangle(x, y, zoom, zoom, color);
    }
  }

  DrawLine(__mousePosition.x - 10, __mousePosition.y, __mousePosition.x + 10,
           __mousePosition.y, RED);
  DrawLine(__mousePosition.x, __mousePosition.y - 10, __mousePosition.x,
           __mousePosition.y + 10, GREEN);
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
  if (IsKeyPressed(KEY_G)) {
    __showGrid = !__showGrid;
  }
}
static void _get_mouse_position(void) {
  Vector2 mouse = GetMousePosition();

  float localX = mouse.x - globalAppState->view.x;
  float localY = mouse.y - globalAppState->view.y;

  bool inside = localX >= 0 && localX < globalAppState->view.width &&
                localY >= 0 && localY < globalAppState->view.height;

  if (inside) {
    __mousePosition.x = (localX / globalAppState->view.width) *
                        TILE_EDITOR_VIRTUAL_SCREEN_WIDTH;
    __mousePosition.y = (localY / globalAppState->view.height) *
                        TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT;
  }
}
