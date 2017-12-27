#include "Snake.h"
//lấy tọa độ x hiện tại
int WhereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//lấy tọa độ y hiện tại
int WhereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//di chuyển con tro tới tọa độ (x,y)
void Gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x,y };
	SetConsoleCursorPosition(hStdout, position);
}
//xóa một vị trí
void Delete(int x, int y) {
	Gotoxy(x, y);
	std::cout << " ";
}
//thực hiện trễ t giây
void Snake::Wait(double seconds)
{
	clock_t ew;
	ew = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < ew) {}
}
//bản đồ
void Snake::Maps() {
	for (short i = 0; i < height; i++) {
		Gotoxy(46, i + 1);
		std::cout << "#";
		Gotoxy(45+width+1, i + 1);
		std::cout << "#";
	}
	for (short i = 45; i < 45+width; i++) {
		Gotoxy(i + 2, 1);
		std::cout << "#";
		Gotoxy(i + 2, height);
		std::cout << "#";
	}
	Gotoxy(103, 3);
	std::cout << "Mark: "<<mark;
}
//điều khiển rắn
int Snake::Control() {
	if (GetAsyncKeyState(VK_UP) != 0 && control != down) {
		return up;
	}
	if (GetAsyncKeyState(VK_RIGHT) != 0 && control != left) {
		return right;
	}
	if (GetAsyncKeyState(VK_LEFT) != 0 && control != right) {
		return left;
	}
	if (GetAsyncKeyState(VK_DOWN) != 0 && control != up) {
		return down;
	}
	return control;
}
//kiểm tra kết thúc game
bool Snake::FinishGame() {
	for (int i = 0; i < height; i++) {
		if (snack[0].x == 46 && snack[0].y == i+1) return true;
		if (snack[0].x == 45 + width+1  && snack[0].y == i+1) return true;
	}
	for (int i = 45; i < 45 + width; i++) {
		if (snack[0].x == i+1 && snack[0].y == 1) return true;
		if (snack[0].x == i+1 && snack[0].y == height) return true;
	}
	for (int i = 1; i < lengthSnack; i++) {
		if (snack[0].x == snack[i].x && snack[0].y == snack[i].y) return true;
	}
	return false;
}
//xuất hiện trái cây
void Snake::AppearFruit() {
	if (snack[0].x == fruit.x && snack[0].y == fruit.y) {
		fruit.x = 46 + rand() % (width - 1);
		fruit.y = 2 + rand() % (height - 2);
		Gotoxy(fruit.x, fruit.y);
		std::cout << "$";
		mark += 10;
		Gotoxy(109, 3);
		std::cout << mark;
		timeWait -= 0.005;
		lengthSnack++;
	}
}
//di chuyển rắn
void Snake::Move() {
	Gotoxy(width / 2, height / 2);
	while (true) {
		control = Control();
		head.x = snack[0].x;
		head.y = snack[0].y;
		Delete(snack[lengthSnack-1].x, snack[lengthSnack-1].y);//xóa đuôi rắn
		AppearFruit();
		//chạy đầu rắn
		switch (control) {
			case right: {
				Gotoxy(head.x+1 , head.y);
				std::cout << "o";
				snack[0].x = head.x + 1;
				snack[0].y = head.y;
				Wait(timeWait);
				break;
			}
			case left: {
				Gotoxy(head.x-1, head.y);
				std::cout << "o";
				snack[0].x = head.x - 1;
				snack[0].y = head.y;
				Wait(timeWait);
				break;
			}
			case up: {
				Gotoxy(head.x, head.y-1);
				std::cout << "o";
				snack[0].x = head.x;
				snack[0].y = head.y-1;
				Wait(timeWait);
				break;
			}
			case down: {
				Gotoxy(head.x, head.y+1);
				std::cout << "o";
				snack[0].x = head.x;
				snack[0].y = head.y+1;
				Wait(timeWait);
				break;
			}
			default: break;
		}
		//chạy đuôi rắn
		for (int i = 1; i < lengthSnack; i++) {
			Gotoxy(head.x, head.y);
			std::cout << "o";
			ToaDo a;
			a.x = head.x;
			a.y = head.y;
			head.x = snack[i].x;
			head.y = snack[i].y;
			snack[i].x = a.x;
			snack[i].y = a.y;
		}
		//kết thúc game
		if (FinishGame()) {
			Gotoxy(65, 20);
			std::cout << "GAME OVER!" << std::endl;
			return;
		}
	}
}
void Snake::Start() {
	lengthSnack = 1;
	timeWait = 0.2;
	head.x = width / 2 + 45;
	head.y = height / 2;
	snack[0].x = head.x;
	snack[0].y = head.y;
	fruit.x = width / 2 - 5 + 45;
	fruit.y = height / 2 + 3;
	Gotoxy(head.x, head.y);
	std::cout << "o";
	Gotoxy(fruit.x, fruit.y);
	std::cout << "$";
}

Snake::Snake()
{
	
}


Snake::~Snake()
{
}
