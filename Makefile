run: build
	./calculator

build:
	eval cc calc.c `pkg-config --libs --cflags raylib` -o calculator