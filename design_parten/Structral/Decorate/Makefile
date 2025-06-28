CC = gcc
CFLAGS = -Wall -g
TARGET = Uart
SRCS =  main.c communicate/crc.c communicate/communicate.c communicate/log.c communicate/XOR.c decorate/decorate.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe

