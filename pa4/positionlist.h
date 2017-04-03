// CS 215, Spring 2014
// Programming assignment 4
// 10 April, 2014
#ifndef POSITIONLIST_H_INCLUDED
#define POSITIONLIST_H_INCLUDED

#include "position.h"

// Class representing a node in a PostionList.  This class
// is intended to be used only by PositionList.
class Node
{
public:
	// Create a new node with no next node and position p.
	Node(Position p);
private:
	// A pointer to the next node in the linked list.
	Node *next;

	// The Position being stored in this node.
	Position pos;

	// The Node class is intended for the internal use of
	// PositionList, so give that class access to our
	// private data members.
	friend class PositionList;
};


// Class representing a position on a two-dimensional board.
// Stores an x and y coordinate, with methods to return and
// set each coordinate, and a method to test whether the
// position falls within a given width and height.
class PositionList
{
public:
	// Initialize an empty list.
	PositionList();

	// Initialize a list as a deep copy of another.
	PositionList(const PositionList &original);

	// Clean up this list by freeing all its nodes.
	~PositionList();

	// Deep copy the contents of another list into this one.  Replace the old
	// contents of this list, freeing those nodes.  Returns the implicit
	// parameter by reference (return *this;)
	//
	// This method implements assignment:   poslist = otherposlist;
	PositionList &operator=(const PositionList &other);

	// Returns true if this list is empty.
	bool empty() const;

	// Calculate the size of the list (number of nodes).
	int size() const;
	
	// Find and return the index-th element in the list, counting from 0.
	// If the index was out of bounds, return the Position (-1, -1).
	Position get(int index) const;

	// Add a new Position object to the beginning of the list.
	void push_front(Position pos);

	// Remove the first element, freeing its node.
	void pop_front();

private:
	// Recursively make a deep copy of a node and all the nodes that follow.
	// Returns the copy.  The input may be NULL, in which case nothing is
	// copied and the function returns NULL.
	// This function will be used by the copy constructor and by operator= .
	Node *copy_nodes(const Node *in) const;

	Node *first;
};

#endif
