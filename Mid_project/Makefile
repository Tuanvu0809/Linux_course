CC = gcc
CFLAGS = -Wall -g
TARGET = Mid_project
SRCS = main.c src/CPU_parameter.c src/RAM.c src/Storetage.c src/network_parameters.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)
