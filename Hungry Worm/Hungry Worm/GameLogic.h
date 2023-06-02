#pragma once
const int HORIZON = 21;
const int VERTICAL = 20;

// 위치.
typedef struct _tagpos
{
	int x;
	int y;
}POS, * PPOS;

typedef struct _tagplayer
{
	POS tpos;       // 플레이어의 위치
	POS tNewpos;    // 플레이어의 새위치
}PLAYER, * PPLAYER;

#include<vector>

void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartpos, PPOS _pEndpos);
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // 값을 변경.
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // 그려주다.