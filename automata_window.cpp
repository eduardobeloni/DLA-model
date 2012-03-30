#include "automata_window.h"

#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/frame.h>

AutomataWindow::AutomataWindow():
	run_btn("Start"),
	stop_btn("Stop"),
	apply_btn("Apply"),
	dla()
{
	this->set_border_width(10);
	this->set_resizable(false);
	this->set_title("DLA model");
	this->set_icon_from_file("./dla_pic.gif");

	Gtk::VBox *main_vbox = Gtk::manage(new Gtk::VBox(false, 10));
	Gtk::HBox *conc_hbox = Gtk::manage(new Gtk::HBox(false, 10));
	Gtk::Frame *conc_frame = Gtk::manage(new Gtk::Frame("Concentration Percentage"));
	Gtk::HButtonBox *btn_box = Gtk::manage(new Gtk::HButtonBox);
	Gtk::Adjustment *rand_setup =
		Gtk::manage(new Gtk::Adjustment(25.0, 10.0, 90.0, 5.0));

	rand_spinbtn.set_adjustment(*rand_setup);
	dla.reset(rand_spinbtn.get_value_as_int());

	this->add(*main_vbox);

	main_vbox->pack_start(dla);
	main_vbox->pack_start(*conc_frame);
	main_vbox->pack_start(*btn_box);

	conc_frame->add(*conc_hbox);
	conc_hbox->pack_start(rand_spinbtn);
	conc_hbox->pack_start(apply_btn);
	conc_hbox->set_border_width(5);

	btn_box->pack_start(run_btn);
	btn_box->pack_start(stop_btn);

	run_btn.signal_clicked().connect(sigc::mem_fun(*this, &AutomataWindow::on_run_button_clicked));
	run_btn.set_sensitive(true);
	run_btn.grab_focus();

	stop_btn.signal_clicked().connect(sigc::mem_fun(*this, &AutomataWindow::on_stop_button_clicked));
	stop_btn.set_sensitive(false);

	apply_btn.signal_clicked().connect(sigc::mem_fun(*this, &AutomataWindow::on_apply_button_clicked));

	this->show_all_children();
}

AutomataWindow::~AutomataWindow() { }

void AutomataWindow::on_run_button_clicked()
{
	run_btn.set_sensitive(false);
	run_btn.set_label("Resume");
	stop_btn.set_sensitive(true);
	apply_btn.set_sensitive(false);
	rand_spinbtn.set_sensitive(false);
	stop_btn.grab_focus();

	// slot I wish to have called when timeout occurs
	sigc::slot<bool> my_slot = sigc::mem_fun(*this, &AutomataWindow::on_timeout);

	// connecting my_slot to Glib::signal_timeout(): slot, delay(ms)
	timer = Glib::signal_timeout().connect(my_slot, 50);
}

void AutomataWindow::on_stop_button_clicked()
{
	stop_btn.set_sensitive(false);
	run_btn.set_sensitive(true);
	apply_btn.set_sensitive(true);
	rand_spinbtn.set_sensitive(true);
	run_btn.grab_focus();

	timer.disconnect();
}

void AutomataWindow::on_apply_button_clicked()
{
	run_btn.set_label("Start");
	run_btn.grab_focus();
	dla.reset(rand_spinbtn.get_value_as_int());
	dla.queue_draw();
}

bool AutomataWindow::on_timeout()
{
	dla.next_state();
	dla.queue_draw();

	return true;	// keeps on timeout until stop button
}
