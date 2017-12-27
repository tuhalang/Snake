#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<time.h>

struct ToaDo {
	short x, y;
};

#define left 1
#define right 2
#define up 3
#define down 4

class Snake
{
private:
	const short height=15;
	const short width = 50;
	ToaDo head, fruit;
	ToaDo snack[100];
	int lengthSnack=1;
	int control  =right;
	int mark=0;
	double timeWait = 0.2;
public:
	void Maps();
	void Move();
	int Control();
	bool FinishGame();
	void AppearFruit();
	void Wait(double);
	void Start();
	Snake();
	~Snake();
};

