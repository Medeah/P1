#ifndef _ROBOT_
#define _ROBOT_
#include "robot.h"
#endif

#ifndef _ASTAR_
#define _ASTAR_
#include "astar.h"
#endif

void ba(robot *r);
void bustrophedon(int busIndex, robot *r);
int isCritical(robot *r);

tile *findClosestOpen(robot *r);
int isCloser(robot *r, tile *t1, tile *t2);

int canStepUpVirtual(robot *r);
int canStepDownVirtual(robot *r);
int canStepLeftVirtual(robot *r);
int canStepRightVirtual(robot *r);