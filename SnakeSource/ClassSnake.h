#pragma once
struct Located
{
	int wL;
	int hL;
	int ID;
};
class ClassSnake
{
public:
	ClassSnake(int w,int h);
	~ClassSnake();
	int  TailIs();
	bool RunSnake(int w, int h);
	bool AddTail(int w, int h);
	bool CheckFood();
	bool IsElementS(int w, int h);
	Located isWhere[100]; // data stored where food have been eaten
	int amoutOfFood; // food still in snake's stomach
	bool isEat ;
	Located elementS[200];
	//use it find the last tail where before go to new location
	Located oldTailLocatedS; 
	//use it update last location before move new place
	void UpdateOldTailS();
private:
	//L : location
	int HEAD = 0;
	int TAIL = 0;
	
};
