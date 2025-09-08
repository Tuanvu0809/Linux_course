CC = gcc
CFLAGS = -Wall -g
TARGET = Mid_project
SRCS = main.c src/cpu_monitor.c src/ram_monitor.c src/disk_monitor.c src/network_monitor.c  src/model.c src/log.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)
