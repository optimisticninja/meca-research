CSTD := -std=gnu11
WARNINGS := -Wall -Werror -Wextra
LIBS := -lm -lpthread `pkg-config --libs sqlite3`
CFLAGS := -O2 `pkg-config --cflags sqlite3`

C_SOURCES := $(wildcard src/*.c)
C_OBJECTS := $(patsubst src/%.c, build/%.o, $(C_SOURCES))

all: bin/secondorder
	./scripts/format.sh

build/%.o: src/%.c
		mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) -c -o $@ $<

bin/secondorder: $(C_OBJECTS)
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	rm -rf build/ bin/

print-%  : ; @echo $* = $($*)
