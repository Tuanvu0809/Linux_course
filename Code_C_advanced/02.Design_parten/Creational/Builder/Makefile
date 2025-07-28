CC = gcc
CFLAGS = -Wall -g
TARGET = uart
SRCS = main.c src/Uart_builder.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe

