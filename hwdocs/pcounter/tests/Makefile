CC	= gcc
CFLAGS	= -g -Wall
LDFLAGS = -lGL -lGLU -lglut -lGLEW
OBJ	= $(wildcard *.o)

all: test_setup_signals

test_setup_signals: test_setup_signals.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) test_setup_signals
