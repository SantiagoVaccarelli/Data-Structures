# LDLIBS := -lm
LDFLAGS := -g
CFLAGS := -g -std=gnu18 -Wall -Wconversion -Wtype-limits -pedantic -Werror 

all: main

clean:
	rm -f -- *.o main

rebuild: clean all

.PHONY: all clean rebuild

include deps.mk