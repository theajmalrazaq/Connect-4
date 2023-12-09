#include<iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// global variable declared for height and width
const int height = 7, width = 8;

// function declarations
void display(char board[][width]);
void check_down(char board[][width], char a, char choice);
void full_row(char board[][width], char a, char choice);
int check_win(char board[][width], char a);
void draw(char board[][width], int& checkfull);
int play(char MenuChoice, int& ScorePlayer1, int& ScorePlayer2, string playeronename, string playertwoname);

int main()
{
	srand(time(0));
	int ScorePlayer1 = 0, ScorePlayer2 = 0;
	char MenuChoice = '0';
	string playeronename, playertwoname;

	cout << "********************************************\n";
	cout << "**          Welcome to Connect Four!      **\n";
	cout << "********************************************\n\n\n";
	cout << "1. Play\n";
	cout << "2. Exit\n";
	cout << "Enter Your Choice: ";
	cin >> MenuChoice;
	cin.ignore();

	while (MenuChoice != '1' || MenuChoice != '2')
	{
		if (MenuChoice == '1') {
			cout << "Enter Player 1 Name: ";
			getline(cin, playeronename);
			cout << "Enter Player 2 Name: ";
			getline(cin, playertwoname);


			play(MenuChoice, ScorePlayer1, ScorePlayer2, playeronename, playertwoname);
			return 0;
		}
		else if (MenuChoice == '2') {
			cout << "Good Bye !!!!\n";
			return 0;
		}
		else {
			cout << "Invalid input!!!\n";

			cin >> MenuChoice;
			cin.ignore();

		}
	}



	system("pause");
}

int play(char MenuChoice, int& ScorePlayer1, int& ScorePlayer2, string playeronename, string playertwoname) {
	int playeroneturns = 0, playertwoturns = 0;
	int toss = rand() % 2;
	int currentPlayer = (toss == 0) ? 1 : 2;

	char board[height][width] = { ' ' }, Player1 = 'X', Player2 = 'O', choice;
	int win = 0, full = 0;
	char MenuTwoChoice = '0';

	if (MenuChoice == '1') {
		system("cls");

		cout << "***********************\n";
		cout << "Score of " << playeronename << " is: " << ScorePlayer1 << "\n";
		cout << "Score of " << playertwoname << " is: " << ScorePlayer2 << "\n";
		cout << "***********************\n";
		display(board);
		cout << ((currentPlayer == 1) ? playeronename : playertwoname) << " Won The Toss\n";
		do {
			draw(board, full);

			if (full == 0)
			{
				cout << "Match Draw!!\n";
				cout << "Total Numbers of Turns are: " << playeroneturns + playertwoturns << "\n";
				cout << "1. Play Again\n";
				cout << "2.Exit\n";
				cin >> MenuTwoChoice;

				while (MenuTwoChoice != '1' || MenuTwoChoice != '2')
				{
					if (MenuTwoChoice == '1') {
						play(MenuChoice, ScorePlayer1, ScorePlayer2, playeronename, playertwoname);
					}
					else if (MenuTwoChoice == '2') {
						cout << "Good Bye !!!!\n";
						return 0;
					}
					else {
						cout << "Invalid input!!!\n";
						cout << "1. Play Again\n";
						cout << "2.Exit\n";
						cin >> MenuTwoChoice;
					}
				}
			}

			cout << ((currentPlayer == 1) ? playeronename : playertwoname) << "'s Turns\nEnter row Between 1 and 7 = ";
			cin >> choice;
			cout << endl;

			while (choice < '1' || choice > '7') {
				cout << "Invalid input !!\n";
				cout << ((currentPlayer == 1) ? "Player 1" : "Player 2") << "\nEnter row Between 1 and 7 = ";
				cin >> choice;
				cout << endl;
			}
			(currentPlayer == 1) ? playeroneturns++ : playertwoturns++;
			check_down(board, (currentPlayer == 1) ? Player1 : Player2, choice);
			full_row(board, (currentPlayer == 1) ? Player1 : Player2, choice);

			system("cls");
			cout << "***********************\n";
			cout << "Score of " << playeronename << " is: " << ScorePlayer1 << "\n";
			cout << "Score of " << playertwoname << " is: " << ScorePlayer2 << "\n";
			cout << "***********************\n";
			display(board);

			win = check_win(board, (currentPlayer == 1) ? Player1 : Player2);

			if (win == 1) {
				cout << "\n\n*******************************************************\n\n";
				cout << " \tCongratulation!!!!!! " << ((currentPlayer == 1) ? playeronename : playertwoname) << " You Won!! In " << ((currentPlayer == 1) ? playeroneturns : playertwoturns) << " turns.\n";
				cout << "\n\n*******************************************************\n\n";
				(currentPlayer == 1) ? ScorePlayer1++ : ScorePlayer2++;

				cout << "1. Play Again\n";
				cout << "2.Exit\n";
				cin >> MenuTwoChoice;

				while (MenuTwoChoice != '1' || MenuTwoChoice != '2') {
					if (MenuTwoChoice == '1') {
						play(MenuChoice, ScorePlayer1, ScorePlayer2, playeronename, playertwoname);
					}
					else if (MenuTwoChoice == '2') {
						cout << "Good Bye !!!!\n";
						return 0;
					}
					else {
						cout << "Invalid input!!!\n";
						cout << "1.Play Again\n";
						cout << "2.Exit\n";
						cin >> MenuTwoChoice;
					}
				}


				playeroneturns += playertwoturns;
			}


			currentPlayer = (currentPlayer == 1) ? 2 : 1;

		} while (true);
	}
}






