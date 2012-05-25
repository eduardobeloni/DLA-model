CXX ?= g++
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

TARGET = dla_model

CXXFLAGS = -O3 -Wall -pipe
CXXFLAGS += `pkg-config --cflags gtkmm-2.4`
LDLIBS += `pkg-config --libs gtkmm-2.4`

all: $(TARGET)

# $^ tells make to compile all prerequisites
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

-include $(DEP)

# $<: compile only the first prerequisite, not all of them
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	$(CXX) -MM $(CFLAGS) $*.cpp > $*.d

clean:
	rm -rf *.o $(TARGET) *.d
