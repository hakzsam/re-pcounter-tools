CC	= gcc
CFLAGS	= -g -Wall
LDFLAGS = -lGL -lGLU -lglut
OBJ	= $(wildcard *.o)

all: test_setup_line_count test_setup_point_count test_setup_triangle_count test_setup_primitive_count

test_setup_line_count: test_setup_line_count.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_setup_line_count.o: test_setup_line_count.c
	$(CC) -c $< $(CFLAGS)

test_setup_point_count: test_setup_point_count.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_setup_point_count.o: test_setup_point_count.c
	$(CC) -c $< $(CFLAGS)

test_setup_triangle_count: test_setup_triangle_count.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_setup_triangle_count.o: test_setup_triangle_count.c
	$(CC) -c $< $(CFLAGS)

test_setup_primitive_count: test_setup_primitive_count.o common.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_setup_primitive_count.o: test_setup_primitive_count.c
	$(CC) -c $< $(CFLAGS)

common.o: common.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) test_setup_line_count test_setup_point_count test_setup_triangle_count test_setup_primitive_count
