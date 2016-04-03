all: Sudoku.o giveQuestion.cpp solve.cpp transform.cpp
	g++ -o giveQuestion giveQuestion.cpp Sudoku.o -std=c++11
	g++ -o solve solve.cpp Sudoku.o -std=c++11
	g++ -o transform transform.cpp Sudoku.o -std=c++11

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp -o Sudoku.o -std=c++11

