CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all: ./cb
	@echo -n ""

./cb: main.o cb.o set.o
	$(CC) $(OPTFLAGS) $^ -o $@

main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

cb.o: src/cb.cpp src/cb.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

set.o: src/set.cpp src/set.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o ./cb output/*
