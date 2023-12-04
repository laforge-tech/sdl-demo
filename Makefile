CFLAGS=$(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs)

main: main.c
	gcc main.c ${CFLAGS} ${LDFLAGS} -o main


