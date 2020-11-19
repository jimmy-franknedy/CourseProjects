// Name:		 Jimmy Franknedy
// CruzID:    	 jfrankne
// Class: 		 CSE-015
// Date:		 10/19/2019
// Project Name: Queens.c
// Project Desc: A program will read an integer n from the command line, indicating the size of the Queens problem to solve. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define ERROR_STRING "Usage: Queens [-v] number\nOption: -v   verbose output, print all solutions\n"
#define VERBOOSE "-v"

// Function Prototypes
void placeQueen(int** B, int n, int i, int j);
void removeQueen(int** B, int n, int i, int j);
void printBoard(int** B, int n);
int findSolutions(int** B, int n, int i, char* mode);
void CUSTOM_viewBoard(int **B, int length);

// Row    = HORIZONTAL
// Column = VERTICAL 

// Function MAIN
int main(int argc, char* argv[]) 
{
	int input,verb,digit,check,board,boardLength = 0;
	char ch;
	char verbose[] = "-v";
	char *test = "";
	int **chessBoard;

	for (int i = 0; i <argc; i++)
	{
    	// Parse as an integer
		int status = sscanf(argv[i], "%d%c", &input, &ch);
		if(status)
		{
			int nValue = atoi(argv[i]);
			if( 1<= nValue && nValue <= 15) digit = 1;
			board = atoi(argv[i]);
			boardLength = board;
			chessBoard = calloc((boardLength+1)*(boardLength+1), sizeof(int*));
			for(int i = 0; i < boardLength+1;i++)
			{
				chessBoard[i] = calloc(boardLength+1,sizeof(int));
			}
		}
		// Check for verbose
		check = strcmp(verbose,argv[i]);
		if(!check) verb = 1;
	}

	if((argc == 2 && digit == 1))
	{
		int result = findSolutions(chessBoard, board, 1, test);
		printf("%d-Queens has %d solutions\n",board,result);
		free(chessBoard);
		chessBoard = NULL;
	}
	else if (argc == 3 && verb == 1 && digit == 1)
	{
		int result = findSolutions(chessBoard, board, 1, verbose);
		printf("%d-Queens has %d solutions\n",board,result);
		free(chessBoard);
		chessBoard = NULL;
	}
	else
	{
		printf(ERROR_STRING);
		free(chessBoard);
		chessBoard = NULL;
	}
	return 0;
}

// Function Definitions

void placeQueen(int** B, int n, int i, int j)
{
	// Create copies of the input values in order to modify them in the program
	int copy_i = i;
	int copy_j = j;

	// Incremet B[i][j] from 0 to 1
	B[i][j] = 1;

	// Set B[i][0] = j
	B[i][0] = j;

	// Set Queen attack downward
	for(copy_i = i+1; copy_i <= n; copy_i++)
	{
		B[copy_i][j] -= 1;
	}
	copy_i = i;

	// Set Queen attack right vertical downward
	while(copy_i != n && copy_j!= n)
	{
		copy_i++;
		copy_j++;
		B[copy_i][copy_j] -= 1;	
	}
	copy_i = i;
	copy_j = j;

	// Set Queen attack left vertical downward
	while(copy_j != n-(n-1) && copy_i != n)
	{
		copy_i++;
		copy_j--;
		B[copy_i][copy_j] -= 1;
	}
	copy_i = i;
	copy_j = j;
}

void removeQueen(int** B, int n, int i, int j)
{
	// Create copies of the input values in order to modify them in the program
	int copy_i = i;
	int copy_j = j;

	// Decrement B[i][j] from 1 to 0
	B[i][j] = 0;

	// Reset B[i][0] = 0;
	B[i][0] = 0;

	// Reset Queen attack downward
	for(copy_i = i+1; copy_i <= n; copy_i++)
	{
		B[copy_i][j] += 1;
	}
	copy_i = i;

	// Reset Queen attack right vertical downward
	while(copy_i != n && copy_j!= n)
	{
		copy_i++;
		copy_j++;
		B[copy_i][copy_j] += 1;
	}
	copy_i = i;
	copy_j = j;

	// Reset Queen attack left vertical downward
	while(copy_j != n-(n-1) && copy_i != n)
	{
		copy_i++;
		copy_j--;
		B[copy_i][copy_j] += 1;
	}
	copy_i = i;
	copy_j = j;
}

void printBoard(int** B, int n)
{
	printf("(");
	for(int i = 1; i <= n; i++)
	{
		if(i != n)
		{
			printf("%d, ", B[i][0]);
		}
		else
		{
			printf("%d",B[i][0]);
		}
	}
	printf(")\n");
}

void CUSTOM_viewBoard(int **B, int length)
{
	printf("     0  1  2  3  4  5  6  7  8\n");
	printf("    -- -- -- -- -- -- -- -- --\n");
	for(int i = 0; i < length; i++)
	{
		printf("%2d| ", i);
		for(int j = 0; j < length; j++) printf("%2d ", B[i][j]);
		printf("\n");
	}
}

int findSolutions(int** B, int n, int i, char* mode)
{
	int sum = 0;
	if(i>n)
	{
		char *checkVerbose = "-v";
		int check = strcmp(mode,checkVerbose);
		if(!check)
		{
			printBoard(B,n);
		}
		sum++;
	}
	else
	{
		for(int p = 1; p <= n; p++)
		{
			if(B[i][p] == 0)
			{
				placeQueen(B,n,i,p);
				sum += findSolutions(B,n,i+1,mode);
				removeQueen(B,n,i,p);
			}
		}
	}
	return sum;
}
