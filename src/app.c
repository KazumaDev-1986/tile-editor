#include <stdint.h>

#include "include/app.h"
#include "include/app_state.h"
#include "include/config.h"
#include "include/package.h"
#include "include/raylib.h"
#include "include/screen.h"

AppState *globalAppState = NULL;
Package *globalPackage = NULL;

// **************************************************
// Static variables declaration.
// **************************************************
static bool __showFps = false;
static RenderTexture2D __target;

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

  app->currentScreen = NULL;
  _screen_change(&app->currentScreen, SCREEN_TYPE_CANVAS);

  __target = LoadRenderTexture(TILE_EDITOR_VIRTUAL_SCREEN_WIDTH,
                               TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT);
  SetTextureFilter(__target.texture, TEXTURE_FILTER_POINT);

  return app;
}

void app_run(App *const app) {
  while (!WindowShouldClose()) {
    // Updating.
    // --------------------------------------------------
    appState_update(globalAppState);
    _keyboard_event();
    ScreenType type = _screen_update(app->currentScreen);
    if (type != SCREEN_TYPE_UNDEFINED) {
      _screen_destroy(&app->currentScreen);
      _screen_change(&app->currentScreen, type);
    }
    // Virtual Drawing.
    // --------------------------------------------------
    BeginTextureMode(__target);
    ClearBackground(globalPackage->theme.colors[0]);
    _screen_draw(app->currentScreen);
    if (__showFps)
      _draw_fps();

    EndTextureMode();

    // Drawing.
    // --------------------------------------------------
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(__target.texture,
                   (Rectangle){
                       0,
                       0,
                       (float)__target.texture.width,
                       -(float)__target.texture.height,
                   },
                   (Rectangle){
                       globalAppState->view.x,
                       globalAppState->view.y,
                       globalAppState->view.width,
                       globalAppState->view.height,
                   },
                   (Vector2){0, 0}, 0, RAYWHITE);

    EndDrawing();
  }
}

void app_destroy(App **ptrApp) {
  if (ptrApp && *ptrApp) {
    _screen_destroy(&(*ptrApp)->currentScreen);
    UnloadRenderTexture(__target);
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

static void _reset_static_variables(void) { __showFps = false; }
