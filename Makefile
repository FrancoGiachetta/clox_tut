CC=clang -std=c23
SRCS_C:=$(shell find src/ -iname "*.c")
SRCS_H:=$(shell find include/ -iname "*.h")
OBJS:=$(patsubst src/%.c,obj/%.o,$(SRCS_C))
EXEC:=clox
CFLAGS=-Wall -Wextra -pedantic -c -g

.PHONY: build
build: dir build/$(EXEC)

dir:
	mkdir -p build
	mkdir -p obj

build/$(EXEC): $(OBJS)
	$(CC) $^ -o $@

$(OBJS): obj/%.o : src/%.c $(SRCS_H)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf build
	rm -rf obj 
	
