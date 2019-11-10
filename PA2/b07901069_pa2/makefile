# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O3 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all: ./mps
	@echo -n ""

# optimized version
./mps: main.o mps.o
	$(CC) $(OPTFLAGS) $^ -o $@

main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

mps.o: src/mps.cpp src/mps.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o ./mps output/*
