CC = gcc
CFLAGS = -Wall -g
TARGET = Behavior
SRCS = main.c src/Publisher.c src/pub/door.c src/pub/smoke.c src/sub/alarm.c src/sub/mobile.c

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe
