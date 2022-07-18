#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;
int cell[10];
int selected, player, gameOver, timeLeft, menuSelect = 1, started = 0;
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

void launch()
{
	colorText(1);
	for (int i = 0; i < 40; i++) cout << "#";
	cout << endl;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}
	cout << "#" << setw(24);
	colorText(3);
	cout << "Tic-Tac-Toe" << setw(15);
	colorText(1);
	cout << "#" << endl;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}

	cout << "#" << setw(29);
	cout << "Play against computer" << setw(10) << "#" << endl;

	cout << "#              ";
	if (menuSelect == 1) colorText(5);
	cout << "Play as X"; colorText(1); cout<< "               #" << endl;

	cout << "#              ";
	if (menuSelect == 2) colorText(5);
	cout << "Play as O"; colorText(1); cout << "               #" << endl;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 40; i++) cout << "#";
}

void menuControls()
{
	if (_kbhit)
		switch (_getch())
		{
		case'w':if (menuSelect != 1) menuSelect--; break;
		case's':if (menuSelect != 2) menuSelect++; break;
		case'e':started = menuSelect; break;
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

void controls(int s)
{
	int p1, p2;
	p1 = s;
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': if ((selected == 1) || (selected == 2) || (selected == 4) || (selected == 5) || (selected == 7) || (selected == 8)) selected--; break;
		case 'd': if ((selected == 0) || (selected == 1) || (selected == 3) || (selected == 4) || (selected == 6) || (selected == 7)) selected++; break;
		case 'w': if ((selected == 3) || (selected == 4) || (selected == 5) || (selected == 6) || (selected == 7) || (selected == 8)) selected-=3; break;
		case 's': if ((selected == 0) || (selected == 1) || (selected == 2) || (selected == 3) || (selected == 4) || (selected == 5)) selected+=3; break;
		case 'e': if (cell[selected] == 0) {
			cell[selected] = p1;
			if ((cell[0] > 0) && (cell[1] > 0) && (cell[2] > 0) && (cell[3] > 0) && (cell[4] > 0) && (cell[5] > 0) && (cell[6] > 0) && (cell[7] > 0) && (cell[8] > 0) && (gameOver == 0))
			{
				player = 1; gameOver = 3;
			} else player = 2;
		} break;
		}
	}
}

void rezCheck(int s)
{
	int p1, p2;
	if (s == 1) { p1 = 1; p2 = 2; }
	if (s == 2) { p1 = 2; p2 = 1; }
	//Player wins
	if ((cell[0] == p1) && (cell[1] == p1) && (cell[2] == p1)) gameOver = 1; 
	if ((cell[3] == p1) && (cell[4] == p1) && (cell[5] == p1)) gameOver = 1; 
	if ((cell[6] == p1) && (cell[7] == p1) && (cell[8] == p1)) gameOver = 1; 
	if ((cell[0] == p1) && (cell[3] == p1) && (cell[6] == p1)) gameOver = 1; 
	if ((cell[1] == p1) && (cell[4] == p1) && (cell[7] == p1)) gameOver = 1; 
	if ((cell[2] == p1) && (cell[5] == p1) && (cell[8] == p1)) gameOver = 1; 
	if ((cell[0] == p1) && (cell[4] == p1) && (cell[8] == p1)) gameOver = 1; 
	if ((cell[2] == p1) && (cell[4] == p1) && (cell[6] == p1)) gameOver = 1; 
	//Computer wins
	if ((cell[0] == p2) && (cell[1] == p2) && (cell[2] == p2)) gameOver = 2; 
	if ((cell[3] == p2) && (cell[4] == p2) && (cell[5] == p2)) gameOver = 2; 
	if ((cell[6] == p2) && (cell[7] == p2) && (cell[8] == p2)) gameOver = 2; 
	if ((cell[0] == p2) && (cell[3] == p2) && (cell[6] == p2)) gameOver = 2; 
	if ((cell[1] == p2) && (cell[4] == p2) && (cell[7] == p2)) gameOver = 2; 
	if ((cell[2] == p2) && (cell[5] == p2) && (cell[8] == p2)) gameOver = 2; 
	if ((cell[0] == p2) && (cell[4] == p2) && (cell[8] == p2)) gameOver = 2; 
	if ((cell[2] == p2) && (cell[4] == p2) && (cell[6] == p2)) gameOver = 2; 
}

