#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;
int cell[17];
int selected = 0, stage = 1, act, lastSelected;
string x1, x2;
double rez;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

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

void controls()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': if ((selected == 1) || (selected == 2) || (selected == 3) || (selected == 5) || (selected == 6) || (selected == 7) || (selected == 9) || (selected == 10) || (selected == 11) || (selected == 13) || (selected == 14) || (selected == 15)) selected--; break;
		case 'd': if ((selected == 0) || (selected == 1) || (selected == 2) || (selected == 4) || (selected == 5) || (selected == 6) || (selected == 8) || (selected == 9) || (selected == 10) || (selected == 12) || (selected == 13) || (selected == 14)) selected++; break;
		case 'w': 
			if ((selected > 3)&&(selected<16)) selected -= 4; 
			if (selected == 16) selected = lastSelected; break;
		case 's': 
			if ((selected >= 12) && (selected != 16)) { lastSelected = selected; selected += 16 - selected; }
			if (selected < 12) selected += 4; break;
		case 'e':
			if ((stage == 4) && (selected < 16)) { stage = 1; x1 = ""; x2 = ""; act = 0; }
			
			if ((stage == 1) && (selected == 0)) x1 += to_string(1);
			if ((stage == 1) && (selected == 1)) x1 += to_string(2);
			if ((stage == 1) && (selected == 2)) x1 += to_string(3);
			if ((stage == 1) && (selected == 4)) x1 += to_string(4);
			if ((stage == 1) && (selected == 5)) x1 += to_string(5);
			if ((stage == 1) && (selected == 6)) x1 += to_string(6);
			if ((stage == 1) && (selected == 8)) x1 += to_string(7);
			if ((stage == 1) && (selected == 9)) x1 += to_string(8);
			if ((stage == 1) && (selected == 10)) x1 += to_string(9);
			if ((stage == 1) && (selected == 13)) x1 += to_string(0);

			if ((stage < 3) && (selected == 3) && (x1 != "")) { act = 1; stage = 2; }
			if ((stage < 3) && (selected == 7) && (x1 != "")) { act = 2; stage = 2; }
			if ((stage < 3) && (selected == 11) && (x1 != "")) { act = 3; stage = 2; }
			if ((stage < 3) && (selected == 15) && (x1 != "")) { act = 4; stage = 2; }
			if ((stage < 3) && (selected == 14) && (x1 != "")) { rez = sqrt(stoi(x1)); stage = 4; }

			if ((stage > 1) && (selected == 0)) { stage = 3; x2 += to_string(1); }
			if ((stage > 1) && (selected == 1)) { stage = 3; x2 += to_string(2); }
			if ((stage > 1) && (selected == 2)) { stage = 3; x2 += to_string(3); }
			if ((stage > 1) && (selected == 4)) { stage = 3; x2 += to_string(4); }
			if ((stage > 1) && (selected == 5)) { stage = 3; x2 += to_string(5); }
			if ((stage > 1) && (selected == 6)) { stage = 3; x2 += to_string(6); }
			if ((stage > 1) && (selected == 8)) { stage = 3; x2 += to_string(7); }
			if ((stage > 1) && (selected == 9)) { stage = 3; x2 += to_string(8); }
			if ((stage > 1) && (selected == 10)) { stage = 3; x2 += to_string(9); }
			if ((stage > 1) && (selected == 13)) { stage = 3; x2 += to_string(0); }

			if ((stage == 3) && (selected == 16))
			{
				if (act == 1) { stage = 4; rez = stoi(x1) + stoi(x2); }
				if (act == 2) { stage = 4; rez = stoi(x1) - stoi(x2); }
				if (act == 3) { stage = 4; rez = stoi(x1) * stoi(x2); }
				if (act == 4) { stage = 4; rez = stoi(x1)*1.0 / stoi(x2); }
			}

			if (selected == 12) { stage = 1; x1 = ""; x2 = ""; }
			break;
		} 
	}
}

