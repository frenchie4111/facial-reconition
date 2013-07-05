CC		= g++
LFLAGS 	= -I include/ -lX11 -lpthread
CFLAGS 	= -I include/

maindeps= bin/main.o bin/blob.o

freq: $(maindeps)
	$(CC) -o $@ $^ $(LFLAGS)

bin/main.o: src/main.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

bin/blob.o: src/blob.cpp include/blob.h
	$(CC) -o $@ -c $< $(CFLAGS)
