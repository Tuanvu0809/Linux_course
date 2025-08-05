CC = gcc
CFLAGS = -Wall -g
TARGET = log
SRCS = main.c src/log.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)

