// Damon V. Caskey
// CS 215, Spring 2014
// Programming assignment 4
// 10 April, 2014

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include "position.h"
#include "positionlist.h"
using namespace std;

class MineSweeperBoard
{
public:
	// Initialize a board with a given width and height, containing the
	// given number of randomly-placed mines.  Nothing should be revealed
	// or flagged.  If there are more mines than spaces for them, fill
	// the entire board with mines.
	MineSweeperBoard(int board_width, int board_height, int mine_count);
	// Clean up the board, freeing any dynamically allocated memory.
	~MineSweeperBoard();

	// Get the size of the board.
	int get_width() const;
	int get_height() const;

	// Reveal a square.
	// If this square wasn't already revealed, and if the number of
	// adjacent mines equals the number of adjacent flags, recursively
	// reveal all the surrounding squares that aren't flagged.
	void reveal(Position p);

	// Put a flag on a square, or remove a flag that is
	// already there.  Returns true if we placed a flag, false if
	// we removed one.
	bool flag(Position p);

	// Return the appearance of the square (what will be
	// displayed to the player) as a single character.
	char appearance(Position p) const;

	// Display the entire board to an output stream.  Prints
	// a header with the column numbers, and prints the row
	// number on each line.  For example,
	//     |  0  1  2  3  4
	//  ---+---------------
	//   0 |  1  /  .  .  .
	//   1 |  1  2  .  .  .
	//   2 |  0  1  .  .  .
	//   3 |  0  1  2  1  1
	//   4 |  0  0  0  0  0
	void display(ostream &out) const;

	// Returns true if the player won (every square with a mine
	// is flagged, and every cell without a mine is revealed).
	bool won() const;

	// Returns true if the player lost (there is a revealed
	// mine).
	bool lost() const;

	// Reveal everything (losing the game in the process)
	void give_up();
private:
	// Returns a list of all the positions adjacent to p.  If p
	// is in the middle of the board, it has eight neighbors,
	// but if it is on an edge or corner it will have fewer.
	PositionList adjacent(Position p) const;

	// Return the number of mines or flags adjacent to a square.
	int adjacent_mines(Position p) const;
	int adjacent_flags(Position p) const;

	// Size of the board.
	int width;
	int height;

	// Dynamically allocated 2D arrays indicating which squares are
	// revealed, which are mined, and which are flagged.
	bool **revealed;
	bool **mined;
	bool **flagged;
};
#endif
