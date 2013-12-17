#ifndef _MAP_
#define _MAP_
#include "map.h"
#endif

typedef struct robot {
  int posX;
  int posY;
  map *map;
  map *world;
} robot;

robot *newRobot(int posX, int posY, map *world);
void freeRobot();

/* 
 * movement
 */
int stepUp(robot *robot);
int stepDown(robot *robot);
int stepLeft(robot *robot);
int stepRight(robot *robot);
int stepToTile(robot *robot, tile *t);
int stepTo(robot *robot, int x, int y);

/* 
 * sensing 
 */
/* checks wether robot* can step (move one tile) */
void sensorTick(robot *robot);
int canStepUp(robot *robot);
int canStepDown(robot *robot);
int canStepLeft(robot *robot);
int canStepRight(robot *robot);