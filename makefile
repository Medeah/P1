CC = gcc
CFLAGS = -Wall -g

sim: sim.c sim.h map.o robot.o bustrophedon.o
	$(CC) $(CFLAGS) sim.c map.o robot.o astar.o bustrophedon.o -o sim

bustrophedon.o: bustrophedon.c bustrophedon.h robot.o robot.h astar.o astar.h
	$(CC) $(CFLAGS) -c bustrophedon.c

astar.o: astar.c astar.h map.o map.h 
	$(CC) $(CFLAGS) -c astar.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

robot.o: robot.c robot.h map.o map.h 
	$(CC) $(CFLAGS) -c robot.c

clean:
	rm -f *.o sim map.pnm