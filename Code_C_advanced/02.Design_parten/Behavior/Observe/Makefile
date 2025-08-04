CC = gcc
CFLAGS = -Wall -g
TARGET = Behavior
SRCS = main.c src/Publisher.c src/Publisher/door.c src/Publisher/smoke.c src/Subscriber/alarm.c src/Subscriber/mobile.c

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)
