#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
class Cell;
template <typename InfoType, typename StateType> class Subject {public: virtual InfoType getInfo() const = 0;};

class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay; // note: row is the outer vector
  const size_t gridSize;
 public:
  TextDisplay(size_t n);

  void notify(Subject<Info, State> &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
