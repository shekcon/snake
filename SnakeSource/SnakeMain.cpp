
/*define function include
function ShowMenu : options for user choose(map,speed,more changelle) & play & show hight score
function RunSnake : play game & check flag of status game
function Intial   : setup attribute width  height , random food,with snake start at middle of map
function Draw     : create map vs snake + food for user interface with it
function InputKey : recognize command line from user & snake follow order in next function
function Logic	   : will follow order from InputKey & snake go to user's direction
& examine have snake found food yet? Y: score increase N:nothing still play
didn't snake hit map? Y:game over N:still play
score will follow rules of snake game (100 points / 1 food)
function Defeat   : will show your score & Have you had score hight at rank?
Y:save & your'name N:get better again Or maybe dont need
after that show menu again
*/


#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <mmsystem.h>
#include <thread>
#include<fstream>
#include <math.h>

//#include<stdlib.h>
#include "ClassSnake.h"
#pragma comment(lib, "winmm.lib")
//using namespace std;
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // For use of SetConsoleTextAttribute()
#define		wdefault	10
#define		hdefault	6
#define		NEWGAME		8
#define		HIGHSCORE	9
#define		SPEED		10
#define		CONTROL		11
#define		EXIT		12
#define		ARROW		42
#define		PONITER		43
#define		TEXTS		44
#define		BACKGROUND	1
#define		EFFECT		2
#define		NOSOUND		0
//define function
void RunSnack();
void Inital();
void DrawMap();
void Update();
void FindWhere(int i);
void InputKey();
void Logic();
void IsDefeat();
void Welcome();
void CheckRules();
void gotoxy(SHORT x,SHORT y);
void Test();
void ShowLocationS();
void Menu();
void ShowConsoleCursor(bool showFlag);
void SetWindow(int height, int width);
void UpdateScroll();
void RunSound(int numberMusic);
void OldOptionMenu(int oldOption);
void NewOptionMenu(int newOption);
int ChangeColorMenu(bool Mode, int &where);
void TestChangeMenu(std::string textOld, std::string textNew, int locationOld, int locationNew, int whereBegin);
void ChangeSpeed();
void ReadFile();
int intValue(std::string  s);
void WriteFileS();
void FirstRunConfig();
void UpdateFile(int start,int end);
void TestSortScore();
int IsWhereEmpty();
void IsHighScore(std::string namePlayer, int ponit);
void ShowHighScore();
// define variable type

struct WorkFile
{
	std::string text;
	std::string name;
	std::string numberS;
	int number;
};
struct Location
{
	int w;
	int h;
};

//define attribute
WorkFile contextFile[7];
int numberSnake = 2;
bool statusGame ;
const int width = 45;
const int height = 23;
int wLocatedSnack, hLocatedSnack, wLocatedFood, hLocatedFood;
Direction dirSnake ;
ClassSnake Snake= ClassSnake(width / 2 - 1, height / 2 - 1);
int ponitOfScore;
Direction oldDirSnake ;
Location newplace;
bool IsChangeTail ;
int speedOfSnake ;
const int Speed[11] = { 0,400,350,300,250,210,190,150,110,70,30 };
int where = 8;
bool exitGame = false;
bool reloadMenu;
bool playBack = false;
std::string isDefaultWork;
/*  x = width : y = height */ 
void gotoxy(SHORT x,SHORT y )
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}  

void Inital() {
	 
	wLocatedSnack = width / 2 -1;
	hLocatedSnack = height / 2 -1;
	Snake.AddTail(wLocatedSnack+ 1, hLocatedSnack);
	Snake.AddTail(wLocatedSnack + 2, hLocatedSnack);
	Snake.UpdateOldTailS();
	Snake.isEat = false;
	Snake.amoutOfFood = 0;
	dirSnake = STOP;
	oldDirSnake = STOP;
	statusGame = true;
	ponitOfScore = 0;
	do
	{
		srand(static_cast<unsigned int>(time(NULL)));
		wLocatedFood = rand() % (width - 1);
		srand(static_cast<unsigned int>(time(NULL)));
		hLocatedFood = rand() % (height - 1);
	} while (Snake.IsElementS(wLocatedFood, hLocatedFood));

}

