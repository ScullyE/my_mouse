CC = gcc

CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror

TARGET = my_mouse

SOURCES := $(shell find $(SOURCEDIR/lib) -name '*.c')

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean fclean

clean:
	@rm $(OBJECTS)

fclean: clean
	@rm $(TARGET) 