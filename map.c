#include "map.h"

map *openMap(char *filePath) {
  FILE *file = fopen(filePath, "r");
  
  /* get width and height of map */
  int width, height;
  if(fscanf(file, "P3 %d %d 255", &width, &height) != 2) {
    printf("error reading frome file\n");
  };
  
  /* create the empty map */
  map *m = newMap(width, height);
  
  /* fill the map */
  parseMap(file, m);
  
  fclose(file);
  
  return m;
}

map *newMap(int width, int height) {
  map *m = (map*) malloc(sizeof(map));
  
  m->width = width;
  m->height = height;
  m->tiles = (tile***) malloc(width * sizeof(tile**));
  
  int x, y;
  for (x = 0; x < width; x++) {
    m->tiles[x] = (tile**) malloc(height * sizeof(tile*));
    
    for(y = 0; y < height; y++) {
      m->tiles[x][y] = newTile(x, y);
    }
  }
  
  return m;
}

tile *newTile(int x, int y) {
  tile *t = (tile*) malloc(sizeof(tile));
  
  t->x = x;
  t->y = y;
  t->type = UNKNOWN;
  t->bustrophedonIndex = 0;
  
  t->parent = NULL;
  t->f = 0;
  t->g = 0;

  return t;
}

void parseMap(FILE *file, map *map) {
  int x, y;
  
  for (y = 0; y < map->height; y++) {
    for (x = 0; x < map->width; x++) {
      int r, g, b;
      if(fscanf(file, "%d %d %d", &r, &g, &b)!= 3) {
        printf("error reading from file\n");
      }
      map->tiles[x][y]->type = rgbToHex(r, g, b);
    }
  }
}

int rgbToHex(int r, int g, int b) {
  return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}

void hexToRgb(int hex, int *r, int *g, int *b) {
  *r = ((hex >> 16) & 0xFF);
  *g = ((hex >> 8) & 0xFF);
  *b = ((hex) & 0xFF);
}

void freeMap(map *map) {
  int x, y;
  
  for (x = 0; x < map->width; x++) {
    for (y = 0; y < map->height; y++) {
      free(&(map->tiles[x][y]));
    }
    free(map->tiles[x]);
  }
  
  free(map);
}

void printMap(map *map) {
  int x, y;
  for (x = 0; x < map->width; x++) {
    for (y = 0; y < map->height; y++) {
      if (map->tiles[x][y]->type == UNKNOWN)
        printf("#");
      else if (map->tiles[x][y]->type == OPEN)
        printf("O");
      else if (map->tiles[x][y]->type == CLOSED)
        printf("C");
      else
        printf("?");
    }
    printf("\n");
  }
}

int isOpen(map *map, int x, int y) {
  return (isWithinBounds(map, x, y) && map->tiles[x][y]->type == OPEN);
}

int isWithinBounds(map *map, int x, int y) {
  return (x >= 0 && y >= 0 && x < map->width && y < map->height);
}

int tileIsWithinBounds(map *map, tile *t) {
  return isWithinBounds(map, t->x, t->y);
}

void exportMap(map *map, char *filePath, int showPasses) {
  FILE *file = fopen(filePath, "w");
  
  /* write headers */
  fprintf(file, "P3\n%d\n%d\n255\n", map->width, map->height);
  
  int x, y, r, g, b, hex;
  for (y = 0; y < map->height; y++) {
    for (x = 0; x < map->width; x++) {
      
      if (showPasses && (map->tiles[x][y]->bustrophedonIndex > 0 || map->tiles[x][y]->bustrophedonIndex == -1))
        hex = colorForPasses(map->tiles[x][y]->bustrophedonIndex);
      else
        hex = map->tiles[x][y]->type;
        
      hexToRgb(hex, &r, &g, &b);
      fprintf(file, "%d %d %d\n", r, g, b);
    }
  }
  
  fclose(file);
}

int colorForPasses(int busIndex) {
  switch (busIndex) {
    case -1: return 0x00FF00;
    case 1: return 0xFF0000;
    case 2: return 0xc19a53;
    case 3: return 0xffff44;
    case 4: return 0xcccc99;
    case 5: return 0xff9000;
    case 6: return 0xdaa520;
    case 7: return 0xc9a8e0;
    case 8: return 0x55460d;
    case 9: return 0x003300;
    case 10: return 0xffc0cb;
    case 11: return 0xf8fb9e;
    case 12: return 0x002649;
    case 13: return 0xe87511;
    case 14: return 0xcfff02;
    default: return (rand() % 0xFFFFFF) + 0xFF0000;
  }
}