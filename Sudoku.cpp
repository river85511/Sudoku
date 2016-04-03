#include<iostream>
#include"Sudoku.h"
#include<iostream>
#include<cstdio>
#include<time.h>
#include<cstdlib>
#include<stdbool.h>

using namespace std;

Sudoku::Sudoku(){

	sol_check = 0;
	map_check = 0;

	for(int i=0; i<sudokuSize; ++i){
		map[i] = 0;
		ans[i] = 0;
		map_element[i] = 0;
	}

	for(int i=0; i<sudokuNum; i++){
		Box_count[i] = 0;
		Row_count[i] = 0;
		Col_count[i] = 0;
	}

	for(int i=0; i<sudokuNum; i++){
		for(int j=0; j<sudokuNum; j++){
			Box[i][j] = 0;
			Row[i][j] = 0;
			Col[i][j] = 0;

		}
	}

	for(int i=0; i<sudokuSize; i++){
		for(int j=0; j<sudokuNum; j++){
			map_Mark_up[i][j] = 0;
		}
	}
	
}

Sudoku::Sudoku(int read[]){
	
	for(int i=0; i<sudokuSize; ++i){
		map[i] = read[i];
	}	

}


void Sudoku::giveQuestion(){

//Original Question
	int map_tmp[sudokuSize]={1,2,3,4,5,6,7,8,9,4,5,6,7,8,9,1,2,3,7,8,9,1,2,3,4,5,6,2,3,4,5,6,7,8,9,1,5,6,7,8,9,1,2,3,4,8,9,1,2,3,4,5,6,7,3,4,5,6,7,8,9,1,2,6,7,8,9,1,2,3,4,5,9,1,2,3,4,5,6,7,8};

	for(int i=0; i<9; ++i){
		for(int j=0; j<9; ++j){
			map[i*9+j] = map_tmp[i*9+j];
		}
	}

//Swapping

		srand(time(NULL));
		changeNum(rand()%sudokuNum+1,rand()%sudokuNum+1);
		changeRow(rand()%3,rand()%3);
		changeCol(rand()%3,rand()%3);
		rotate(rand()%101);
		flip(rand()%2);

//Create Blank

	int tag[sudokuSize] = {0};
	for(int i=0; i<9; ++i){
		for(int j=0; j<9; ++j){
			tag[i*9+j] = (i*9+j);
		}
	}
		
	srand(time(NULL));
	int ran = 0;

	for(int i=0; i<20; ++i){
		ran = rand() % 81;

		if(ran == tag[ran]){
			map[ran] = 0;			
			tag[ran] = 0;		
	
		}
	}

//Output Question

	printOut(false);

}

void Sudoku::readIn(){
	
	for(int i=0; i<sudokuSize; ++i){
		scanf("%1d",&map[i]);
	}

	Box_Save();
	Row_Save();
	Col_Save();
	Mark_up();
	//P_Mark_up();

	int check_arr[9] = {0};
	int x =0;
	for(int i =0;i <sudokuNum; i++){

	  //printf("Row %d : ",i);
		for(x =0; x<sudokuNum; x++){	//check Row
			if(map[i*sudokuNum+x] !=0 ){
			check_arr[map[i*sudokuNum+x]-1]++;
			//printf("%d->%d ",(map[i*sudokuNum+x]-1),check_arr[map[i*sudokuNum+x]-1]);			
			}
		}

		for(x =0; x<sudokuNum; x++){
			if(check_arr[x] >1){
				//printf("0\n");
				//exit(1);
				map_check = 1;
			}
		}	  	
	  Init(check_arr);
	  //printf("\n");

	}
	/*for(x =0; x<sudokuNum; x++){
		if(check_arr[x] >1){
			printf("0\n");
			exit(1);
		}
	}*/
	
	Init(check_arr);
	for(int j =0;j <sudokuNum; j++){

	  //printf("Col %d : ",j);
		for(x =0; x<sudokuNum; x++){
			if(map[x*sudokuNum+j] != 0){
				check_arr[map[x*sudokuNum+j]-1]++;
			//printf("%d->%d ",(map[x*sudokuNum+j]-1),check_arr[map[x*sudokuNum+j]-1]);
			}
		}

		for(x =0; x<sudokuNum; x++){
			if(check_arr[x] >1){
				//printf("0\n");
				//exit(1);
				map_check = 1;
			}
		}	
	
	  Init(check_arr);
	  //printf("\n");	

	}

	Init(check_arr);
}

