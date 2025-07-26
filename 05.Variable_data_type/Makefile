CC = gcc
CFLAGS = -Wall -g
TARGET = Smart_Plant
SRCS = main.c src\led.c src\actuators.c src\button.c src\sensor.c src\watering_logic.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe
