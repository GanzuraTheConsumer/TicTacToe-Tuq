#include "cell.h"
#include <iostream>

// inverts direction, e.g. N |-> S
Direction reverseDir(Direction d) {
  if(d == Direction::N) {
    return Direction::S;
  } else if(d == Direction::NE) {
    return Direction::SW;
  } else if(d == Direction::E) {
    return Direction::W;
  } else if(d == Direction::SE) {
    return Direction::NW;
  } else if(d == Direction::S) {
    return Direction::N;
  } else if(d == Direction::SW) {
    return Direction::NE;
  } else if(d == Direction::W) {
    return Direction::E;
  } else if(d == Direction::NW) {
    return Direction::SE;
  }
  else return Direction::N; // note: should never be called
}


Cell::Cell(size_t r, size_t c): r{r}, c{c}, colour{Colour::NoColour} {}

bool Cell::setPiece(Colour colour) {
  this->colour = colour;
  // note: direction is a dummy value
  setState(State{StateType::NewPiece, colour, Direction::N});
  notifyObservers();

	// if victory
	return this->getState().type == StateType::Reply;
}

void Cell::notify(Subject<Info, State> &whoFrom) {
  if(colour == Colour::NoColour) {
    return;
  }
  State newState;
  newState.colour = whoFrom.getState().colour;
  
  // decides where the update is coming from
  if(whoFrom.getInfo().row == r) { // same row
    if(whoFrom.getInfo().col > c) {
      newState.direction = Direction::E;
    } else if(whoFrom.getInfo().col < c) {
      newState.direction = Direction::W;
    }
    
  } else if(whoFrom.getInfo().row > r) { // row above
    if(whoFrom.getInfo().col > c) {
      newState.direction = Direction::SE;
    } else if(whoFrom.getInfo().col < c) {
      newState.direction = Direction::SW;
    } else if(whoFrom.getInfo().col == c) {
      newState.direction = Direction::S;
    }
    
  } else if(whoFrom.getInfo().row < r) { // row below
    if(whoFrom.getInfo().col > c) {
      newState.direction = Direction::NE;
    } else if(whoFrom.getInfo().col < c) {
      newState.direction = Direction::NW;
    } else if(whoFrom.getInfo().col == c) {
      newState.direction = Direction::N;
    }
  }

  // decides what kind of message to pass on
  if(whoFrom.getState().type == StateType::NewPiece) {
    // if you're not the same colour, ignore
    if(colour != whoFrom.getInfo().colour) {
      return;
    }
    // if it's new, relay the message
    newState.type = StateType::Relay;
    setState(newState);
    notifyObservers();
    return;
    
  }
  else if(whoFrom.getState().type == StateType::Relay) {
    // if it's a relay going in the right direction...
    if(whoFrom.getState().direction != newState.direction) {
      return;
    }
    // if I'm the same colour as the reply, that makes 3 in a row
    if(colour == whoFrom.getState().colour) {
      // first, swap the direction
      newState.direction = reverseDir(newState.direction);
      // then reply a victory
      newState.type = StateType::Reply;
      setState(newState);
      notifyObservers();
      return;
    }    
  }
  else if(whoFrom.getState().type == StateType::Reply) {
    // if it's a relay going in the right direction...
    if(whoFrom.getState().direction != newState.direction) {
      return;
    }
    // if I'm not the same colour, stop
    if(colour != whoFrom.getState().colour) {
      return;
    }
    // else, set state to victory
    setState(whoFrom.getState());
    notifyObservers();
    return;
  }
}

Info Cell::getInfo() const {
  return Info{r, c, colour};
}