void Sudoku::changeNum(int a, int b){

	for(int i =0; i<sudokuSize; i++)
	{
		if(map[i] == a){
			map[i] = b;
		}else if(map[i] == b ){
			map[i] = a;
		}
	}

}

void Sudoku::changeRow(int a, int b){

	int cRow_tmp[27] = {0};
	
	int x =0;
	int y =0;

	switch (a){
	  case 0: x =0; break;
	  case 1: x =3; break;
	  case 2: x =6; break;
	}
	switch (b){
	  case 0: y =0; break;
	  case 1: y =3; break;
	  case 2: y =6; break;
	}

	for(int i =0; i<3; i++)	//B->tmp
	{
		for(int j=0; j<9; j++)
		{		
		   cRow_tmp[i*9+j] = map[(y+i)*9+j];
		}
	}

	
	for(int i =0; i<3; i++) //A->B
	{
		for(int j=0; j<9; j++)
		{
			map[(y+i)*9+j] = map[(x+i)*9+j];
		}

	}

	for(int i =0; i<3; i++) //tmp->A
	{
		for(int j=0; j<9; j++)
		{
			map[(x+i)*9+j]=cRow_tmp[i*9+j];
		}
	}

}

void Sudoku::changeCol(int a, int b){
	
	int cCol_tmp[27] = {0};
	
	int x =0;
	int y =0;

	switch (a){
	  case 0: x =0; break;
	  case 1: x =3; break;
	  case 2: x =6; break;
	}
	switch (b){
	  case 0: y =0; break;
	  case 1: y =3; break;
	  case 2: y =6; break;
	}

	for(int i=0; i<9; i++) //B->tmp
	{
		for(int j =0; j<3; j++)
		{
			cCol_tmp[i*3+j] = map[i*9+(j+y)];
		}
	}

	for(int i=0; i<9; i++) //A->B
	{
		for(int j =0; j<3; j++)
		{
			map[i*9+(j+y)] = map[i*9+(j+x)];
		}
	}

	for(int i=0; i<9; i++) //tmp->A
	{
		for(int j =0; j<3; j++)
		{
			map[i*9+(j+x)] = cCol_tmp[i*3+j];
		}
	}
}

void Sudoku::rotate(int n){

	int x = 0;  x = (n%4);
	int rotate_tmp[sudokuSize] = {0};	
	
	while(x>0){

		for(int i =0; i<9; i++) //A->rotate->tmp
		{
			for(int j =0; j<9; j++)
			{
				rotate_tmp[j*9+(8-i)] = map[i*9+j];
			}	
		}

		for(int i=0; i<9; i++) //tmp->A
		{
			for(int j=0; j<9; j++)
			{
				map[i*9+j] = rotate_tmp[i*9+j];
			}
		}
	  x--;
	}	
}

void Sudoku::flip(int n){

	int flip_tmp[36] = {0};

	if(n == 0) //Flip Vertically
	{
		for(int i=0; i<4; i++) //B->tmp
		{
			for(int j=0; j<9; j++)
			{
				flip_tmp[i*9+j] = map[(i+5)*9+j];
			}
		}

		
		for(int i=0; i<4; i++) // A->B
		{
			for(int j =0; j<9; j++)
			{
				map[(i+5)*9+j] = map[(3-i)*9+j];
			}
		
		}

		for(int i=0; i<4; i++) //tmp->A
		{
			for(int j=0; j<9; j++)
			{
				map[(3-i)*9+j] = flip_tmp[i*9+j];
			}
		}

		
	}
	
	if(n == 1) //Flip Horizontally
	{
		for(int i =0; i<9; i++) //B->tmp
		{
			for(int j =5; j<9; j++)
			{
				flip_tmp[i*4+(j-5)] = map[i*9+j];
			}
		}

		for(int i =0; i<9; i++) //A->B
		{
			for(int j =0; j<4; j++)
			{
				map[i*9+(j+5)] = map[i*9+(3-j)];
			}
		}

		for(int i =0; i<9; i++)
		{
			for(int j =0; j<4; j++)
			{
				map[i*9+(3-j)] = flip_tmp[i*4+j];
			}
		}

	}

}

