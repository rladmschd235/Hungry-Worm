#pragma once
#include <Windows.h>
enum class COLOR
{
    BLACK, BLUE, GREEN, SKYBLUE, RED,
    VIOLET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
    LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
    LIGHT_YELLOW, WHITE
};
void FullScreen();
void Gotoxy(int, int);
BOOL Gotoxytest(int, int);
void Cursorset(bool, DWORD);
void SetColor(int, int);
int GetColor();
int Getbgcolor();