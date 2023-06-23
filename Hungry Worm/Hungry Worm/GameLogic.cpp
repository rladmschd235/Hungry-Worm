#pragma once
#include<iostream>
#include<queue>
#include<Windows.h>
#include<algorithm>
#include "GameLogic.h"
#include "console.h"
#include "GameOver.h"
using namespace std;

bool isBeforeStart;
int itemCount = 0;
int wormLength = 1;
int currentDirection = 0;

void Init(char _cMaze[VERTICAL][HORIZON], queue<PLAYER>& _pPlayer, PPOS _pSpawnpos)
{
	srand((unsigned int)time(NULL));
	system("mode con cols=30 lines=21");
	Cursorset(false, 1);
	SetConsoleTitle(TEXT("Hungry Worm"));	
	//Cursorset(false, 1);

	isBeforeStart = true;

	// strcpy: string copy / 0: 벽, 1: 길
	strcpy_s(_cMaze[2], "111111111111111");
	strcpy_s(_cMaze[3], "100000000000001");
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
	strcpy_s(_cMaze[16],"111111111111111");	
	
	_pPlayer = queue <PLAYER>();
	
	_pSpawnpos->x = 7;
	_pSpawnpos->y = 9;

	PLAYER tSetplayer = { *_pSpawnpos };
	_pPlayer.push(tSetplayer);
}

void Update(char _cMaze[VERTICAL][HORIZON], queue<PLAYER>& _pPlayer)
{	
	// ============ 플레이어 움직임 =============
	_pPlayer.back().tNewpos = _pPlayer.back().tpos;
	// 플레이어 움직이고 싶어.
	
	switch (currentDirection)
	{
		case 1:
			--_pPlayer.back().tNewpos.y; // 위
			break;
		case 2:
			++_pPlayer.back().tNewpos.y; // 아래
			break;
		case 3:
			--_pPlayer.back().tNewpos.x; // 왼
			break;
		case 4:
			++_pPlayer.back().tNewpos.x; // 오른
			break;
		default:
			break;
	}
	
	// 키 입력받아서 플레이어의 좌표를 바꿔줘야해.
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		isBeforeStart = false;
		currentDirection = 1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		isBeforeStart = false;
		currentDirection = 2;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		isBeforeStart = false;
		currentDirection = 3;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		isBeforeStart = false;
		currentDirection = 4;
	}

	CreateItem(_cMaze);
	
	if (WallCrash(_cMaze[_pPlayer.back().tNewpos.y][_pPlayer.back().tNewpos.x], _pPlayer) || wormLength == 0)
	{
		_pPlayer.back().isdie = PlayerDie();
	}

	if (GetItem(_cMaze[_pPlayer.back().tNewpos.y][_pPlayer.back().tNewpos.x], _pPlayer))
	{
		_cMaze[_pPlayer.back().tNewpos.y][_pPlayer.back().tNewpos.x] = '0';
	}

	if (_cMaze[_pPlayer.back().tNewpos.y][_pPlayer.back().tNewpos.x] != '1' && wormLength > 1)
	{
		// 늘려라.
		for (int i = 0; i < wormLength; i++)
		{
			PLAYER temp = { {},_pPlayer.back().tNewpos };
			_pPlayer.push(temp);
			//_pPlayer[i].tpos = _pPlayer[i].tNewpos;
		}

		//_pPlayer.front().tpos = _pPlayer.front().tNewpos;
		//for (int i = 0; i < _pPlayer.size(); i++)
		//{
		//	_pPlayer[i + 1].tNewpos = _pPlayer[i].tpos;
		//	_pPlayer[i].tpos = _pPlayer[i].tNewpos;
		//}
	}
	_pPlayer.back().tpos = _pPlayer.back().tNewpos;

	Sleep(100);
}

void Render(char _cMaze[VERTICAL][HORIZON], queue<PLAYER>& _pPlayer)
{
	cout << endl << "현재 벌레의 길이란다: " << wormLength;

	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			bool drawed = false;
			for (int k = 0; k < wormLength; k++)
			{
				if (_pPlayer.back().tNewpos.x == j && _pPlayer.back().tNewpos.y == i)
				{
					cout << "□";
					drawed = true;
					break;
				}
			}
			if (drawed) continue;
			if (_cMaze[i][j] == '0') // 길5
				cout << "  ";
			//if (_pPlayer[0].tpos.x == j && _pPlayer[0].tpos.y == i)
			//	cout << "□";
			//else if (_cMaze[i][j] == '0') // 길5
			//	cout << "  ";
			else if (_cMaze[i][j] == '1') // 벽
				cout << "■"; // 공백을 2번
			else if (_cMaze[i][j] == '2')
			{
				cout << "①";
			}
			else if (_cMaze[i][j] == '3')
			{
				cout << "②";
			}
			else if (_cMaze[i][j] == '4')
			{
				cout << "③";
			}
			else if (_cMaze[i][j] == '5')
			{
				cout << "Θ";
			}
		}
		cout << endl;
	}
	
	if (isBeforeStart == true)
	{
		cout << endl << "아무 방향키 클릭 시 시작한단다";
	}
	else
	{
		cout << endl << "                              ";
	}
}

void CreateItem(char _cMaze[VERTICAL][HORIZON])
{
	int itemArray[5];

	for (auto i : itemArray)
	{
		if (itemCount < 5)
		{
			int xRandom = rand() % (14 - 3 + 1) + 3;
			int yRandom = rand() % (14 - 1 + 1) + 1;

			if (_cMaze[yRandom][xRandom] == '0')
			{
				float fRandom = rand() % 10001 / 100.f; // 0.0 ~ 100.0%

				if (fRandom <= 101.0f) // 아이템. 
				{
					// 아이템을 확률로 나오게 하면되잖아.
					fRandom = rand() % 10001 / 100.f;
					if (fRandom <= 60.f)
					{
						_cMaze[yRandom][xRandom] = '2';
						itemCount++;
					}
					else if (fRandom <= 70.f)
					{
						_cMaze[yRandom][xRandom] = '3';
						itemCount++;
					}
					else if (fRandom <= 80.f)
					{
						_cMaze[yRandom][xRandom] = '4';
						itemCount++;
					}
					else
					{
						_cMaze[yRandom][xRandom] = '5';
						itemCount++;
					}
				}
				else
					_cMaze[yRandom][xRandom] = '0';
			}
		}
	}
}

bool GetItem(char _cItem, queue<PLAYER>& _pPlayer)
{
	PLAYER tail;
	
	if (_cItem == '2')
	{
		wormLength += 1;
		//_pPlayer.push(tail);
		itemCount--;
		return true;
	}
	else if (_cItem == '3')
	{
		wormLength += 2;
		//for (int i = 0; i < 2; i++)
		//{
		//	_pPlayer.push(tail);
		//}
		itemCount--;
		return true;
	}
	else if (_cItem == '4')
	{
		wormLength += 3;
		itemCount--;
		//for (int i = 0; i < 3; i++)
		//{
		//	_pPlayer.push(tail);
		//}
		return true;
	}
	else if (_cItem == '5')
	{
		wormLength -= 1;
		itemCount--;
		if (_pPlayer.size() <= 1)
		{
			_pPlayer.back().isdie = PlayerDie();
		}
		//_pPlayer.pop();
		return true;
	}
	return false;
}

bool WallCrash(char _cWall, queue<PLAYER>& _pPlayer)
{
	if (_cWall == '1')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerDie()
{
	return true;
}
