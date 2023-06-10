#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
#include<algorithm>
#include "GameLogic.h"
#include "console.h"
using namespace std;

int currentDirection = 0;

void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pSpawnpos)
{
	system("mode con cols=30 lines=20");
	SetConsoleTitle(TEXT("Hungry Worm"));
	Cursorset(false, 1);
	// strcpy: string copy / 0: 벽, 1: 길, 2: 생성 위치
	strcpy_s(_cMaze[3], "111111111111111");
	strcpy_s(_cMaze[4], "100000000000001");
	strcpy_s(_cMaze[5], "100000000000001");
	strcpy_s(_cMaze[6], "100000000000001");
	strcpy_s(_cMaze[7], "100000000000001");
	strcpy_s(_cMaze[8], "100000000000001");
	strcpy_s(_cMaze[9], "100000000000001");
	strcpy_s(_cMaze[10],"100000000000001");
	strcpy_s(_cMaze[11],"100000000000001");
	strcpy_s(_cMaze[12],"100000000000001");
	strcpy_s(_cMaze[13],"100000000000001");
	strcpy_s(_cMaze[14],"100000000000001");
	strcpy_s(_cMaze[15],"100000000000001");
	strcpy_s(_cMaze[16],"100000000000001");
	strcpy_s(_cMaze[17],"111111111111111");
	
	_pSpawnpos->x = 7;
	_pSpawnpos->y = 10;

	PLAYER tSetplayer = { *_pSpawnpos, 1, 0 };
	*_pPlayer = tSetplayer;
}

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer)
{	
	Sleep(200);
	// ============ 플레이어 움직임 =============
	_pPlayer->tNewpos = _pPlayer->tpos;
	// 플레이어 움직이고 싶어.
	
	switch (currentDirection)
	{
		case 1:
			--_pPlayer->tNewpos.y;
			break;
		case 2:
			++_pPlayer->tNewpos.y;
			break;
		case 3:
			--_pPlayer->tNewpos.x;
			break;
		case 4:
			++_pPlayer->tNewpos.x;
			break;
		default:
			break;
	}
	
	// 키 입력받아서 플레이어의 좌표를 바꿔줘야해.
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		currentDirection = 1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		currentDirection = 2;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		currentDirection = 3;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		currentDirection = 4;
	}

	// 벽 밖으로 나가는거 예외처리		16 18
	_pPlayer->tNewpos.x = std::clamp (_pPlayer->tNewpos.x, 0, HORIZON - 2); // 15
	_pPlayer->tNewpos.y = std::clamp(_pPlayer->tNewpos.y, 0, VERTICAL - 1); // 17

	if (_cMaze[_pPlayer->tNewpos.y][_pPlayer->tNewpos.x] != '1')
	{
		_pPlayer->tpos = _pPlayer->tNewpos;
	}
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			if (_pPlayer->tpos.x == j
				&& _pPlayer->tpos.y == i)
				cout << "□";
			else if (_cMaze[i][j] == '0') // 벽
				cout << "  ";
			else if (_cMaze[i][j] == '1') // 길
				cout << "■"; // 공백을 2번
		}
		cout << endl;
	}
}