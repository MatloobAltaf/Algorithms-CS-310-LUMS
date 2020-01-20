
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
complexity O(n^2)
*/
int value = 0;
vector<pair<int, int>> results;
void print(int **gameBoard, int n)
{
	for(int i = 0; i< results.size(); i = i+3){
		cout<<gameBoard[results[i].first][results[i].second]<<" ("<<results[i].first<<","<<results[i].second<<") ("
		<<results[i+1].first<<","<<results[i+1].second<<") ("<<results[i+2].first<<","<<results[i+2].second<<")"<<endl;
	}
	// for(int i=0; i<n;i++)
	// {
	// 	for(int j=0 ;j<n;j++)
	// 	{
	// 		cout << gameBoard[i][j];
	// 		if(gameBoard[i][j]>9){
	// 			cout<< " ";
	// 		}
	// 		else{
	// 			cout<<"  ";
	// 		}
	// 	}
	// 	cout<<endl;
	// }
}

void initialisingBoard(int**&board, int n,int row, int col)
{
	board = new int*[n];
	for(int i=0; i<n;i++)
	{
		board[i] = new int[n];
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0; j<n ;j++)
		{
			if(i == row && j == col)
			{
				board[i][j] = -1;
			}
			else
			{
				board[i][j] = value;
			}
		}
	}
}
// Adds defective pieces in all the quadrants other than the one which already has it.
void insert(int **board, int row1, int col1, int row2, int col2, int row3, int col3)
{
	value++;
	board[row1][col1] = value;
	board[row2][col2] = value;
	board[row3][col3] = value;
	results.push_back(make_pair(row1, col1));
	results.push_back(make_pair(row2, col2));
	results.push_back(make_pair(row3, col3));
}
void filingBoard(int **gameBoard,int row, int col, int maxRow, int maxCol, int dr, int dc, int n)
{
	//base case
	if(maxRow == 2)
	{
		value++;
		for(int i=row; i < (row+maxRow); i++)
		{
			for(int j= col; j<(col+maxCol);j++)
			{
				if(gameBoard[i][j] == 0)
				{
					gameBoard[i][j] = value;
					results.push_back(make_pair(i, j));	
				}
			}
		}
		return;
	}

    //Finding defective piece in the 
    for(int i = row; i < (row+maxRow); i++){
        for(int j = col; j<(col+maxCol); j++){
            if(gameBoard[i][j] != 0){
                dr = i;
                dc = j;
            }
        }
    }

    //if the fault is in first quadrant
    if(dr < (row+maxRow/2) && dc >= (col+maxCol/2)){
        insert(gameBoard, row+(maxRow/2)-1, col+(maxCol/2)-1, row+(maxRow/2),col+(maxCol/2)-1, row+(maxRow/2), col+(maxCol/2));
    }
    //if the faoult is in second quadrant
    else if(dr < (row+maxRow/2) && dc < (col+maxCol/2)){
        insert(gameBoard, row+(maxRow/2)-1, col+(maxCol/2), row+(maxRow/2),col+(maxCol/2), row+(maxRow/2), col-1+(maxCol/2));
    }
    //if the fault is in third quadrant
    else if(dr >= (row+maxRow/2) && dc < (col+maxCol/2)){
        insert(gameBoard, row+(maxRow/2)-1, col+(maxCol/2)-1, row+(maxRow/2),col+(maxCol/2), row+(maxRow/2)-1, col+(maxCol/2));
    }
    //if the fault is in fourth quadrant
    else if(dr >= (row+maxRow/2) && dc >= (col+maxCol/2)){
        insert(gameBoard, row+(maxRow/2)-1, col+(maxCol/2)-1, row+(maxRow/2)-1,col+(maxCol/2), row+(maxRow/2), col-1+(maxCol/2));
    }
	//recursive calls

	//to first quadrant
    filingBoard(gameBoard, row, col+(maxCol/2), (maxRow/2), (maxCol/2), dr, dc, n);
    //to second quadrant
	filingBoard(gameBoard, row, col, (maxRow/2), (maxCol/2), dr, dc, n);
    //to third quadrant
	filingBoard(gameBoard, row+(maxRow/2), col, (maxRow/2), (maxCol/2), dr, dc, n);
    //to fourth quadrant
	filingBoard(gameBoard, row+(maxRow/2), col+(maxCol/2), (maxRow/2), (maxCol/2), dr, dc, n);
}

int main(int argc, char** argv)
{
    if(argc < 2){
		exit(1);
	}
	ifstream inFile;
	// argv[1] = "test13.txt";
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(1);
	}
	string line = "";
	int n,row,col;
	int **board;

	getline(inFile, line);
	n = stoi(line.substr(2, line.find('\0')));
	getline(inFile, line);
	row = stoi(line.substr(1, line.find(',')));
	col = stoi(line.substr(line.find(',')+1, line.find('\0')));

	
	initialisingBoard(board,n,row,col);
	filingBoard(board,0, 0, n, n, row, col, n);
	print(board, n);


}
