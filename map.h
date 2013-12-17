#ifndef _STD_
#define _STD_
#include <stdio.h>
#include <stdlib.h>
#endif

typedef enum tileType {
  UNKNOWN = 0xCCCCCC,
  OPEN = 0xFFFFFF,
  CLOSED = 0x000000
} tileType;

typedef struct tile tile;
struct tile {
  int x;
  int y;
  tileType type;
  int bustrophedonIndex;
  
  tile *parent;
  int f;
  int g;
};

typedef struct map {
  int width;
  int height;
  tile ***tiles;
} map;

map *openMap(char *filePath);
map *newMap(int width, int height);
tile *newTile();
void parseMap(FILE *file, map *map);

int rgbToHex(int r, int g, int b);
void hexToRgb(int hex, int *r, int *g, int *b);

void freeMap(map *map);
void printMap(map *map);

int isOpen(map *world, int x, int y);
int isWithinBounds(map *map, int x, int y);

void exportMap(map *map, char *filePath, int showPasses);
int colorForPasses(int busIndex);