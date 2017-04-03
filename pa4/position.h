// Damon V. Caskey
// CS 215, Spring 2014
// Programming assignment 4
// 10 April, 2014
#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

// Class representing a position on a two-dimensional board.
// Stores an x and y coordinate, with methods to return and
// set each coordinate, and a method to test whether the
// position falls within a given width and height.
class Position
{
public:
	// Create a Position object for the origin (0, 0).
	Position();

	// Create a Position object for the position (xc, yc).
	Position(int xc, int yc);

	// Getters and setters for x and y coordinates.
	int x() const;
	int y() const;
	void set_x(int new_x);
	void set_y(int new_y);

	// Returns true if this position's coordinates are
	// within the given bounds: 0 <= x < width and
	// 0 <= y < height .
	bool in_bounds(int width, int height) const;
private:
	int xcoord;
	int ycoord;
};

#endif
