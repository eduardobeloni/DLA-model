CXX ?= g++
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = dla_model

CXXFLAGS = -O3 -Wall -pipe
CXXFLAGS += `pkg-config --cflags gtkmm-2.4`
LDLIBS += `pkg-config --libs gtkmm-2.4`

all: $(TARGET)

# $^ tells make to compile all prerequisites
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# $<: compile only the first prerequisite, not all of them
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

automata_window.o: automata_window.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dla.o: dla.cpp dla.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
