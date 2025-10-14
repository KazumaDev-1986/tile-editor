#include <stddef.h>
#include <stdint.h>

#include "include/app.h"
#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"
#include "include/screen.h"
#include "include/status_bar.h"
#include "include/tool_bar.h"

AppState *globalAppState = NULL;
Package *globalPackage = NULL;

// **************************************************
// Static variables declaration.
// **************************************************
static bool __showFps = false;
static StatusBar *__statusBar = NULL;
static ToolBar *__toolBar = NULL;

// **************************************************
// Static functions declaration.
// **************************************************
static void _reset_static_variables(void);
static void _initialize_raylib(void);
static void _finalize_raylib(void);
static ScreenType _screen_update(Screen *const screen);
static void _screen_draw(const Screen *const screen);
static void _screen_destroy(Screen **ptrScreen);
static void _screen_change(Screen **ptrScreen, ScreenType type);
static void _keyboard_event(void);
static void _draw_fps(void);

// **************************************************
// Public functions implementation.
// **************************************************
App *app_create(void) {
  _reset_static_variables();
  App *app = MemAlloc(sizeof(App));
  if (!app) {
    return NULL;
  }
  _initialize_raylib();
  globalPackage = package_create();
  globalAppState = appState_create();
  if (!globalPackage || !globalAppState) {
    app_destroy(&app);
    return NULL;
  }

  __statusBar = statusBar_create();
  if (!__statusBar) {
    app_destroy(&app);
    return NULL;
  }

  __toolBar = toolBar_create();
  if (!__toolBar) {
    app_destroy(&app);
    return NULL;
  }

  app->currentScreen = NULL;
  _screen_change(&app->currentScreen, SCREEN_TYPE_CANVAS);

  return app;
}

void app_run(App *const app) {
  while (!WindowShouldClose()) {
    appState_update(globalAppState);
    _keyboard_event();
    ScreenType type = _screen_update(app->currentScreen);
    if (type != SCREEN_TYPE_UNDEFINED) {
      _screen_destroy(&app->currentScreen);
      _screen_change(&app->currentScreen, type);
    }
    statusBar_update(__statusBar);
    toolBar_update(__toolBar);
    BeginDrawing();
    _screen_draw(app->currentScreen);
    statusBar_draw(__statusBar);
    toolBar_draw(__toolBar);
    if (__showFps) _draw_fps();
    EndDrawing();
  }
}

void app_destroy(App **ptrApp) {
  if (ptrApp && *ptrApp) {
    _screen_destroy(&(*ptrApp)->currentScreen);
    statusBar_destroy(&__statusBar);
    toolBar_destroy(&__toolBar);
    package_destroy(&globalPackage);
    appState_destroy(&globalAppState);
    _finalize_raylib();
    MemFree(*ptrApp);
    *ptrApp = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _initialize_raylib(void) {
#if defined(TILE_EDITOR_DEBUG)
  SetTraceLogLevel(LOG_DEBUG);
#endif

#if defined(TILE_EDITOR_SCREEN_RESIZABLE)
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
#endif

  InitWindow(TILE_EDITOR_SCREEN_WIDTH, TILE_EDITOR_SCREEN_HEIGHT,
             TILE_EDITOR_TITLE);

  SetTargetFPS(TILE_EDITOR_SCREEN_FPS);
}

static void _finalize_raylib(void) { CloseWindow(); }

static ScreenType _screen_update(Screen *const screen) {
  ScreenType nextScreenType = SCREEN_TYPE_UNDEFINED;
  if (screen) {
    switch (screen->type) {
      case SCREEN_TYPE_SETUP:
        setup_update(screen);
        nextScreenType = setup_next_screen();
        break;
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
      case SCREEN_TYPE_SETUP:
        setup_draw(screen);
        break;
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
      case SCREEN_TYPE_SETUP:
        setup_destroy(ptrScreen);
        break;
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
      case SCREEN_TYPE_SETUP:
        *ptrScreen = setup_create();
        break;
      case SCREEN_TYPE_CANVAS:
        *ptrScreen = canvas_create();
        break;
      default:
        break;
    }
  }
}

static void _keyboard_event(void) {
  if (IsKeyPressed(KEY_F1)) {
    __showFps = !__showFps;
  }
}

static void _draw_fps(void) { DrawFPS(0, 0); }

static void _reset_static_variables(void) {
  __showFps = false;
  __statusBar = NULL;
  __toolBar = NULL;
}
