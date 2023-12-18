#include<iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

//row or colum ki height set ki 1+ se q ke array 1 se start krni hai
const int row = 7, column = 8;

// function declarations
void display(char board[][column]);
void check_down(char board[][column], char a, int choice);
void full_row(char board[][column], char a, int choice, string playername);
bool check_win(char board[][column], char a);
void draw(char board[][column], int & checkfull);
int play(char MenuChoice, int & ScorePlayer1, int & ScorePlayer2, string playeronename, string playertwoname);
void credits_fun();
void rules_fun();
void record();
void setrecord(string playername, int playerterns);

int main() {

	srand(time(0));
	int ScorePlayer1 = 0, ScorePlayer2 = 0, recursincount = 0;
	char MenuChoice = '0';
	string playeronename, playertwoname;

	//Menu
	cout << "********************************************\n";
	cout << "**          Welcome to Connect Four!      **\n";
	cout << "********************************************\n\n\n";
	bool checkmenu = true;
	cout << "1.Play\n";
	cout << "2.Exit\n";
	cout << "3.Credits\n";
	cout << "4.Instructions\n";
	cout << "5.Record\n";
	while (checkmenu) {
		cout << "Enter Your Choice: ";
		cin >> MenuChoice;
		cin.ignore();


		//agar input 1 mil gya tu play function call kr ke game start kr do
		if (MenuChoice == '1') {


			cout << "Enter Player 1 Name: ";
			getline(cin, playeronename);


			bool alphcheck = true;
			while (alphcheck){
				if (playeronename[0] >= 'A' && playeronename[0] <= 'Z' || playeronename[0] >= 'a' && playeronename[0] <= 'z'){
					alphcheck = false;
				}
				else{
					alphcheck = true;
				}
				if (alphcheck){
					cout << "invalid input\nEnter Name again: ";
					getline(cin, playeronename);
				}

			}

			cout << "Enter Player 2 Name: ";
			getline(cin, playertwoname);
			alphcheck = true;
			while (alphcheck){
				if (playertwoname[0] >= 'A' && playertwoname[0] <= 'Z' || playertwoname[0] >= 'a' && playertwoname[0] <= 'z'){
					alphcheck = false;
				}
				else{
					alphcheck = true;
				}
				if (alphcheck){
					cout << "invalid input\nEnter Name again: ";
					getline(cin, playertwoname);
				}

			}
			checkmenu = false;
			play(MenuChoice, ScorePlayer1, ScorePlayer2, playeronename, playertwoname);

		}
		else if (MenuChoice == '2') {
			cout << "Good Bye !!!!\n";
			return 0;
		}
		else if (MenuChoice == '3') {
			credits_fun();
		}
		else if (MenuChoice == '4') {
			rules_fun();
		}
		else if (MenuChoice == '5') {
			record();
		}
		else {
			cout << "invalid input\n";

		}
	}

	system("pause");
}


