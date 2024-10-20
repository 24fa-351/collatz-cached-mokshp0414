CC = gcc
CFLAGS = -Wall -O2
TARGET = collatz

all: $(TARGET)

$(TARGET): main.o collatz.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o collatz.o

main.o: main.c collatz.h
	$(CC) $(CFLAGS) -c main.c

collatz.o: collatz.c collatz.h
	$(CC) $(CFLAGS) -c collatz.c

clean:
	rm -f *.o $(TARGET)
