CC = gcc
CFLAGS = -Wall -g
TARGET = media
SRCS = main.c src/Musicplayer.c src/pause.c src/playing.c src/stopped.c

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe
