  #include "sim.h"
  #include <time.h>

int main(int argc, char *argv[]) {

  if (argc != 2){
    printf("Programmet skal køres med en parameter.\n"
           "Eksempel:\n"
           "./sim maps/60-40.pnm\n");
    return EXIT_FAILURE;
  }
    
    
  map *world = openMap(argv[1]);
  robot *robot = newRobot(0, 0, world);
  
  ba(robot);
    
  exportMap(robot->map, "map.pnm", 1);
  printf("Output map exportet to \"map.pnm\"\n");
  
  return EXIT_SUCCESS;
}
