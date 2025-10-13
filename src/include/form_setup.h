#ifndef TILE_EDITOR_FORM_SETUP
#define TILE_EDITOR_FORM_SETUP

#include "config.h"

TILE_EDITOR typedef enum {
  FORM_SETUP_STATE_INVALID = 0,
  FORM_SETUP_STATE_VALID,
} FormSetupState;

TILE_EDITOR typedef struct {
  Vector2 position;
  Vector2 size;
    
  int32_t width;
  int32_t height;
  int32_t cell;

  FormSetupState state;
} FormSetup;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR FormSetup *formSetup_create(Vector2 position, Vector2 size);
TILE_EDITOR void formSetup_update(FormSetup *const form);
TILE_EDITOR void formSetup_draw(FormSetup *const form);
TILE_EDITOR void formSetup_destroy(FormSetup **ptrForm);

#if defined(__cplusplus)
}
#endif

#endif  // TILE_EDITOR_FORM_SETUP