void DrawMap() {
	system("cls");
	
	gotoxy(wdefault+width/2 -20,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
	std::cout << "Score:" << ponitOfScore;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(35, 2);
	std::cout << "Coder by : @Shekcon";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	std::cout << std::endl<< std::endl;
	{
		for (int i = 0; i < width + 2; i++)
		{
			if (0 == i) { std::cout << "\t"; }std::cout << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width + 2; ++j)
			{
				if (0 == j || (width + 2) - 1 == j)
				{
					if (0 == j) std::cout << "\t";
					
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
					std::cout << " ";
				}
				else 
				{ SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); 
				std::cout << " ";
				}

			}
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		for (int i = 0; i < width + 2; i++)
		{
			if (0 == i) { std::cout << "\t"; }

			std::cout << " ";
		}
	}
	int resultTail = Snake.TailIs();  // return id allow know TAIL's location
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	for (int i = 0; i <= resultTail; ++i)
	{
		FindWhere(i);   // goto location element i of Snake
			switch (i)
			{
			case 0:
				std::cout << ">";
				break;
			default:
				std::cout << "=";
				break;
			}
	}
	SHORT w = wdefault + wLocatedFood - 1;
	SHORT h = hdefault + hLocatedFood - 1;
	gotoxy(w, h);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
	std::cout << "@";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
}

void Update()
{
	if (dirSnake!=STOP)
	{
		if (!(IsChangeTail))
		{
			SHORT w = wdefault + Snake.oldTailLocatedS.wL -1;
			SHORT h = hdefault + Snake.oldTailLocatedS.hL -1;
			gotoxy(w, h);
			std::cout << " ";
			IsChangeTail = false;
		}
		FindWhere(0); // update HEAD   0 access HEAD
		switch (dirSnake)
		{
		case LEFT:
			std::cout << ">";
			break;

		case RIGHT:
			std::cout << "<";
			break;

		case UP:
			std::cout << "v";
			break;

		case DOWN:
			std::cout << "^";
			break;

		default:
			break;
		}
		FindWhere(1);// update behind HEAD  1 access element behind HEAD
		std::cout << "=";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
		SHORT w = wdefault + wLocatedFood - 1;
		SHORT h = hdefault + hLocatedFood - 1;
		gotoxy(w, h);
		std::cout << "@";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		gotoxy(0, 0);
		Sleep(10);
		
	}
	
}

/*goto location element i of Snake */
void FindWhere(int i)
{
	// coz run located at 0,0
	SHORT w = wdefault + Snake.elementS[i].wL -1;
	SHORT h = hdefault + Snake.elementS[i].hL -1;
	gotoxy(w, h);
}

