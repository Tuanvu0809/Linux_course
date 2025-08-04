CC = gcc
CFLAGS = -Wall -g
TARGET = pixel
SRCS = main.c src/led_driver.c test/test.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)

