/*

ASMT01 Part 1 - Tic Tac Toe
Anne Lanaza
CSC 340
7/3/18
Professor Duc Ta

*/

#include <iostream>
using namespace std;

bool isWon(char c, char board[][3]);
bool isDraw(char board[][3]);
void displayBoard(char board[][3]);
void makeAMove(char board[][3], char c);


int main() {
	//
	//	PLEASE DO NOT CHANGE main()
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {
	// The first player makes a move
	makeAMove(board, 'X');
	displayBoard(board);
	if (isWon('X', board)) {
	cout << "X player won" << endl;
	exit(0);
	}
	else if (isDraw(board)) {
	cout << "No winner" << endl;
	exit(0);
	}

	// The second player makes a move
	makeAMove(board, 'O');
	displayBoard(board);

	if (isWon('O', board)) {
	cout << "O player won" << endl;
	exit(0);
	}
	else if (isDraw(board)) {
	cout << "No winner" << endl;
	exit(0);
	}
	}

	return 0;
}

bool isDraw(char board[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') return false;
		}
	}
	return true;
}

bool isWon(char c, char board[][3]) {

	return ((board[0][0] == c) && (board[0][1] == c) && (board[0][2] == c)) ^
		((board[1][0] == c) && (board[1][1] == c) && (board[1][2] == c)) ^
		((board[2][0] == c) && (board[2][1] == c) && (board[2][2] == c)) ^
		((board[0][0] == c) && (board[1][0] == c) && (board[2][0] == c)) ^
		((board[0][1] == c) && (board[1][1] == c) && (board[2][1] == c)) ^
		((board[0][2] == c) && (board[1][2] == c) && (board[2][2] == c)) ^
		((board[0][0] == c) && (board[1][1] == c) && (board[2][2] == c)) ^
		((board[0][2] == c) && (board[1][1] == c) && (board[2][0] == c));

	return false;
}

void makeAMove(char board[][3], char a) {
	unsigned int rowMove, colMove; //player's chosen row and column
	bool valid = false;

	while (!valid) {
		cout << "Enter a row(0, 1, 2) for player " << a << " : ";
		cin  >> rowMove;

		cout << "Enter a column (0, 1, 2) for player " << a << " : ";
		cin >> colMove;

		//check if slot in board is empty
		if (board[rowMove][colMove] != ' ') {
			cout << "This cell is already occupied. Try a different cell" << endl;
		}
		else if ((rowMove > 2) || (colMove > 2)) {
			cout << "Please enter a valid number" << endl;
		}
		else {
			valid = true;
			board[rowMove][colMove] = a;
		}
	}
	cout << " " << endl;
}

void displayBoard(char board[][3]) {
	cout << "-------------" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "| " << board[i][j] << " ";
		}
		cout << "|" << endl;
		cout << "-------------" << endl;
	}
}


