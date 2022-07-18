#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
int cell[10];
int selected, player, gameOver, timeLeft;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
bool moveMade;

void colorText(int k)
{
	switch (k)
	{
	case(1):SetConsoleTextAttribute(handle, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)); break;
	case(2):SetConsoleTextAttribute(handle, (FOREGROUND_RED)); break;
	case(3):SetConsoleTextAttribute(handle, (FOREGROUND_GREEN)); break;
	case(4):SetConsoleTextAttribute(handle, 0); break;
	case(5):SetConsoleTextAttribute(handle, 23); break;
	}
}

void cellCheck(int c)
{
	if ((cell[c] == 0) && (selected != c)) { colorText(4); cout << " "; colorText(1);};
	if ((cell[c] == 0) && (selected == c)) { colorText(5); cout << " ";  colorText(4);  colorText(1);};
	if ((cell[c] == 1) && (selected != c)) { colorText(4); colorText(2); cout << "X"; colorText(1);};
	if ((cell[c] == 1) && (selected == c)) { colorText(5); cout << "X";  colorText(4); colorText(1);};
	if ((cell[c] == 2) && (selected != c)) { colorText(4); colorText(3); cout << "O"; colorText(1);};
	if ((cell[c] == 2) && (selected == c)) {colorText(5); cout << "O";  colorText(4); colorText(1);};
}

void line(int l)
{
	switch (l)
	{
	case(1):for (int i = 0; i < 13; i++) { colorText(1); cout << "#"; }; cout << endl; break;
	case(2):for (int i = 0; i < 3; i++) { cout << "#"; for (int j = 0; j < 3; j++) { cout << " "; } }; cout << "#" << endl; break;
	case(3):for (int i = 0; i < 3; i++) { cout << "#" << " "; cellCheck(i); cout << " "; }  cout << "#" << endl; break;
	case(4):for (int i = 0; i < 3; i++) { cout << "#" << " "; cellCheck(i + 3); cout << " "; }  cout << "#" << endl; break;
	case(5):for (int i = 0; i < 3; i++) { cout << "#" << " "; cellCheck(i + 6); cout << " "; }  cout << "#" << endl; break;
	}
}

void graphics()
{
	line(1);
	line(2);
	line(3); 
	line(2);
	line(1);
	line(2);
	line(4); 
	line(2);
	line(1);
	line(2);
	line(5); 
	line(2);
	line(1);
}

void setup()
{
	timeLeft = 7;
	srand(time(NULL));
	gameOver = 0;
	selected = 0;
	for (int i = 0; i < 9; i++)
	{
		cell[i] = 0;
	}
	player = rand() % 2 + 1;
}

void controls()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': if ((selected == 1) || (selected == 2) || (selected == 4) || (selected == 5) || (selected == 7) || (selected == 8)) selected--; break;
		case 'd': if ((selected == 0) || (selected == 1) || (selected == 3) || (selected == 4) || (selected == 6) || (selected == 7)) selected++; break;
		case 'w': if ((selected == 3) || (selected == 4) || (selected == 5) || (selected == 6) || (selected == 7) || (selected == 8)) selected-=3; break;
		case 's': if ((selected == 0) || (selected == 1) || (selected == 2) || (selected == 3) || (selected == 4) || (selected == 5)) selected+=3; break;
		case 'e': if (cell[selected] == 0) {
			cell[selected] = 1;
			if ((cell[0] > 0) && (cell[1] > 0) && (cell[2] > 0) && (cell[3] > 0) && (cell[4] > 0) && (cell[5] > 0) && (cell[6] > 0) && (cell[7] > 0) && (cell[8] > 0) && (gameOver == 0))
			{
				player = 1; gameOver = 3;
			} else player = 2;
		} break;
		}
	}
}

void rezCheck()
{
	//X wins
	if ((cell[0] == 1) && (cell[1] == 1) && (cell[2] == 1)) gameOver = 1; 
	if ((cell[3] == 1) && (cell[4] == 1) && (cell[5] == 1)) gameOver = 1; 
	if ((cell[6] == 1) && (cell[7] == 1) && (cell[8] == 1)) gameOver = 1; 
	if ((cell[0] == 1) && (cell[3] == 1) && (cell[6] == 1)) gameOver = 1; 
	if ((cell[1] == 1) && (cell[4] == 1) && (cell[7] == 1)) gameOver = 1; 
	if ((cell[2] == 1) && (cell[5] == 1) && (cell[8] == 1)) gameOver = 1; 
	if ((cell[0] == 1) && (cell[4] == 1) && (cell[8] == 1)) gameOver = 1; 
	if ((cell[2] == 1) && (cell[4] == 1) && (cell[6] == 1)) gameOver = 1; 
	//O wins
	if ((cell[0] == 2) && (cell[1] == 2) && (cell[2] == 2)) gameOver = 2; 
	if ((cell[3] == 2) && (cell[4] == 2) && (cell[5] == 2)) gameOver = 2; 
	if ((cell[6] == 2) && (cell[7] == 2) && (cell[8] == 2)) gameOver = 2; 
	if ((cell[0] == 2) && (cell[3] == 2) && (cell[6] == 2)) gameOver = 2; 
	if ((cell[1] == 2) && (cell[4] == 2) && (cell[7] == 2)) gameOver = 2; 
	if ((cell[2] == 2) && (cell[5] == 2) && (cell[8] == 2)) gameOver = 2; 
	if ((cell[0] == 2) && (cell[4] == 2) && (cell[8] == 2)) gameOver = 2; 
	if ((cell[2] == 2) && (cell[4] == 2) && (cell[6] == 2)) gameOver = 2; 
}

