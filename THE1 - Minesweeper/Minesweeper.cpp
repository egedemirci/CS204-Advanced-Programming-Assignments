#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include "strutils.h"
using namespace std;

/******************************************************************************
									CS204 THE1 - Minesweeper Game
									Author: Ege Demirci - 28287
									Date: 06/10/2021
									Any known bugs: -
******************************************************************************/


/*
	around_bomb_counter: This function takes the game board and row-col coordinates. It counts bombs around and returns counter.
	variables:
	row_first_idx = The start row index of a submatrix is row coordinate - 1.
	row_last_idx = The last row index of a submatrix is row coordinate + 1.
	col_first_idx = The start column index of a submatrix is column coordinate - 1.
	col_last_idx = The last column index of a submatrix is column coordinate + 1.
	row_size = It specifies the row size of the matrix.
	col_size = It specifies the row size of the matrix.

*/

int around_bomb_counter(vector<vector<string>> board, int row, int col){
	int bombcounter, row_first_idx = row - 1, row_last_idx = row + 1, col_first_idx = col-1, col_last_idx = col+1;
	int row_size = board.size(), col_size = board[0].size();
	if (row_first_idx < 0){ /*If the given coordinate is [0,cols], row_first_idx should be 0 instead of row - 1.*/
		row_first_idx = 0;
	}
	else if (row_last_idx > row_size - 1){ /*If the given coordinate is [row_size-1,cols], row_last_idx should be row_size - 1.*/
		row_last_idx = row_size - 1;
	}
	if (col_first_idx < 0){/* If the given coordinate is [rows,0]. col_first_idx should be 0 instead of col-1.*/
		col_first_idx = 0;
	}
	else if (col_last_idx > col_size-1){ /*If the given coordinate is [rows,col_size-1]. col_last_idx should be col_size - 1*/
		col_last_idx = col_size-1;
	}
	if (board[row][col] == "B"){ /*If the given coordinate is a bomb, the submatrix should skip it, so the counter starts from -1.*/
		bombcounter = -1;
	}
	else if (board[row][col] != "B"){/*If the given coordinate is not a bomb,the counter should start from 0.*/
		bombcounter = 0;
	}
	for (int i = row_first_idx; i <= row_last_idx; i++){ /*With for loop, bombcounter counts "B"  which indicates bombs in a submatrix.*/
		for (int k = col_first_idx ; k <= col_last_idx; k++){
			if (board[i][k] == "B"){
				bombcounter++;
			}
		}
	}
	return bombcounter;
}

/*
	printMatrix: This function takes the matrix and prints it.
*/
void printMatrix(vector<vector< string >> matrix){
	for (int i=0; i < matrix.size();i++){
		for (int k=0; k < matrix[i].size();k++){
			cout << matrix[i][k] << " ";
		}
		cout << endl;
	}
}


