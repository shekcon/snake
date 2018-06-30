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
	ClassSnake();
	ClassSnake(int w,int h);//create head of Snake
	~ClassSnake();
	int  TailIs();			// return located of tail in Snake 
	bool RunSnake(int w, int h); // move snake
	bool AddTail(int w, int h);// add tail of snake
	bool CheckFood();		//check snake have eaten yet ? yes: wait until where is eaten and add more element Snake
	bool IsElementS(int w, int h);
	Located isWhere[100]; // data stored where food have been eaten
	int amoutOfFood; // food still in snake's stomach
	bool isEat ;// check snake have eaten yet
	Located elementS[200];// location of each element of Snake
	
	//use it find the last tail where before go to new location
	Located oldTailLocatedS; 
	//use it update last location before move new place
	void UpdateOldTailS();
private:
	int HEAD = 0;
	int TAIL = 0;
};
