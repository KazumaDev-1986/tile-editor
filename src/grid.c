#include <stddef.h>

#include "include/config.h"
#include "include/grid.h"
#include "include/raylib.h"

// **************************************************
// Static functions declaration.
// **************************************************
static bool _create_squares(Grid *const grid);
static void _destroy_squares(Square **ptrSquare);
static void _load_canvas(Grid *const grid);
static void _unload_canvas(Grid *const grid);

// **************************************************
// Public functions implementation.
// **************************************************
Grid *grid_create(uint8_t width, uint8_t height, uint8_t side) {
  Grid *grid = MemAlloc(sizeof(Grid));
  if (!grid) {
    return NULL;
  }

  grid->width = width;
  grid->height = height;
  grid->side = side;
  if (_create_squares(grid)) {
    grid_destroy(&grid);
    return NULL;
  }
  _load_canvas(grid);
  return grid;
}

void grid_update(Grid *const grid) {
  if (grid) {
    // TODO
  }
}

void grid_draw(const Grid *const grid) {
  if (grid) {
    DrawTextureRec(grid->canvas.texture,
                   (Rectangle){
                       0,
                       0,
                       grid->canvas.texture.width,
                       -grid->canvas.texture.width,
                   },
                   (Vector2){0}, TILE_EDITOR_COLOR_GRAY_LIGHT);
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
    int32_t screenWidth = GetScreenWidth();
    int32_t screenHeight = GetScreenHeight();
    grid->canvas = LoadRenderTexture(screenWidth, screenHeight);

    BeginTextureMode(grid->canvas);
    ClearBackground(TILE_EDITOR_COLOR_GRAY_LIGHT);
    for (size_t i = 0; i < grid->height; ++i) {
      for (size_t j = 0; j < grid->width; ++j) {
        int32_t posX = (int32_t)grid->buffer[i * grid->width + j].x;
        int32_t posY = (int32_t)grid->buffer[i * grid->width + j].y;
        DrawRectangleLines(posX, posY, grid->side, grid->side,
                           TILE_EDITOR_COLOR_PURPLE_DARK);
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
