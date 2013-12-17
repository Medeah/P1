#include "bustrophedon.h"

void ba(robot *r) {
  int busIndex = 1;
  while (1) {
    r->map->tiles[r->posX][r->posY]->bustrophedonIndex = busIndex;
    
    bustrophedon(busIndex++, r);

    tile *closest = findClosestOpen(r);
    
    if (closest == NULL)
      break;
    
    tileSet *path = getAstarRoute(newTile(r->posX, r->posY), closest, r->map);
    
    if (path == NULL || path->count == 0){
      printf("PATH NOT FOUND\n");
      break;
    }
    
    int i;
    for (i = path->count - 1; i >= 0; i--) {
      stepToTile(r, path->tiles[i]);
      r->map->tiles[r->posX][r->posY]->bustrophedonIndex = -1;
    }

  }
}

void bustrophedon(int busIndex, robot *r) {
  while (!isCritical(r)) {
    if (canStepUpVirtual(r))
      stepUp(r);
    else if (canStepDownVirtual(r))
      stepDown(r);
    else if (canStepRightVirtual(r))
      stepRight(r);
    else
      stepLeft(r);
    
    r->map->tiles[r->posX][r->posY]->bustrophedonIndex = busIndex;
  }
}

int isCritical(robot *r) {
    return !(canStepUpVirtual(r) || canStepDownVirtual(r) || canStepLeftVirtual(r) || canStepRightVirtual(r));
}

tile *findClosestOpen(robot *r) {
  tile *closest = NULL;
    int x, y;
    for (x = 0; x < r->map->width; x++) {
      for (y = 0; y < r->map->height; y++) {
        if (r->map->tiles[x][y]->type == OPEN && r->map->tiles[x][y]->bustrophedonIndex == 0) {
          if (closest == NULL || isCloser(r, r->map->tiles[x][y], closest)) {
            closest = r->map->tiles[x][y];
          }
        }
      }
    }

  return closest;
}

int isCloser(robot *r, tile *t1, tile *t2) {
  int est1 = costEstimate(newTile(r->posX, r->posY), t1),
      est2 = costEstimate(newTile(r->posX, r->posY), t2);
  return (est1 < est2);
}

int canStepUpVirtual(robot *r) {
  return canStepUp(r) && r->map->tiles[r->posX][r->posY - 1]->bustrophedonIndex == 0;
}

int canStepDownVirtual(robot *r) {
  return canStepDown(r) && r->map->tiles[r->posX][r->posY + 1]->bustrophedonIndex == 0;
}

int canStepRightVirtual(robot *r) {
  return canStepRight(r) && r->map->tiles[r->posX + 1][r->posY]->bustrophedonIndex == 0;
}

int canStepLeftVirtual(robot *r) {
  return canStepLeft(r) && r->map->tiles[r->posX - 1][r->posY]->bustrophedonIndex == 0;
}