void InputKey() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			
			if (!(dirSnake == RIGHT) ) {
				
				dirSnake = LEFT;
				oldDirSnake = dirSnake;
			}
			break;

		case 'd':
			if (!(dirSnake == LEFT)) {
				if (dirSnake == STOP && oldDirSnake == STOP)   break;
				dirSnake = RIGHT;
				oldDirSnake = dirSnake;
			}
			break;

		case 'w':
			if (!(dirSnake == DOWN)) {
				dirSnake = UP;
				oldDirSnake = dirSnake;
			}
			break;

		case 's':
			if (!(dirSnake == UP)) {
				dirSnake = DOWN;
				oldDirSnake = dirSnake;
			}
			break;

		case 'p':
			dirSnake = STOP;
			oldDirSnake = dirSnake;
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
	switch (dirSnake)
	{
	case STOP:

		break;

	case LEFT:
		--wLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		CheckRules();
		break;

	case RIGHT:
		++wLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		CheckRules();
		break;

	case UP:
		--hLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		CheckRules();
		break;

	case DOWN:
		++hLocatedSnack;
		newplace = { wLocatedSnack,hLocatedSnack };
		CheckRules();
		break;

	default:
		break;
	}
	if (Snake.IsElementS(wLocatedFood,hLocatedFood))
	{
		
		Snake.isEat = true;
		++Snake.amoutOfFood;
		Snake.isWhere[Snake.amoutOfFood].ID = Snake.TailIs();
		ponitOfScore += 1;
		gotoxy(wdefault + width / 2 -20, 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
		std::cout << "Score:" << ponitOfScore;
		do
		{
			srand(static_cast<unsigned int>(time(NULL)));
			wLocatedFood = rand() % (width-1);
			srand(static_cast<unsigned int>(time(NULL)));
			hLocatedFood = rand() % (height-1);
		} while (Snake.IsElementS(wLocatedFood,hLocatedFood));
		SHORT w = wdefault + wLocatedFood - 1;
		SHORT h = hdefault + hLocatedFood - 1;
		gotoxy(w, h);
		std::cout << "@";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		//PlaySound(TEXT("D:\\C++\\SolutionC++\\SnackGame\\NFF-steal-02.wav"), NULL, SND_FILENAME | SND_ASYNC);
		RunSound(EFFECT);
		//PlaySound(TEXT("Nandemonai.ogg"), NULL, SND_FILENAME | SND_ASYNC);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	}
	if (Snake.CheckFood())
	{
		Snake.AddTail(Snake.isWhere[1].wL, Snake.isWhere[1].hL);
		IsChangeTail = false;
	}
	
}

void IsDefeat() {
	system("cls");
	SetWindow(500, 700);
	UpdateScroll();
	ShowConsoleCursor(false);
	gotoxy(25, 8);
	std::cout << "GAME OVER";
	Snake.~ClassSnake();
	Snake = ClassSnake(width / 2 - 1, height / 2 - 1);
	Sleep(900);
}   

void CheckRules() {
	if (wLocatedSnack > width-1    || 
		wLocatedSnack < 0          ||
		hLocatedSnack > height-1   ||
		hLocatedSnack < 0		   || !(Snake.RunSnake(newplace.w, newplace.h)))
	{
		statusGame = false;
	}
	else if (Snake.RunSnake(newplace.w, newplace.h))
	{
		IsChangeTail=true;
	}
}

/*Show menu options for user*/
void Welcome() {
	
	/*HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX();
	font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(cons, 0, font);
	font->dwFontSize.X = 14;
	font->dwFontSize.Y = 18;
	font->FontWeight = 14;
	font->FontFamily = FF_DECORATIVE;
	SetCurrentConsoleFontEx(cons, 0, font);*/
	//ReadFile();
	RunSound(BACKGROUND);
	SetConsoleTitle(TEXT("Snake @Shekcon"));
	SetConsoleTextAttribute(console, 241);
	HWND console = GetConsoleWindow();
	statusGame = true;
	MoveWindow(console, 500, 150, 750, 500, TRUE);
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	system("cls"); //clrscr(); //clear the console
				   //Ascii art reference: http://www.chris.com/ascii/index.php?art=animals/reptiles/snakes
	ShowConsoleCursor(false);
	UpdateScroll();
	printf("\n\n\n");
	printf("\t    _________         _________ 			\n");
	printf("\t   /         \\       /         \\ 		\n");
	printf("\t  /  /~~~~~\\  \\     /  /~~~~~\\  \\ 	\n");
	printf("\t  |  |     |  |     |  |     |  | 			\n");
	printf("\t  |  |     |  |     |  |     |  | 			\n");
	printf("\t  |  |     |  |     |  |     |  |         /	\n");
	printf("\t  |  |     |  |     |  |     |  |       //	\n");
	printf("\t (o  o)    \\  \\_____/  /     \\  \\_____/ / \n");
	printf("\t  \\__/      \\         /       \\        / 	\n");
	printf("\t    |        ~~~~~~~~~         ~~~~~~~~ 		\n");
	printf("\t    ^											\n");
	printf("\t    Welcome To The Snake Game!			\n");
	printf("\t             Loading...	\n");
	printf("\n");
	
	
}

void Menu() {
	do
	{
		ShowConsoleCursor(false);
		if (playBack)
		{
			RunSound(BACKGROUND);
			playBack = false;
		}
		reloadMenu = false;
		statusGame = true;
		system("cls");
		SetConsoleTextAttribute(console, 250);
		std::cout << std::endl;
		printf("           ---_ ...... _/_ - CODER\n");
		printf("          /  . .    ./ .'*\\ \\     S \n");
		printf("          : '_-        /__-'  \\.  H  \n");
		printf("         /                      ) E \n");
		printf("       _/                  >   .' K  \n");
		printf("     /   .   .       _.-\" / .'    C  \n");
		printf("     \\           __/\" / .'/|      O \n");
		printf("       \\ '--  .-\" /     //' |\\|   N   \n");
		printf("        \\|  \\ | /     //_ _ |/| \n");
		printf("         `.  \\:     //|_ _ _|\\|  \n");
		printf("         | \\/.    //  | _ _ |/|  \n");
		printf("          \\_ | \\/ /    \\ _ _ \\\\\\  \n");
		printf("              \\__/      \\ _ _ \\|\\ \n");
		//ShowConsoleCursor(true);
		SetConsoleTextAttribute(console, 251);
		gotoxy(38, 4);				printf("Snake Game");
		SetConsoleTextAttribute(console, 240);
		gotoxy(ARROW, NEWGAME);	printf("  NEW GAME");
		gotoxy(ARROW, HIGHSCORE); printf("  HIGH SCORE");
		gotoxy(ARROW, SPEED);     printf("  SPEED");
		gotoxy(ARROW, CONTROL);	printf("  CONTROL");
		gotoxy(ARROW, EXIT);		printf("  EXIT");
		gotoxy(PONITER, NEWGAME);
		NewOptionMenu(where);
		ShowConsoleCursor(false);
		do
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case 'w':

					ChangeColorMenu(false, where);
					ShowConsoleCursor(false);
					break;
				case 's':

					ChangeColorMenu(true, where);
					ShowConsoleCursor(false);
					break;

				case 'p':

					break;
				case 27://ESC
				{
					int resultEsc = MessageBox(NULL, TEXT("Do you close?"), TEXT("Comfirm"), MB_OKCANCEL);
					if (resultEsc == 1) {
						exitGame = true;
					}
					break;
				}
				case 13:
					switch (where)
					{
					case 8: //NEW GAME
						RunSound(NOSOUND);
						ShowConsoleCursor(false);
						Inital();
						RunSnack();
						IsDefeat();
						TestSortScore();
						ShowHighScore();
						Sleep(2000);
						statusGame = false;
						reloadMenu = true;
						playBack = true;
						break;

					case 9://HIGH SCORE
						ShowHighScore();
						Sleep(2000);
						statusGame = false;
						reloadMenu = true;
						break;

					case 10://SPEED
						system("cls");
						ChangeSpeed();
						statusGame = false;
						reloadMenu = true;
						break;

					case 11://CONTROL

						break;

					case 12://EXIT
					{
						int result = MessageBox(NULL, TEXT("Do you close?"), TEXT("Comfirm"), MB_OKCANCEL);
						if (result == 1) {
							exitGame = true;
						}
						break;
					}
					default:
						break;
					}
					break;
				default:
					ShowConsoleCursor(false);
					break;
				}
			}
		} while (statusGame && exitGame == false);

	} while (reloadMenu && exitGame == false);
}

