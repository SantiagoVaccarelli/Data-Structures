LDLIBS := -lm
LDFLAGS := -g
CFLAGS := -g -std=gnu18 -Wall -Wconversion -Wtype-limits -pedantic -Werror

test: main
	valgrind --leak-check=full --show-leak-kinds=all -s ./main && ./cover.sh abb.c *.c

all: main
	
clean:
	rm -f -- *.o main

rebuild: clean all

.PHONY: all clean rebuild

include deps.mk