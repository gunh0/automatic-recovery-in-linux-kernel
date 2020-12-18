SUFFIXES = .c .o

OBJS = main.o
SRCS = main.c

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
# CFLAGS = -g

# the build target executable:
TARGET = recovery

all: $(TARGET)

$(TARGET): $(OBJS)
#$(CC) $(CFLAGS) -o $(OBJS) $(SRCS)
	$(CC) -o $(TARGET) $(OBJS)

start:
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET) core