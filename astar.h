#ifndef _STD_
#define _STD_
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef _LIMITS_
#define _LIMITS_
#include <limits.h>
#endif

#ifndef _MATH_
#define _MATH_
#include <math.h>
#endif

#ifndef _MAP_
#define _MAP_
#include "map.h"
#endif

typedef struct {
  int count;
  tile **tiles;
} tileSet;

tileSet *newTileSet(map *world);

tileSet *getAstarRoute(tile *start, tile *goal, map *world);
int costEstimate(tile *start, tile *goal);
void add(tile *elem, tileSet *set);
void removeFromSet(int index, tileSet *set);
int tileWithLowestFScore(const tileSet *set);
int isEqual(tile *t1, tile *t2);
tileSet *getNeighbours(tile *t, map *world);
int isInSet(tile *t, tileSet *set);
tileSet *reconstructPath(tile *goal);