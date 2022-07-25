#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;
bool gameOver;
int wall[39];
int playerX, playerY, timeLeft, started = 0, menuSelect=1, speed;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void colorText(int k)
{
	switch (k)
	{
	case(1):SetConsoleTextAttribute(handle, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)); break;
	case(2):SetConsoleTextAttribute(handle, (FOREGROUND_RED)); break;
	case(3):SetConsoleTextAttribute(handle, (FOREGROUND_GREEN)); break;
	case(5):SetConsoleTextAttribute(handle, 23); break;
	}
}

void launch()
{
	for (int i = 0; i < 40; i++) cout << "#";
	cout << endl;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}
	cout << "#" << setw(26);
	colorText(3);
	cout << "OBSTACLE RACE" << setw(13);
	colorText(1);
	cout << "#" << endl;

	cout << "#" << setw(27);
	colorText(2);
	cout << "by AlexandrGreat" << setw(12);
	colorText(1);
	cout << "#" << endl;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}

	cout << "#                 ";
	if (menuSelect == 1) colorText(5);
	cout << "Easy"; colorText(1); cout << "                 #" << endl;

	cout << "#                ";
	if (menuSelect == 2) colorText(5);
	cout << "Medium"; colorText(1); cout << "                #" << endl;

	cout << "#                 ";
	if (menuSelect == 3) colorText(5);
	cout << "Hard"; colorText(1); cout << "                 #" << endl;

	cout << "#        ";
	if (menuSelect == 4) colorText(5);
	cout << "Increasing difficulty"; colorText(1); cout << "         #" << endl;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}

	for (int i = 0; i < 40; i++) cout << "#";
	cout << endl;
}

void menuControls()
{
	if (_kbhit)
		switch (_getch())
		{
		case'w':if (menuSelect != 1) menuSelect--; break;
		case's':if (menuSelect != 4) menuSelect++; break;
		case'e':started = 1; break;
		}
}

void setSpeed(int s)
{
	if (s == 1) speed = 2000;
	if (s == 2) speed = 1000;
	if (s == 3) speed = 500;
	if (s == 4) { speed = 2000; Sleep(15000); speed = 1000; Sleep(15000); speed = 500;}
}

void setup()
{
	gameOver = false;
	playerX = 20;
	playerY = 18;
	timeLeft = 5;
	wall[38] = 0;
}

void wallDraw()
{
	srand(time(NULL));
	int wallLeft = rand() % 30;
	for (int i = 0; i < wallLeft; i++)
		wall[i] = 1;
	for (int i = wallLeft; i < wallLeft+5; i++)
		wall[i] = 0;
	for (int i = wallLeft+5; i < 38; i++)
		wall[i] = 1;
	
}

void controls()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':  if (playerX != 0) playerX--; break;
		case 'd':  if (playerX != 36) playerX++; break;
		case 'w':  if (playerY != 0) playerY--; break;
		case 's':  if (playerY != 18) playerY++; break;
		}
	}
}

void graphics()
{
	colorText(1);
	for (int i = 0; i < 40; i++)
		cout << "#";
	cout << endl;
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 38; j++)
			{
				if (j == 0) cout << "#";
				if ((wall[j] == 1) && (wall[38] == i)) { colorText(2); cout << "#"; colorText(1);} else
				if ((wall[j] == 1) && (wall[38] == i-1)) { colorText(2); cout << "#"; colorText(1); } else
				if ((wall[j] == 1) && (wall[38] == i-2)) { colorText(2); cout << "#"; colorText(1); }
				else if ((wall[j] == 0) && (wall[38] == i)) cout << " ";
				else if ((i == playerY) && (j == playerX)) { colorText(3); cout << "A"; colorText(1);}
				else cout << " ";
				if (j == 37) cout << "#" << endl;
				if (((playerX == j) && (playerY == wall[38]) && (wall[j] == 1))||((playerX == j) && (playerY == wall[38]-1) && (wall[j] == 1)) || ((playerX == j) && (playerY == wall[38] - 2) && (wall[j] == 1))) gameOver = true;
			}
		}
	colorText(1);
	for (int i = 0; i < 40; i++)
		cout << "#";
	cout << endl;
}

int main()
{
	menuSelect = 1;
	while (started == 0)
	{
		launch();
		menuControls();
		system("cls");
	}
	setup();
	while (!gameOver)
	{
		wallDraw();
			while (!gameOver) 
			{
				graphics();
				controls();
				wall[38]++;
				controls();
				Sleep(100);
				controls();
				system("cls");
				if (wall[38] > 19) { wall[38] = 0; wallDraw(); }
			}
	}
	for (int i = 0; i < 5; i++)
	{
		cout << "Game Over" << endl << "respawn in " << timeLeft;
		timeLeft--;
		Sleep(1000);
		system("cls");
	}
	started = 0;
	main();
}