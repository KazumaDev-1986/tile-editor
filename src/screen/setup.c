#include <stdint.h>

#include "../include/raygui.h"
#include "../include/screen.h"

// **************************************************
// Static variables declaration.
// **************************************************
static ScreenType __nextScreenType = SCREEN_TYPE_UNDEFINED;
static float __zoom = 1.0f;
static bool __cellValueEditMode = false;
static int32_t __cellValueValue = 0;
static bool __widthValueEditMode = false;
static int32_t __widthValueValue = 0;
static bool __heightValueEditMode = false;
static int32_t __heightValueValue = 0;
static bool __createMapBtnPressed = false;

// **************************************************
// Static functions declaration.
// **************************************************
static void _reset_static_variables(void);
static void _draw_form(void);

// **************************************************
// Public functions implementation.
// **************************************************
Screen *setup_create(void) {
  Screen *screen = MemAlloc(sizeof(Screen));
  if (!screen) {
    return NULL;
  }

  _reset_static_variables();
  screen->type = SCREEN_TYPE_SETUP;
  return screen;
}

void setup_update(Screen *const screen) {
  // TODO
}

void setup_draw(const Screen *const screen) {
  ClearBackground(TILE_EDITOR_COLOR_GRAY_LIGHT);

  int32_t width = 250;
  int32_t height = 200;
  int32_t middleWidth = GetScreenWidth() / 2;
  int32_t middleHeight = GetScreenHeight() / 2;
  int32_t posX = middleWidth - width / 2;
  int32_t posY = middleHeight - height / 2;

  _draw_form();

  DrawLine(-100 + middleWidth, middleHeight, 100 + middleWidth, middleHeight,
           RED);
  DrawLine(middleWidth, -100 + middleHeight, middleWidth, middleHeight + 100,
           GREEN);
}

ScreenType setup_next_screen(void) { return __nextScreenType; }

void setup_destroy(Screen **ptrScreen) {
  if (ptrScreen && *ptrScreen) {
    MemFree(*ptrScreen);
    *ptrScreen = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _reset_static_variables(void) {
  __nextScreenType = SCREEN_TYPE_UNDEFINED;
  __zoom = 1.0f;
  __cellValueEditMode = false;
  __cellValueValue = 0;
  __widthValueEditMode = false;
  __widthValueValue = 0;
  __heightValueEditMode = false;
  __heightValueValue = 0;
  __createMapBtnPressed = false;
}

static void _draw_form(void) {
  GuiGroupBox((Rectangle){312, 264, 368, 256}, "Configuracion Mapa");
  if (GuiValueBox((Rectangle){360, 304, 288, 24}, "Cell", &__cellValueValue, 0,
                  100, __cellValueEditMode))
    __cellValueEditMode = !__cellValueEditMode;
  if (GuiValueBox((Rectangle){360, 368, 288, 24}, "Width", &__widthValueValue,
                  0, 100, __widthValueEditMode))
    __widthValueEditMode = !__widthValueEditMode;
  if (GuiValueBox((Rectangle){360, 408, 288, 24}, "Height", &__heightValueValue,
                  0, 100, __heightValueEditMode))
    __heightValueEditMode = !__heightValueEditMode;
  GuiLine((Rectangle){336, 440, 312, 16}, NULL);
  __createMapBtnPressed = GuiButton((Rectangle){528, 472, 120, 24}, "Create");
}
