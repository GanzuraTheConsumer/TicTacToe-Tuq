#include "grid.h"

Grid::~Grid() {
  delete td;
}

void Grid::setObserver(Observer<Info, State> *ob) {
  this->ob = ob;
}

bool Grid::isFull() const {
  return (numSpaces == 0);
}

void Grid::init(size_t n) {  
  delete td;
  td = new TextDisplay(n);
  // set number of blank spaces to be 9
  numSpaces = 9;
  size = n;

  // clear anything already there
  size_t iterateTo = theGrid.size();
  for(size_t i = 0; i < iterateTo; ++i) {
    theGrid.pop_back();
  }

  for(size_t i = 0; i < n; ++i) {
    std::vector<Cell> column;
    theGrid.push_back(column);
  }

  for(size_t i = 0; i < n; ++i) {
    for(size_t j = 0; j < n; ++j) {
      theGrid.at(i).push_back(Cell(i, j));
      theGrid.at(i).back().attach(td);
    }
  }

  // links all adjacent cells together
  for(size_t r = 0; r < n; ++r) {
    for(size_t c = 0; c < n; ++c) {
      
			if (r > 0) { // North block
				theGrid.at(r).at(c).attach(&theGrid.at(r - 1).at(c)); // sets cell to observe the one N of it
				if (c > 0) {
					theGrid.at(r).at(c).attach(&theGrid.at(r - 1).at(c - 1)); // sets cell to observe the one NW of it
				}
				if (c < n - 1) {
					theGrid.at(r).at(c).attach(&theGrid.at(r - 1).at(c + 1)); // sets cell to observe the one NE of it
				}
			}
      
			if (r < n - 1) { // South block
				theGrid.at(r).at(c).attach(&theGrid.at(r + 1).at(c)); // sets cell to observe the one S of it
				if (c > 0) {
					theGrid.at(r).at(c).attach(&theGrid.at(r + 1).at(c - 1)); // sets cell to observe the one SW of it
				}
				if (c < n - 1) {
					theGrid.at(r).at(c).attach(&theGrid.at(r + 1).at(c + 1)); // sets cell to observe the one SE of it
				}
			}

			if (c > 0) { // East/West block
				theGrid.at(r).at(c).attach(&theGrid.at(r).at(c - 1)); // sets cell to observe the one W of it
			}
			if (c < n - 1) {
				theGrid.at(r).at(c).attach(&theGrid.at(r).at(c + 1)); // sets cell to observe the one E of it
			}
    }
  }
}

bool Grid::setPiece(size_t r, size_t c, Colour colour) {
  if(td == nullptr) {
    throw InvalidMove{};
  }
  if((r < 0) || (c < 0) || (r > size) || (c > size)) {
    throw InvalidMove{};
  }
  Cell &target = theGrid.at(r).at(c);

  if(target.getInfo().colour != Colour::NoColour) {
    throw InvalidMove{};
  }
  
  bool ans = target.setPiece(colour);
  --numSpaces;

	return ans;
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
  out << *g.td;
  return out;
}
