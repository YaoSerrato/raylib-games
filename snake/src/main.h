#ifndef MAIN_H
#define MAIN_H

#include <ctime>
#include <deque>
#include <raylib.h>
#include <raymath.h>

#define     CELL_SIZE       (30)
#define     CELL_COUNT      (25)
#define     FRAME_OFFSET    (75)

#define     COLOR_BACKGROUND        CLITERAL(Color){0x4D, 0x5E, 0x72, 0xFF}
#define     COLOR_SNAKE             CLITERAL(Color){0xF1, 0xE6, 0xC1, 0xFF}
#define     COLOR_FOOD              CLITERAL(Color){0xF2, 0xCC, 0x8C, 0xFF}
#define     COLOR_FRAME             CLITERAL(Color){0x00, 0x00, 0x00, 0xFF}
#define     COLOR_TEXT              CLITERAL(Color){0xDD, 0xA5, 0xB6, 0xFF}

#endif  /* MAIN_H */