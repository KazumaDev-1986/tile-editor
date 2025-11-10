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
static float __wheelCounter = 0;
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
static void _mouse_events(TileMap *const tileMap);
static void _get_mouse_position(void);
static void _draw_background_grid(const TileMap *const tileMap);
static void _draw_grid_hover(const Tile *const tile, Offset offset,
                             size_t diffX, size_t diffY);
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
  _mouse_events(tileMap);
  _get_mouse_position();
}

void tileMap_draw(const TileMap *const tileMap) {
  _draw_background_grid(tileMap);
  _draw_tileMap(tileMap);
}

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
  __wheelCounter = 0;
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
      tile->pixels[index].color = globalPackage->theme.colors[0];
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

  for (size_t py = 0; py < tile->height; ++py) {
    for (size_t px = 0; px < tile->width; ++px) {
      size_t index = py * tile->width + px;
      const Pixel *const pixel = &tile->pixels[index];

      size_t x = (pixel->x - offset.x + diffX) * zoom;
      size_t y = (pixel->y - offset.y + diffY) * zoom;
      DrawRectangle(x, y, zoom, zoom, pixel->color);
    }
  }

  _draw_grid_hover(tile, offset, diffX, diffY);
}

static void _keyboatd_events(TileMap *const tileMap) {
  if (IsKeyPressed(KEY_UP)) {
    tileMap->offset.y -= __VELOCITY;
  }
  if (IsKeyPressed(KEY_RIGHT)) {
    tileMap->offset.x += __VELOCITY;
  }
  if (IsKeyPressed(KEY_DOWN)) {
    tileMap->offset.y += __VELOCITY;
  }
  if (IsKeyPressed(KEY_LEFT)) {
    tileMap->offset.x -= __VELOCITY;
  }
  if (IsKeyPressed(KEY_G)) {
    __showGrid = !__showGrid;
  }
}

static void _mouse_events(TileMap *const tileMap) {
  if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
    Vector2 mouseDelta = GetMouseDelta();
    ZoomLevel zoom = globalAppState->zoom;
    float speed = 0.3f;

    tileMap->offset.x -= mouseDelta.x * speed / zoom;
    tileMap->offset.y -= mouseDelta.y * speed / zoom;
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    __wheelCounter += wheel * 0.4f;
    if (__wheelCounter < ZOOM_LEVEL_ONE)
      __wheelCounter = ZOOM_LEVEL_ONE;
    if (__wheelCounter > ZOOM_LEVEL_FOUR)
      __wheelCounter = ZOOM_LEVEL_FOUR;

    appState_setZoom(globalAppState, (int32_t)__wheelCounter);
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

static void _draw_background_grid(const TileMap *const tileMap) {
  const Tile *const tile = &tileMap->tiles[0];
  ZoomLevel zoom = globalAppState->zoom;

  size_t x = (tile->pixels[0].x - tileMap->offset.x) * zoom;
  size_t y = (tile->pixels[0].y - tileMap->offset.y) * zoom;
  size_t width = TILE_EDITOR_TILE_MAP_PIXEL_LIST_WIDTH *
                 TILE_EDITOR_TILE_MAP_TILE_LIST_WIDTH * zoom;
  size_t height = TILE_EDITOR_TILE_MAP_PIXEL_LIST_HEIGHT *
                  TILE_EDITOR_TILE_MAP_TILE_LIST_HEIGHT * zoom;

  // Info:Padding background.
  DrawRectangle(x - 1, y - 1, width + 2, height + 2,
                globalPackage->theme.colors[7]);
  DrawRectangle(x, y, width, height, globalPackage->theme.colors[0]);
}

static void _draw_grid_hover(const Tile *const tile, Offset offset,
                             size_t diffX, size_t diffY) {
  ZoomLevel zoom = globalAppState->zoom;
  Rectangle rec = (Rectangle){(tile->pixels[0].x - offset.x + diffX) * zoom,
                              (tile->pixels[0].y - offset.y + diffY) * zoom,
                              TILE_EDITOR_TILE_MAP_PIXEL_LIST_WIDTH * zoom,
                              TILE_EDITOR_TILE_MAP_PIXEL_LIST_HEIGHT * zoom};

  if (CheckCollisionPointRec(__mousePosition, rec)) {
    DrawRectangleLinesEx(rec, 1.f, globalPackage->theme.colors[6]);
  }
}
