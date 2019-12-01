CC= g++
CFLAGS = -o

STD= -std=c++11
SOURCES = src/fuel_counter.cpp
EXECUTABLE = fuel_counter

INCLUDEPATH = -I./include

all: clean fuel_counter clean-object run

fuel_counter:
	$(CC) $(STD) $(CFLAGS)  $(EXECUTABLE) $(SOURCES) $(INCLUDEPATH) $(FRAMEWORK)

run:
	./$(EXECUTABLE)

clean-object:
	rm -rf *.o

clean:
	rm -rf *.o $(EXECUTABLE)