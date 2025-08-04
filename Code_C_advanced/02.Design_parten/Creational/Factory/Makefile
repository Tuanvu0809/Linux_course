CC = gcc
CFLAGS = -Wall -g
TARGET = factory
SRCS =  main.c src/light.c src/temp.c src/factory.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)