void cellCheck(int c)
{
	//not selected
	if ((c == 0) && (selected != 0)) { colorText(3); cout << "1"; colorText(1); }
	if ((c == 1) && (selected != 1)) { colorText(3); cout << "2"; colorText(1); }
	if ((c == 2) && (selected != 2)) { colorText(3); cout << "3"; colorText(1); }
	if ((c == 3) && (selected != 3)) { colorText(2); cout << "+"; colorText(1); }
	if ((c == 4) && (selected != 4)) { colorText(3); cout << "4"; colorText(1); }
	if ((c == 5) && (selected != 5)) { colorText(3); cout << "5"; colorText(1); }
	if ((c == 6) && (selected != 6)) { colorText(3); cout << "6"; colorText(1); }
	if ((c == 7) && (selected != 7)) { colorText(2); cout << "-"; colorText(1); }
	if ((c == 8) && (selected != 8)) { colorText(3); cout << "7"; colorText(1); }
	if ((c == 9) && (selected != 9)) { colorText(3); cout << "8"; colorText(1); }
	if ((c == 10) && (selected != 10)) { colorText(3); cout << "9"; colorText(1); }
	if ((c == 11) && (selected != 11)) { colorText(2); cout << "X"; colorText(1); }
	if ((c == 12) && (selected != 12)) { colorText(2); cout << "C"; colorText(1); }
	if ((c == 13) && (selected != 13)) { colorText(3); cout << "0"; colorText(1); }
	if ((c == 14) && (selected != 14)) { colorText(2); cout << "S"; colorText(1); }
	if ((c == 15) && (selected != 15)) { colorText(2); cout << "/"; colorText(1); }
	if ((c == 16) && (selected != 16)) { colorText(1); cout << "="; }
	//selected
	if ((c == 0) && (selected == 0)) { colorText(5); cout << "1"; colorText(1); }
	if ((c == 1) && (selected == 1)) { colorText(5); cout << "2"; colorText(1); }
	if ((c == 2) && (selected == 2)) { colorText(5); cout << "3"; colorText(1); }
	if ((c == 3) && (selected == 3)) { colorText(5); cout << "+"; colorText(1); }
	if ((c == 4) && (selected == 4)) { colorText(5); cout << "4"; colorText(1); }
	if ((c == 5) && (selected == 5)) { colorText(5); cout << "5"; colorText(1); }
	if ((c == 6) && (selected == 6)) { colorText(5); cout << "6"; colorText(1); }
	if ((c == 7) && (selected == 7)) { colorText(5); cout << "-"; colorText(1); }
	if ((c == 8) && (selected == 8)) { colorText(5); cout << "7"; colorText(1); }
	if ((c == 9) && (selected == 9)) { colorText(5); cout << "8"; colorText(1); }
	if ((c == 10) && (selected == 10)) { colorText(5); cout << "9"; colorText(1); }
	if ((c == 11) && (selected == 11)) { colorText(5); cout << "X"; colorText(1); }
	if ((c == 12) && (selected == 12)) { colorText(5); cout << "C"; colorText(1); }
	if ((c == 13) && (selected == 13)) { colorText(5); cout << "0"; colorText(1); }
	if ((c == 14) && (selected == 14)) { colorText(5); cout << "S"; colorText(1); }
	if ((c == 15) && (selected == 15)) { colorText(5); cout << "/"; colorText(1); }
	if ((c == 16) && (selected == 16)) { colorText(5); cout << "="; colorText(1); }
}

void line(int l)
{
	switch (l)
	{
	case(1):for (int i = 0; i < 17; i++) { colorText(1); cout << "#"; }; cout << endl; break;
	case(2):for (int i = 0; i < 4; i++) { cout << "#"; for (int j = 0; j < 3; j++) { cout << " "; } }; cout << "#" << endl; break;
	case(3):for (int i = 0; i < 4; i++) { cout << "#" << " "; cellCheck(i); cout << " "; }  cout << "#" << endl; break;
	case(4):for (int i = 0; i < 4; i++) { cout << "#" << " "; cellCheck(i + 4); cout << " "; }  cout << "#" << endl; break;
	case(5):for (int i = 0; i < 4; i++) { cout << "#" << " "; cellCheck(i + 8); cout << " "; }  cout << "#" << endl; break;
	case(6):for (int i = 0; i < 4; i++) { cout << "#" << " "; cellCheck(i + 12); cout << " "; }  cout << "#" << endl; break;
	}
}

void graphics()
{
	colorText(3);
	cout << "---";
	colorText(2);
	cout << "CALCULATOR";
	colorText(3);
	cout << "---" << endl << endl;
	colorText(1);
	if ((stage < 3) && (x1 == "")) cout << "0" << endl;
	if ((stage < 3) && (x1 != "")) cout << x1 << endl;
	if (stage == 3) cout << x2 << endl;
	if (stage == 4) cout << rez << endl;
	colorText(3);
	cout << endl << "----------------" << endl;
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
	line(2);
	line(6);
	line(2);
	line(1);
	cout << "#               #" << endl;
	cout << "#       "; cellCheck(16); cout << "       #" << endl;
	cout << "#               #" << endl;
	line(1);
}

int main()
{
	controls();
	graphics();
	Sleep(10);
	system("cls");
	main();
}