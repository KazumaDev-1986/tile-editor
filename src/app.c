#include <stddef.h>

#include "include/app.h"
#include "include/config.h"
#include "include/raylib.h"
#include "include/screen.h"

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_raylib(void);
static void _finalize_raylib(void);

static ScreenType _screen_update(Screen *const screen);
static void _screen_draw(const Screen *const screen);
static void _screen_destroy(Screen **ptrScreen);
static void _screen_change(Screen **ptrScreen, ScreenType type);

// **************************************************
// Public functions implementation.
// **************************************************
App *app_create(void) {
  App *app = MemAlloc(sizeof(App));
  if (!app) {
    return NULL;
  }
  _initialize_raylib();
  app->currentScreen = NULL;
  _screen_change(&app->currentScreen, SCREEN_TYPE_CANVAS);

  return app;
}

void app_run(App *const app) {
  while (!WindowShouldClose()) {
    ScreenType type = _screen_update(app->currentScreen);
    if (type != SCREEN_TYPE_UNDEFINED) {
      _screen_destroy(&app->currentScreen);
      _screen_change(&app->currentScreen, type);
    }

    BeginDrawing();
    _screen_draw(app->currentScreen);
    EndDrawing();
  }
}

void app_destroy(App **ptrApp) {
  if (ptrApp && *ptrApp) {
    _screen_destroy(&(*ptrApp)->currentScreen);
    _finalize_raylib();
    MemFree(*ptrApp);
    *ptrApp = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_raylib(void) {
  InitWindow(TILE_EDITOR_SCREEN_WIDTH, TILE_EDITOR_SCREEN_HEIGHT,
             TILE_EDITOR_TITLE);
}

static void _finalize_raylib(void) { CloseWindow(); }

static ScreenType _screen_update(Screen *const screen) {
  ScreenType nextScreenType = SCREEN_TYPE_UNDEFINED;
  if (screen) {
    switch (screen->type) {
    case SCREEN_TYPE_CANVAS:
      canvas_update(screen);
      nextScreenType = canvas_next_screen();
      break;
    default:
      break;
    }
  }
  return nextScreenType;
}

static void _screen_draw(const Screen *const screen) {
  if (screen) {
    switch (screen->type) {
    case SCREEN_TYPE_CANVAS:
      canvas_draw(screen);
      break;
    default:
      break;
    }
  }
}

static void _screen_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    switch ((*ptrScreen)->type) {
    case SCREEN_TYPE_CANVAS:
      canvas_destroy(ptrScreen);
      break;
    default:
      break;
    }
  }
}

static void _screen_change(Screen **ptrScreen, ScreenType type) {
  if (ptrScreen) {
    switch (type) {
    case SCREEN_TYPE_CANVAS:
      *ptrScreen = canvas_create();
      break;
    default:
      break;
    }
  }
}
