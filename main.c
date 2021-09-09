/// Yaniv Avrahami 302374921

/*
This program is a game called connect 4. 
Is a two-player game in which the players take turns
dropping one sign into one of the columns.
The first to line 4 signs of his kind wins the game.
A tie can happen when the board is full and no one won.
*/

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define ROWS 6 //6
#define COLS 7 //7

char board[ROWS][COLS];

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function gets a row number and a sign. 
/// then places the sign at the lowest available 
/// space within the column.
void placeTop(int col, char sign);

/// This function gets a column and returns 
/// the highest row in the column which has a sign.
int getTop(int col);

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function prints the board.
void printBoard();

/// This function clears the screen.
void clearScreen();

/// This function gets a row number, a column number
/// and a sign. The function returns true if there is 4 
/// same chars vertically.
bool checkVertically(int row, int col, char sign);

/// This function gets a row number, a column number
/// and a sign. The function returns true if there is 4 
/// same chars horizontally.
bool checkHorizontally(int row, int col, char sign);

/// This function gets a row number, a column number
/// and a sign. The function returns true if there is 4 
/// same chars diagonally up.
bool checkDiagonallyUp(int row, int col, char sign);

/// This function gets a row number, a column number
/// and a sign. The function returns true if there is 4 
/// same chars diagonally down.
bool checkDiagonallyDown(int row, int col, char sign);

/// This function gets a row number, a column number
/// a sign char and an address for winner number. 
/// This function returns the winner number if a line 
/// of 4 has been made.
void checkFour(int row, int col, char sign, int* winner);

/// This function gets a player number, a sign char 
/// and an address of winner number. This function asks 
/// for a column from the player and places the sign 
/// in the chosen column. And declares a winner or a tie.
void processInput(int player, char sign, int* winner);

int main()
{
	int player = 1;
	char sign = 'X';
	int winner = 0;

	initBoard();
	printBoard();

	while (winner == 0 || winner == 3)
	{
		processInput(player, sign, &winner);
		clearScreen();
		printBoard();

		if (winner == 1 || winner == 2)
		{
			printf("Player number %d won! :)\n", player);
		}
		else if (winner == 3)
		{
			printf("There is a tie!\n");

			system("pause");

			winner = 0;
			clearScreen();
			initBoard();
			printBoard();
		}

		if (winner == 1 || winner == 2)
			break;

		//swaps current player
		if (player == 1)
		{
			player = 2;
			sign = 'O';
		}
		else
		{
			player = 1;
			sign = 'X';
		}

	}

	system("pause");

}

char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void placeTop(int col, char sign) {
	int i;

	for (i = 1; i <= ROWS; i++)
	{
		if (i == ROWS && getCell(i, col) == ' ')
		{
			setCell(i, col, sign);
			break;
		}
		else if (getCell(i, col) != ' ')
		{
			setCell(i - 1, col, sign);
			break;
		}
	}
}

int getTop(int col)
{
	int i;
	for (i = 1; i <= ROWS; i++)
	{
		if (getCell(i, col) != ' ')
			return i;
	}
}

void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void printBoard()
{
	int i, j;

	printf("  ");

	for (i = 1; i <= COLS; i++)
	{
		printf("%d ", i);
	}

	printf("\n");

	for (i = 1; i <= ROWS; i++)
	{
		printf("%c ", i + 'A' - 1);
		for (j = 1; j <= COLS; j++)
			printf("%c ", getCell(i, j));
		printf("\n");
	}
}

void clearScreen() {
	system("cls");
}

bool checkVertically(int row, int col, char sign) {
	int count = 1, initial_row = row;

	//count upwards
	row = row - 1;

	while (row >= 1 && sign == getCell(row, col)) {
		count = count + 1;
		row = row - 1;
	}

	row = initial_row;

	//count downwards
	row = row + 1;

	while (row <= ROWS && sign == getCell(row, col)) {
		count = count + 1;
		row = row + 1;
	}

	if (count >= 4)
		return true;
	else
		return false;
}

bool checkHorizontally(int row, int col, char sign) {
	int count = 1, initial_col = col;

	//count right
	col = col + 1;

	while (col <= COLS && sign == getCell(row, col)) {
		count = count + 1;
		col = col + 1;
	}

	col = initial_col;

	//count left
	col = col - 1;

	while (col >= 1 && sign == getCell(row, col)) {
		count = count + 1;
		col = col - 1;
	}

	if (count >= 4)
		return true;
	else
		return false;
}

bool checkDiagonallyUp(int row, int col, char sign) {
	int count = 1, initial_col = col, initial_row = row;

	//count right up
	col = col + 1;
	row = row - 1;

	while (col <= COLS && row >= 1 && sign == getCell(row, col)) {
		count = count + 1;
		col = col + 1;
		row = row - 1;
	}

	col = initial_col;
	row = initial_row;

	//count left down
	col = col - 1;
	row = row + 1;

	while (col >= 1 && row <= ROWS && sign == getCell(row, col)) {
		count = count + 1;
		col = col - 1;
		row = row + 1;
	}

	if (count >= 4)
		return true;
	else
		return false;
}

bool checkDiagonallyDown(int row, int col, char sign) {
	int count = 1, initial_col = col, initial_row = row;

	//count right down
	col = col + 1;
	row = row + 1;

	while (col <= COLS && row <= ROWS && sign == getCell(row, col)) {
		count = count + 1;
		col = col + 1;
		row = row + 1;
	}

	col = initial_col;
	row = initial_row;

	//count left up
	col = col - 1;
	row = row - 1;

	while (col >= 1 && row >= 1 && sign == getCell(row, col)) {
		count = count + 1;
		col = col - 1;
		row = row - 1;
	}

	if (count >= 4)
		return true;
	else
		return false;
}

void checkFour(int row, int col, char sign, int* winner) {
	if (checkVertically(row, col, sign) || checkHorizontally(row, col, sign) ||
		checkDiagonallyDown(row, col, sign) || checkDiagonallyUp(row, col, sign))
	{
		if (sign == 'X')
			*winner = 1;
		else
			*winner = 2;
	}
}

void processInput(int player, char sign, int* winner) {
	printf("Player number %d:\n", player);
	printf("Please enter column input (a number between 1-7): ");

	int col;
	scanf("%d", &col);

	//check for wrong input
	while ((col < 1 || col > COLS) || (getCell(1, col) != ' '))
	{
		if (col < 1 || col > COLS)
		{
			printf("Wrong input.\n");
		}
		else if (getCell(1, col) != ' ')
		{
			printf("The col you entered is full.\n");
		}
		printf("Please enter column input(a number between 1 - 7) : \n");
		scanf("%d", &col);
	}

	placeTop(col, sign);

	int row = getTop(col);

	checkFour(row, col, sign, winner);

	bool firstRowFull = true;
	for (int i = 1; i <= COLS; i++) {
		if (getCell(1, i) == ' ')
			firstRowFull = false;
	}

	if (firstRowFull)
		*winner = 3;

}
