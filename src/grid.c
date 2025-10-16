#include <stddef.h>

#include "include/app_state.h"
#include "include/grid.h"
#include "include/package.h"
#include "include/raylib.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************

// **************************************************
// Static functions declaration.
// **************************************************
static bool _create_squares(Grid *const grid);
static void _destroy_squares(Square **ptrSquare);
static void _check_hover_square(Grid *const grid);
static void _keyboard_event(void);

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
  return grid;
}

void grid_update(Grid *const grid) {
  if (grid) {
    _check_hover_square(grid);
    _keyboard_event();
  }
}

void grid_draw(const Grid *const grid) {
  if (!grid) {
    return;
  }

  // if (grid->hoverPos.x > -1 && grid->hoverPos.y > -1) {
  //   DrawRectangleLines(grid->hoverPos.x, grid->hoverPos.y, grid->side,
  //                      grid->side, globalPackage->theme.colors[7]);
  // }
}

void grid_destroy(Grid **ptrGrid) {
  if (ptrGrid && *ptrGrid) {
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

static void _check_hover_square(Grid *const grid) {
  // TODO
}
static void _keyboard_event(void) {
  // TODO
}
