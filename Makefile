# Define the compiler
CC=gcc

# Compiler flags
CFLAGS=-Wall -g 

# Debugging flags
DFLAGS=-Wall -g -D__DEBUG

# Define the target executable name
TARGET_SPCHK=spchk

# List of source files for spchk
SOURCES_SPCHK= linestream.c spchk.c binaryTree.c

# Object files to generate for spchk
OBJECTS_SPCHK=$(SOURCES_SPCHK:.c=.o)

# Default rule to build the spchk
spchk: $(TARGET_SPCHK)
	make clean

# Debug rule to build the program spchk with debug flags
debug_spchk: CFLAGS = $(DFLAGS)
debug_spchk: $(TARGET_SPCHK)
	make clean

# Rule for linking the program
$(TARGET_SPCHK): $(OBJECTS_SPCHK)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling source files to object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# Special case for spchk.c which might not need a spchk.h
spchk.o: spchk.c
	$(CC) $(CFLAGS) -c $<

# Rule for cleaning up
clean:
	del -f $(OBJECTS_SPCHK) $(OBJECTS_MEMTEST)

# Dependencies
linestream.o: linestream.c linestream.h
binaryTree.o: binaryTree.c binaryTree.h
spchk.o: spchk.c spchk.h # Add this line if spchk.h exists and is used