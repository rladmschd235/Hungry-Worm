#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<Windows.h>
#include<algorithm>
#include "GameLogic.h"
#include "console.h"
#include "GameOver.h"
using namespace std;

bool isBeforeStart;
int itemCount = 0;
int warmLength = 1;
int currentDirection = 0;

void Init(char _cMaze[VERTICAL][HORIZON], vector<PLAYER>& _pPlayer, PPOS _pSpawnpos)
{
	system("mode con cols=30 lines=20");
	SetConsoleTitle(TEXT("Hungry Worm"));	
	Cursorset(false, 1);

	isBeforeStart = true;

	// strcpy: string copy / 0: ��, 1: ��
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
	
	_pSpawnpos->x = 7;
	_pSpawnpos->y = 9;

	PLAYER tSetplayer = { *_pSpawnpos, 1, 0 };
	_pPlayer.push_back(tSetplayer);
}

void Update(char _cMaze[VERTICAL][HORIZON], vector<PLAYER>& _pPlayer)
{	
	cout << endl << "���� ������ ���̶���: " << warmLength;
	
	// ============ �÷��̾� ������ =============
	_pPlayer.front().tNewpos = _pPlayer.front().tpos;
	// �÷��̾� �����̰� �;�.
	
	switch (currentDirection)
	{
		case 1:
			--_pPlayer.front().tNewpos.y; // ��
			break;
		case 2:
			++_pPlayer.front().tNewpos.y; // �Ʒ�
			break;
		case 3:
			--_pPlayer.front().tNewpos.x; // ��
			break;
		case 4:
			++_pPlayer.front().tNewpos.x; // ����
			break;
		default:
			break;
	}
	
	// Ű �Է¹޾Ƽ� �÷��̾��� ��ǥ�� �ٲ������.
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
	
	if (_cMaze[_pPlayer.front().tNewpos.y][_pPlayer.front().tNewpos.x] != '1')
	{
		for (int i = 0; i < _pPlayer.size()-1; i++)
		{
			_pPlayer[i + 1].tpos = _pPlayer[i].tpos;
			_pPlayer[i].tpos = _pPlayer[i].tNewpos;
		}
	}

	if (GetItem(_cMaze[_pPlayer.front().tpos.y][_pPlayer.front().tpos.x], _pPlayer))
	{
		_cMaze[_pPlayer.front().tpos.y][_pPlayer.front().tpos.x] = '0';
	}

	if (WallCrash(_cMaze[_pPlayer.front().tNewpos.y][_pPlayer.front().tNewpos.x], _pPlayer))
	{
		_pPlayer.front().isdie = PlayerDie();
	}

	Sleep(200);
}

void Render(char _cMaze[VERTICAL][HORIZON], vector<PLAYER>& _pPlayer)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			for (int k = 0; k < _pPlayer.size(); k++)
			{
				if (_pPlayer[k].tpos.x == j && _pPlayer[k].tpos.y == i)
				{
					cout << "��";
				}
			}
			if (_cMaze[i][j] == '0') // ��
				cout << "  ";
			else if (_cMaze[i][j] == '1') // ��
				cout << "��"; // ������ 2��
			else if (_cMaze[i][j] == '2')
			{
				cout << "��";
			}
			else if (_cMaze[i][j] == '3')
			{
				cout << "��";
			}
			else if (_cMaze[i][j] == '4')
			{
				cout << "��";
			}
			else if (_cMaze[i][j] == '5')
			{
				cout << "��";
			}
		}
		cout << endl;
	}
	
	if (isBeforeStart == true)
	{
		cout << endl << "�ƹ� ����Ű Ŭ�� �� �����Ѵܴ�";
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
			int xRandom = rand() % (15 - 1 + 1) + 1;
			int yRandom = rand() % (17 - 3 + 1) + 3;

			if (_cMaze[yRandom][xRandom] == '0')
			{
				float fRandom = rand() % 10001 / 100.f; // 0.0 ~ 100.0%

				if (fRandom <= 50.f) // ������. 
				{
					// �������� Ȯ���� ������ �ϸ���ݾ�.
					fRandom = rand() % 10001 / 100.f;
					if (fRandom <= 30.f)
					{
						_cMaze[yRandom][xRandom] = '2';
						itemCount++;
					}
					else if (fRandom <= 60.f)
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

bool GetItem(char _cItem, vector<PLAYER>& _pPlayer)
{
	if (_cItem == '2')
	{
		warmLength += 1;
		itemCount--;
		return true;
	}
	else if (_cItem == '3')
	{
		warmLength += 2;
		itemCount--;
		return true;
	}
	else if (_cItem == '4')
	{
		warmLength += 3;
		itemCount--;
		return true;
	}
	else if (_cItem == '5')
	{
		warmLength -= 1;
		itemCount--;
		return true;
	}
	return false;
}

bool WallCrash(char _cWall, vector<PLAYER>& _pPlayer)
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
