CC=clang -std=c23
SRC_C=$(wildcard src/*.c)
SRC_H:=$(patsubst src/%c,inlude/%.h,$(SRC_C))
OBJ:=$(patsubst src/%.c,obj/%.o,$(SRC_C))
FLAGS=-Wall -Wextra -Werror -pedantic -c -g

.PHONY:all
all: dir $(BUILD)/$(EXEC)

dir:
	mkdir -p $(BUILD)

$(BUILD)/$(EXEC): $(OBJ)
	$(CC) $^ -o $@

$(OBJ): $(SRC_C) $(SRC_H)
	$(CC) $(FLAGS) $@ -o $< $(FLAGS) 
	
