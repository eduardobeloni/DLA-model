CXXFLAGS = -O3 -Wall -pipe
CXXFLAGS += `pkg-config --cflags gtkmm-2.4`
LDLIBS += `pkg-config --libs gtkmm-2.4`

all: dla_model

dla_model: main.o automata_window.o dla.o
	g++ main.o automata_window.o dla.o -o dla_model $(CXXFLAGS) $(LDLIBS)

main.o: main.cpp
	g++ -c $(CXXFLAGS) main.cpp

automata_window.o: automata_window.cpp
	g++ -c $(CXXFLAGS) automata_window.cpp

dla.o: dla.cpp dla.h
	g++ -c $(CXXFLAGS) dla.cpp

clean:
	rm -rf *.o dla_model
