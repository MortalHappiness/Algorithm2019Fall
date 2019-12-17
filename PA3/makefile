CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all: ./cb
	@echo -n ""

./cb: main.o cb.o graph.o
	$(CC) $(OPTFLAGS) $^ -o $@

main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

cb.o: src/cb.cpp src/cb.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

graph.o: src/graph.cpp src/graph.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o ./cb output/*
