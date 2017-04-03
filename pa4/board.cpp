// Damon V. Caskey
// CS 215, Spring 2014
// Programming assignment 4
// 10 April, 2014

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
using namespace std;

// Constructor
MineSweeperBoard::MineSweeperBoard(int board_width, int board_height, int mine_count)
{
	//Initialize a board of the given size, dynamically allocating the 2D array data members. Randomly place the requested number of mines.
	
	// Mine place coordinates.
	struct coords
	{		
		int x;	// Coloumn
		int y;	// Row.
	} coords;
		
	int mines		= mine_count;	// Mines left to place on board.
	int i			= 0;			// Loop counter.

	// Seed the random number generator.
	srand(time(NULL));

	// Set data members.
	height = board_height;
	width = board_width;

	// Allocate memory for rows.
	revealed	= new bool *[height];
	mined		= new bool *[height];
	flagged		= new bool *[height];

	// Allocate memory for elements of each column.
	for(i = 0; i < height; i++ )
	{
		revealed[i] = new bool[width];
		mined[i]	= new bool[width];
		flagged[i]	= new bool[width];
	}
	
	// Let's set all board values to false.
	for (coords.y = 0; coords.y < height; coords.y++) 
	{
		for (coords.x = 0; coords.x < width; coords.x++) 
		{
			mined[coords.y][coords.x] = false;
			flagged[coords.y][coords.x] = false;
			revealed[coords.y][coords.x] = false;			
		}
	}

	// Let's set up the mined positions.
	while(mines > 0)
	{
		coords.x = rand() % (width -1);		// Random column.
		coords.y = rand() % (height -1);	// Random row.

		// Debug output
		// cout << endl << "Choosing mine locations... (X: " << coords.x << ", Y: " << coords.y << ").";

		// If selected position is not already mined, mark it as mined
		// and decrement remaining mines to add.
		if(!(mined[coords.y][coords.x] == true))
		{	
			mined[coords.y][coords.x] = true;		

			// Debug output.
			// cout << endl << "Armed. Mines remaining: " << mines;
			mines--;
		}				
	}
}

// Destructor
MineSweeperBoard::~MineSweeperBoard()
{
	int i = 0; // Loop counter.

	// Clean up allocated memory.
	for(i = 0; i < height; i++)
	{
		delete[] revealed[i];
		delete[] mined[i];	
		delete[] flagged[i];		
	}

	delete[] revealed;
	delete[] mined;
	delete[] flagged;
}

// Return width of board.
int MineSweeperBoard::get_width() const
{
	return width;
}

// Return height of board.
int MineSweeperBoard::get_height() const
{
	return height;
}

// Place a flag at the given position, or remove a flag that is already there. Returns true if it placed a flag, false if it removed one.
bool MineSweeperBoard::flag(Position p)
{
	bool result = false;	// Final result.
	
	int x = p.x();
	int y = p.y();

	// If not flagged, we'll prepare a true value.
	if(flagged[y][x] == false)
	{
		result = true;
	}

	// Set flag status.
	flagged[y][x] = result;

	// Return result.
	return result;
}

char MineSweeperBoard::appearance(Position p) const
{
	int x = p.x();
	int y = p.y();

	if (flagged[y][x]) {
		return '/';
	} else if (revealed[y][x]) {
		if (mined[y][x]) {
			// Boom!
			return '*';
		} else {
			// At most 8 adjacent mines, so one digit.
			int adjmines = adjacent_mines(p);
			// Convert a number to a digit character.
			return '0' + adjmines;
		}
	} else {
		// Unrevealed, unflagged.
		return '.';
	}
}

// Display entire board to the output stream.  
void MineSweeperBoard::display(ostream &out) const
{
	// loop counters.
	struct loop
	{
		int y;	// Vertical axis.
		int x;	// Horizontal axis.
	} loop;

	Position P;
	
	// Let's paint the horizontal header.
	
	//   | 0  1  2 
	//___|_________
	// 0 | F  F  F

	// Spaces and first pipe (vertical line).  "   |"
	out << endl << endl << "   " << "|"; 
	
	// Horizontal numbers. "| 0  1  2..."
	for(loop.x = 0; loop.x < width; loop.x++)
	{
		out << " " << loop.x << " ";
	}

	// Horizontal rule. "___|"
	out << endl << "___|";

	// "___ ..."
	for(loop.x = 0; loop.x < width; loop.x++)
	{
		out << "___";
	}

	// Vertical numbers and board.
	for(loop.y = 0; loop.y < height; loop.y++)
	{
		out << endl << " " << loop.y << " |";
		for (loop.x = 0; loop.x < width; loop.x++)
		{
			P.set_x(loop.x);
			P.set_y(loop.y);

			out << " " << appearance(P) << " ";
		}
	}
}


