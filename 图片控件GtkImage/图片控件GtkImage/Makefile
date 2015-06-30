CC = gcc  
SRC = image.c
TARGET = demo
CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)
.PHONY clean:
	rm $(TARGET) -rf