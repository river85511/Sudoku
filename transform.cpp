#include"Sudoku.h"

int main(){
	Sudoku ss;
	ss.readIn();
	//ss.transform();
	ss.rotate(1);
	ss.printOut(false);

	return 0;
}
