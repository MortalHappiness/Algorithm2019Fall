CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
OPTFLAGS = -O3

all: ./cb
	@echo -n ""

# optimization version
./cb: main.o cb.o set.o
	$(CC) $(OPTFLAGS) $^ -o $@

main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

cb.o: src/cb.cpp src/cb.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

set.o: src/set.cpp src/set.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# timing version
time: ./cb_time
	@echo -n ""

./cb_time: time.o cb.o set.o lib
	$(CC) $(OPTFLAGS) time.o cb.o set.o -ltm_usage -Llib -o $@

time.o: src/time.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -Ilib -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf *.o lib/*.a lib/*.o ./cb* output/*
