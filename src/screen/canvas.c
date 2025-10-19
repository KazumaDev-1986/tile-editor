#include <stddef.h>

#include "../include/app_state.h"
#include "../include/bar.h"
#include "../include/package.h"
#include "../include/raylib.h"
#include "../include/screen.h"
#include "../include/tile_map.h"

extern Package *globalPackage;
extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;
static Bar *__menuBar = NULL;
static Bar *__statusBar = NULL;
static TileMap *__tileMap = NULL;
static RenderTexture __backaground;

// **************************************************
// Static function declaration.
// **************************************************
static void _reset_static_variables(void);
static void _load_background(void);
static void _draw_background(void);
static void _unload_background(void);

// **************************************************
// Public functions implementation.
// **************************************************
Screen *canvas_create(void) {
  Screen *screen = MemAlloc(sizeof(Screen));
  if (!screen) {
    return NULL;
  }
  _reset_static_variables();
  screen->type = SCREEN_TYPE_CANVAS;

  __menuBar = menuBar_create();
  if (!__menuBar) {
    canvas_destroy(&screen);
    return NULL;
  }

  __statusBar = statusBar_create();
  if (!__statusBar) {
    canvas_destroy(&screen);
    return NULL;
  }

  __tileMap = tileMap_create();
  if (!__tileMap) {
    canvas_destroy(&screen);
    return NULL;
  }

  _load_background();
  return screen;
}

void canvas_update(Screen *const screen) {
  tileMap_update(__tileMap);
  menuBar_update(__menuBar);
  statusBar_update(__statusBar);
}

void canvas_draw(const Screen *const screen) {
  ClearBackground(globalPackage->theme.colors[0]);
  // _draw_background();
  tileMap_draw(__tileMap);
  // menuBar_draw(__menuBar);
  // statusBar_draw(__statusBar);
}

ScreenType canvas_next_screen(void) { return __nextScreenType; }

void canvas_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    _unload_background();
    tileMap_destroy(&__tileMap);
    menuBar_destroy(&__menuBar);
    statusBar_destroy(&__statusBar);
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}

// **************************************************
// Static function declaration.
// **************************************************
static void _load_background(void) {
  int32_t width = TILE_EDITOR_VIRTUAL_SCREEN_WIDTH;
  int32_t height = TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT;

  __backaground = LoadRenderTexture(width, height);

  BeginTextureMode(__backaground);
  ClearBackground(globalPackage->theme.colors[0]);

  for (int32_t y = 0; y < height * 2; y += 8) {
    DrawLine(0, y, width, y - width, globalPackage->theme.colors[1]);
    DrawLine(0, y + 1, width, (y + 1) - width, globalPackage->theme.colors[1]);
  }
  DrawRectangle(0, 8, width, 1, globalPackage->theme.colors[0]);
  DrawRectangle(0, height - 9, width, 1, globalPackage->theme.colors[6]);

  EndTextureMode();
}

static void _draw_background(void) {
  if (__backaground.id != 0) {
    DrawTextureRec(__backaground.texture,
                   (Rectangle){
                       0,
                       0,
                       __backaground.texture.width,
                       -__backaground.texture.height,

                   },
                   (Vector2){0, 0}, WHITE);
  }
}

static void _unload_background(void) {
  if (__backaground.id != 0) {
    UnloadRenderTexture(__backaground);
  }
}

static void _reset_static_variables(void) {
  __nextScreenType = SCREEN_TYPE_UNDEFINED;
  __menuBar = NULL;
  __statusBar = NULL;
  __tileMap = NULL;
}
