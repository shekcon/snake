#include "ClassSnake.h"

ClassSnake::ClassSnake(int w,int h)
{
	elementS[HEAD].wL = w;
	elementS[HEAD].hL = h;
}

ClassSnake::~ClassSnake()
{
}

int ClassSnake::TailIs()
{
	
	return TAIL;
}

bool ClassSnake::RunSnake(int w, int h)
{
	if (!IsElementS(w,h))
	{
		UpdateOldTailS();
		for (int i = TAIL; i > 0; --i)
		{
			elementS[i].wL = elementS[i - 1].wL;
			elementS[i].hL = elementS[i - 1].hL;
		}
		elementS[HEAD].wL = w;
		elementS[HEAD].hL = h;
		return true;
	}
	return false;
	
}

bool ClassSnake::AddTail(int w,int h)
{
	
	if (!(IsElementS(w,h)))
	{
		++TAIL;
		elementS[TAIL].wL = w;
		elementS[TAIL].hL = h;
		return true;
	}
	return false;
}

bool ClassSnake::CheckFood()
{
	
	if (amoutOfFood != 0) {
		for (int i = 1; i <= amoutOfFood; ++i)
		{
			--isWhere[i].ID;
		}
	}
	if (isEat&&isWhere[1].ID==0)
	{
		for (int i = 1; i < amoutOfFood; ++i)
		{
			isWhere[i].ID = isWhere[i + 1].ID;
		}
		--amoutOfFood;
		if (amoutOfFood==0)
		{
			isEat = false;
		}
		return true;
	}
	return false;
	
}

bool ClassSnake::IsElementS(int w, int h) {
	for (int i = 0; i <= TAIL; ++i)
	{
		if (elementS[i].wL == w && elementS[i].hL==h) {
			return true;
		}
	}
	return false;
}

void ClassSnake::UpdateOldTailS()
{
	oldTailLocatedS.wL = elementS[TAIL].wL;
	oldTailLocatedS.hL = elementS[TAIL].hL;
}

