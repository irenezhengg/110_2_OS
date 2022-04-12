/*
Team members:
資工三 方文昊 108590048
資工三 鄭琳玲 108590056
資工三 黃聖耀 108590061
電資三 李以謙 108820021
*/

#include <string>
#include <thread>
#include <vector>
#include <mutex>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

//Sudoku input examples

int sudokuValids[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 1, 8, 3, 6, 7, 4, 2},
	{8, 6, 4, 7, 2, 1, 9, 5, 3},
	{6, 9, 8, 4, 7, 3, 2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 5, 3, 6, 4, 1, 8, 9},
	{1, 3, 6, 2, 9, 8, 5, 7, 4}
};

int colInvalid[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 1, 8, 3, 6, 7, 4, 2},
	{8, 6, 4, 7, 2, 1, 9, 5, 3},
	{6, 9, 8, 4, 7, 3, 2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 8, 3, 6, 4, 1, 8, 9},
	{1, 3, 6, 2, 9, 8, 5, 7, 4}
};

int rowInvalid[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 1, 8, 3, 6, 7, 4, 2},
	{8, 6, 4, 7, 2, 1, 9, 7, 3},
	{6, 9, 8, 4, 7, 3, 2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 5, 3, 6, 4, 1, 8, 9},
	{1, 3, 6, 2, 9, 8, 5, 7, 4}
};

int gridInvalid[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 1, 8, 3, 6, 7, 4, 2},
	{8, 6, 4, 7, 2, 1, 9, 5, 3},
	{6, 9, 8, 4, 7, 3, 2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 5, 3, 6, 4, 1, 8, 9},
	{1, 3, 7, 2, 9, 8, 5, 7, 4}
};

int numbersNegative[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 1, 8, 3, 6, 7, 4, 2},
	{8, 6, 4, 7, 2, 1, 9, 5, 3},
	{6, 9, 8, 4, 7, 3, -2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 5, 3, 6, 4, 1, 8, 9},
	{1, 3, 6, 2, 9, 8, 5, 7, 4}
};

int zeroInside[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 0, 8, 3, 6, 7, 4, 2},
	{8, 6, 4, 7, 2, 1, 9, 5, 3},
	{6, 9, 8, 4, 7, 3, 2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 5, 3, 6, 4, 1, 8, 9},
	{1, 3, 6, 2, 9, 8, 5, 7, 4}
};

int exceededNumbers[9][9] = {
    	{7, 2, 3, 5, 4, 9, 8, 6, 1},
	{9, 5, 1, 8, 3, 6, 7, 4, 15},
	{8, 6, 4, 7, 2, 1, 9, 5, 3},
	{6, 9, 8, 4, 7, 3, 2, 1, 5},
	{5, 4, 7, 9, 1, 2, 6, 3, 8},
	{3, 1, 2, 6, 8, 5, 4, 9, 7},
	{4, 8, 9, 1, 5, 7, 3, 2, 6},
	{2, 7, 5, 3, 6, 4, 1, 8, 9},
	{1, 3, 6, 2, 9, 8, 5, 7, 4}
};



mutex theMutex;

bool validates = true;

