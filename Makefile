run: build
	./calculator

build:
	eval cc main.c src/*.c `pkg-config --libs --cflags raylib` -lm -g -o calculator
