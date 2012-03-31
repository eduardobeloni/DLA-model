#ifndef DLA_H
#define DLA_H

#include <gtkmm/drawingarea.h>

class DLA: public Gtk::DrawingArea
{
protected:
	virtual void on_realize();
	virtual bool on_expose_event(GdkEventExpose *e);

	Gdk::Color red_colour,
			green_colour,
			black_colour;
	Glib::RefPtr<Gdk::GC> red_gc,
				green_gc,
				black_gc;

private:
	static const short SIZE = 300;
	enum { EMPTY = 0, DIFFUSION = 1, AGREGATION = 2 };
	short sites[SIZE+1][SIZE+1];
	short down_right;
	bool final_state;

	void rotate_block(short *neigh[2][2], int nr);
	void update_block(short *neigh[2][2], bool agregation);

public:
	DLA();
	~DLA();

	void reset(short new_rand);
	void next_state();
	bool final_state_reached();
};

#endif
