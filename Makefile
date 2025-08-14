CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic

.PHONY: all clean
all: invaderspp

invaderspp: $(wildcard src/*.cpp) $(wildcard src/*.hpp)
	$(CXX) $(CXXFLAGS) -o invaderspp $(wildcard src/*.cpp) -lSDL2

clean:
	rm -f invaderspp
