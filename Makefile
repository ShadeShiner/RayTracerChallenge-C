CC=gcc
CFLAGS=-Wall -I includes
LIBS=-lm

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXE=$(SRC:.c=)

TEST_SRC=$(wildcard tests/test*.c)
TEST_EXE=$(TEST_SRC:.c=)

EOC_SRC=$(wildcard end_of_chapters/eoc*.c)
EOC_EXE=$(EOC_SRC:.c=)


src: $(OBJ)
	@echo src

test: $(TEST_EXE)
	@echo done

$(TEST_EXE): $(TEST_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) $@.c -o $@

eoc: $(EOC_EXE)
	@echo done 

$(EOC_EXE): $(EOC_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) $@.c -o $@

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: target
clean:
	find . -name "*.o" -delete
	find tests -type f -executable -delete
	find end_of_chapters -type f -executable -delete

