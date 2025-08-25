TARGET = bin/http_srv

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)

run: clean default
	./$(TARGET)

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.db

$(TARGET): $(OBJ)
	gcc -o $@ $?

$(OBJ): obj/%.o: src/%.c
	gcc -Wall -Wextra -Wpedantic -Werror -c $< -o $@ -Iinclude