void priority(int s)
{
	int p1, p2;
	if (s == 1) { p1 = 1; p2 = 2; }
	if (s == 2) { p1 = 2; p2 = 1; }
	if (player == 2)
	{
		//row 1 full
		if ((cell[0] == p2) && (cell[1] == p2) && (cell[2] == 0) && (!moveMade)) { cell[2] = p2; moveMade = true; }
		if ((cell[0] == p2) && (cell[2] == p2) && (cell[1] == 0) && (!moveMade)) { cell[1] = p2; moveMade = true; }
		if ((cell[1] == p2) && (cell[2] == p2) && (cell[0] == 0) && (!moveMade)) { cell[0] = p2; moveMade = true; }
		//row 2 full
		if ((cell[3] == p2) && (cell[4] == p2) && (cell[5] == 0) && (!moveMade)) { cell[5] = p2; moveMade = true; }
		if ((cell[3] == p2) && (cell[5] == p2) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p2) && (cell[5] == p2) && (cell[3] == 0) && (!moveMade)) { cell[3] = p2; moveMade = true; }
		//row 3 full
		if ((cell[6] == p2) && (cell[7] == p2) && (cell[8] == 0) && (!moveMade)) { cell[8] = p2; moveMade = true; }
		if ((cell[6] == p2) && (cell[8] == p2) && (cell[7] == 0) && (!moveMade)) { cell[7] = p2; moveMade = true; }
		if ((cell[7] == p2) && (cell[8] == p2) && (cell[6] == 0) && (!moveMade)) { cell[6] = p2; moveMade = true; }
		//column 1 full
		if ((cell[0] == p2) && (cell[3] == p2) && (cell[6] == 0) && (!moveMade)) { cell[6] = p2; moveMade = true; }
		if ((cell[0] == p2) && (cell[6] == p2) && (cell[3] == 0) && (!moveMade)) { cell[3] = p2; moveMade = true; }
		if ((cell[3] == p2) && (cell[6] == p2) && (cell[0] == 0) && (!moveMade)) { cell[0] = p2; moveMade = true; }
		//column 2 full
		if ((cell[1] == p2) && (cell[4] == p2) && (cell[7] == 0) && (!moveMade)) { cell[7] = p2; moveMade = true; }
		if ((cell[1] == p2) && (cell[7] == p2) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p2) && (cell[7] == p2) && (cell[1] == 0) && (!moveMade)) { cell[1] = p2; moveMade = true; }
		//column 3 full
		if ((cell[2] == p2) && (cell[5] == p2) && (cell[8] == 0) && (!moveMade)) { cell[8] = p2; moveMade = true; }
		if ((cell[2] == p2) && (cell[8] == p2) && (cell[5] == 0) && (!moveMade)) { cell[5] = p2; moveMade = true; }
		if ((cell[5] == p2) && (cell[8] == p2) && (cell[2] == 0) && (!moveMade)) { cell[2] = p2; moveMade = true; }
		//main diagonal full
		if ((cell[0] == p2) && (cell[4] == p2) && (cell[8] == 0) && (!moveMade)) { cell[8] = p2; moveMade = true; }
		if ((cell[0] == p2) && (cell[8] == p2) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p2) && (cell[8] == p2) && (cell[0] == 0) && (!moveMade)) { cell[0] = p2; moveMade = true; }
		//diagonal 2 full
		if ((cell[2] == p2) && (cell[4] == p2) && (cell[6] == 0) && (!moveMade)) { cell[6] = p2; moveMade = true; }
		if ((cell[2] == p2) && (cell[6] == p2) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p2) && (cell[6] == p2) && (cell[2] == 0) && (!moveMade)) { cell[2] = p2; moveMade = true; }

		//row 1
		if ((cell[0] == p1) && (cell[1] == p1) && (cell[2] == 0) && (!moveMade)) { cell[2] = p2; moveMade = true; }
		if ((cell[0] == p1) && (cell[2] == p1) && (cell[1] == 0) && (!moveMade)) { cell[1] = p2; moveMade = true; }
		if ((cell[1] == p1) && (cell[2] == p1) && (cell[0] == 0) && (!moveMade)) { cell[0] = p2; moveMade = true; }
		//row 2
		if ((cell[3] == p1) && (cell[4] == p1) && (cell[5] == 0) && (!moveMade)) { cell[5] = p2; moveMade = true; }
		if ((cell[3] == p1) && (cell[5] == p1) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p1) && (cell[5] == p1) && (cell[3] == 0) && (!moveMade)) { cell[3] = p2; moveMade = true; }
		//row 3
		if ((cell[6] == p1) && (cell[7] == p1) && (cell[8] == 0) && (!moveMade)) { cell[8] = p2; moveMade = true; }
		if ((cell[6] == p1) && (cell[8] == p1) && (cell[7] == 0) && (!moveMade)) { cell[7] = p2; moveMade = true; }
		if ((cell[7] == p1) && (cell[8] == p1) && (cell[6] == 0) && (!moveMade)) { cell[6] = p2; moveMade = true; }
		//column 1
		if ((cell[0] == p1) && (cell[3] == p1) && (cell[6] == 0) && (!moveMade)) { cell[6] = p2; moveMade = true; }
		if ((cell[0] == p1) && (cell[6] == p1) && (cell[3] == 0) && (!moveMade)) { cell[3] = p2; moveMade = true; }
		if ((cell[3] == p1) && (cell[6] == p1) && (cell[0] == 0) && (!moveMade)) { cell[0] = p2; moveMade = true; }
		//column 2
		if ((cell[1] == p1) && (cell[4] == p1) && (cell[7] == 0) && (!moveMade)) { cell[7] = p2; moveMade = true; }
		if ((cell[1] == p1) && (cell[7] == p1) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p1) && (cell[7] == p1) && (cell[1] == 0) && (!moveMade)) { cell[1] = p2; moveMade = true; }
		//column 3
		if ((cell[2] == p1) && (cell[5] == p1) && (cell[8] == 0) && (!moveMade)) { cell[8] = p2; moveMade = true; }
		if ((cell[2] == p1) && (cell[8] == p1) && (cell[5] == 0) && (!moveMade)) { cell[5] = p2; moveMade = true; }
		if ((cell[5] == p1) && (cell[8] == p1) && (cell[2] == 0) && (!moveMade)) { cell[2] = p2; moveMade = true; }
		//main diagonal
		if ((cell[0] == p1) && (cell[4] == p1) && (cell[8] == 0) && (!moveMade)) { cell[8] = p2; moveMade = true; }
		if ((cell[0] == p1) && (cell[8] == p1) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p1) && (cell[8] == p1) && (cell[0] == 0) && (!moveMade)) { cell[0] = p2; moveMade = true; }
		//diagonal 2
		if ((cell[2] == p1) && (cell[4] == p1) && (cell[6] == 0) && (!moveMade)) { cell[6] = p2; moveMade = true; }
		if ((cell[2] == p1) && (cell[6] == p1) && (cell[4] == 0) && (!moveMade)) { cell[4] = p2; moveMade = true; }
		if ((cell[4] == p1) && (cell[6] == p1) && (cell[2] == 0) && (!moveMade)) { cell[2] = p2; moveMade = true; }
	}
}

