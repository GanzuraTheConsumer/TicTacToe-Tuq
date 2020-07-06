#include "textdisplay.h"

TextDisplay::TextDisplay(size_t n): theDisplay{std::vector<std::vector<char>> (n, std::vector<char> (n, '-'))}, gridSize{n} {}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
  
  char newColour = '-';
  if(whoNotified.getInfo().colour == Colour::White) {
    newColour = 'O';
  } else if(whoNotified.getInfo().colour == Colour::Black) {
    newColour = 'X';
  }

  theDisplay.at(whoNotified.getInfo().row).at(whoNotified.getInfo().col) = newColour;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for(auto sub: td.theDisplay) {
    for(char c: sub) {
      out << c;
    }
    out << std::endl;
  }
  return out;
}
