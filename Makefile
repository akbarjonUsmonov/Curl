CC = gcc
CFLAGS = -g -Wall -Wextra -Werror# -g3 -fsanitize=address
SOURCES = ./curl/c/*.c
TARGET = my_curl

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean check

fclean:
	@rm -r $(TARGET)