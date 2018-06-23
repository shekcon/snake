#ifdef SNAKE_H
#define SNAKE_H
#endif // SNAKE_H

#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
enum BodySnake{HEAD,BODY,TAIL,NONE};
//define function
void RunSnack();
void Inital();
void Draw();
void InputKey();
void Logic();
void IsDefeat();
void ShowMenu();

// define variable type
struct Location
{
	int w;
	int h;
	BodySnake snakeApart;
};
struct Flag
{
	bool eat;
	Location where;
	int time[10];
};
struct StructuredSnake {
	Location elementSnake[50];
	Flag isEat;
	void AddElement(StructuredSnake &Snake, int i, int w, int h,BodySnake apart) {
		Snake.elementSnake[i].w = w;
		Snake.elementSnake[i].h =h;
		Snake.elementSnake[i].snakeApart = apart;
	}
	void AddElement(StructuredSnake &Snake,int i, int w, int h) {
		Snake.elementSnake[i].w = w;
		Snake.elementSnake[i].h = h;
		Snake.elementSnake[i].snakeApart = BODY;
	}
	bool IsTail(StructuredSnake Snake, int i) {
		return Snake.elementSnake[i].snakeApart == TAIL;
	}
	void AddWhere(StructuredSnake &Snake, int w, int h) {
		Snake.isEat.where.w = w;
		Snake.isEat.where.h = h;
		Snake.isEat.eat = true;
		Snake.isEat.time= Snake.NumberTail(Snake);
	}
	BodySnake IsElementSnake(StructuredSnake Snake, int checkw, int checkh) {
		for (int i = 0; i < 50; ++i)
		{
			if (Snake.elementSnake[i].w == checkw && Snake.elementSnake[i].h == checkh)
				return Snake.elementSnake[i].snakeApart;
			if (Snake.elementSnake[i].snakeApart == TAIL)
			{
				break;
			}
		}
		return NONE;
	}
	int NumberTail(StructuredSnake Snake) {
		for (int i = 0; i < 50; ++i)
		{
			if (Snake.elementSnake[i].snakeApart == TAIL)
			{
				return i;
			}
		}
	}
	void RunSnake(StructuredSnake &Snake,int Tail) {
		for (int i = Tail; i > 0; --i)
		{
			Snake.elementSnake[i].w = Snake.elementSnake[i-1].w;
			Snake.elementSnake[i].h = Snake.elementSnake[i-1].h;
		}
	}
	void RenewHeadSnake(StructuredSnake &Snake,Location place) {
		Snake.elementSnake[0].w = place.w;
		Snake.elementSnake[0].h = place.h;
	}
	void ChangeTail(StructuredSnake &Snake, int numberSnake) {
		Snake.elementSnake[numberSnake].snakeApart = BODY;
	}
};

//define attribute
int numberSnake = 2;
bool statusGame = true;
const int width = 30;
const int height = 15;
int wLocatedSnack, hLocatedSnack, wLocatedFood, hLocatedFood;
Direction dirSnake = STOP;
StructuredSnake Snake;
int ponitOfScore = 0;
int numberOfFood = 0;
void ShowMenu() {

}

void RunSnack() {
	do
	{
		Draw();
		InputKey();
		Logic();
		_sleep(200);
	} while (statusGame);
}

void Inital() {
	wLocatedSnack = width / 2;
	hLocatedSnack = height / 2;	
	Snake.AddElement(Snake, 0, wLocatedSnack, hLocatedSnack, HEAD);
	Snake.AddElement(Snake, 1, wLocatedSnack+1, hLocatedSnack);
	Snake.AddElement(Snake, 2, wLocatedSnack+2, hLocatedSnack, TAIL);
	Snake.isEat.eat = false;
	wLocatedFood = rand() % width;
	hLocatedFood = rand() % height;

}

void Draw() {
	system("cls");
	cout << endl << endl <<"\t\t Score:"<<ponitOfScore<< endl << endl;
	for (int i = 0; i < width + 1; i++)
	{
		if (0 == i) { cout << "\t"; }cout << "*";
	}
	cout << endl;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (0 == j || width - 1 == j) {
				if (0 == j) cout << "\t";
				cout << "*";

			}
			BodySnake result = Snake.IsElementSnake(Snake,j,i);
			if (!(result==NONE))
			{
				if(result==HEAD)cout << "<";
				else cout << "-";
			}
			else
				if (hLocatedFood == i &&wLocatedFood == j)
				{
					cout << "@";
				}
				else cout << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++)
	{
		if (0 == i) { cout << "\t"; }
		cout << "*";
	}

}

void InputKey() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dirSnake = LEFT;
			break;

		case 'd':
			dirSnake = RIGHT;
			break;

		case 'w':
			dirSnake = UP;
			break;

		case 's':
			dirSnake = DOWN;
			break;

		case 'p':
			dirSnake = STOP;
			break;
		case 27://ESC
			statusGame = false;
			break;
		default:

			break;
		}
	}

}

void Logic() {
	Location newplace = {wLocatedSnack,hLocatedSnack};
	switch (dirSnake)
	{
	case STOP:

		break;

	case LEFT:
		--wLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		Snake.RunSnake(Snake, Snake.NumberTail(Snake));
		Snake.RenewHeadSnake(Snake, newplace);

		break;

	case RIGHT:
		++wLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		Snake.RunSnake(Snake, Snake.NumberTail(Snake));
		Snake.RenewHeadSnake(Snake, newplace);
		break;

	case UP:
		--hLocatedSnack; 
		newplace = { wLocatedSnack,hLocatedSnack };
		Snake.RunSnake(Snake, Snake.NumberTail(Snake));
		Snake.RenewHeadSnake(Snake, newplace);
		break;

	case DOWN:
		++hLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		Snake.RunSnake(Snake, Snake.NumberTail(Snake));
		Snake.RenewHeadSnake(Snake, newplace);
		break;

	default:
		break;
	}
	/*if (hLocatedSnack<=0 || hLocatedSnack > height || wLocatedSnack <=0 || wLocatedSnack >width)
	{
		statusGame = false;
	}*/
	if (newplace.w == wLocatedFood && newplace.h == hLocatedFood)
	{
		ponitOfScore += 1;
		wLocatedFood = rand() % width;
		hLocatedFood = rand() % height;
		Snake.isEat.eat = true;
		Snake.AddWhere(Snake, newplace.w, newplace.h);
		numberOfFood++;
	}
	if (Snake.isEat.eat)
	{
		--Snake.isEat.time[0];
	}
	if (Snake.isEat.eat && Snake.isEat.time == 0)
	{
		Snake.ChangeTail(Snake, Snake.NumberTail(Snake));
		Snake.AddElement(Snake, ++numberSnake, Snake.isEat.where.w, Snake.isEat.where.h, TAIL);
		Snake.isEat.eat = false;
		--numberOfFood;
	}
}

void IsDefeat() {
	cout << "Game Over";
}


