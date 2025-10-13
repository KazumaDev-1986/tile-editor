#include <stddef.h>
#include <stdint.h>

#include "include/app.h"
#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"
#include "include/screen.h"

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

AppState *globalAppState = NULL;
Package *globalPackage = NULL;

// **************************************************
// Static variables declaration.
// **************************************************
static bool __showFps = false;

// **************************************************
// Static functions declaration.
// **************************************************
static void _initialize_raylib(void);
static void _initialize_raygui(void);
static void _finalize_raylib(void);
static ScreenType _screen_update(Screen *const screen);
static void _screen_draw(const Screen *const screen);
static void _screen_destroy(Screen **ptrScreen);
static void _screen_change(Screen **ptrScreen, ScreenType type);
static void _keyboard_event(void);
static void _draw_fps(void);
static void _check_resize_screen(void);

// **************************************************
// Public functions implementation.
// **************************************************
App *app_create(void) {
  App *app = MemAlloc(sizeof(App));
  if (!app) {
    return NULL;
  }
  _initialize_raylib();
  globalPackage = package_create();
  globalAppState = appState_create();
  _initialize_raygui();
  if (!globalPackage || !globalAppState) {
    app_destroy(&app);
    return NULL;
  }

  app->currentScreen = NULL;
  _screen_change(&app->currentScreen, SCREEN_TYPE_SETUP);

  return app;
}

void app_run(App *const app) {
  while (!WindowShouldClose()) {
    appState_update(globalAppState);
    _check_resize_screen();
    _keyboard_event();
    ScreenType type = _screen_update(app->currentScreen);
    if (type != SCREEN_TYPE_UNDEFINED) {
      _screen_destroy(&app->currentScreen);
      _screen_change(&app->currentScreen, type);
    }

    BeginDrawing();
    _screen_draw(app->currentScreen);
    if (__showFps) _draw_fps();
    EndDrawing();
  }
}

void app_destroy(App **ptrApp) {
  if (ptrApp && *ptrApp) {
    _screen_destroy(&(*ptrApp)->currentScreen);
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

static void _initialize_raygui(void) {
  GuiSetFont(globalPackage->fonts[0]);  // Font[0]: 04b_03
  GuiSetStyle(DEFAULT, TEXT_SIZE, TILE_EDITOR_RAYGUI_FONT_SIZE);
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

static void _check_resize_screen(void) {
  if (globalAppState->shouldUpdateScreen) {
    float scale =
        fminf((float)globalAppState->screenWidth / TILE_EDITOR_SCREEN_WIDTH,
              (float)globalAppState->screenHeight / TILE_EDITOR_SCREEN_HEIGHT);
    TraceLog(LOG_DEBUG, "scale: %f", scale);
    GuiSetStyle(DEFAULT, TEXT_SIZE, TILE_EDITOR_RAYGUI_FONT_SIZE * scale);
  }
}
