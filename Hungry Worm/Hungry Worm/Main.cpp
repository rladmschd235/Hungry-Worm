#include <iostream>
#include <vector>
#include "GameLogic.h"
#include "console.h"
#include "GameOver.h"
using namespace std;

int main()
{
	char cMaze[VERTICAL][HORIZON] = {};
	vector<PLAYER> tPlayer = {};
	POS tSpawnpos = {};
	
	Init(cMaze, tPlayer, &tSpawnpos);

	while (true)
	{
		Gotoxy(0, 0);
		Update(cMaze, tPlayer);
		Render(cMaze, tPlayer);
		if (tPlayer.front().isdie)
		{
			break;
		}
	}
	OnDie();
}