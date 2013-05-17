GCC		= gcc
CFLAGS		= -g -Wall
EXEC		= nv-ioctls-trace
OBJ		= $(EXEC).o
SRC		= $(EXEC).c

$(EXEC): $(OBJ)
	$(GCC) -o $@ $<

$(OBJ): $(SRC)
	$(GCC) -c $(CFLAGS) $<

clean:
	rm -f $(EXEC) $(OBJ)
