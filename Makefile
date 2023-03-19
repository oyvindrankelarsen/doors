PROG=doors.exe
CC=gcc -std=c99
CFLAGS=-g -Wall 

DEPS = doors.h  safeinput.h
OBJ = doors.o  safeinput.o
 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)