void ChangeSpeed(){
	SetConsoleTextAttribute(console, 241);
	gotoxy(25, 3); std::cout << "Speed of Snake:" << speedOfSnake;
	gotoxy(27, 6); std::cout << "> EXIT";
	SetConsoleTextAttribute(console, 240);
	gotoxy(27, 5); std::cout << "  CHANGE";
	bool Pressed = false;
	bool isExit = true;
	do
	{

		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				if (isExit) {
					TestChangeMenu("EXIT", "CHANGE", 6, 5, 27);
					isExit = false;
				}
				else {
					TestChangeMenu("CHANGE", "EXIT", 5, 6, 27);
					isExit = true;
				}
				break;
			case 's':
				if (isExit) {
					TestChangeMenu("EXIT", "CHANGE", 6, 5, 27);
					isExit = false;
				}
				else {
					TestChangeMenu("CHANGE", "EXIT", 5, 6, 27);
					isExit = true;
				}
				break;
			case 13:
				if (isExit)
				{
					Pressed = true;
				}
				else
				{
					system("cls");
					gotoxy(15, 5);
					std::cout << "Set speed of Snake (1...10): ";
					std::cin >> speedOfSnake;
					while (speedOfSnake<1 || speedOfSnake > 10)
					{
						
						gotoxy(15, 5);
						std::cout<< "Invaild...Please set again:               ";
						gotoxy(15 + 29, 5);
						std::cin >> speedOfSnake;
					}
					gotoxy(20, 7);
					SetConsoleTextAttribute(console, 241);
					std::cout << " CHANGE SUCCESS ";
					SetConsoleTextAttribute(console, 240);
					Sleep(800);
					Pressed = true;
				}
				break;
			
			}
		}
	} while (!Pressed);
}					 
	
