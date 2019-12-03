CC= g++
CFLAGS = -o

STD= -std=c++11
SOURCES = src/intcode.cpp
EXECUTABLE = intcode

INCLUDEPATH = -I./include

all: clean fuel_counter clean-object run

fuel_counter:
	$(CC) $(STD) $(CFLAGS)  $(EXECUTABLE) $(SOURCES) $(INCLUDEPATH)

run:
	./$(EXECUTABLE)

clean-object:
	rm -rf *.o

clean:
	rm -rf *.o $(EXECUTABLE)
