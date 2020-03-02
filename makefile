# the compiler
CC=gcc
# options for the compiler
CFLAGS=-c -Wall
LDFLAGS=
SRC_FOLDER=src
BIN_FOLDER=bin
SOURCES=${SRC_FOLDER}/main.c ${SRC_FOLDER}/luanda-debugger.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=${BIN_FOLDER}/luanda-dbg

all: $(SOURCES) $(EXECUTABLE)

${EXECUTABLE}: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o $(EXECUTABLE)