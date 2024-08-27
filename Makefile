# Compiler and flags
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcrypto -lc
TARGET = bin/controller.o

# Source files
SRCS = main.c controller.c registrator.c inspector.c arg_parser.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p bin
	@touch control-list.txt
	$(CC) $(CFLAGS) main.o controller.o registrator.o inspector.o arg_parser.o $(LDFLAGS) -o bin/controller

# Compile each source file individually
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

controller.o: controller.c
	$(CC) $(CFLAGS) -c controller.c -o controller.o

registrator.o: registrator.c
	$(CC) $(CFLAGS) -c registrator.c -o registrator.o

inspector.o: inspector.c
	$(CC) $(CFLAGS) -c inspector.c -o inspector.o

arg_parser.o: arg_parser.c
	$(CC) $(CFLAGS) -c arg_parser.c -o arg_parser.o

# Clean up the build
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program with the specified arguments
run: $(TARGET)
	./bin/controller --help

.PHONY: all clean run

