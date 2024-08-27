# Compiler and flags
CC = gcc
CFLAGS = -Wall  -Wunused-result
LDFLAGS = -lcrypto -lc
TARGET = bin/controller

# Source files
SRCS = main.c controller.c registrator.c inspector.c arg_parser.c

# Object files
OBJS = $(SRCS:.c=.o)
OBJDIR = obj

# Default target
all: $(TARGET)

# Create the target directory if it doesn't exist and link the object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p bin
	@mkdir -p $(OBJDIR)
	@touch control-list.txt
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile each source file individually and store object files in $(OBJDIR)
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# Run the program with the specified arguments
run: $(TARGET)
	./bin/controller --help

.PHONY: all clean run
