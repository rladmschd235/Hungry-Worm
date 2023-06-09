#pragma once
const int HORIZON = 16;
const int VERTICAL = 18;

// ��ġ.
typedef struct _tagpos
{
	int x;
	int y;
}POS, * PPOS;

typedef struct _tagplayer
{
	POS tpos;       // �÷��̾��� ��ġ
	POS tNewpos;    // �÷��̾��� ����ġ
}PLAYER, * PPLAYER;

#include<vector>

void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pSpawnpos);
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // ���� ����.
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // �׷��ִ�.
