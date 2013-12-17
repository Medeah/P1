#include "astar.h"

tileSet *newTileSet(map *world) {
  tileSet *set = (tileSet*) malloc(sizeof(tileSet));
  set->count = 0;
  
  if (world != NULL)
    set->tiles = (tile**) malloc(world->width * world->height * sizeof(tile));
  
  return set;
}

tileSet *getAstarRoute(tile *start, tile *goal, map *world) {
  tileSet *closedSet = newTileSet(world);

  tileSet *openSet = newTileSet(world);
  openSet->count = 1;
  openSet->tiles[0] = start;
  
  openSet->tiles[0]->g = 0;
  openSet->tiles[0]->f = costEstimate(start, goal);
  
  /* loop until no more tiles to check */
  while (openSet->count != 0) {
    int curOpenIndex = tileWithLowestFScore(openSet);
    
    if (curOpenIndex == -1)
      return NULL;
      
    tile *current = openSet->tiles[curOpenIndex];
    
    /* is *current our goal tile? */
    if (isEqual(current, goal))
      return reconstructPath(current);
      
    removeFromSet(curOpenIndex, openSet);
    add(current, closedSet);
    
    /* get neighbour tiles */
    if (current == NULL)
      printf("current is NULL\n");
      
    tileSet *neighbours = getNeighbours(current, world);
    int i;
    for (i = 0; i < neighbours->count; i++) {
      /* calc cost for this neighbour */
      int tentativeGScore = current->g + 1;
      int tentativeFScore = tentativeGScore + costEstimate(neighbours->tiles[i], goal);
      
      if (isInSet(neighbours->tiles[i], closedSet) && tentativeFScore >= neighbours->tiles[i]->f)
        continue;
        
      if (!isInSet(neighbours->tiles[i], openSet) || tentativeFScore < neighbours->tiles[i]->f) {
        neighbours->tiles[i]->f = tentativeFScore;
        neighbours->tiles[i]->g = tentativeGScore;
        
        neighbours->tiles[i]->parent = current;
        
        if (!isInSet(neighbours->tiles[i], openSet))
          add(neighbours->tiles[i], openSet);
      }
    }
    free(neighbours);
  }
  
  return NULL;
}

int costEstimate(tile *start, tile *goal) {
  return abs(start->x - goal->x) + abs(start->y - goal->y);
}

void add(tile *elem, tileSet *set) {
  set->tiles[set->count++] = elem;
}

void removeFromSet(int index, tileSet *set) {
   int i;
   for (i = index; i < set->count; i++)
     set->tiles[i] = set->tiles[i+1];
     
   set->count--;
}

int isEqual(tile *t1, tile *t2) {
    return (t1->x == t2->x && t1->y == t2->y);
}

int tileWithLowestFScore(const tileSet *set) {
  int i, index = -1, tmpValue = INT_MAX;
    
  for (i = 0; i < set->count; i++) {
    if (set->tiles[i]->f < tmpValue) {
      tmpValue = set->tiles[i]->f;
      index = i;
    }
  }
  
  return index;
}

tileSet *getNeighbours(tile *t, map *world) {
  tileSet *neighbours = newTileSet(NULL);
  neighbours->tiles = (tile**) malloc(4 * sizeof(tile*));
  
  int x = t->x, y = t->y;

  if (isWithinBounds(world, x, y-1) && world->tiles[x][y-1]->type == OPEN) {
    neighbours->tiles[neighbours->count++] = world->tiles[x][y-1];
  }
  
  if (isWithinBounds(world, x, y+1) && world->tiles[x][y+1]->type == OPEN) {
    neighbours->tiles[neighbours->count++] = world->tiles[x][y+1];
  }
  
  if (isWithinBounds(world, x-1, y) && world->tiles[x-1][y]->type == OPEN) {
    neighbours->tiles[neighbours->count++] = world->tiles[x-1][y];
  }
  
  if (isWithinBounds(world, x+1, y) && world->tiles[x+1][y]->type == OPEN) {
    neighbours->tiles[neighbours->count++] = world->tiles[x+1][y];
  }
  return neighbours;
}

int isInSet(tile *t, tileSet *set) {
  int i;
  for (i = 0; i < set->count; i++)
    if (t->x == set->tiles[i]->x && t->y == set->tiles[i]->y)
      return 1;
      
  return 0;
}

tileSet *reconstructPath(tile *goal) {
  int allocSize = 10;
  tileSet *path = (tileSet*) malloc(sizeof(tileSet));
  path->tiles = (tile**) malloc(allocSize * sizeof(tile*));
  path->count = 0;
  
  tile *cur = goal;
  do {
    add(cur, path);
    if (path->count == allocSize) {
      allocSize *= 2;
      path->tiles = (tile**) realloc(path->tiles, allocSize * sizeof(tile*));
    }
  } while ((cur = cur->parent) != NULL);
  
  return path;
}