void Sudoku::transform(){
	readIn();
	change();
	printOut(false);
}

void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%sudokuNum+1, rand()%sudokuNum+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}

void Sudoku::printOut(bool isAns){
	int i;
	if(!isAns)
		for(i=0; i<sudokuSize; ++i)
			printf("%d%c",map[i],(i+1)%9==0?'\n':' ');
	else
		for(i=0; i<sudokuSize; ++i)
			printf("%d%c",ans[i],(i+1)%9==0?'\n':' ');
}

void Sudoku::Box_Save(){
	
	int i =0;
	int j =0;

	for(i=0; i<sudokuNum; i++){
		for(j=0; j<sudokuNum; j++){
			int Row = (i*sudokuNum+j)/sudokuNum;
			int Box_Row = Row/sudokuUnit;
			int Col = (i*sudokuNum+j)%sudokuNum;
			int Box_Col = Col/sudokuUnit;

			if(map[i*sudokuNum+j] != 0){
				
				if( (Box_Row == 0)&&(Box_Col == 0) ){ //Box_A
					
					Box[0][Box_count[0]] = map[(i*sudokuNum+j)];
					Box_count[0]++;					

				}else if( (Box_Row == 0)&&(Box_Col == 1) ){ //Box_B

					Box[1][Box_count[1]] = map[(i*sudokuNum+j)];
					Box_count[1]++;	

				}else if( (Box_Row == 0)&&(Box_Col == 2)){ //Box_C

					Box[2][Box_count[2]] = map[(i*sudokuNum+j)];
					Box_count[2]++;	

				}else if( (Box_Row == 1)&&(Box_Col == 0) ){ //Box_D

					Box[3][Box_count[3]] = map[(i*sudokuNum+j)];
					Box_count[3]++;	

				}else if( (Box_Row == 1)&&(Box_Col == 1) ){ //Box_E

					Box[4][Box_count[4]] = map[(i*sudokuNum+j)];
					Box_count[4]++;	

				}else if( (Box_Row == 1)&&(Box_Col == 2) ){ //Box_F

					Box[5][Box_count[5]] = map[(i*sudokuNum+j)];
					Box_count[5]++;	

				}else if( (Box_Row == 2)&&(Box_Col == 0) ){ //Box_G

					Box[6][Box_count[6]] = map[(i*sudokuNum+j)];
					Box_count[6]++;	

				}else if( (Box_Row == 2)&&(Box_Col == 1) ){ //Box_H

					Box[7][Box_count[7]] = map[(i*sudokuNum+j)];
					Box_count[7]++;	

				}else if( (Box_Row == 2)&&(Box_Col == 2) ){ //Box_I

					Box[8][Box_count[8]] = map[(i*sudokuNum+j)];
					Box_count[8]++;	

				}
			}
		}
	}

}

/*
void Sudoku::P_Box(){
	
	int i = 0;
	int j = 0;

		//"Display Box"
	for(i =0; i<sudokuNum; i++){ // Display Box_A~I
		
		switch (i){
			case 0:	printf("Box A:\t");	break;
			case 1:	printf("Box B:\t");	break;
			case 2:	printf("Box C:\t");	break;
			case 3:	printf("Box D:\t");	break;
			case 4:	printf("Box E:\t");	break;
			case 5:	printf("Box F:\t");	break;
			case 6:	printf("Box G:\t");	break;
			case 7:	printf("Box H:\t");	break;
			case 8:	printf("Box I:\t");	break;
	
 			default: break;
		}

		for(j =0; j<Box_count[i]; j++){
			printf("%d ",Box[i][j]);
		}
		
		printf("\n");
	}

}*/

void Sudoku::Row_Save(){

	int i =0;
	int j =0;	

	for(i=0; i<sudokuNum; i++){
		for(j=0; j<sudokuNum; j++){
			if(map[i*sudokuNum+j] != 0){
				Row[i][Row_count[i]] = map[i*sudokuNum+j];
				Row_count[i]++;
			}
		}
	}

}

