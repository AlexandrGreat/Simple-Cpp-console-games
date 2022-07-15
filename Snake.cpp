#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int  width = 26;
const int height = 26;
int headX, headY, foodX, foodY, score, timeLeft;
static int highscore = 0;
int tailX[250], tailY[250];
int tailLength;
enum Direction {Stop = 0, Left, Right, Up, Down};
Direction direction;
bool started = false;
bool barriers;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void colorText(int k)
{
	switch (k)
	{
	case(1):SetConsoleTextAttribute(handle, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)); break;
	case(2):SetConsoleTextAttribute(handle, (FOREGROUND_RED)); break;
	case(3):SetConsoleTextAttribute(handle, (FOREGROUND_GREEN)); break;
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
		cout<<endl;
	}
	cout << "#" << setw(24);
	colorText(3);
	cout << "SNAKE GAME" << setw(15);
	colorText(1);
	cout << "#" << endl;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}

	cout << "#" << setw(33);
	cout << "Play with barriers (y/n)?" << setw(6) << "#" << endl;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 40; i++)
			if ((i == 0) || (i == 39))cout << "#"; else cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 40; i++) cout << "#";

	switch (_getch())
	{
		case 'y': barriers = true; started = true; break;
		case 'n': barriers = false; started = true; break;
	}
	system("cls");
}

void setup()
{
	score = 0;
	for (int i = 1; i < tailLength; i++)
	{
		tailX[i] = 0;
		tailY[i] = 0;
	}
	tailLength = 0;
	timeLeft = 5;
	gameOver = false;
	direction = Stop;
	headX = width / 2;
	headY = height / 2;
	srand(time(NULL));
	foodX = rand() % width;
	foodY = rand() % height;
}

void graphics()
{
	system("cls");
	colorText(1);
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)  cout << "#"; 
			if ((j == headX) && (i == headY)) { colorText(2);  cout << "O"; }
			else
				if ((j == foodX) && (i == foodY)){ colorText(3); cout << "*";}
				else
				{
					bool print = false;
					for (int t = 1; t < tailLength; t++)
					{
						if ((tailX[t] == j) && (tailY[t] == i))
						{
							colorText(2);
							cout << "o";
							print = true;
						}
					}
					if (!print)
					cout << " ";
				}
			if (j == width - 1) { colorText(1); cout << "#"; }
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << endl << "Score: " << score << endl << "Highscore: " << highscore;
}

void controls()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': if (direction != Right) direction = Left; break;
		case 'd': if (direction != Left) direction = Right; break;
		case 'w': if (direction != Down) direction = Up; break;
		case 's': if (direction != Up) direction = Down; break;
		}
	}
}

void logic()
{
	tailX[0] = headX;
	tailY[0] = headY;
	int lastX = tailX[0];
	int lastY = tailY[0];
	int lastX2, lastY2;
	for (int i = 1; i < tailLength; i++)
	{
		lastX2 = tailX[i];
		lastY2 = tailY[i];
		tailX[i] = lastX;
		tailY[i] = lastY;
		lastX = lastX2;
		lastY = lastY2;
	}
	switch (direction)
	{
	case Left: headX--; break;
	case Right: headX++; break;
	case Up: headY--; break;
	case Down: headY++; break;
	}	
	if ((headX > width - 1 || headX < 0 || headY > height - 1 || headY < 0) && (barriers == true)) gameOver = true;
	if ((headX > width - 1) && (barriers == false)) headX=0;
	if ((headX < 0) && (barriers == false)) headX = width-1;
	if ((headY > height - 1) && (barriers == false)) headY = 0;
	if ((headY < 0) && (barriers == false)) headY = height - 1;
	for (int i = 0; i < tailLength; i++)
		if ((tailX[i] == headX) && (tailY[i] == headY)) gameOver = true;
	if ((headX == foodX) && (headY == foodY))
	{
		score++;
		if (score > highscore) highscore++;
		foodX = rand() % width;
		foodY = rand() % height;
		for (int i=0;i<tailLength;i++)
			if ((tailX[i] == foodX) && (tailY[i] == foodY))
			{
				foodX = rand() % width;
				foodY = rand() % height;
			}
		tailLength++;
	}

}

int main()
{
	int w1,w2;
	while (!started)
	{
		launch();
	}
	setup();
	while (!gameOver)
	{
		graphics();
		controls();
		logic();
		Sleep(10);
	}
	system("cls");

	if ((score > -1) && (score < 10)) w1 = 14;
	if ((score > 9) && (score < 100)) w1 = 13;
	if ((score > 99) && (score < 1000)) w1 = 12;

	if ((highscore > -1) && (highscore < 10)) w2 = 15;
	if ((highscore > 9) && (highscore < 100)) w2 = 14;
	if ((highscore > 99) && (highscore < 1000)) w2 = 13;

	for (int i = 0; i < 5; i++)
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
		cout << ("GAME OVER")<<setw(17);
		colorText(1);
		cout << "#" << endl;

		cout << "#" << setw(24) << "your score : ";
		colorText(3);
		cout << score << setw(w1);
		colorText(1);
		cout << "#" << endl;

		cout << "#" << setw(23) << "Highscore : ";
		colorText(3);
		cout << highscore << setw(w2);
		colorText(1);
		cout << "#" << endl;
		
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
	started = false;
	main();
}