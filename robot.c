#include "robot.h"

robot *newRobot(int posX, int posY, map *world) {
  robot *r = (robot*) malloc(sizeof(robot));
  
  r->posX = posX;
  r->posY = posY;
  r->map = newMap(world->width, world->height);
  r->world = world;
  
  return r;
}

void freeRobot(robot *r) {
  freeMap(r->map);
  freeMap(r->world);
  free(r);
}

/*
 * movement
 */
int stepUp(robot *robot) {
  return stepTo(robot, robot->posX, robot->posY-1);
}

int stepDown(robot *robot) {
  return stepTo(robot, robot->posX, robot->posY+1);
}

int stepLeft(robot *robot) {
  return stepTo(robot, robot->posX-1, robot->posY);
}

int stepRight(robot *robot) {
  return stepTo(robot, robot->posX+1, robot->posY);
}

int stepToTile(robot *robot, tile *t) {
  return stepTo(robot, t->x, t->y);
}

int stepTo(robot *robot, int x, int y) {
  sensorTick(robot);
  if (isWithinBounds(robot->world, x, y)
      && abs(robot->posX - x) <= 1 && abs(robot->posY - y) <= 1) {
    if (isOpen(robot->world, x, y)) {
      robot->map->tiles[x][y]->type = OPEN;
      robot->posX = x;
      robot->posY = y;
      return 1;
    } else {
      robot->map->tiles[x][y]->type = CLOSED;
      printf("Cannot move to closed tile!\n");
      return 0;
    }
  } else {
    printf("Unreachable tile!\n");
    return 0;
  }
}

/*
 * sensing
 */
void sensorTick(robot *robot) {
  int x = robot->posX,
      y = robot->posY;
      
  if (canStepUp(robot))
    robot->map->tiles[x][y - 1]->type = OPEN;
  else if (isWithinBounds(robot->world, x, y - 1))
    robot->map->tiles[x][y - 1]->type = CLOSED;
    
  if (canStepDown(robot))
    robot->map->tiles[x][y + 1]->type = OPEN;
  else if (isWithinBounds(robot->world, x, y + 1))
    robot->map->tiles[x][y + 1]->type = CLOSED;
    
  if (canStepLeft(robot))
    robot->map->tiles[x - 1][y]->type = OPEN;
  else if (isWithinBounds(robot->world, x - 1, y))
    robot->map->tiles[x - 1][y]->type = CLOSED;
    
  if (canStepRight(robot))
    robot->map->tiles[x + 1][y]->type = OPEN;
  else if (isWithinBounds(robot->world, x + 1, y))
    robot->map->tiles[x + 1][y]->type = CLOSED;
}

int canStepUp(robot *robot) {
  return isWithinBounds(robot->world, robot->posX, robot->posY-1) && isOpen(robot->world, robot->posX, robot->posY-1);
}

int canStepDown(robot *robot) {
  return isWithinBounds(robot->world, robot->posX, robot->posY+1) && isOpen(robot->world, robot->posX, robot->posY+1);
}

int canStepLeft(robot *robot) {
  return isWithinBounds(robot->world, robot->posX-1, robot->posY) && isOpen(robot->world, robot->posX-1, robot->posY);
}

int canStepRight(robot *robot) {
  return isWithinBounds(robot->world, robot->posX+1, robot->posY) && isOpen(robot->world, robot->posX+1, robot->posY);
}
