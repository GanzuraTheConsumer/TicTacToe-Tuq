#ifndef STATE_H
#define STATE_H

/* State types are:
    NewPiece -- I am a new piece. I was just placed on the board. I'm letting
                you know that I exist, in case you are the same as me.

    Relay -- I have a neighbour who is a new piece of my colour, and is a straight line away from me.
             I'm letting you know that that neighbour exists, and in which
             direction it is, in case you are the same as well.

    Reply -- I am part of a chain of 3 of the same type, signifying victory
*/
enum class StateType { NewPiece, Relay, Reply };
enum class Colour { NoColour, Black, White };
enum class Direction { NW, N, NE, W, E, SW, S, SE };

struct State {
  StateType type;  // See above
  Colour colour;   // What colour was the new piece?  (NOT what is my colour)
  Direction direction;  // In which direction from me is the new piece?
};

#endif