int main(){
	/*rows,cols and bombs are input for matrix, counter counts cells with a bomb, nobombcounter counts cells which is not a bomb.*/
	int rows,cols,bombs,counter=0,nobombcounter=0; 
	RandGen random;
	bool gameover = false; /*gameover for exit situation, default value is false.*/
	cout << "Give the dimensions of the matrix: ";
	cin >> rows >> cols;
	int cellsize = rows*cols; 
	cout << "How many bombs: ";
	cin >> bombs;
	while (bombs > (cellsize-1)){
		cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
		cin >> bombs;
		while (bombs < 1){
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> bombs;
		}
	}
	vector<vector< string >> gameboard(rows, vector<string>(cols, "X" )); /*gameboard matrix which is seen by the users.*/
	vector<vector< string >> actualboard(rows, vector<string>(cols, "0")); /*actualboard matrix for a background of the game.*/
	vector<vector< string >> bombsaround(rows, vector<string>(cols, "0")); /*bombsaround matrix for count the bombs around.*/

	/*This while loop place bombs in cells. The loop continues until the counter equals the number of bombs.*/
	while (counter != bombs){  
		int randomrow = random.RandInt(0,rows-1); 
		int randomcolumn = random.RandInt(0,cols-1);
		if (actualboard[randomrow][randomcolumn] != "B"){ /*If the given cell is already a bomb, it should find new random cells.*/
			actualboard[randomrow][randomcolumn] = "B";
			counter ++;
		}
	}
	/*This for loop fills the number of bombs around the cells into the bombsaround matrix, it uses around_bomb_counter matrix
	for this purpose.*/
	for (int i=0; i < actualboard.size();i++){
		for (int k=0; k< actualboard[i].size(); k++){
			int minecounter = around_bomb_counter(actualboard,i,k);
			bombsaround[i][k] = itoa(minecounter); /*Because minecounter is a integer, it should be converted to string with itoa function.*/
			if (actualboard[i][k] != "B"){
				actualboard[i][k] = itoa(minecounter); /*For background of the game and if it needed to display background structure in menu 2. */
			}
		}
	}
	cout<< "\n\n";
	for (int i=0; i < gameboard.size();i++){
		for (int k=0; k< gameboard[i].size(); k++){
			cout << gameboard[i][k] << " ";
		}
		cout << endl;
	}
	string menu; /*String menu input from the user.*/
 	int rowinp, colinp; /*Row and column inputs from the user.*/
	while (gameover == false){ /*Game continues until gameover became false. */
		cout << "\n\nPress:\n1. If you want to find out the surrounding of a cell\n2. If you want to open the cell\n3. If you want to exit." << endl;
		cin >> menu;
		while (menu != "1" && menu != "2" && menu != "3"){
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
			cin >> menu;
		}
		if (menu == "1"){
			cout << "Give the coordinates: ";
			cin >> rowinp >> colinp; /*rows-1 and cols-1 are the last possible indexes for matrix so if given coordinate is bigger, it is out of range.*/
			while (rowinp > rows-1 || colinp > cols-1){
				cout <<  "It is out of range. Please give a valid coordinates: ";
				cin >> rowinp >> colinp;
			}
			gameboard[rowinp][colinp] = bombsaround[rowinp][colinp]; /*The given coordinate will be updated on the game board according to the number of bombs around it.*/
			cout << endl << endl << "Displaying the surrounding of (" << rowinp << "," << colinp << "):" << endl;
			printMatrix(gameboard); /*The game board will be printed.*/
			gameboard[rowinp][colinp] = "X"; /*Option 1 not permanent so gameboard will be converted to default.*/
			cout << "Around (" << rowinp << "," << colinp << ") you have " << bombsaround[rowinp][colinp] << " bomb(s)" << endl; /*The number of bombs in the surrounding will be displayed with bombsaround matrix.*/

		}
		if (menu == "2"){
			cout << "Give the coordinates: ";
			cin >> rowinp >> colinp;
			while (rowinp > rows-1 || colinp > cols-1){
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> rowinp >> colinp;
			}
			cout << "\nOpening cell (" << rowinp <<"," << colinp << "):" << endl;
			gameboard[rowinp][colinp] = actualboard[rowinp][colinp];  /*The given coordinate will be updated on the game board according to the value of the background board.*/
			printMatrix(gameboard); 
			if (actualboard[rowinp][colinp] == "B"){ /*If value equals to B, user will lost and gameover will be updated as a true.*/
				cout << "\nUnfortunately, you stepped on a mine"<< endl;
				gameover = true;
				cout << "Arrangement of mines:" << endl;
				printMatrix(actualboard);
				cout << "\n>>>>> Game Over! <<<<<" << endl;
			}
			else{ /*If value is different than B, nobombcounter will be incremented by 1*/
				nobombcounter++; 
				if (nobombcounter == cellsize-bombs){ /*If nobombcounter equals to cells without bomb, user will win and gameover will be updated as a true. */
					cout << "Congratulations! All the non-mined cells opened successfully" << endl;
					cout << "You won!" << endl;
					cout << "\n>>>>> Game Over! <<<<<" << endl;
					gameover = true;
				}
			}
		}
		if (menu == "3"){ /*If user directly chooses 3, gameover will be updated as a true. */
			gameover = true;
			cout << "Program exiting..." << endl;
		}

	}
	return 0;
}
