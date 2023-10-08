CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic

source_code = my_mastermind.c
object = my_mastermind.o
target = my_mastermind

all: $(target)

$(target): $(object)
	$(CC) $(CFLAGS) -o $(target) $(object)

clean:
	rm -f $(object)

fclean: clean
	rm -f $(target)