void NewOptionMenu(int newOption) {
	switch (newOption)
	{
	case NEWGAME:
		SetConsoleTextAttribute(console, 241);
		gotoxy(ARROW, NEWGAME);			std::cout << "> NEW GAME";
		SetConsoleTextAttribute(console, 240);
		break;

	case HIGHSCORE:

		SetConsoleTextAttribute(console, 241);
		gotoxy(ARROW, HIGHSCORE);		std::cout << "> HIGH SCORE";
		gotoxy(PONITER, HIGHSCORE);
		SetConsoleTextAttribute(console, 240);
		break;

	case SPEED:

		SetConsoleTextAttribute(console, 241);
		gotoxy(ARROW, SPEED);			std::cout << "> SPEED";
		gotoxy(PONITER, SPEED);
		SetConsoleTextAttribute(console, 240);
		break;

	case CONTROL:

		SetConsoleTextAttribute(console, 241);
		gotoxy(ARROW, CONTROL);			std::cout << "> CONTROL";
		gotoxy(PONITER, CONTROL);
		SetConsoleTextAttribute(console, 240); 
		break;

	case EXIT:

		SetConsoleTextAttribute(console, 241);
		gotoxy(ARROW, EXIT);			std::cout << "> EXIT";
		gotoxy(PONITER, EXIT);
		SetConsoleTextAttribute(console, 240); 
		
		break;
	default:
		break;
	}
}

void OldOptionMenu(int oldOption) {
	switch (oldOption)
	{
	case NEWGAME:
		gotoxy(ARROW, NEWGAME);			std::cout << "  NEW GAME";
		break;

	case HIGHSCORE:
		gotoxy(ARROW, HIGHSCORE);		std::cout << "  HIGH SCORE";
		break;

	case SPEED:
		gotoxy(ARROW, SPEED);			std::cout << "  SPEED";
		break;

	case CONTROL:
		gotoxy(ARROW, CONTROL);			std::cout << "  CONTROL";
		break;

	case EXIT:
		gotoxy(ARROW, EXIT);			std::cout << "  EXIT";
		break;
	default:
		break;
	}
}

