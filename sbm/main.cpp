#include "pch.h"

using namespace std;

inline bool operator==(COORD a, COORD b) {
	return (a.X == b.X) && (a.Y == b.Y);
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	uint period = 333;
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ccinf;
	ccinf.bVisible = FALSE;
	ccinf.dwSize = 100;
	queue<COORD> vive;
	SetConsoleCursorInfo(hOut, &ccinf);
	bool ate = false;
	bool upd = false;
	char imp = 0;
	uint dir = 0;
	int diffx = 0;
	int diffy = 0;
	auto startt = chrono::steady_clock::now();
	uint score = 0;
	COORD point{ 16, 8 };
	COORD playtimes{ 44, 7 };
	COORD scorepts{44, 8};
	COORD size{ 34, 17 };
	vector<COORD> apples;
	vector<COORD> taken;
	taken.reserve(450);
	apples.reserve(3);
	vive.push(point);
	taken.push_back(point);
	chrono::steady_clock::time_point spent;
	srand(time(0));
	printf("%s",    "[][][][][][][][][][][][][][][][][]\n" // 30x15
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []   Time:  0\n"
					"[]              e               []   Score: 0\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[]                              []\n"
					"[][][][][][][][][][][][][][][][][]\n");
	while (1) {
		spent = chrono::steady_clock::now();
		if (_kbhit()) {
			imp = (char)_getch();
			while (_kbhit()) (void)_getch();
			if (imp) {
				switch (imp)
				{
				case 'a':
				case 'ф':
					if (dir != 1 && dir != 3) {
						dir = 1;
						upd = true;
					}
					break;
				case 'w':
				case 'ц':
					if (dir != 2 && dir != 4) {
						dir = 2;
						upd = true;
					}
					break;
				case 'd':
				case 'в':
					if (dir != 3 && dir != 1) {
						dir = 3;
						upd = true;
					}
					break;
				case 's':
				case 'ы':
				case 'і':
					if (dir != 4 && dir != 2) {
						dir = 4;
						upd = true;
					}
					break;
				default:
					SetConsoleCursorPosition(hOut, COORD{ size.X + rand() % 60, size.Y + rand() % 40 });
					cout << "eblan?";
					break;
				}
				imp = 0;
			}
		}

		if (dir) {
			if (upd) {
				switch (dir)
				{
				case 1:
					diffx = -1;
					diffy = 0;
					break;
				case 2:
					diffx = 0;
					diffy = -1;
					break;
				case 3:
					diffx = 1;
					diffy = 0;
					break;
				case 4:
					diffx = 0;
					diffy = 1;
					break;
				}
			}
			upd = false;
			SetConsoleCursorPosition(hOut, point);
			printf("o");
			point.X += diffx;
			point.Y += diffy;
			if (point.X < 2 || point.X > 31 || point.Y < 1 || point.Y > 15)
				break;

			SetConsoleCursorPosition(hOut, point);
			auto it = find(apples.begin(), apples.end(), point);
			if (it != apples.end()) {
				apples.erase(it);
				taken.erase(find(taken.begin(), taken.end(), point));
				ate = true;
				score++;
			}
			else if (find(taken.begin(), taken.end(), point) != taken.end())
				break;
			vive.push(point);
			taken.push_back(point);
			printf("e");
			if (!ate) {
				auto dest = vive.front(); vive.pop();
				taken.erase(find(taken.begin(), taken.end(), dest));
				SetConsoleCursorPosition(hOut, dest);
				printf(" ");
			}
			else
				ate = false;

			if (rand() % 100 < ((3 - apples.size())) * 5) {
				auto tmp = COORD{ 2 + rand() % 30, 1 + rand() % 15 };
				while (find(taken.begin(), taken.end(), tmp) != taken.end()) tmp = COORD{ 2 + rand() % 30, 1 + rand() % 15 };
				apples.push_back(tmp);
				taken.push_back(tmp);
				SetConsoleCursorPosition(hOut, tmp);
				printf("a");
			}
		}
		auto tp1 = chrono::steady_clock::now() - startt;
		SetConsoleCursorPosition(hOut, playtimes);
		printf("%u", (uint)chrono::duration_cast<chrono::seconds>(tp1).count());
		SetConsoleCursorPosition(hOut, scorepts);
		printf("%u", score);
		this_thread::sleep_for(chrono::milliseconds(period - chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - spent).count()));
	}
	SetConsoleCursorPosition(hOut, size);
	cout << "gg";
}