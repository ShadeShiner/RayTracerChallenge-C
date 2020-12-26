CC=gcc
CFLAGS=-Wall -I includes
LIBS=-lm

SRC_DIR=src
SRCS=camera.c canvas.c intersections.c lights.c logger.c material.c matrix.c my_string.c ray.c sphere.c test_library.c tuple.c world.c
OBJ_DIR=obj
OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
EXE=$(SRC:.c=)

TEST_DIR=tests
TEST_SRCS=test_camera.c test_canvas.c test_intersections.c test_lights.c test_materials.c test_matrix.c test_rays.c test_spheres.c test_transformations.c test_tuple.c test_world.c

BUILD_DIR=build
TEST_EXE=$(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=))

EOC_DIR=end_of_chapters
EOC_SRCS=eoc_1.c eoc_2.c eoc_3.c eoc_4.c eoc_5.c eoc_6.c eoc_7.c
EOC_EXE=$(addprefix $(BUILD_DIR)/, $(EOC_SRCS:.c=))


.PHONY: all
all: build src test eoc

build: obj
	mkdir -p $(BUILD_DIR)

obj:
	mkdir -p $(OBJ_DIR)

src: obj $(OBJS)

test: build src $(TEST_EXE)

eoc: build src $(EOC_EXE)

$(TEST_EXE): $(BUILD_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) -g $(CFLAGS) $(LIBS) $(OBJS) $< -o $@

$(EOC_EXE): $(BUILD_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) -g $(CFLAGS) $(LIBS) $(OBJS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -g $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) -g $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EOC_DIR)/%.c
	$(CC) -g $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