void TestChangeMenu(std::string textOld, std::string textNew, int locationOld, int locationNew, int whereBegin) {
	gotoxy((SHORT)whereBegin, (SHORT)locationOld); std::cout << "  " << textOld;
	SetConsoleTextAttribute(console, 241);
	gotoxy((SHORT)whereBegin, (SHORT)locationNew); std::cout << "> " << textNew ;
	SetConsoleTextAttribute(console, 240);
}

/*Mode = false : UP   true : DOWN*/
int ChangeColorMenu(bool Mode, int &where){
	if (Mode == false) //fas
	{
		if (where == 8)
		{
			where = 12;
			OldOptionMenu(NEWGAME);
			NewOptionMenu(EXIT);
			return 0;
		}
		--where;
		switch (where)
		{
		case 11:
			OldOptionMenu(EXIT);
			NewOptionMenu(CONTROL);
			
			break;
		case 10:
			OldOptionMenu(CONTROL);
			NewOptionMenu(SPEED);
			
			break;
		case 9:
			OldOptionMenu(SPEED);
			NewOptionMenu(HIGHSCORE);
			break;
		case 8:
			OldOptionMenu(HIGHSCORE);
			NewOptionMenu(NEWGAME);
			
			break;
		default:
			break;
		}
	}
	if (Mode == true) {
		if (where == 12)
		{
			where = 8;
			OldOptionMenu(EXIT);
			NewOptionMenu(NEWGAME);
			return 0;
		}
		++where;
		switch (where)
		{
		case 9:
			OldOptionMenu(NEWGAME);
			NewOptionMenu(HIGHSCORE);

			break;
		case 10:
			OldOptionMenu(HIGHSCORE);
			NewOptionMenu(SPEED);

			break;
		case 11:
			OldOptionMenu(SPEED);
			NewOptionMenu(CONTROL);

			break;
		case 12:
			OldOptionMenu(CONTROL);
			NewOptionMenu(EXIT);

			break;
		default:

			break;
		}
	}
	return 0;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void RunSnack() {
	//HWND console = GetConsoleWindow();
	//MoveWindow(console, 500, 150, 750, 800, TRUE);
	SetWindow(780, 750);
	ShowConsoleCursor(false);
	DrawMap();
	do
	{
		Update();
		ShowLocationS();
		Sleep(Speed[speedOfSnake]);
		InputKey();
		Logic();
		//Test();
		
	} while (statusGame);
}

void UpdateScroll() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(console, &csbi);
	COORD scrollbar = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(console, scrollbar);
}

void SetWindow(int height, int width) {
	HWND console = GetConsoleWindow();
	MoveWindow(console, 500, 150, width, height, TRUE);
}

int main() {
	Welcome();
	ReadFile();
	if (isDefaultWork[0]!='T')
	{
		FirstRunConfig();
		ReadFile();
	}
	Sleep(500);
	Menu();
	WriteFileS();
	return 0;
}

void Test() {
	gotoxy(2, hdefault + height/2 );
	std::cout << "wLocatedSnack < 0 :" << wLocatedSnack;
	if (wLocatedSnack < 0)
	{
		std::cout << " right";
	}
	else std::cout << " wrong";
	std::cout << std::endl;
	std::cout << "wLocatedSnack > width-1 :" << wLocatedSnack <<" "<< width -1;
	if (wLocatedSnack > width-2)
	{
		std::cout << " right";
	}
	else std::cout << " wrong";
	std::cout << std::endl;
	std::cout << "hLocatedSnack < 0 :" << hLocatedSnack;
	if (hLocatedSnack < 0)
	{
		std::cout << " right";
	}
	else std::cout << " wrong";
	std::cout << std::endl;
	std::cout << "hLocatedSnack > height-1 :" << hLocatedSnack << " " << height - 1;
	if (hLocatedSnack > height - 1)
	{
		std::cout << " right";
	}
	else std::cout << " wrong";
}

