#include <math.h>

#include "include/app_state.h"
#include "include/config.h"
#include "include/form_setup.h"
#include "include/raygui.h"

extern AppState *globalAppState;

// **************************************************
// Static variables declaration.
// **************************************************
static float __zoom = 1.0f;
static bool __cellValueEditMode = false;
static bool __widthValueEditMode = false;
static bool __heightValueEditMode = false;
static bool __createMapBtnPressed = false;

// **************************************************
// Static functions declaration.
// **************************************************
static void _reset_static_variables(void);
static void _resize(FormSetup *const form);

// **************************************************
// Public functions implementation.
// **************************************************
FormSetup *formSetup_create(Vector2 position, Vector2 size) {
  FormSetup *form = MemAlloc(sizeof(FormSetup));
  if (!form) {
    return NULL;
  }

  form->position = position;
  form->size = size;
  form->width = 0;
  form->height = 0;
  form->cell = 0;
  form->state = FORM_SETUP_STATE_INVALID;
  return form;
}

void formSetup_update(FormSetup *const form) {
  if (globalAppState->shouldUpdateScreen) {
    _resize(form);
  }
}

void formSetup_draw(FormSetup *const form) {
  GuiGroupBox((Rectangle){form->position.x, form->position.y,
                          form->size.x * __zoom, form->size.y * __zoom},
              "Configuracion Mapa");

  // if (GuiValueBox(
  //         (Rectangle){form->position.x + 48, form->position.y + 40, 288, 24},
  //         "Cell", &form->cell, 0, 100, __cellValueEditMode))
  //   __cellValueEditMode = !__cellValueEditMode;

  // if (GuiValueBox(
  //         (Rectangle){form->position.x + 48, form->position.y + 80, 288, 24},
  //         "Width", &form->width, 0, 100, __widthValueEditMode))
  //   __widthValueEditMode = !__widthValueEditMode;

  // if (GuiValueBox(
  //         (Rectangle){form->position.x + 48, form->position.y + 120, 288,
  //         24}, "Height", &form->width, 0, 100, __heightValueEditMode))
  //   __heightValueEditMode = !__heightValueEditMode;

  // // GuiLine((Rectangle){336, 440, 312, 16}, NULL);

  // __createMapBtnPressed = GuiButton(
  //     (Rectangle){form->position.x + 216, form->position.y + 208, 120, 24},
  //     "Create");
}

void formSetup_destroy(FormSetup **ptrForm) {
  if (ptrForm && *ptrForm) {
    MemFree(*ptrForm);
    *ptrForm = NULL;
  }
}

// **************************************************
// Static functions implementation.
// **************************************************
static void _reset_static_variables(void) {
  __zoom = 1.0f;
  __cellValueEditMode = false;
  __widthValueEditMode = false;
  __heightValueEditMode = false;
  __createMapBtnPressed = false;
}

static void _resize(FormSetup *const form) {
  __zoom =
      fminf((float)globalAppState->screenWidth / TILE_EDITOR_SCREEN_WIDTH,
            (float)globalAppState->screenHeight / TILE_EDITOR_SCREEN_HEIGHT);

  int32_t middleWidth = globalAppState->screenWidth / 2;
  int32_t middleHeight = globalAppState->screenHeight / 2;
  form->position.x = middleWidth - (form->size.x * __zoom) / 2;
  form->position.y = middleHeight - (form->size.y * __zoom) / 2;
  // TraceLog(LOG_DEBUG, "x:%f, y:%f", form->position.x, form->position.y);
}