// Return true of player won.
bool MineSweeperBoard::won() const
{
	// Check every square.  If we see a square that is mined but
	// not flagged, or unmined but not revealed, return false
	// immediately.  If we get to the end, every square is correct,
	// so the user won and we return true.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (mined[y][x] && !flagged[y][x]) {
				return false;
			} else if (!mined[y][x] && !revealed[y][x]) {
				return false;
			}
		}
	}
	return true;
}

// Return true if the player lost: if one or more mines have been revealed.
bool MineSweeperBoard::lost() const
{
	// Check every square.  If we see a square that is mined 
	// and revealed return true immediately.  
	// If we get to the end, the user has not lost thus far
	// and we return false.
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			if (mined[y][x] && revealed[y][x]) 
			{
				return true;
			}
		}
	}
	return false;
}

// Return a list of the positions adjacent to the given one, horizontally, vertically, and diagonally.
PositionList MineSweeperBoard::adjacent(Position p) const
{
	PositionList result;

	// Loop over the 3x3 block centered around p.
	for (int adj_y = p.y() - 1; adj_y <= p.y() + 1; adj_y++) 
	{
		for (int adj_x = p.x() - 1; adj_x <= p.x() + 1; adj_x++) 
		{
			// Make a position out of the new coordinates.
			Position adj(adj_x, adj_y);
		
			// Skip out-of-bounds squares
			if (!adj.in_bounds(width, height))
			{
				continue;
			}
			
			// Also skip the center.
			if (adj.x() == p.x() && adj.y() == p.y())
			{
				continue;
			}

			// If we get here, it's really adjacent, so add it to the list.
			result.push_front(adj);
		}
	}
	return result;
}

// Return the number of mined squares adjacent to the indicated square.
int MineSweeperBoard::adjacent_mines(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) 
	{
		Position adj = neighbors.get(i);
		
		// If it's mined, increase the count.
		if (mined[adj.y()][adj.x()])
		{
			adjacent_count++;
		}
	}
	return adjacent_count;
}

// Return the number of flagged squares adjacent to the indicated square.
int MineSweeperBoard::adjacent_flags(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) 
	{
		Position adj = neighbors.get(i);
		
		// If it's flagged, increase the count.
		if (flagged[adj.y()][adj.x()])
		{
			adjacent_count++;
		}
	}
	return adjacent_count;
}

// Reveal the square at the given position, and recursively reveal some adjacent squares
void MineSweeperBoard::reveal(Position p)
{
	int i = 0; // Loop counter.

	struct coords
	{
		int x;	// Column.
		int y;	// Row.
	} coords;

	coords.x = p.x();
	coords.y = p.y();

	// If already revealed, exit.
	if(revealed[coords.y][coords.x])
	{
		return;
	}

	// Set base.
	revealed[coords.y][coords.x] = true;
	flagged[coords.y][coords.x] = false;
	
	// If mine is here, exit.
	if(mined[coords.y][coords.x])
	{
		return;
	}

	// Same count of mines as flags?
	if(adjacent_mines(p) == adjacent_flags(p))
	{
		// Get adjacent elements list.
		PositionList list = adjacent(p);

		// Loop over list elements. 
		for(i = 0; i < list.size(); i++)
		{
			// If no flag found, call self with next item.
			if(!flagged[list.get(i).y()][list.get(i).x()])
			{
				reveal(list.get(i));
			}
		}
	}
}

// Give up the game and reveal the entire board.
void MineSweeperBoard::give_up()
{
	// loop counters.
	struct loop
	{
		int y;	// Vertical axis.
		int x;	// Horizontal axis.
	} loop;

	// Loop entire board and set all elements to revealed.
	for(loop.y = 0; loop.y < height; loop.y++)
	{
		for(loop.x = 0; loop.x < width; loop.x++)
		{
			revealed[loop.y][loop.x] = true;
		}
	}
}