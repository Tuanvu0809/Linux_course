CC = gcc
CFLAGS = -Wall -g
TARGET = Uart
SRCS =  main.c src/CRC.c src/communicate.c src/Log.c src/XOR.c src/decorate.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe

