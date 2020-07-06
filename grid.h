#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "state.h"
#include "info.h"

class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay; // note: row is the outer vector
  const size_t gridSize;
 public: TextDisplay(size_t n); void notify(Subject<Info, State> &whoNotified) override;
};
std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  TextDisplay *td = nullptr; // The text display.
  Observer<Info, State> *ob = nullptr;
  size_t numSpaces; // number of blank spaces
  size_t size;

 public:
  ~Grid();
  
  void setObserver(Observer<Info, State> *ob);
  bool isFull() const;  // Is the game over, i.e., is the grid full?
  void init(size_t n); // Sets up an n x n grid.  Clears old grid, if necessary.
  bool setPiece(size_t r, size_t c, Colour colour);  // Plays piece at row r, col c. Returns true on victory.

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
