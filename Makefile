OBJS = main.cpp
CC = g++
COMPILER_FLAGS = -w -Wall
OBJ_NAME = main.out
all : $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(OBJS) -o $(OBJ_NAME)
.PHONY: all clean
