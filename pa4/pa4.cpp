// Damon V. Caskey
// CS 215, Spring 2014
// Programming assignment 4
// 10 April, 2014
// Dimension limits for board.

#define TITLE	"Minesweeper"
#define AUTHOR	"Damon Vaughn Caskey"
#define RELEASE	"2014-05-01"
#define CONTACT	"www.caskeys.com/dc"

// Game limitations.
#define DIMENSIONMIN 5
#define DIMENSIONMAX 20

// Minimum mines allowed.
#define MINESMIN 0

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "board.h"
using namespace std;

enum action
{
	INVALID,
	REVEAL,
	FLAG,
	QUIT
};

// Prototypes.
void pause_215(bool have_newline);	// Pause at end of program.
action action_input();				// Validate and return action constant from user input.

int main()
{
	// Seed random number generator.
	srand(static_cast<unsigned int>(time(NULL)));
	
	// Position object.
	Position p;

	// Game parameter inputs structure.
	struct parameters
	{
		int x;		// Board size request (columns).
		int y;		// Board size request (rows).
		int mines;	// Number of mines requested.
	} parameters;

	// Game time structure
	struct timer
	{
		time_t start;	// Start time.		
		int seconds;	// Seconds elapsed.
	} timer;
	
	action action;		// User action.

	
	// Get starting time.
	timer.start = time(NULL);

	// Author info.
	cout << TITLE << endl << AUTHOR << endl << RELEASE << endl << CONTACT << endl << endl;

	// Start the game prompt.
	cout << "Let's play Minesweeper!" << endl;
	
	// Prompt for and get board size.
	do
	{
		// Prompt user for input.
		cout << endl << "How large should the board be (width height)? Enter sizes between " << DIMENSIONMIN << " and " << DIMENSIONMAX << "." << endl;
	
		// Clear any existing errors and attempt to populate result with input.
		if(!(cin >> parameters.x >> parameters.y))
		{
			cout << endl << " Please enter two numbers separated by a space." << endl;
			cin.clear();
			cin.ignore(10000,'\n');

			// Set for loop.
			parameters.x = -1;
		}

		if(parameters.x < DIMENSIONMIN || parameters.x > DIMENSIONMAX)
		{
			cout << endl << " The X value is out of bounds. You must enter values between " << DIMENSIONMIN << " and " << DIMENSIONMAX << "." << endl;
			parameters.x = -1;
		}

		if(parameters.y < DIMENSIONMIN || parameters.y > DIMENSIONMAX)
		{
			cout << endl << " The Y value is out of bounds. You must enter values between " << DIMENSIONMIN << " and " << DIMENSIONMAX << "." << endl;
			parameters.x = -1;
		}

	} while(parameters.x == -1);
	
	// Prompt for and get maximum number of mines.
	do
	{
		// Prompt user for input.
		cout << endl << "How many mines would you like (" << MINESMIN << " to " << parameters.x * parameters.y << ")?" << endl;

		// Clear any existing errors and attempt to populate result with input.
		if(!(cin >> parameters.mines))
		{
			cout << endl << " Please enter a numeric value." << endl;
			cin.clear();
			cin.ignore(10000,'\n');

			// Set for loop.
			parameters.mines = -1;
		}

		if(parameters.mines < MINESMIN || parameters.mines > (parameters.x * parameters.y))
		{
			cout << endl << " The value is out of bounds. You must enter values between " << MINESMIN << " and " << parameters.x * parameters.y << "." << endl;
			parameters.mines = -1;
		}

	} while(parameters.mines == -1);
	
	// Create a board using above params.
	MineSweeperBoard board(parameters.x, parameters.y, parameters.mines);
	
	while (!board.lost()  && !board.won())
	{
		board.display(cout);

		// Get user input.
		action = action_input();

		switch (action)
		{
			case REVEAL:				
								
				// Prompt for and get position.
				do
				{
					// Prompt user for input.
					cout << endl << "Which position (X Y)?" << endl;
	
					// Clear any existing errors and attempt to populate result with input.
					if(!(cin >> parameters.x >> parameters.y))
					{
						cout << endl << " Please enter two numbers separated by a space." << endl;
						cin.clear();
						cin.ignore(10000,'\n');

						// Set for loop.
						parameters.x = -1;
					}

					if(parameters.x < 0 || parameters.x > board.get_width()-1)
					{
						cout << endl << " The X value is out of bounds. You must enter values between " << 0 << " and " << board.get_width()-1 << "." << endl;
						parameters.x = -1;
					}

					if(parameters.y < 0 || parameters.y > board.get_height()-1)
					{
						cout << endl << " The Y value is out of bounds. You must enter values between " << 0 << " and " << board.get_height()-1 << "." << endl;
						parameters.x = -1;
					}

				} while(parameters.x == -1);

				// Set values.
				p.set_x(parameters.x);
				p.set_y(parameters.y);
				
				// Run reveal method.
				board.reveal(p);

			break;
				
			case FLAG:				
				
				// Prompt for and get position.
				do
				{
					// Prompt user for input.
					cout << endl << "Which position (X Y)?" << endl;
	
					// Clear any existing errors and attempt to populate result with input.
					if(!(cin >> parameters.x >> parameters.y))
					{
						cout << endl << " Please enter two numbers separated by a space." << endl;
						cin.clear();
						cin.ignore(10000,'\n');

						// Set for loop.
						parameters.x = -1;
					}

					if(parameters.x < 0 || parameters.x > board.get_width()-1)
					{
						cout << endl << " The X value is out of bounds. You must enter values between " << 0 << " and " << board.get_width()-1 << "." << endl;
						parameters.x = -1;
					}

					if(parameters.y < 0 || parameters.y > board.get_height()-1)
					{
						cout << endl << " The Y value is out of bounds. You must enter values between " << 0 << " and " << board.get_height()-1 << "." << endl;
						parameters.x = -1;
					}

				} while(parameters.x == -1);

				// Set values.
				p.set_x(parameters.x);
				p.set_y(parameters.y);
								
				// Run flag method.
				board.flag(p);			

			break;

			case QUIT:

				// Reveal all and display end result.
				board.give_up();				
			break;
		}		
	}
	
	// Display final result.
	board.display(cout);

	if(action != QUIT)
	{
		// Prompt user of win or loss.
		if(board.lost() == true)
		{
			cout << endl << endl << "BOOM! Better luck next time!";
		}
	
		if(board.won() == true)
		{
			cout << endl << endl << "You won, nice job!";
		}	
	}
	else
	{
		// Jab at user for quitting!
		cout << endl << "Quitting? It's offical, YOU SUCK!" << endl;
	}

	// Get elapsed time (in seconds) and prompt player of total time played.
	timer.seconds = time(NULL) - timer.start;
	cout << endl << endl << "Total play time: " << timer.seconds / 60 << " minutes, " << timer.seconds % 60 << " seconds.";

	pause_215(true);
	return 0;
}

void pause_215(bool have_newline)
{
    if (have_newline) {
        // Ignore the newline after the user's previous input.
        cin.ignore(200, '\n');
    }

    // Prompt for the user to press ENTER, then wait for a newline.
    cout << endl << "Press ENTER to continue." << endl;
    cin.ignore(200, '\n');
}

action action_input()
{
	string input;
	action result = INVALID;	// Final result.
	
	// Let's get the user's input, and make sure it's one of three commands.
	do
	{
		// Prompt user for command input.
		cout << endl << endl << "What would you like to do? [R]eveal, [F]lag, or [G]ive up?" << endl;
		cin >> input;

		if(input == "r" || input == "R")
		{
			result = REVEAL;
		}
		else if(input == "f" || input == "F")
		{
			result = FLAG;
		}
		else if(input == "g" || input == "G")
		{
			result = QUIT;
		}
		else
		{
			result = INVALID;
		}
		
	} while (result == INVALID);

	// Return the result.
	return result;
}
