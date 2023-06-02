#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
#include<algorithm>
#include "GameLogic.h"
#include "console.h"
using namespace std;
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartpos, PPOS _pEndpos)
{
	system("mode con cols=80 lines=30");
	SetConsoleTitle(TEXT("2-3 Bomb man"));
	Cursorset(false, 1);
	// strcpy: string copy / 0: 벽, 1: 길, 2: 시작, 3: 도착
	strcpy_s(_cMaze[0], "21111100000000111111");
	strcpy_s(_cMaze[1], "00100111111111100000");
	strcpy_s(_cMaze[2], "11100100000000100100");
	strcpy_s(_cMaze[3], "00100100000000100100");
	strcpy_s(_cMaze[4], "00100100000000100100");
	strcpy_s(_cMaze[5], "00100100000000100100");
	strcpy_s(_cMaze[6], "00100100000000100100");
	strcpy_s(_cMaze[7], "00100111111100100100");
	strcpy_s(_cMaze[8], "00100100000100100100");
	strcpy_s(_cMaze[9], "00100100000100100100");
	strcpy_s(_cMaze[10], "00100100000100000100");
	strcpy_s(_cMaze[11], "00100100000111111100");
	strcpy_s(_cMaze[12], "00100100000000000000");
	strcpy_s(_cMaze[13], "00100111111111111113");
	strcpy_s(_cMaze[14], "00100100000000000000");
	strcpy_s(_cMaze[15], "00000100000000000110");
	strcpy_s(_cMaze[16], "00000100000000000100");
	strcpy_s(_cMaze[17], "00000100000000000100");
	strcpy_s(_cMaze[18], "00000111111111111100");
	strcpy_s(_cMaze[19], "00000100000000000000");
	_pStartpos->x = 0;
	_pStartpos->y = 0;
	_pEndpos->x = 19;
	_pEndpos->y = 13;
	PLAYER tSetplayer = { *_pStartpos,1,0,false,false,false };
	*_pPlayer = tSetplayer;

}

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer)
{
	// ============ 플레이어 움직임 =============
	_pPlayer->tNewpos = _pPlayer->tpos;
	// 플레이어 움직이고 싶어.
	// 키 입력받아서 플레이어의 좌표를 바꿔줘야해.
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		--_pPlayer->tNewpos.y;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		++_pPlayer->tNewpos.y;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		--_pPlayer->tNewpos.x;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		++_pPlayer->tNewpos.x;

	// 벽 밖으로 나가는거 예외처리		21 20
	_pPlayer->tNewpos.x = std::clamp(_pPlayer->tNewpos.x, 0, HORIZON - 2);
	_pPlayer->tNewpos.y = std::clamp(_pPlayer->tNewpos.y, 0, VERTICAL - 1); // 20 

	if (_cMaze[_pPlayer->tNewpos.y][_pPlayer->tNewpos.x] != '0')
	{
		_pPlayer->tpos = _pPlayer->tNewpos;
	}
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<POS> boomEffect)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			if (_pPlayer->tpos.x == j
				&& _pPlayer->tpos.y == i)
				cout << "§";
			else if (_cMaze[i][j] == '0') // 벽
				cout << "■";
			else if (_cMaze[i][j] == '1') // 길
				cout << "  "; // 공백을 2번
			else if (_cMaze[i][j] == '2') // 시작
				cout << "®";
			else if (_cMaze[i][j] == '3') // 도착
				cout << "♨";
			else if (_cMaze[i][j] == '4') // 물풍선 powerup
				cout << "◐";
			else if (_cMaze[i][j] == '5') // 슬라임
				cout << "♤";
			else if (_cMaze[i][j] == '6') // 벽 푸시
				cout << "▩";
		}
		cout << endl;
	}
}