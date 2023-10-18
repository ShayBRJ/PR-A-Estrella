OBJS	= build/main.o build/Box.o build/Maze.o build/Utils.o
SOURCE	= src/main.cc src/Box.cc src/Maze.cc src/Utils.cc
HEADER	= include/Box.hh include/Maze.hh include/Utils.hh
OUT	= A-Estrella.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS)  -o $(OUT) $(LFLAGS)

build/main.o: src/main.cc
	$(CC) $(FLAGS) src/main.cc -o build/main.o

build/Box.o: src/Box.cc
	$(CC) $(FLAGS) src/Box.cc -o build/Box.o

build/Maze.o: src/Maze.cc
	$(CC) $(FLAGS) src/Maze.cc -o build/Maze.o

build/Utils.o: src/Utils.cc
	$(CC) $(FLAGS) src/Utils.cc -o build/Utils.o


clean:
	rm -f $(OBJS) $(OUT)