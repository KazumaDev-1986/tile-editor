#include <stddef.h>

#include "include/app_state.h"
#include "include/config.h"
#include "include/grid.h"
#include "include/package.h"
#include "include/raylib.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static const CustomCamera *__customCamera = NULL;
static bool __showGrid = true;

// **************************************************
// Static functions declaration.
// **************************************************
static bool _create_squares(Grid *const grid);
static void _destroy_squares(Square **ptrSquare);
static void _load_canvas(Grid *const grid);
static void _unload_canvas(Grid *const grid);
static void _check_hover_square(Grid *const grid);
static void _keyboard_event(void);

// **************************************************
// Public functions implementation.
// **************************************************
Grid *grid_create(uint8_t width, uint8_t height, uint8_t side,
                  const CustomCamera *customCamera) {
  Grid *grid = MemAlloc(sizeof(Grid));
  if (!grid) {
    return NULL;
  }

  grid->width = width;
  grid->height = height;
  grid->side = side;
  __customCamera = customCamera;
  if (_create_squares(grid)) {
    grid_destroy(&grid);
    return NULL;
  }
  _load_canvas(grid);
  return grid;
}

void grid_update(Grid *const grid) {
  if (grid) {
    _check_hover_square(grid);
    _keyboard_event();
  }
}

void grid_draw(const Grid *const grid) {
  if (grid) {
    if (__showGrid) {
      DrawTextureRec(grid->canvas.texture,
                     (Rectangle){
                         0,
                         0,
                         grid->canvas.texture.width,
                         -grid->canvas.texture.height,
                     },
                     (Vector2){0}, globalPackage->theme.colors[7]);
    }
  }

  if (grid->hoverPos.x > -1 && grid->hoverPos.y > -1) {
    DrawRectangleLines(grid->hoverPos.x, grid->hoverPos.y, grid->side,
                       grid->side, globalPackage->theme.colors[7]);
  }
}

void grid_destroy(Grid **ptrGrid) {
  if (ptrGrid && *ptrGrid) {
    _unload_canvas((*ptrGrid));
    _destroy_squares(&(*ptrGrid)->buffer);
    MemFree(*ptrGrid);
    *ptrGrid = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static bool _create_squares(Grid *const grid) {
  size_t size = grid->width * grid->height;
  grid->buffer = MemAlloc(sizeof(Square) * size);
  if (!grid->buffer) {
    grid->buffer = NULL;
    return true;
  }

  uint16_t posX = 0;
  uint16_t posY = 0;
  for (size_t i = 0; i < grid->height; ++i) {
    for (size_t j = 0; j < grid->width; ++j) {
      grid->buffer[i * grid->width + j] = (Square){
          .x = posX,
          .y = posY,
          .value = 0,
      };
      posX += grid->side;
    }
    posX = 0;
    posY += grid->side;
  }

  return false;
}

static void _destroy_squares(Square **ptrSquare) {
  if (ptrSquare && *ptrSquare) {
    MemFree(*ptrSquare);
    *ptrSquare = NULL;
  }
}

static void _load_canvas(Grid *const grid) {
  if (grid) {
    int32_t screenWidth = TILE_EDITOR_VIRTUAL_SCREEN_WIDTH;
    int32_t screenHeight = TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT;
    grid->canvas = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(grid->canvas.texture, TEXTURE_FILTER_POINT);

    BeginTextureMode(grid->canvas);
    for (size_t i = 0; i < grid->height; ++i) {
      for (size_t j = 0; j < grid->width; ++j) {
        int32_t posX = (int32_t)grid->buffer[i * grid->width + j].x;
        int32_t posY = (int32_t)grid->buffer[i * grid->width + j].y;
        DrawRectangleLines(posX, posY, grid->side, grid->side,
                           globalPackage->theme.colors[7]);
        // DrawRectangleLinesEx((Rectangle){posX, posY, grid->side, grid->side},
        // 1,
        //                      TILE_EDITOR_COLOR_GRAY_LIGHT);
      }
    }
    EndTextureMode();
  }
}

static void _unload_canvas(Grid *const grid) {
  if (grid && grid->canvas.id != 0) {
    UnloadRenderTexture(grid->canvas);
  }
}

static void _check_hover_square(Grid *const grid) {
  if (__customCamera) {
    Vector2 world =
        GetScreenToWorld2D(GetMousePosition(), __customCamera->camera);

    int x = (int)(world.x / grid->side);
    int y = (int)(world.y / grid->side);
    grid->hoverPos = (Vector2){-1, -1};
    if (x >= 0 && x < grid->width && y >= 0 && y < grid->height) {
      grid->hoverPos.x = x * grid->side;
      grid->hoverPos.y = y * grid->side;
    }
  }
}
static void _keyboard_event(void) {
  if (IsKeyPressed(KEY_F2)) {
    __showGrid = !__showGrid;
  }
}