void priority()
{
	if (player == 2)
	{
		//row 1
		if ((cell[0] == 1) && (cell[1] == 1) && (cell[2] == 0) && (!moveMade)) { cell[2] = 2; moveMade = true; }
		if ((cell[0] == 1) && (cell[2] == 1) && (cell[1] == 0) && (!moveMade)) { cell[1] = 2; moveMade = true; }
		if ((cell[1] == 1) && (cell[2] == 1) && (cell[0] == 0) && (!moveMade)) { cell[0] = 2; moveMade = true; }
		//row 2
		if ((cell[3] == 1) && (cell[4] == 1) && (cell[5] == 0) && (!moveMade)) { cell[5] = 2; moveMade = true; }
		if ((cell[3] == 1) && (cell[5] == 1) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 1) && (cell[5] == 1) && (cell[3] == 0) && (!moveMade)) { cell[3] = 2; moveMade = true; }
		//row 3
		if ((cell[6] == 1) && (cell[7] == 1) && (cell[8] == 0) && (!moveMade)) { cell[8] = 2; moveMade = true; }
		if ((cell[6] == 1) && (cell[8] == 1) && (cell[7] == 0) && (!moveMade)) { cell[7] = 2; moveMade = true; }
		if ((cell[7] == 1) && (cell[8] == 1) && (cell[6] == 0) && (!moveMade)) { cell[6] = 2; moveMade = true; }
		//column 1
		if ((cell[0] == 1) && (cell[3] == 1) && (cell[6] == 0) && (!moveMade)) { cell[6] = 2; moveMade = true; }
		if ((cell[0] == 1) && (cell[6] == 1) && (cell[3] == 0) && (!moveMade)) { cell[3] = 2; moveMade = true; }
		if ((cell[3] == 1) && (cell[6] == 1) && (cell[0] == 0) && (!moveMade)) { cell[0] = 2; moveMade = true; }
		//column 2
		if ((cell[1] == 1) && (cell[4] == 1) && (cell[7] == 0) && (!moveMade)) { cell[7] = 2; moveMade = true; }
		if ((cell[1] == 1) && (cell[7] == 1) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 1) && (cell[7] == 1) && (cell[1] == 0) && (!moveMade)) { cell[1] = 2; moveMade = true; }
		//column 3
		if ((cell[2] == 1) && (cell[5] == 1) && (cell[8] == 0) && (!moveMade)) { cell[8] = 2; moveMade = true; }
		if ((cell[2] == 1) && (cell[8] == 1) && (cell[5] == 0) && (!moveMade)) { cell[5] = 2; moveMade = true; }
		if ((cell[5] == 1) && (cell[8] == 1) && (cell[2] == 0) && (!moveMade)) { cell[2] = 2; moveMade = true; }
		//main diagonal
		if ((cell[0] == 1) && (cell[4] == 1) && (cell[8] == 0) && (!moveMade)) { cell[8] = 2; moveMade = true; }
		if ((cell[0] == 1) && (cell[8] == 1) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 1) && (cell[8] == 1) && (cell[0] == 0) && (!moveMade)) { cell[0] = 2; moveMade = true; }
		//diagonal 2
		if ((cell[2] == 1) && (cell[4] == 1) && (cell[6] == 0) && (!moveMade)) { cell[6] = 2; moveMade = true; }
		if ((cell[2] == 1) && (cell[6] == 1) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 1) && (cell[6] == 1) && (cell[2] == 0) && (!moveMade)) { cell[2] = 2; moveMade = true; }

		//row 1 O
		if ((cell[0] == 2) && (cell[1] == 2) && (cell[2] == 0) && (!moveMade)) { cell[2] = 2; moveMade = true; }
		if ((cell[0] == 2) && (cell[2] == 2) && (cell[1] == 0) && (!moveMade)) { cell[1] = 2; moveMade = true; }
		if ((cell[1] == 2) && (cell[2] == 2) && (cell[0] == 0) && (!moveMade)) { cell[0] = 2; moveMade = true; }
		//row 2 O
		if ((cell[3] == 2) && (cell[4] == 2) && (cell[5] == 0) && (!moveMade)) { cell[5] = 2; moveMade = true; }
		if ((cell[3] == 2) && (cell[5] == 2) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 2) && (cell[5] == 2) && (cell[3] == 0) && (!moveMade)) { cell[3] = 2; moveMade = true; }
		//row 3 O
		if ((cell[6] == 2) && (cell[7] == 2) && (cell[8] == 0) && (!moveMade)) { cell[8] = 2; moveMade = true; }
		if ((cell[6] == 2) && (cell[8] == 2) && (cell[7] == 0) && (!moveMade)) { cell[7] = 2; moveMade = true; }
		if ((cell[7] == 2) && (cell[8] == 2) && (cell[6] == 0) && (!moveMade)) { cell[6] = 2; moveMade = true; }
		//column 1 O
		if ((cell[0] == 2) && (cell[3] == 2) && (cell[6] == 0) && (!moveMade)) { cell[6] = 2; moveMade = true; }
		if ((cell[0] == 2) && (cell[6] == 2) && (cell[3] == 0) && (!moveMade)) { cell[3] = 2; moveMade = true; }
		if ((cell[3] == 2) && (cell[6] == 2) && (cell[0] == 0) && (!moveMade)) { cell[0] = 2; moveMade = true; }
		//column 2 O
		if ((cell[1] == 2) && (cell[4] == 2) && (cell[7] == 0) && (!moveMade)) { cell[7] = 2; moveMade = true; }
		if ((cell[1] == 2) && (cell[7] == 2) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 2) && (cell[7] == 2) && (cell[1] == 0) && (!moveMade)) { cell[1] = 2; moveMade = true; }
		//column 3 O
		if ((cell[2] == 2) && (cell[5] == 2) && (cell[8] == 0) && (!moveMade)) { cell[8] = 2; moveMade = true; }
		if ((cell[2] == 2) && (cell[8] == 2) && (cell[5] == 0) && (!moveMade)) { cell[5] = 2; moveMade = true; }
		if ((cell[5] == 2) && (cell[8] == 2) && (cell[2] == 0) && (!moveMade)) { cell[2] = 2; moveMade = true; }
		//main diagonal O
		if ((cell[0] == 2) && (cell[4] == 2) && (cell[8] == 0) && (!moveMade)) { cell[8] = 2; moveMade = true; }
		if ((cell[0] == 2) && (cell[8] == 2) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 2) && (cell[8] == 2) && (cell[0] == 0) && (!moveMade)) { cell[0] = 2; moveMade = true; }
		//diagonal 2 O
		if ((cell[2] == 2) && (cell[4] == 2) && (cell[6] == 0) && (!moveMade)) { cell[6] = 2; moveMade = true; }
		if ((cell[2] == 2) && (cell[6] == 2) && (cell[4] == 0) && (!moveMade)) { cell[4] = 2; moveMade = true; }
		if ((cell[4] == 2) && (cell[6] == 2) && (cell[2] == 0) && (!moveMade)) { cell[2] = 2; moveMade = true; }
	}
}

void notPriority()
{
	int randomCell = rand() % 9;
	if (cell[randomCell] != 0) notPriority(); else cell[randomCell] = 2;
	cout << randomCell << endl;
}

void logic()
{
	int randomCell;
	if ((player == 2) && (gameOver==0))
	{
		priority();
		if (!moveMade)
		notPriority();
	}
	moveMade = false;
	player = 1;
}

int main()
{
	setup();
	while (gameOver==0)
	{
		logic();
		rezCheck();
		graphics();
		controls();
		system("cls");
	}
	system("cls");
	for (int i = 0; i < 7; i++) 
	{
		if (gameOver == 1) cout << "X wins" << endl;
		if (gameOver == 2) cout << "O wins" << endl;
		if (gameOver == 3) cout << "Draw" << endl;
		cout << "New game in " << timeLeft;
		Sleep(1000);
		timeLeft--;
		system("cls");
	}
	main();
}