/* 
 0: dont have sound
   1: background music
   2: effect sound
*/
void RunSound(int numberMusic){
	
	switch (numberMusic)
	{
	case 0:
		PlaySound(NULL, 0, 0);
		break;

	case 1:
		sndPlaySound(MAKEINTRESOURCE(106), SND_RESOURCE | SND_LOOP | SND_ASYNC);
		break;

	case 2:
		sndPlaySound(MAKEINTRESOURCE(105), SND_RESOURCE | SND_ASYNC);
		break;
	default:

		break;
	}
	
}

void ShowLocationS() {
	gotoxy(10, hdefault + height); 
	std::cout << hLocatedSnack +1 <<":" << wLocatedSnack +1 <<"    ";
	gotoxy(0, 0);
	
}


void ReadFile() 
{
	std::ifstream File("config.ino");
	//std::string buffer_string;
	int i = -1;
	if (!File.is_open())
	{
		//MessageBox(NULL, TEXT("Can't open loading infomation"), TEXT("Error"), MB_OK);
		isDefaultWork[0] = 'F';
	}
	else {
		
		while (File.good())
		{
			if (-1 == i) { std::getline(File, isDefaultWork); 
			if (isDefaultWork[0] != 'T') { i = -1; break; }
			}
			else std::getline(File, contextFile[i].text);
			++i;
		}
		int size_speed = contextFile[0].text.size();
		switch (size_speed)
		{
		case 1:
			if (contextFile[0].text[0]<'0' || contextFile[0].text[0]>'9')
			{
				isDefaultWork[0] = 'F';
				i = -1;
			}
			break;
		case 2:
			if (contextFile[0].text[0]<'0' || contextFile[0].text[0]>'9' && contextFile[0].text[1] != '0')
			{
				isDefaultWork[0] = 'F';
				i = -1;
			}
			break;

		default:
			isDefaultWork[0] = 'F';
			i = -1;
			break;

		}
		if (i!=-1)
		{
			speedOfSnake = intValue(contextFile[0].text);
			for (int i = 1; i < 6; ++i)
			{
				int search = contextFile[i].text.find(":");
				for (int j = search + 1; j != contextFile[i].text.size(); ++j)
				{
					contextFile[i].numberS += contextFile[i].text[j];
				}
				contextFile[i].number = intValue(contextFile[i].numberS);
				for (int j = 0; j < search; ++j)
				{
					contextFile[i].name += contextFile[i].text[j];
				}
			}
			/*std::cout << speedOfSnake << std::endl;
			for (int i = 1; i < 6; ++i)
			{
				std::cout << i << "\t" << contextFile[i].name << "\t\t" << contextFile[i].numberS << std::endl;
			}*/
		}
		else isDefaultWork[0] = 'F';
		
		
		
	}
}

void WriteFileS() {
	std::fstream File;
	File.open("config.ino", std::ios::out);
	//std::string buffer_string;
	int i = 0;
	if (!File.is_open())
	{
		MessageBox(NULL, TEXT("Can't loading data"), TEXT("Error"), MB_OK);
		
	}
	else {

		std::string speedS= std::to_string(speedOfSnake);
		File << isDefaultWork[0] << std::endl;
		File << speedS << std::endl;
		
		
		contextFile[1].text = contextFile[1].name + ":" + contextFile[1].numberS;
		contextFile[2].text = contextFile[2].name + ":" + contextFile[2].numberS;
		contextFile[3].text = contextFile[3].name + ":" + contextFile[3].numberS;
		contextFile[4].text = contextFile[4].name + ":" + contextFile[4].numberS;
		contextFile[5].text;
		for (int i = 1; i < 6; i++)
		{
			File << contextFile[i].text << std::endl;
		}
		File.close();	
		
		
	}
}

