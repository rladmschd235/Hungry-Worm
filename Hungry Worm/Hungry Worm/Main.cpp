#include <iostream>
#include "GameLogic.h"
#include "console.h"
using namespace std;

int main()
{
	char cMaze[VERTICAL][HORIZON] = {};
	PLAYER tPlayer = {};
	POS tStartpos = {};
	POS tEndpos = {};
	Init(cMaze, &tPlayer, &tStartpos);

	while (true)
	{
		Gotoxy(0, 0);
		Update(cMaze, &tPlayer);
		Render(cMaze, &tPlayer);
	}
}