#include <vector>
#pragma once
const int HORIZON = 16;
const int VERTICAL = 17;

// 위치.
typedef struct _tagpos
{
	int x;
	int y;
}POS, * PPOS;

typedef struct _tagplayer
{
	POS tpos;       // 플레이어의 위치
	POS tNewpos;    // 플레이어의 새 위치
	POS tDirection; // 플레이어 방향
	bool isdie;
}PLAYER, * PPLAYER;

void Init(char _cMaze[VERTICAL][HORIZON], std::vector<PLAYER>& _pPlayer, PPOS _pSpawnpos);
void Update(char _cMaze[VERTICAL][HORIZON], std::vector<PLAYER>& _pPlayer); // 값을 변경.
void Render(char _cMaze[VERTICAL][HORIZON], std::vector<PLAYER>& _pPlayer); // 그려주다.
void CreateItem(char _cMaze[VERTICAL][HORIZON]); // 아이템 생성할 때
bool GetItem(char _cItem, std::vector<PLAYER>& _pPlayer); // 아이템 먹었을 때
bool WallCrash(char _cWall, std::vector<PLAYER>& _pPlayer); // 벽에 부딪혔을 때
bool PlayerDie(); // 죽었을 때