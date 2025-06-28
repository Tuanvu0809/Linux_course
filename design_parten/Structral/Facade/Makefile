CC = gcc
CFLAGS = -Wall -g
TARGET = smart_home
SRCS = main.c smarthome/smarthome.c sercurity/sercurity.c light/light.c hvac/hvac.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe

