CC = gcc
CFLAGS = -Wall -g
TARGET = Mid_project
SRCS = main.c src/cpu.c src/ram.c src/disk.c src/network.c  src/model.c src/log.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)
