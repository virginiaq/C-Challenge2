CC=clang
CFLAGS= -Werror -Wno-pragma-pack -I SDL2/include
LDFLAGS= -lSDL2 -L SDL2/lib/x64
BINARY = clock
BINARY_TESTS = clock_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

clock.exe: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@  $^
