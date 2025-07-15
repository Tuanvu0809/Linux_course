CC = gcc
CFLAGS = -Wall -g
TARGET = factory
SRCS =  main.c light/light.c temp/temp.c sensor/factory.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe

