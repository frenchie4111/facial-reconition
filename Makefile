CC		= g++
LFLAGS	= -I/usr/include/SDL/ -I include/ -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lstdc++ 
CFLAGS 	= -I include/

maindeps= bin/main.o bin/lyonsSDL.o

main: $(maindeps)
	$(CC) -o $@ $^ $(LFLAGS)

bin/main.o: src/main.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

bin/lyonsSDL.o: src/lyonsSDL.cpp include/lyonsSDL.h
	$(CC) -o $@ -c $< $(CFLAGS)
