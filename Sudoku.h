#include<iostream>
#include<stdbool.h>
using namespace std;

class Sudoku{

	public:
	
	Sudoku();
	Sudoku(int read[]);
	
	void giveQuestion();
	void readIn();
	//void solve();
	void changeNum(int a, int b);
	void changeRow(int a, int b);
	void changeCol(int a, int b);
	void rotate(int n);
	void flip(int n);
	void transform();
	void change();
	void printOut(bool isAns);

	void Box_Save();
	//void P_Box();
	void Row_Save();
	void Col_Save();
	//void P_RC();
	void Mark_up();
	void P_Mark_up();
	void Init(int check_arr[]);
	bool findBlank(int m[]);
	bool checkUnity(int m[],int i, int j);
	void solve();	
	bool sol();


	int getSol();

	static const int sudokuSize = 81;
	static const int sudokuNum = 9;
	static const int sudokuUnit = 3;

	private:	
	int map[sudokuSize];
	int ans[sudokuSize];
	int Box_count[sudokuNum];
	int Box[sudokuNum][sudokuNum];
	int Row_count[sudokuNum];
	int Row[sudokuNum][sudokuNum];
	int Col_count[sudokuNum];
	int Col[sudokuNum][sudokuNum];
	
	int map_Mark_up[sudokuSize][sudokuNum];
	int map_element[sudokuSize];
	int sol_check;
	int map_check;
};
