#ifndef AUTOMATA_WINDOW_H
#define AUTOMATA_WINDOW_H

#include "dla.h"

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/label.h>

class AutomataWindow : public Gtk::Window
{
protected:
	Gtk::Button run_btn,
				stop_btn,
				apply_btn;
	Gtk::Label final_state_text;
	DLA dla;
	sigc::connection timer;
	Gtk::SpinButton rand_spinbtn;

	virtual void on_run_button_clicked();
	virtual void on_stop_button_clicked();
	virtual void on_apply_button_clicked();
	virtual bool on_timeout();

public:
	AutomataWindow();
	virtual ~AutomataWindow();
};

#endif
