CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

TARGET = programa
SRC = main.cpp skaitymas.cpp meniu.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.exe

.PHONY: all run clean