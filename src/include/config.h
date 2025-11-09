#ifndef TILE_EDITOR_CONFIG_H
#define TILE_EDITOR_CONFIG_H

#include <stddef.h>
#include <stdint.h>

#include "raylib.h"

#define TILE_EDITOR
#define TILE_EDITOR_DEBUG

// Screen setup.
// -------------------------------------------------------------
#define TILE_EDITOR_TITLE "Mika-Editor"
#define TILE_EDITOR_SCREEN_WIDTH 800
#define TILE_EDITOR_SCREEN_HEIGHT 600
#define TILE_EDITOR_VIRTUAL_SCREEN_WIDTH 128
#define TILE_EDITOR_VIRTUAL_SCREEN_HEIGHT 128
#define TILE_EDITOR_SCREEN_RESIZABLE 1
#define TILE_EDITOR_SCREEN_FPS 30

// TileMap setup.
// -------------------------------------------------------------
#define TILE_EDITOR_TILE_MAP_PIXEL_LIST_WIDTH 8
#define TILE_EDITOR_TILE_MAP_PIXEL_LIST_HEIGHT 8
#define TILE_EDITOR_TILE_MAP_TILE_LIST_WIDTH 4
#define TILE_EDITOR_TILE_MAP_TILE_LIST_HEIGHT 2

// Package setup.
// -------------------------------------------------------------
#define TILE_EDITOR_PACKAGE_FONT_SIZE 2
#define TILE_EDITOR_PACKAGE_FONT_04b_03 "data/fonts/04b_03/04B_03__.TTF"
#define TILE_EDITOR_PACKAGE_FONT_BM_MINI "data/fonts/bm_mini/BMmini.TTF"

// Palette setup.
// -------------------------------------------------------------
#define TILE_EDITOR_COLOR_PALETTE_SIZE 16
#define TILE_EDITOR_COLOR_PICO8_0 (Color){0, 0, 0, 255}        // #000000
#define TILE_EDITOR_COLOR_PICO8_1 (Color){29, 43, 83, 255}     // #1D2B53
#define TILE_EDITOR_COLOR_PICO8_2 (Color){126, 37, 83, 255}    // #7E2553
#define TILE_EDITOR_COLOR_PICO8_3 (Color){0, 135, 81, 255}     // #008751
#define TILE_EDITOR_COLOR_PICO8_4 (Color){171, 82, 54, 255}    // #AB5236
#define TILE_EDITOR_COLOR_PICO8_5 (Color){95, 87, 79, 255}     // #5F574F
#define TILE_EDITOR_COLOR_PICO8_6 (Color){194, 195, 199, 255}  // #C2C3C7
#define TILE_EDITOR_COLOR_PICO8_7 (Color){255, 241, 232, 255}  // #FFF1E8
#define TILE_EDITOR_COLOR_PICO8_8 (Color){255, 0, 77, 255}     // #FF004D
#define TILE_EDITOR_COLOR_PICO8_9 (Color){255, 163, 0, 255}    // #FFA300
#define TILE_EDITOR_COLOR_PICO8_10 (Color){255, 236, 39, 255}  // #FFEC27
#define TILE_EDITOR_COLOR_PICO8_11 (Color){0, 228, 54, 255}    // #00E436
#define TILE_EDITOR_COLOR_PICO8_12 (Color){41, 173, 255, 255}  // #29ADFF
#define TILE_EDITOR_COLOR_PICO8_13 (Color){131, 118, 156, 255} // #83769C
#define TILE_EDITOR_COLOR_PICO8_14 (Color){255, 119, 168, 255} // #FF77A8
#define TILE_EDITOR_COLOR_PICO8_15 (Color){255, 204, 170, 255} // #FFCCAA

#endif // TILE_EDITOR_CONFIG_H
