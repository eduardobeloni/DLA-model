#include "automata_window.h"

#include <gtkmm/main.h>

int main(int argc, char **argv)
{
	Gtk::Main automata(argc, argv);
	AutomataWindow dla;
	automata.run(dla);

	return 0;
}