int play(char MenuChoice, int & ScorePlayer1, int & ScorePlayer2, string playeronename, string playertwoname) {

	//iniatlly sab set kr dia taka jab bhi recursive function call kryn to reset ho kr call ho function
	int playeroneturns = 0, playertwoturns = 0;

	//toss krne or choose krne ke lyie current player 1 ho ga ya 2
	int toss = rand() % 2;
	int currentPlayer = (toss == 0) ? 1 : 2;
	char board[row][column] = {
		' '
	}, Player1 = 'X', Player2 = 'O';
	int win = 0, full = 0, choice;
	char MenuTwoChoice = '0';


	//agar menu choice 1 mily main se tu screan clear kr ke score show kry or game board
	if (MenuChoice == '1') {
		system("cls");
		cout << "***********************\n";
		cout << "Score of " << playeronename << " is: " << ScorePlayer1 << "\n";
		cout << "Score of " << playertwoname << " is: " << ScorePlayer2 << "\n";
		cout << "***********************\n";
		display(board);
		cout << ((currentPlayer == 1) ? playeronename : playertwoname) << " Won The Toss\n";

		//tab tak yeh krty raho jab tak loop maually break na ho
		do {
			//board check krne ke lyie kahi full tu nhi 

			draw(board, full);
			if (full == 0) {
				cout << "Match Draw!!\n";
				cout << "Total Numbers of Turns are: " << playeroneturns + playertwoturns << "\n";
				cout << "1. Play Again\n";
				cout << "2.Exit\n";
				cout << "3.Credits\n";
				cout << "4.Instructions\n";
				cout << "5.Record\n";

				bool MenuTwoChoicecheck = true;
				while (MenuTwoChoicecheck) {
					cout << "Enter Your Choice: ";
					cin >> MenuTwoChoice;
					cin.ignore();
					if (MenuTwoChoice == '1') {
						if (!play(MenuChoice, ScorePlayer1, ScorePlayer2, playeronename, playertwoname)) {
							return 0;
						}
						MenuTwoChoicecheck = false;
					}
					else if (MenuTwoChoice == '2') {
						cout << "Good Bye !!!!\n";
						return 0;
					}
					else if (MenuTwoChoice == '3') {
						credits_fun();
					}
					else if (MenuTwoChoice == '4') {
						rules_fun();
					}
					else if (MenuTwoChoice == '5') {
						record();
					}
					else {
						cout << "Invalid input!!!\n";

					}
				}
			}
			//current player dekhna or uski choice lna
			cout << ((currentPlayer == 1) ? playeronename : playertwoname) << "'s Turns\nEnter row Between 1 and 7 = ";
			cin >> choice;
			cout << endl;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invaid input\n";
				continue;
			}
			while (choice < 1 || choice > 7) {
				cout << "Invalid input !!\n";
				cout << ((currentPlayer == 1) ? playeronename : playertwoname) << "'s Turns\nEnter row Between 1 and 7 : ";
				cin >> choice;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
			}

			//current player check krna or us ke number of turns increase krna
			(currentPlayer == 1) ? playeroneturns++ : playertwoturns++;
			check_down(board, (currentPlayer == 1) ? Player1 : Player2, choice);
			full_row(board, (currentPlayer == 1) ? Player1 : Player2, choice, (currentPlayer == 1) ? playeronename : playertwoname);

			system("cls");
			cout << "***********************\n";
			cout << "Score of " << playeronename << " is: " << ScorePlayer1 << "\n";
			cout << "Score of " << playertwoname << " is: " << ScorePlayer2 << "\n";
			cout << "***********************\n";
			display(board);

			win = check_win(board, (currentPlayer == 1) ? Player1 : Player2);

			//winner check krne ke lyie
			if (win == 1) {
				cout << "\n\n*******************************************************\n\n";
				cout << " \tCongratulation!!!!!! " << ((currentPlayer == 1) ? playeronename : playertwoname) << " You Won!! In " << ((currentPlayer == 1) ? playeroneturns : playertwoturns) << " turns.\n";
				cout << "\n\n*******************************************************\n\n";
				setrecord(((currentPlayer == 1) ? playeronename : playertwoname), ((currentPlayer == 1) ? playeroneturns : playertwoturns));
				(currentPlayer == 1) ? ScorePlayer1++ : ScorePlayer2++;
				cout << "1.Play Again\n";
				cout << "2.Exit\n";
				cout << "3.Credits\n";
				cout << "4.Instructions\n";
				cout << "5.Record\n";
				bool MenuTwoChoicecheck = true;
				while (MenuTwoChoicecheck) {
					cout << "Enter Your Choice: ";
					cin >> MenuTwoChoice;
					cin.ignore();
					if (MenuTwoChoice == '1') {
						if (!play(MenuChoice, ScorePlayer1, ScorePlayer2, playeronename, playertwoname)) {
							return 0;
						}
						MenuTwoChoicecheck = false;
					}
					else if (MenuTwoChoice == '2') {
						cout << "Good Bye !!!!\n";
						return 0;
					}
					else if (MenuTwoChoice == '3') {
						credits_fun();
					}
					else if (MenuTwoChoice == '4') {
						rules_fun();
					}
					else if (MenuTwoChoice == '5') {
						record();
					}
					else {
						cout << "Invalid input!!!\n";

					}
				}
			}

			//player switch krne ke lyie
			currentPlayer = (currentPlayer == 1) ? 2 : 1;

		} while (true);
	}

	return 0;
}

