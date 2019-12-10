CC= g++
CFLAGS = -o
WARNING = -fstack-protector-all -fPIC -O2 -pedantic-errors -Wall -Weffc++ -Werror -Wextra -Wshadow -Wswitch-default


STD= -std=c++11
SOURCES = src/*.cpp
EXECUTABLE = program.out

INCLUDEPATH = -I./include

all: clean crossed_wires clean-object run

crossed_wires:
	$(CC) $(STD) $(CFLAGS)  $(EXECUTABLE) $(SOURCES) $(INCLUDEPATH) $(WARNING)

run:
	./$(EXECUTABLE)

clean-object:
	rm -rf *.o

clean:
	rm -rf *.o $(EXECUTABLE)