void sudokuColCheck(int theBoard[9][9], int theColumn) {

    theMutex.lock();
    
    int nmbr;
    int nmbrsLt[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    for(int i = 0; i < 9; i++){
    
        nmbr = theBoard[i][theColumn];
        
        if(nmbr <= 0 || nmbr > 9){
            validates = false;
            break;
        }
        
        if(nmbrsLt[nmbr - 1] == -1) {nmbrsLt[nmbr - 1] = i;} 
        
        else {
            validates = false;
            break;
            
        }
    }
    
    theMutex.unlock();
}

void sudokuRowCheck(int theBoard[9][9], int theRow) {

    theMutex.lock();
    
    int nmbr;
    int nmbrsLt[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    for(int j = 0; j < 9; j++){
    
        nmbr = theBoard[theRow][j];
        
        if(nmbr <= 0 || nmbr > 9){
            validates = false;
            break;
        }
        
        if(nmbrsLt[nmbr - 1] == -1) {nmbrsLt[nmbr - 1] = j;}
        
        else{
            validates = false;
            break;
        }
    }
    
    theMutex.unlock();
    
}


void sudokuGridCheck(int theBoard[9][9], int theRow, int theColumn){

    theMutex.lock();
    
    int nmbr;
    int nmbrsLt[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    for(int i = 0; i < 3; i++){
    
        for(int j = 0; j < 3; j++){
        
            nmbr = theBoard[theRow + i][theColumn + j];
            
            if(nmbr <= 0 || nmbr > 9){
            
                validates = false;
                break;
            }
            
            if(nmbrsLt[nmbr - 1] == -1) {nmbrsLt[nmbr -1] = 10 * i + j;} 
            
            else {
            
            	int thenRow = theRow + nmbrsLt[nmbr - 1] / 10;
            	int thenCol = theColumn + nmbrsLt[nmbr - 1] % 10;
            	
            	validates = false;
            	break;
            }
        }
        
        if(validates == false) {break;}
    }
    
    theMutex.unlock();
    
}

void validatorSudoku(int theBoard[9][9]){

    validates = true;

    vector<thread> theThreads;
    
    for(int i = 0; i < 9; i++){
    
        for(int j = 0; j < 9; j ++){
        
            if(i % 3 == 0 && j % 3 == 0) {
            
                theThreads.push_back(thread(sudokuGridCheck, theBoard, i, j));
            }
            
            if(i == 0) {theThreads.push_back(thread(sudokuColCheck, theBoard, j));}
            if(j == 0) {theThreads.push_back(thread(sudokuRowCheck, theBoard, i));}
            
            if(validates == false) {break;}
        }
        
        if(validates == false) {break;}
    }
    
    for(int i = 0; i < theThreads.size(); i++) {theThreads[i].join();}
    
    if(validates == true) {cout << "Sudoku is valid.\n" << endl;} 
    
    else {cout << "Sudoku is invalid.\n" <<endl;}
    
}

int showSudokuBoard(int sudokuBoard[9][9]){
    
    string sep = " ";
    
    for(int i = 0; i<9; i++){
    
        sep = "";
        cout<<"{";
        
        for(int j = 0; j<9; j++){
        
        cout<< sep << sudokuBoard[i][j];
        sep = ", ";
        
    	}
    
    cout<<"}"<<endl;
    
    }
    return sudokuBoard[9][9];
}

int main() {

    cout << "Below are the examples of valid and invalid sudoku that are\nchecked or validated by the sudoku validator.\n"<< endl;
    
    cout << "Valid sudoku checking\n" << endl;
    showSudokuBoard(sudokuValids);
    cout << endl;
    validatorSudoku(sudokuValids);
    
    cout << "\nSeveral invalid sudoku conditions:\n" << endl;
    
    //column checking
    cout << "Column checking\n" << endl;
    showSudokuBoard(colInvalid);
    cout << "\nthere are same numbers in the column which are [3][2] and [7][2], therefore: ";
    validatorSudoku(colInvalid);
    
    //row checking
    cout << "Row checking\n" << endl;
    showSudokuBoard(rowInvalid);
    cout << "\n there are same numbers in the row which are [2][3] and [2][7], therefore: ";
    validatorSudoku(rowInvalid);
    
    //grid checking
    cout << "Grid checking\n" << endl;
    showSudokuBoard(gridInvalid);
    cout << "\nthere are same numbers in the grid which are [7][1] and [8][2], therefore: ";
    validatorSudoku(gridInvalid);
    
    cout << "Some others invalid sudoku conditions checking:\n" << endl;
    //if there exist number less than one such as zero or negative numbers
    cout << "Number less than one checking\n" << endl;
    showSudokuBoard(zeroInside);
    cout << "\nthere is a zero number in [1][2], therefore: ";
    validatorSudoku(zeroInside);
    
    cout << "Number less than one checking\n" << endl;
    showSudokuBoard(numbersNegative);
    cout << "\nthere is a negative number in [3][6], therefore: ";
    validatorSudoku(numbersNegative);
    
    //if there exist number more than nine
    cout << "Number more than nine checking\n" << endl;
    showSudokuBoard(exceededNumbers);
    cout << "\nthere is a number which is more than nine in [1][8]: ";
    validatorSudoku(exceededNumbers);
    
    return 0;
}