//win condition check krne ke lyie function 
bool check_win(char board[][column], char a) {


	for (int i = row - 1; i >= 1; i--) {
		for (int j = column - 1; j >= 1; j--) {
			int countdiagonalleft = 0;
			int counthorizontal = 0;
			int countvertical = 0;
			int countdiagonalright = 0;

			for (int k = 0; k < 4; k++) {
				//digonal left ke lyie
				if (board[i - k][j - k] == a) {
					countdiagonalleft++;
				}
				else {
					countdiagonalleft = 0;
				}
				//horizontal  ke lyie
				if (board[i][j - k] == a) {
					counthorizontal++;
				}
				else {
					counthorizontal = 0;
				}
				//vertical  ke lyie
				if (board[i - k][j] == a) {
					countvertical++;
				}
				else {
					countvertical = 0;
				}
				//digonal right ke lyie
				if (board[i - k][j + k] == a) {
					countdiagonalright++;
				}
				else {
					countdiagonalright = 0;
				}
			}

			if (countdiagonalleft == 4 || counthorizontal == 4 || countvertical == 4 || countdiagonalright == 4) {
				return true;
			}
		}
	}

	return false;
}

//full row  dekhny ke lyie 
void full_row(char board[][column], char a, int choice, string playername) {
	int x = 0;
	while (x != 1) {
		if (board[0][choice] != 'X' && board[0][choice] != 'O') {
			x = 1;
		}
		else {
			cout << "The following line is full!!!!\nSelect another line: ";
			cin >> choice;
			while (choice < 1 || choice > 7) {
				cout << "Invalid input !!\n";
				cout << playername << " Enter row Between 1 and 7 :";
				cin >> choice;
				cout << endl;

			}
			check_down(board, a, choice);
		}
	}
}

//user ki choice pr character put krne ke lyie 
void check_down(char board[][column], char a, int choice) {
	int x = 6, y = 0;
	while (y != 1) {
		if (board[x][choice] != 'X' && board[x][choice] != 'O') {
			board[x][choice] = a;
			y = 1;
		}
		else {
			--x;
		}

	}
}

//board show krne ke lyie function 
void display(char board[][column]) {
	cout << "  1  2  3  4  5  6  7  \n";
	cout << "***********************\n";
	for (int i = 1; i <= 6; i++) {
		cout << "*";
		for (int j = 1; j <= 7; j++) {
			if (board[i][j] != 'X' && board[i][j] != 'O')
				board[i][j] = ' ';

			cout << " " << board[i][j] << " ";

		}

		cout << "*" << endl;
	}
	cout << "***********************\n";

}

//full board check krne ke lyie 
void draw(char board[][column], int & checkfull) {
	checkfull = 0;
	for (int i = 1; i <= row - 1; i++) {
		for (int j = 1; j <= column - 1; j++) {
			if (board[i][j] != 'X' && board[i][j] != 'O') {
				checkfull++;
			}
		}
	}
}
//crdits dekhny ke lyie
void credits_fun() {
	cout << "\n\t     Credits\n**********************************************\n\n";
	cout << "\t     Game made by   \n\n\t    1.Usman Dilbar \n\t    2.Ajmal Razaq \n";
	cout << "\n\n**********************************************\n\n";

}
//rules dekhny ke lyie
void rules_fun() {
	cout << "\n\t     Instruction/Rules\n*****************************************************************************************\n\n\n";
	cout << "1. Players take turns dropping by selecting one of seven columns into a 6x7 Board. \n\n";
	cout << "2. The goal is to connect four 'X' or 'O'  in a Board.\n\n";
	cout << "3. Connections can be horizontal, vertical, or diagonal. \n\n";
	cout << "4. The first to achieve this wins, or it's a draw if the Board is full. \n\n";
	cout << "\n\n*****************************************************************************************\n\n";
}
//record show krne ke lyie
void record(){
	ifstream fin;
	fin.open("Scores.txt");
	string record;
	while (!(fin.eof())){
		getline(fin, record);
		cout << record << endl;
	}
}
//record set krne ke lyie file mn
void setrecord(string playername, int playerterms)
{
	ofstream fout;
	fout.open("Scores.txt", ios::app);
	string record = "Player Name: " + playername + " || Player No of Turns: " + to_string(playerterms);
	if (fout.is_open())
	{
		if (!(fout.eof()))
		{
			fout << record << endl;
		}
		fout.close();
	}
}