void Sudoku::Col_Save(){

	int i =0;
	int j =0;

	for(i=0; i<sudokuNum; i++){
		for(j=0; j<sudokuNum; j++){
			if(map[i*sudokuNum+j] != 0){
				Col[j][Col_count[j]] = map[i*sudokuNum+j];
				Col_count[j]++;
			}
		}
	}


}

/*
void Sudoku::P_RC(){

	int i =0;
	int j =0;

	for(i=0; i<sudokuNum; i++){
	
		
	  printf("Row%d = ",i);

		for(j=0; j<Row_count[i]; j++){
			printf("%d ",Row[i][j]);
		}
	  printf("\n");
	

	  printf("Col%d = ",i);
		
		for(j=0; j<Col_count[i]; j++){
			printf("%d ",Col[i][j]);
		}
	  printf("\n");
	
	}

}
*/

void Sudoku::Mark_up(){

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	for(i=0; i<sudokuNum; i++){
		for(j=0; j<sudokuNum; j++){
			if(map[i*sudokuNum+j] == 0){
				
				int R = (i*sudokuNum+j)/sudokuNum;	int Box_R = R/sudokuUnit;
				int C = (i*sudokuNum+j)%sudokuNum;	int Box_C = C/sudokuUnit;
				int All[sudokuNum] = {1,2,3,4,5,6,7,8,9};
				
				///////////////////////////////			
				for(k=0; k<Row_count[R]; k++){	//Check Row
					for(l=0; l<sudokuNum; l++){
						if(Row[R][k] == All[l]){
							All[l] = 0;
						}
					}
				}

				for(k=0; k<Col_count[C]; k++){	//Check Col
					for(l=0; l<sudokuNum; l++){
						if(Col[C][k] == All[l]){
							All[l] = 0;
						}
					}
				}
				////
				if( (Box_R == 0)&&(Box_C == 0) ){ //Box_A
					for(k=0; k<Box_count[0]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[0][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 0)&&(Box_C == 1) ){ //Box_B
					for(k=0; k<Box_count[1]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[1][k] == All[l]){
								All[l] =0;
							}
						}
					}	
				}else if( (Box_R == 0)&&(Box_C == 2) ){ //Box_C
					for(k=0; k<Box_count[2]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[2][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 1)&&( Box_C == 0) ){ //Box_D
					for(k=0; k<Box_count[3]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[3][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 1)&&( Box_C == 1) ){ //Box_E
					for(k=0; k<Box_count[4]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[4][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 1)&&( Box_C == 2) ){ //Box_F
					for(k=0; k<Box_count[5]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[5][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 2)&&( Box_C == 0) ){ //Box_G
					for(k=0; k<Box_count[6]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[6][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 2)&&( Box_C == 1) ){ //Box_H
					for(k=0; k<Box_count[7]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[7][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}else if( (Box_R == 2)&&( Box_C == 2) ){ //Box_I
					for(k=0; k<Box_count[8]; k++){
						for(l=0; l<sudokuNum; l++){
							if(Box[8][k] == All[l]){
								All[l] =0;
							}
						}
					}
				}

				/////////////////////////////////////////
		

				for(k=0; k<sudokuNum; k++){
					if(All[k] != 0){
						map_Mark_up[i*sudokuNum+j][map_element[i*sudokuNum+j]] = All[k];
						map_element[i*sudokuNum+j]++;
					}
				}
				

			}
		}
	}

}


void Sudoku::P_Mark_up(){

	int i,j,k = 0;

	for(i=0; i<sudokuNum; i++){
		for(j=0; j<sudokuNum; j++){
		
			if(map_element[i*sudokuNum+j] != 0){
			    printf("map(%d,%d) = ",i,j);
				
				for(k=0; k<map_element[i*sudokuNum+j]; k++){
					printf("%d ",map_Mark_up[i*sudokuNum+j][k]);
				}		
			    printf("\n");
			}
		
		}
	}

}



void Sudoku::Init(int check_arr[]){
	int i = 0;

	for( i=0; i<sudokuNum; i++){
		check_arr[i] = 0;
	}
}

bool Sudoku::findBlank(int m[]){
	
	int i =0;
	for(i=0; i<sudokuSize; i++){
		if(m[i]==0){
			return true;
		}
	}

	return false;
}

bool Sudoku::checkUnity(int m[],int i, int j){

	int R = (i*sudokuNum+j)/sudokuNum;	int Box_R = R/sudokuUnit;
	int C = (i*sudokuNum+j)%sudokuNum;	int Box_C = C/sudokuUnit;
	int check_arr[sudokuNum] = {0};
	
	int x = 0;
	int y = 0;

	for(x =0; x<sudokuNum; x++){	//check Row
		if(m[i*sudokuNum+x] !=0 ){
			check_arr[m[i*sudokuNum+x]-1]++;
		}
	}
	
	for(x =0; x<sudokuNum; x++){
		if(check_arr[x] >1){
			return false;
		}
	}
	
	Init(check_arr);

	for(x =0; x<sudokuNum; x++){
		if(m[x*sudokuNum+j] != 0){
			check_arr[m[x*sudokuNum+j]-1]++;
		}
	}

	for(x =0; x<sudokuNum; x++){
		if(check_arr[x] >1){
			return false;
		}
	}

	Init(check_arr);

	for(x=0; x<sudokuNum; x++){
		for(y=0; y<sudokuNum; y++){
			int R_tmp = (x*sudokuNum+y)/sudokuNum; int Box_R_tmp = R_tmp/sudokuUnit;
			int C_tmp = (x*sudokuNum+y)%sudokuNum; int Box_C_tmp = C_tmp/sudokuUnit;
			
			if( (Box_R_tmp == Box_R)&&(Box_C_tmp == Box_C) ){
				if(m[x*sudokuNum+y] != 0){
					check_arr[m[x*sudokuNum+y]-1]++;
				}
			}
		}
	}


	for(x =0; x<sudokuNum; x++){
			
		//printf("%d ",check_arr[x]);
	
		if(check_arr[x] >1){
			return false;
		}
	}

	

   return true;

}

bool Sudoku::sol(){

	int i =0;
	int j =0;
	int k =0;
	int t = 0;
	

	if(!findBlank(map)){	//if no more blanks can be found, it means that the solution is found.
		
		//printf("!!!!!!!!!!!!!!!Find!!!!!!!!!!!!!!!!!!!!!!\n");
		/*for(int i= 0; i<9; i++){
			for(int j =0; j<9; j++){			
				printf("%d ",map[i*9+j]);
			}	
			printf("\n");	
		}*/
		sol_check++;//find one solution
		if(sol_check == 1){
			for(i=0; i<81; i++){
				ans[i] = map[i];
			}
		}

		if( sol_check<2){	//go for another solution
		return false;
		}

		
	}else{
			
		for(i=0;i<sudokuNum;i++){	
			for(j=0; j<sudokuNum;j++){
				if(map[i*sudokuNum+j]==0){	//Search till the blank one is found;
					for(k=0; k<map_element[i*sudokuNum+j];k++){	//start trying with Mark_up
						map[i*sudokuNum+j] = map_Mark_up[i*sudokuNum+j][k];
						//printf("(%d,%d) = %d\n",i,j,map[i*sudokuNum+j]);
						if(checkUnity(map,i,j)){
							//printf("Pass Check!\n");
							if(sol()){
								return true;
							}else{
								map[i*sudokuNum+j] = 0;
							}
						}else{
							//printf("didn't Pass!\n");
							map[i*sudokuNum+j] = 0;
							//return false;
						}
					}
					return false;
				}
			}					
		}
	}

}

int Sudoku::getSol(){
		return sol_check;	
}

void Sudoku::solve(){
	
	if(map_check == 0){
	sol();
	}

	
	int i =0; int j=0;

	if(getSol() == 0){
		printf("0\n");
	}else if(getSol() == 1){
		printf("1\n");
		for(i=0; i<9;i++){
			for(j=0;j<9;j++){
				printf("%d ",ans[i*9+j]);
			}
		  printf("\n");
		}
	}else if(getSol() > 1){
		printf("2\n");
	}
}


