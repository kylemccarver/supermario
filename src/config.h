#ifndef CONFIG_H
#define CONFIG_H

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 448;
const float ASPECT = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

const int TILES_X = 32;
const int TILES_Y = 28;

const int TILE_SIZE = WINDOW_WIDTH / TILES_X;

#endif