void notPriority(int s)
{
	int p1, p2;
	if (s == 1) p2 = 2; 
	if (s == 2) p2 = 1; 
	int randomCell = rand() % 9;
	if (cell[randomCell] != 0) notPriority(started); else cell[randomCell] = p2;
}

void logic()
{
	int randomCell;
	if ((player == 2) && (gameOver==0))
	{
		priority(started);
		if (!moveMade)
		notPriority(started);
	}
	moveMade = false;
	if ((cell[0] > 0) && (cell[1] > 0) && (cell[2] > 0) && (cell[3] > 0) && (cell[4] > 0) && (cell[5] > 0) && (cell[6] > 0) && (cell[7] > 0) && (cell[8] > 0) && (gameOver == 0))
	{
		player = 1; gameOver = 3;
	} else player = 1;
}

int main()
{
	while (started==0)
	{
		launch();
		menuControls();
		Sleep(10);
		system("cls");
	}
	setup();
	while (gameOver==0)
	{
		logic();
		rezCheck(started);
		graphics();
		controls(started);
		Sleep(10);
		system("cls");
	}
	system("cls");

	for (int i = 0; i < 7; i++)
	{
		colorText(1);
		for (int i = 0; i < 40; i++) cout << "#";
		cout << endl;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 40; i++)
				if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
			cout << endl;
		}
		cout << "#" << setw(22);
		colorText(2);
		cout << ("GAME OVER") << setw(17);
		colorText(1);
		cout << "#" << endl;

		int w1,w2;
		if (gameOver == 1) w1 = 22;
		if (gameOver == 2) w1 = 24;
		if (gameOver == 3) w1 = 20;
		cout << "#" << setw(w1);
		if (gameOver == 1) { colorText(3); cout << "You Win!"; w2 = 17; colorText(1);}
		if (gameOver == 2) { colorText(3); cout << "Computer Won!"; w2 = 15; colorText(1);}
		if (gameOver == 3) { colorText(3); cout << "Draw!"; w2 = 19; colorText(1);}
		colorText(1);
		cout <<setw(w2)<< "#" << endl;

		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 40; i++)
				if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
			cout << endl;
		}

		cout << "#" << setw(30) << "Return to main menu in " << timeLeft << setw(8) << "#" << endl;

		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 40; i++)
				if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
			cout << endl;
		}

		for (int i = 0; i < 40; i++) cout << "#";
		cout << endl;

		Sleep(1000);
		timeLeft--;
		system("cls");
	}
	started = 0;
	menuSelect = 1;
	main();
}