//win condition check krne ke lyie function 

int check_win(char board[][width], char a)
{
	// hr row ko check krna ka lia 
	int count = 0;
	for (int i = height - 1; i >= 1; --i)
	{
		for (int j = 1; j <= width - 1; ++j)
		{
			if (board[i][j] == a)
			{
				count++;
				if (count == 4)
				{
					return 1;
				}
			}
			else
			{
				count = 0;
			}
		}
	}


	// hr column ko check krna ka lia 
	count = 0;
	for (int i = height - 1; i >= 1; --i)
	{
		for (int j = 1; j <= width - 1; ++j)
		{
			if (board[j][i] == a)
			{
				count++;
				if (count == 4)
				{
					return 1;
				}
			}
			else
			{
				count = 0;
			}
		}
	}


	for (int i = 1; i <= height - 1; i++) {
		for (int j = 1; j <= width - 1; j++) {
			for (int k = 0; k <= 3; k++){
				if (board[i - k][j + k] == a){
					count++;
					if (count == 4)
					{
						return 1;
					}
				}
				else
				{
					count = 0;
				}
			}
			
		}
	}

	count = 0;
	for (int i = 1; i <= height - 1; i++) {
		for (int j = 1; j <= width - 1; j++) {
			for (int k = 0; k <= 3; k++){
				if(board[i + k][j + k] == a){
					count++;
					if (count == 4)
					{
						return 1;
					}
				}
				else
				{
					count = 0;
				}
			}
		}
	}






	return 0;

}





//full row dekhny ke lyie 
void full_row(char board[][width], char a, char choice)
{
	int x = 0;
	while (x != 1)
	{
		if (board[0][static_cast<int> (choice)-48] != 'X' && board[0][static_cast<int> (choice)-48] != 'O')
		{

			x = 1;

		}
		else
		{
			cout << "The following line is full!!!!Select another line = ";
			cin >> choice;
			while (choice < '1' || choice>'7')
			{
				cout << "Invalid input !!\n";
				cout << "Player 1 \nEnter row Between 1 and 7 = ";
				cin >> choice;
				cout << endl;

			}
			check_down(board, a, choice);
		}
	}
}





//user ki choice pr character put krne ke lyie 
void 	check_down(char board[][width], char a, char choice)
{
	int x = 6, y = 0;
	while (y != 1)
	{
		if (board[x][static_cast<int> (choice)-48] != 'X' && board[x][static_cast<int> (choice)-48] != 'O')
		{
			board[x][static_cast<int> (choice)-48] = a;
			y = 1;
		}
		else
		{
			--x;
		}

	}
}




//board show krne ke lyie function 
void display(char board[][width])
{
	cout << "  1  2  3  4  5  6  7  \n";
	cout << "***********************\n";
	for (int i = 1; i <= 6; i++)
	{
		cout << "*";
		for (int j = 1; j <= 7; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
				board[i][j] = ' ';

			cout << " " << board[i][j] << " ";

		}

		cout << "*" << endl;
	}
	cout << "***********************\n";

}






//full board check krne ke lyie 
void draw(char board[][width], int& checkfull)
{
	checkfull = 0;
	for (int i = 1; i <= height - 1; i++)
	{
		for (int j = 1; j <= width - 1; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
			{
				checkfull++;
			}
		}
	}
}
