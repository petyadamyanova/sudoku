#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

void print(int arr[9][9]){
     for (int i = 0; i < 9; i++){
         for(int j = 0; j < 9; j++)
            cout << arr[i][j];
         cout << endl;
    }
}

bool valid_row(int sudoku[9][9], int row, int num){
    for(int i=0;i<9;i++){
        if(sudoku[row][i] == num){
            return false;
        }
    }

    return true;
}

bool valid_col(int sudoku[9][9], int col, int num){
    for(int i=0;i<9;i++){
        if(sudoku[i][col] == num){
            return false;
        }
    }

    return true;
}

bool valid_square(int sudoku[9][9], int row, int col, int num){
    for(int i=0;i<3;i++){
        for(int j = 0; j < 3;j++){
            if(sudoku[i + (row - row % 3)][j + (col - col % 3)] == num){
                return false;
            }
        }
    }

    return true;
}


bool valid_num(int sudoku[9][9], int row, int col, int num){
    if(valid_row(sudoku, row, num) == false)
        return false;

    if(valid_col(sudoku, col, num) == false)
        return false;


    if(valid_square(sudoku, row, col, num) == false)
        return false;

    return true;
}

bool sudokusolver(int sudoku[9][9], int row, int col){

    if(row == 9 && col == 8){
        return true;
    }

    if(row == 9){
        row = 0;
        col = col + 1;
    }


    if(sudoku[row][col] != 0){
       return sudokusolver(sudoku, row + 1, col);
    }


    for(int i=1;i<10;i++){
        if(valid_num(sudoku, row, col, i) == true){
            sudoku[row][col] = i;

            if(sudokusolver(sudoku, row + 1, col) == true){
                return true;
            }
        }


        sudoku[row][col] = 0;
    }

    return false;

}

void fill(int sudoku[9][9], int row, string line){
    int current_col = 0;
    for(int i=0;i<11;i++){
        if(line.at(i) == '.'){
            sudoku[row][current_col] = 0;
            current_col++;
        }else if(line.at(i) == '|'){
            continue;
        }else{
            sudoku[row][current_col] = line.at(i) - '0';
            current_col++;
        }
    }
}

string row_string(int sudoku[9][9], int row){
    string line;
    int current_col=0;
    for(int i=0;i<11;i++){
        if(i == 3 || i == 7){
            line = line.append("|");
        }else{
            string str;
            stringstream ss;
            ss << sudoku[row][current_col];
            ss >> str;
            current_col++;

            line = line.append(str);
        }
    }

    return line;
}


int main()
{
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    int sudoku[9][9];
    ifstream file(filename.c_str());
    ofstream loggerFile("solutions.txt", ios_base::app);

    while(!file){
        cout << "This file does not exist! Enter new filename: ";
        cin >> filename;
        ifstream file(filename.c_str());

        if(file.is_open()){
            break;
        }
    }

    string line;
    getline(file, line);

    int count = atoi(line.c_str());
    loggerFile << line;

    int current_row = 0;
    for(int i=0;i<count;i++){
        for(int j=0;j<11;j++){
            getline(file, line);
            if(j != 3 && j != 7){
                fill(sudoku, current_row, line);
                current_row++;
            }
        }


        current_row = 0;

        if(sudokusolver(sudoku, 0, 0) == true){
            loggerFile << endl;
            for(int j=0;j<11;j++){
                if(j == 3 || j == 7){
                    loggerFile << "-----------" << endl;
                }else{
                    loggerFile << row_string(sudoku, current_row) << endl;
                    current_row++;

                }
            }

            current_row = 0;
        }

        getline(file, line);

    }

    return 0;
}
