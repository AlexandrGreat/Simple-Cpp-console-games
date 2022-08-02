#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;
int menuSelect = 1, up = 0, low = 0, num = 0, sym = 0, mode;
bool numTog = false, symTog = false, upTog = false, lowTog = false;
char upArray[27] = { "A" "B" "C" "D" "E" "F" "G" "H" "I" "J" "K" "L" "M" "N" "O" "P" "Q" "R" "S" "T" "U" "V" "W" "X" "Y" "Z"};
char lowArray[27] = { "a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z" };
char numArray[11] = { "1" "2" "3" "4" "5" "6" "7" "8" "9" "0" };
char symArray[17] = { "!" "@" "#" "$" "%" "^" "&" "*" "(" ")" "?" "/" "[" "]" "{" "}"};
string passLength = "", password = "";
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void colorText(int k)
{
	switch (k)
	{
	case(1):SetConsoleTextAttribute(handle, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)); break;
	case(2):SetConsoleTextAttribute(handle, (FOREGROUND_RED)); break;
	case(3):SetConsoleTextAttribute(handle, (FOREGROUND_GREEN)); break;
	case(4):SetConsoleTextAttribute(handle, 23); break;
	}
}

void menuControls()
{
	if (_kbhit)
		switch (_getch())
		{
		case'w':if (menuSelect != 1) menuSelect--; break;
		case's':if (menuSelect != 7) menuSelect++; break;
		case '1':if (menuSelect == 1) passLength += "1"; break;
		case '2':if (menuSelect == 1) passLength += "2"; break;
		case '3':if (menuSelect == 1) passLength += "3"; break;
		case '4':if (menuSelect == 1) passLength += "4"; break;
		case '5':if (menuSelect == 1) passLength += "5"; break;
		case '6':if (menuSelect == 1) passLength += "6"; break;
		case '7':if (menuSelect == 1) passLength += "7"; break;
		case '8':if (menuSelect == 1) passLength += "8"; break;
		case '9':if (menuSelect == 1) passLength += "9"; break;
		case '0':if ((menuSelect == 1) && (passLength != "")) passLength += "0"; break;
		case 'e':
			if (menuSelect == 2) passLength = "";
			if ((menuSelect == 3) && (!upTog)) { up = 1; }
			if ((menuSelect == 4) && (!lowTog)) { low = 1; }
			if ((menuSelect == 5) && (!numTog)) { num = 1; }
			if ((menuSelect == 6) && (!symTog)) { sym = 1; }
			
			if ((menuSelect == 3) && (upTog)) { up = 0; }
			if ((menuSelect == 4) && (lowTog)) { low = 0; }
			if ((menuSelect == 5) && (numTog)) { num = 0; }
			if ((menuSelect == 6) && (symTog)) { sym = 0; }

			if ((menuSelect == 7) && (passLength != ""))
			{
				srand(time(NULL));
				password = "";
				for (int i = 0; i < stoi(passLength); i++)
				{
					int randArray = (rand() % 4)+1;
					int ready = 0;
					while (ready==0) 
					{
						if (((randArray == 1) && (up == 0)) || ((randArray == 2) && (low == 0)) || ((randArray == 3) && (num == 0)) || ((randArray == 4) && (sym == 0))) { randArray = (rand() % 4) + 1; }
						if ((randArray == 1) && (up == 1)) { ready = 1; }
						if ((randArray == 2) && (low == 1)) { ready = 2; }
						if ((randArray == 3) && (num == 1)) { ready = 3; }
						if ((randArray == 4) && (sym == 1)) { ready = 4; }
					}
					if (ready == 1) { int j = rand() % 26;  password += upArray[j]; }
					if (ready == 2) { int j = rand() % 26;  password += lowArray[j]; }
					if (ready == 3) { int j = rand() % 10;  password += numArray[j]; }
					if (ready == 4) { int j = rand() % 16;  password += symArray[j]; }
				}
			}
			break;
		}
}

void menuCheck()
{
	if (up == 1)
	{
		upTog = true;
	}
	else upTog = false;
	if (low == 1)
	{
		lowTog = true;
	}
	else lowTog = false;
	if (num == 1)
	{
		numTog = true;
	}
	else numTog = false;
	if (sym == 1)
	{
		symTog = true;
	}
	else symTog = false;
}

void graphics()
{
	colorText(3);
	cout << "------";
	colorText(2);
	cout << "PASSWORD GENERATOR";
	colorText(3);
	cout << "------" << endl << endl << endl;
	colorText(1);
	if (menuSelect == 1) colorText(4);
	cout << "Passwod length (input here):";
	colorText(1);
	cout << " " << passLength << endl;
	if (menuSelect == 2) colorText(4);
	cout << "Clear length"<<endl;
	colorText(1);
	if (menuSelect == 3) colorText(4);
	cout << "Capital letters"; 
	if (up == 1) { colorText(3); cout << "         Enabled" << endl; }
	if (up == 0) { colorText(2); cout << "         Disabled" << endl; }
	colorText(1);
	if (menuSelect == 4) colorText(4);
	cout << "Lower case letters";
	if (low == 1) { colorText(3); cout << "      Enabled" << endl; }
	if (low == 0) { colorText(2); cout << "      Disabled" << endl; }
	colorText(1);
	if (menuSelect == 5) colorText(4);
	cout << "Numbers";
	if (num == 1) { colorText(3); cout << "                 Enabled" << endl; }
	if (num == 0) { colorText(2); cout << "                 Disabled" << endl; }
	colorText(1);
	if (menuSelect == 6) colorText(4);
	cout << "Symbols";
	if (sym == 1) { colorText(3); cout << "                 Enabled" << endl; }
	if (sym == 0) { colorText(2); cout << "                 Disabled" << endl; }
	colorText(1);
	cout << endl;
	cout << "     ";
	if (menuSelect == 7) colorText(4);
	cout << "Generate your password"<<endl;
	colorText(3);
	cout << endl;
	cout << "YOUR PASSWORD: ";
	colorText(1);
	cout << password << endl << endl;
	colorText(3);
	cout << "------------------------------";
}

int main()
{
	graphics();
	menuControls();
	menuCheck();
	system("cls");
	main();
}