CC = gcc
CFLAGS = -Wall -g
TARGET = smart_home
SRCS = main.c src/smarthome.c src/sercurity.c src/light.c src/hvac.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)

