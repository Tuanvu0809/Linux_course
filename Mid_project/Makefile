CC = gcc
CFLAGS = -Wall -g
TARGET = Mid_project
SRCS = main.c src/CPU_parameter.c src/RAM_parameter.c src/Disk_parameter.c src/Network_parameters.c src/Handle_function.c src/Log.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)
