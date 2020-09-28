#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>

using namespace std;

void gotoxy(int x, int y) {
	COORD position = { x,y };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(out, &cursorInfo);
}

class Map {
private:
	class Unit {
	public:
		int x, y;
	};

	int height, width;
	string** mat;
	vector<Unit> Units;

public:
	Map(int w, int h) {
		mat = new string * [w];
		for (int i = 0; i < w; i++) {
			mat[i] = new string[h];
		}
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				mat[i][j] = " ";
			}
		}
		height = h;
		width = w;
	}

	void printMap() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
					cout << mat[j][i];
			}
			cout << endl;
		}
	}

	void spawnUnits(int amount) {
		for (int i = 0; i < amount; i++) {
			Unit unit;
			unit.x = rand() % width;
			unit.y = rand() % height;
			if (mat[unit.x][unit.y] == " ") {
				Units.push_back(unit);
				mat[unit.x][unit.y] = "o";
			}
			else {
				i--;
				continue;
			}
		}
	}

	void goLive() {
		int upOrDown[2] = { -1, 1 };
		int leftOrRight[2] = { 0, 1 };

		printMap();

		for (int i = 0; i < 2;) {
			for (int j = 0; j < Units.size(); j++) {
				int whereToGo = upOrDown[rand() % 2];
				int axis = leftOrRight[rand() % 2];;
				if (axis == 0 and Units[j].x + whereToGo < width and Units[j].x + whereToGo >= 0 and mat[Units[j].x + whereToGo][Units[j].y] != "o ") {
					gotoxy(Units[j].x , Units[j].y);
					printf("\b ");
					gotoxy(Units[j].x , Units[j].y);
					cout << " ";
					gotoxy((Units[j].x + whereToGo) , Units[j].y);
					printf("\b ");
					gotoxy((Units[j].x + whereToGo) , Units[j].y);
					cout << "o";
					//Sleep(100);
					mat[Units[j].x][Units[j].y] = " ";
					mat[Units[j].x + whereToGo][Units[j].y] = "o";
					Units[j].x += whereToGo;
				}
				if (axis == 1 and Units[j].y + whereToGo < height and Units[j].y + whereToGo >= 0 and mat[Units[j].x][Units[j].y + whereToGo] != "o ") {
					gotoxy(Units[j].x , Units[j].y);
					printf("\b ");
					gotoxy(Units[j].x , Units[j].y);
					cout << " ";
					gotoxy(Units[j].x , Units[j].y + whereToGo);
					printf("\b ");
					gotoxy(Units[j].x , Units[j].y + whereToGo);
					cout << "o";
					//Sleep(100);
					mat[Units[j].x][Units[j].y] = " ";
					mat[Units[j].x][Units[j].y + whereToGo] = "o";
					Units[j].y += whereToGo;
				}
			}
			Sleep(100);
			ShowConsoleCursor(false);
		}
	}

};

int main()
{
	srand(time(NULL));

	_COORD coordinates;
	coordinates.X = 1000;
	coordinates.Y = 1000;

	if (0 == SetConsoleScreenBufferSize(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coordinates
	))
	{
		return -1;
	}

	Map map(950, 210);
	map.spawnUnits(9999);
	map.goLive();
}