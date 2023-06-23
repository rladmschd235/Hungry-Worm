#include <queue>
#pragma once
const int HORIZON = 16;
const int VERTICAL = 17;

// ��ġ.
typedef struct _tagpos
{
	int x;
	int y;
}POS, * PPOS;

typedef struct _tagplayer
{
	POS tpos;       // �÷��̾��� ��ġ
	POS tNewpos;    // �÷��̾��� �� ��ġ
	POS tDirection; // �÷��̾� ����
	bool isdie;
}PLAYER, * PPLAYER;

void Init(char _cMaze[VERTICAL][HORIZON], std::queue<PLAYER>& _pPlayer, PPOS _pSpawnpos);
void Update(char _cMaze[VERTICAL][HORIZON], std::queue<PLAYER>& _pPlayer); // ���� ����.
void Render(char _cMaze[VERTICAL][HORIZON], std::queue<PLAYER>& _pPlayer); // �׷��ִ�.
void CreateItem(char _cMaze[VERTICAL][HORIZON]); // ������ ������ ��
bool GetItem(char _cItem, std::queue<PLAYER>& _pPlayer); // ������ �Ծ��� ��
bool WallCrash(char _cWall, std::queue<PLAYER>& _pPlayer); // ���� �ε����� ��
bool PlayerDie(); // �׾��� ��