void FirstRunConfig(){
	remove("config.ino");
	FILE * createFile;
	size_t err= fopen_s(&createFile,"config.ino","a+");
	if(!(err==0)){
		MessageBox(NULL,TEXT("Can't loading data"),TEXT("Error"),MB_OK);
	}
	else {
		//fputc('T', createFile);
		fclose(createFile);
		//notice have write default info into file
	}
	for (int x = 1; x < 6; ++x)
	{
		contextFile[x].text = "";
	}
	std::fstream importFile("config.ino");
	if (!importFile.is_open()) {
		MessageBox(NULL, TEXT("Can't loading data"), TEXT("Error"), MB_OK);
		
	}
	else {
		std::string mode = "T";
		importFile << mode << std::endl;
		int defaultSpeed = 5;
		speedOfSnake = 5;
		std::string speed = std::to_string(defaultSpeed);
		importFile << speed << std::endl;
		std::string defaultGame = " :empty";
		
		for (int i = 1; i < 6; ++i)
		{

			importFile << defaultGame << std::endl;
		}
		importFile.close();

	}

}

int intValue(std::string  s) {
	int res = 0;

	for (int i = 0; i != s.size(); ++i) 
		res = res * 10 + (s[i]-'0');
	return res;
}

void IsHighScore(std::string namePlayer,int ponit) {
	contextFile[6].name = namePlayer;
	contextFile[6].number = ponit;
	bool isUpdate = false;
	int whereIsEmpty = IsWhereEmpty();
	for (int i = 1; i < whereIsEmpty; i++)
	{
		if (ponit > contextFile[i].number) {
			isUpdate = true;
			UpdateFile(whereIsEmpty , i); // coz where update behind where empty - 1;
			break;
		}
	}
	if (!isUpdate)
	{
		if (whereIsEmpty<=5)
		{
			contextFile[whereIsEmpty].name = contextFile[6].name;
			contextFile[whereIsEmpty].number = contextFile[6].number;
			contextFile[whereIsEmpty].numberS = std::to_string(contextFile[whereIsEmpty].number);
			contextFile[whereIsEmpty].text = contextFile[whereIsEmpty].name + ":" + contextFile[whereIsEmpty].numberS;
		}
	}
}

int IsWhereEmpty(){
	for (int i = 1; i < 6 ; ++i)
	{
		if (contextFile[i].numberS=="empty")
		{
			return i;
		}
	}
	return 6;
}

/*start: begin location - 1 numberS = "empty"
end : where high score write into it*/
void UpdateFile(int start,int end){
	if (start == 6) start = 5;
	for(int j=start;j>end;--j){
		contextFile[j].name = contextFile[j-1].name;
		contextFile[j].number = contextFile[j-1].number;
		contextFile[j].numberS = std::to_string(contextFile[j].number);
		contextFile[j].text = contextFile[j].name + ":" + contextFile[j].numberS;
	}
	contextFile[end].name = contextFile[6].name;
	contextFile[end].number = contextFile[6].number;
	contextFile[end].numberS = std::to_string(contextFile[end].number);
	contextFile[end].text = contextFile[end].name + ":" + contextFile[end].numberS;
}

void TestSortScore(){
	system("cls");
	std::string test;
	gotoxy(13, 6);
	std::cout << "what's your name? :";
	std::cin >> test;
	IsHighScore(test, ponitOfScore);
}

void ShowHighScore() {
	system("cls");
	SetConsoleTextAttribute(console, 241);
	gotoxy(12, 3); std::cout << "Name";
	gotoxy(30, 3); std::cout << "Score";
	SetConsoleTextAttribute(console, 240);
	for (int y = 1; y < 6; ++y)
	{
		gotoxy(8, 3+y); std::cout << y << ".";
		gotoxy(11, 3 + y);
		std::cout << contextFile[y].name;
		gotoxy(30, 3 + y); std::cout << contextFile[y].numberS;
	}


}