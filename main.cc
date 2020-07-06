#include <iostream>
#include <string>
#include "grid.h"
#include "state.h"
using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  bool isXTurn = 1;
	int winner = 0; // 0 is tie, 1 is X, 2 is O
	string victoryMsg = "";

	cout << "Enter \"new\" to start a game or reset the board" << endl;
	cout << "Enter \"play c r\" to put a new piece at colum c, row r" << endl;
	cout << "X plays first, indexing start at 0" << endl;

  try {
		while (true) {
			cin >> cmd;
			if (cmd == "new") {
				try {
					g.init(3);
					cout << g;
					isXTurn = 1; // reset the turn
				}
				catch (InvalidMove &) {}
			}
			else if (cmd == "play") {
				try {
					int r = 0, c = 0;
					cin >> r >> c;

					if (g.setPiece(r, c, isXTurn ? Colour::Black : Colour::White)) {
						if (isXTurn) {
							winner = 1;
							victoryMsg = "X ";
						} else {
							winner = 2;
							victoryMsg = "O ";
						}
					}
					cout << g;

					//checks for victory
					if (g.isFull() || winner) {
						break;
					}

					isXTurn = !isXTurn;
				}
				catch (InvalidMove &) {}
			}
		}

    // prints win message
		if (winner) {
			victoryMsg += "wins!";
		} else {
			victoryMsg = "Tie!";
		}
		cout << victoryMsg << endl;
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
