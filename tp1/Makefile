LDLIBS := -lm
LDFLAGS := -g
CFLAGS := -g -std=c11 -Wall -Wconversion -Wtype-limits -pedantic

all: pruebas dc infix

clean:
	rm -f -- *.o pruebas dc infix

rebuild: clean all

.PHONY: all clean rebuild

include deps.mk