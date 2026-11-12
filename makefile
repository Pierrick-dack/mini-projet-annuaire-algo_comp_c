CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c sequential.c hash.c sorted.c

all: annuaire

annuaire: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o annuaire

clean:
	rm -f annuaire