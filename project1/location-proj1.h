

#ifndef LOCATION_PROJ1_H
#define LOCATION_PROJ1_H

#include <iostream>

using namespace std;

/* An object of the Location class represents a location, and also the ability
 * to find out all the possible "neighbors" of this location through an
 * iteration interface.
 *
 * The coordinates inside the Location are hidden.  A client may stream in a
 * Location object, or stream it out, but may not view its internals directly.
 * However, a client may test to see whether two Location objects are equal
 * (which is true only if their data members row and col are equal).
 *
 * A Location object acts as an iterator over all neighbor locations.  Two
 * Locations are neighbors if their rows are the same and their columns differ
 * by 1, or if their columns are the same and their rows differ by 1. A client
 * should be able to find all the neighbors of a Location loc the following
 * way:
 *
 *   for (loc.iterationBegin(); !loc.iterationDone(); loc.iterationAdvance()) {
 *       Location neighbor = loc.iterationCurrent();
 *       cout << neighbor << endl;
 *   }
 *
 * The iterationBegin() method initializes the iteration capability of a
 * Location object.  The iterationCurrent() method creates a copy of the current
 * Location object, modifies the copy so that it represents a different location
 * (either in row or column), and it returns the neighbor it created.  The
 * iterationAdvance() method moves the iteration forward, so that the next time
 * iterationCurrent() is called, it returns a different neighbor.  The
 * iterationDone() method returns true when the all the neighbors of a Location
 * have been iterated over.
 *
 * Iteration must proceed in a well-defined way for this project. The first
 * neighbor visited is to the right of the current location, then down, then to
 * the left, then up. The iterationCurrent() method should never return the same
 * Location that it was called on (i.e. a Location is never a neighbor of
 * itself).
 *
 * A Location object keeps track of where it is in the iteration sequence with
 * the data member nextDirection, which should take the value RIGHT, DOWN,
 * LEFT, UP, or DONE. These constant values are defined in the enum in the
 * class.
 *
 * The operator==() provides a means of comparing two Location objects. Two
 * Location objects are equal if they represent the same row and col (again,
 * regardless of each one's iteration status).
 *
 * The friend functions operator<<() and operator>>() provide a means of
 * streaming a Location object in or out. The operator<<() should not write an
 * endline; let the caller determine whether it wants a return.  Remember to
 * return a stream reference from each function so that input and output can be
 * chained together.
 *
 * The constructor should initialize the data members to reasonable values.
 *
 * We don't need to write the "big five" (operator=, copy constructor, move
 * constructor, and move operator=, and destructor) for this class because the
 * class does not allocate any memory, so the ones the compiler automatically
 * creates are sufficient.
 *
 * Test Mazes:
 *   0 1 2 3
 * 0 E X X X
 * 1 X X X X
 * 2 X X X X
 * 3 X X X s
 * 16
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 1 0
 * 1 1
 * 1 2
 * 1 3
 * 2 0
 * 2 1
 * 2 2
 * 2 3
 * 3 0
 * 3 1
 * 3 2
 * 3 3
 * 3 3
 * 0 0
 *
 *   0 1 2 3 4 5
 * 0 X     X X s
 * 1 X X   X   X
 * 2 X X   X X X
 * 3 X X   X
 * 4 X X X E X
 * 5 X     X X X
 * 25
 * 0 0
 * 0 3
 * 0 4
 * 0 5
 * 1 0
 * 1 1
 * 1 3
 * 1 5
 * 2 0
 * 2 1
 * 2 3
 * 2 4
 * 2 5
 * 3 0
 * 3 1
 * 3 3
 * 4 0
 * 4 1
 * 4 2
 * 4 3
 * 4 4
 * 5 0
 * 5 3
 * 5 4
 * 5 5
 * 0 4
 * 4 3
 *
 *   0 1 2 3 4
 * 0 X X S X X
 * 1 X   X   X
 * 2 X X X X X
 * 3   X     X
 * 4   E X X X
 * 19
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 0 4
 * 1 0
 * 1 2
 * 1 4
 * 2 0
 * 2 1
 * 2 2
 * 2 3
 * 2 4
 * 3 1
 * 3 4
 * 4 1
 * 4 2
 * 4 3
 * 4 4
 * 0 2
 * 4 1
 *
 *    -3 -2 -1  0
 * -3  X  X  E  X
 * -2  X     X  X
 * -1  S     X  X
 *  0  X  X  X
 *  13
 * -3 -3
 * -3 -2
 * -3 -1
 * -3 0
 * -2 -3
 * -2 -1
 * -2 0
 * -1 -3
 * -1 -1
 * -1 0
 * 0 -3
 * 0 -2
 * 0 -1
 * -1 -3
 * -3 -1
 *
 *    2 3 4 5 6 7 8 9 10 11
 * 2  X X   X   X X X X  X
 * 3  S X X     X X   X
 * 4  X X   X X X X X X  X
 * 5    X X X X X X X X
 * 6  X   X   X   X   X
 * 7  X   X X   X X X    X
 * 8  X     X   X X   X  X
 * 9    X X X   X X X X
 * 10 X           e      X
 * 11 X X X X X X X X X  X
 * 69
 * 2 2
 * 2 3
 * 2 5
 * 2 7
 * 2 8
 * 2 9
 * 2 10
 * 2 11
 * 3 2
 * 3 3
 * 3 4
 * 3 7
 * 3 8
 * 3 10
 * 4 2
 * 4 3
 * 4 5
 * 4 6
 * 4 7
 * 4 8
 * 4 9
 * 4 10
 * 4 11
 * 5 3
 * 5 4
 * 5 5
 * 5 6
 * 5 7
 * 5 8
 * 5 9
 * 5 10
 * 6 2
 * 6 4
 * 6 6
 * 6 8
 * 6 10
 * 7 2
 * 7 4
 * 7 5
 * 7 7
 * 7 8
 * 7 9
 * 7 11
 * 8 2
 * 8 5
 * 8 7
 * 8 8
 * 8 10
 * 8 11
 * 9 3
 * 9 4
 * 9 5
 * 9 7
 * 9 8
 * 9 9
 * 9 10
 * 10 2
 * 10 8
 * 10 11
 * 11 2
 * 11 3
 * 11 4
 * 11 5
 * 11 6
 * 11 7
 * 11 8
 * 11 9
 * 11 10
 * 11 11
 * 3 2
 * 10 8
 *
 *   0 1 2 3 4
 * 0 S X X X X
 * 1         X
 * 2 X X X X X
 * 3 X
 * 4 X X X X e
 * 17
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 0 4
 * 1 4
 * 2 0
 * 2 1
 * 2 2
 * 2 3
 * 2 4
 * 3 1
 * 4 0
 * 4 1
 * 4 2
 * 4 3
 * 4 4
 * 0 0
 * 4 4
 *
 *   1 2 3 4
 * 1 X e X X
 * 2 X X   X
 * 3 X X X
 * 4 X   X S
 * 13
 * 1 1
 * 1 2
 * 1 3
 * 1 4
 * 2 1
 * 2 2
 * 2 4
 * 3 1
 * 3 2
 * 3 3
 * 4 1
 * 4 3
 * 4 4
 * 4 4
 * 1 2
 *
 *   0 1 2 3
 * 0 S X X e
 * 4
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 0 0
 * 0 3
 *
 *   0 1 2 3
 * 0 S X X X
 * 1   X   X
 * 2 X X
 * 3 X   X e
 * 4 X   X
 * 5 X X X
 * 16
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 1 1
 * 1 3
 * 2 0
 * 2 1
 * 3 0
 * 3 2
 * 3 3
 * 4 0
 * 4 2
 * 5 0
 * 5 1
 * 5 2
 * 0 0
 * 3 3
 *
 *   0 1 2 3 4
 * 0     e
 * 1     X
 * 2 X X S X X
 * 3     X
 * 4     X
 * 9
 * 0 2
 * 1 2
 * 2 0
 * 2 1
 * 2 2
 * 2 3
 * 2 4
 * 3 2
 * 4 2
 * 2 2
 * 0 2
 */
class Location {
public:
    Location();

    void iterationBegin();
    Location iterationCurrent() const;
    void iterationAdvance();
    bool iterationDone() const;

    bool operator==(const Location &loc) const;

    friend ostream &operator<<(ostream &os, const Location &loc);
    friend istream &operator>>(istream &is, Location &loc);

    enum { RIGHT, DOWN, LEFT, UP, DONE };

protected:
    int row, col;
    unsigned int nextDirection;
};

#endif
