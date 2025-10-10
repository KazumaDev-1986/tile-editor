#ifndef TILE_EDITOR_APP_H
#define TILE_EDITOR_APP_H

#include "config.h"
#include "screen.h"

TILE_EDITOR typedef struct {
  Screen *currentScreen;
} App;

#if defined(__cplusplus)
extern "C" {
#endif

TILE_EDITOR App *app_create(void);

TILE_EDITOR void app_run(App *const app);

TILE_EDITOR void app_destroy(App **ptrApp);

#if defined(__cplusplus)
}
#endif

#endif // TILE_EDITOR_APP_H
