CXX=g++ # compiler command
CXXFLAGS=-std=c++14 -Wall -Werror -g -Werror=vla # compiler options
EXEC=TicTacToe # name of resultant file
OBJECTS=main.o cell.o grid.o textdisplay.o # object files

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o: main.cc grid.h state.h
cell.o: cell.cc cell.h state.h subject.h observer.h info.h
grid.o: grid.cc textdisplay.cc grid.h cell.h state.h info.h
textdisplay.o:textdisplay.cc textdisplay.h observer.h state.h info.h

clean:
	rm ${OBJECTS} ${EXEC}

.PHONY: clean
