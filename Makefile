CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

SRC = main.cpp skaitymas.cpp meniu.cpp Generavimas.cpp spausdinam.cpp laikai.cpp tyrimas.cpp

all: programa_vector programa_list programa_deque

programa_vector:
	$(CXX) $(CXXFLAGS) $(SRC) -o programa_vector

programa_list:
	$(CXX) $(CXXFLAGS) -DUSE_LIST $(SRC) -o programa_list

programa_deque:
	$(CXX) $(CXXFLAGS) -DUSE_DEQUE $(SRC) -o programa_deque

clean:
	rm -f programa_vector programa_list programa_deque *.exe benchmark_*.md

.PHONY: all clean
