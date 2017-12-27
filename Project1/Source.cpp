#include"Snake.h"
#include<windows.h>
#include<conio.h>


void GotoXY(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x,y };
	SetConsoleCursorPosition(hStdout, position);
}
void DeleteChoose(int n) {
	for (int i = 0; i < 23; i++) {
		GotoXY(10 + i, 4 + 2 * n);
		std::cout << " ";
		GotoXY(10 + i, 6 + 2 * n);
		std::cout << " ";
	}
}
void DisplaySelect(int n) {
	for (int i = 0; i < 23; i++) {
		GotoXY(10 + i, 4 +  2*n);
		std::cout << "_";
		GotoXY(10 + i, 6 + 2*n);
		std::cout << "_";
	}
}
void MoveUp(int choose) {
	DeleteChoose(choose);
	DisplaySelect(choose - 1);
	//choose--;
	_getch();
}
void MoveDown(int choose) {
	DeleteChoose(choose);
	DisplaySelect(choose + 1);
	//choose++;
	_getch();
}
void Menu(int choose) {
	GotoXY(10, 3);
	std::cout << "==========MENU=========" << std::endl;
	GotoXY(17, 5);
	std::cout << "New game" << std::endl;
	GotoXY(16, 7);
	std::cout << "How to play" << std::endl;
	GotoXY(18, 9);
	std::cout << "Exit" << std::endl;
	DisplaySelect(choose);
}
void HowToPlay() {
	GotoXY(45, 5);
	std::cout << "Use the arrow keys to control the snake to eat the fruit !";
	GotoXY(60, 6);
	std::cout << "Don't use mouse ! :D";
}
void Choose() {
	bool kt = true;
	int choose = 0;
	Snake ran1;
	while (kt) {
		if (GetAsyncKeyState(VK_UP) != 0 && choose > 0) {
			MoveUp(choose);
			choose--;
		}if (GetAsyncKeyState(VK_DOWN) != 0 && choose < 2) {
			MoveDown(choose);
			choose++;
		}
		if (GetAsyncKeyState(VK_RETURN) && choose == 1) {
			system("cls");
			Menu(choose);
			HowToPlay();
		}
		if (GetAsyncKeyState(VK_RETURN) && choose == 2) {
			kt = false;
			GotoXY(8, 15);
		}
		if (GetAsyncKeyState(VK_RETURN) && choose == 0) {
			system("cls");
			Menu(choose);
			ran1.Start();
			ran1.Maps();
			ran1.Move();
		}
		_getch();
	}
}
//hàm ẩn con trỏ trong màn hình console
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int main() {
	Nocursortype();
	Menu(0);
	Choose();	
	system("pause");
}