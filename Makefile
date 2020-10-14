CC=gcc
CFLAGS=-Wall -I includes
LIBS=-lm

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXE=$(SRC:.c=)

TEST_SRC=$(wildcard tests/test*.c)
TEST_OBJ=$(TEST_SRC:.c=.o) 
TEST_EXE=$(TEST_SRC:.c=)

src: $(OBJ)
	@echo src

test: $(TEST_EXE)
	@echo done

$(TEST_EXE): $(TEST_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) $@.c -o $@

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: target
clean:
	find . -name "*.o" -delete
	find tests -type f -executable -delete

