CC		= g++
LFLAGS 	= -I include/ -lX11 -lpthread
CFLAGS 	= -I include/

maindeps= bin/main.o

main: $(maindeps)
	$(CC) -o $@ $^ $(LFLAGS)

bin/main.o: src/main.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
