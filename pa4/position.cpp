// Damon V. Caskey
// CS 215, Spring 2014
// Programming assignment 4
// 10 April, 2014
#include "position.h"

Position::Position()
	: xcoord(0), ycoord(0)
{}

Position::Position(int xc, int yc)
	: xcoord(xc), ycoord(yc)
{}

int Position::x() const
{
	return xcoord;
}

int Position::y() const
{
	return ycoord;
}

void Position::set_x(int new_x)
{
	xcoord = new_x;
}

void Position::set_y(int new_y)
{
	ycoord = new_y;
}

bool Position::in_bounds(int width, int height) const
{
	return 0 <= xcoord && xcoord < width
	    && 0 <= ycoord && ycoord < height;
}
