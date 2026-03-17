run: build
	./calculator

build:
	eval cc main.c `pkg-config --libs --cflags raylib` -o calculator