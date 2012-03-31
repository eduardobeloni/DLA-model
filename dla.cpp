#include "dla.h"

#include <cstdlib>
#include <iostream>

DLA::DLA():
	red_colour("red"),
	green_colour("green"),
	black_colour("black"),
	down_right(0)
{
	time_t t;
	time(&t);
	srandom(t);

	this->set_size_request(SIZE, SIZE);
}

DLA::~DLA() { }

void DLA::reset(short new_rand)
{
	for (int j = 0; j <= SIZE; j++)
		for (int i = 0; i <= SIZE; i++)
			if (rand() % 100 < new_rand)
				sites[j][i] = DIFFUSION;
			else
				sites[j][i] = EMPTY;

	sites[SIZE/2][SIZE/2] = AGREGATION;
	sites[SIZE/2][SIZE/2+1] = AGREGATION;
	sites[SIZE/2+1][SIZE/2] = AGREGATION;
	sites[SIZE/2+1][SIZE/2+1] = AGREGATION;
}

void DLA::on_realize()
{
	Gtk::DrawingArea::on_realize();

	// a colourmap to allocate resources
	Glib::RefPtr<Gdk::Colormap> curr_colourmap = this->get_default_colormap();
	curr_colourmap->alloc_color(red_colour);
	curr_colourmap->alloc_color(green_colour);
	curr_colourmap->alloc_color(black_colour);

	// getting window to create graphical contexts
	Glib::RefPtr<Gdk::Window> curr_win = this->get_window();

	red_gc = Gdk::GC::create(curr_win);
	red_gc->set_foreground(red_colour);

	green_gc = Gdk::GC::create(curr_win);
	green_gc->set_foreground(green_colour);

	black_gc = Gdk::GC::create(curr_win);
	black_gc->set_foreground(black_colour);
}

bool DLA::on_expose_event(GdkEventExpose *e)
{
	// getting the current window to draw
	Glib::RefPtr<Gdk::Window> curr_win = this->get_window();

	// a black square
	std::vector<Gdk::Point> sqr;
	// storing black square's points
	sqr.push_back(Gdk::Point(1, 1));
	sqr.push_back(Gdk::Point(1, SIZE));
	sqr.push_back(Gdk::Point(SIZE, SIZE));
	sqr.push_back(Gdk::Point(SIZE, 1));
	// drawing the black square
	curr_win->draw_polygon(black_gc, true, sqr);

	// drawing the points
	for (int y = 1; y < SIZE; y++)
	{
		for (int x = 1; x < SIZE; x++)
		{
			if (sites[y][x] == DIFFUSION)
				curr_win->draw_point(red_gc, x, y);
			else if (sites[y][x] == AGREGATION)
				curr_win->draw_point(green_gc, x, y);
		}
	}

	return true;
}

void DLA::rotate_block(short *neigh[2][2], int nr)
{
	short tmp;

	while (nr--)
	{
		tmp = *neigh[0][0];
		*neigh[0][0] = *neigh[1][0];
		*neigh[1][0] = *neigh[1][1];
		*neigh[1][1] = *neigh[0][1];
		*neigh[0][1] = tmp;
	}
}
void DLA::update_block(short *neigh[2][2], bool agregation)
{
	if (agregation)
	{
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++)
				if (*neigh[y][x] != EMPTY)
					*neigh[y][x] = AGREGATION;
	}
	else
		this->rotate_block(neigh, rand() % 3);
}

void DLA::next_state()
{
	short *neigh[2][2];
	bool agreg = false;

	for (int j = down_right; j < SIZE + down_right; j += 2)
	{
		for (int i = down_right; i < SIZE + down_right; i += 2)
		{
			neigh[0][0] = &sites[j][i];
			if (*neigh[0][0] == AGREGATION) agreg = true;

			neigh[0][1] = &sites[j][i+1];
			if (*neigh[0][1] == AGREGATION) agreg = true;

			neigh[1][0] = &sites[j+1][i];
			if (*neigh[1][0] == AGREGATION) agreg = true;

			neigh[1][1] = &sites[j+1][i+1];
			if (*neigh[1][1] == AGREGATION) agreg = true;

			this->update_block(neigh, agreg);
			agreg = false;
		}
	}

	down_right = down_right ? 0 : 1;
}
