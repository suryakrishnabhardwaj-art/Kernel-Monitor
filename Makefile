CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = kernel_monitor
SOURCE = kernel_monitor.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
