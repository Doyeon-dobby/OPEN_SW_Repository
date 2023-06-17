#include <stdio.h>
#include <windows.h>
#include "Startmain.h"
#include "ConsoleControll.h"
#include "Drawing.h"
#include "Keys.h"
#include "Colors.h"

int bar_interval = 3;
int click_high = 26;
int click_low = 32;
int click_x = 36;
int click_y = 26;

void titleDraw() {
	printf("\n\n\n\n");
	Set_Color(BLUE);
	printf("         ####     #####         ########                ########         ########       ###        ###############					\n");
	printf("         ####   ######        ##        ##            ##        ##       ###   ###      ###       ###								\n");
	Set_Color(WHITE);
	printf("         #########          ##           ##          ##          ##      ###    ###     ###      ###								\n");
	printf("         #########          ##           ##          ##          ##      ###     ###    ###     ###									\n");
	Set_Color(RED);
	printf("         ##########         ##           ##          ##          ##      ###      ###   ###     ###									\n");
	printf("         ####   ######      ##           ##          ##          ##      ###       ###  ###     ###        #########				\n");
	Set_Color(WHITE);
	printf("         ####    #####      ##           ##          ##          ##      ###        #######     ###           ######				\n");
	printf("         ####      ####     ##           ##          ##          ##      ###         ######     ###            #####				\n");
	Set_Color(YELLOW);
	printf("         ####      ####     ##           ##          ##          ##      ###          #####      ###            ####				\n");
	printf("         ####      ####      ##         ##            ##        ##       ###           ####       ###            ##					\n");
	Set_Color(WHITE);
	printf("         ####      ####        #########                ########         ###            ###       #################                 \n");
}

int DrawGameSettingBar()
{
	SetCurrentCursorPos(8, 0);
	titleDraw();
	PrintClickBar(click_x, click_y);
	PrintBar();
	while (1)
	{
		int key;
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			case UP:
				EraseClickBar(click_x, click_y);
				PrintClickBar(click_x, click_y - bar_interval);
				break;
			case KeyW:
				EraseClickBar(click_x, click_y);
				PrintClickBar(click_x, click_y - bar_interval);
				break;
			case DOWN:
				EraseClickBar(click_x, click_y);
				PrintClickBar(click_x, click_y + bar_interval);
				break;
			case KeyS:
				EraseClickBar(click_x, click_y);
				PrintClickBar(click_x, click_y + bar_interval);
				break;
			case SPACE:
				if (click_y == 26)
				{
					return 0;
				}
				else if (click_y == 26 + bar_interval)
				{
					return 1;
				}
				else if (click_y == 26 + 2 * bar_interval)
				{
					return 2;
				}
				break;
			default:
				break;
			}
		}
	}
}
void PrintBar()
{
	int gameStarBar_x = 40;
	int gameStarBar_y = 26;

	int gameExplainBar_x = 40;
	int gameExplainBar_y = 26 + bar_interval;

	int gameExitBar_x = 40;
	int gameExitBar_y = 26 + 2 * bar_interval;

	SetCurrentCursorPos(gameStarBar_x, gameStarBar_y);
	printf("게임시작");
	SetCurrentCursorPos(gameExplainBar_x, gameExplainBar_y);
	printf("게임설명");
	SetCurrentCursorPos(gameExitBar_x, gameExitBar_y);
	printf("게임종료");
	SetCurrentCursorPos(gameExitBar_x -4 , gameExitBar_y+10);
	printf("스페이스바를 누르세요!");
}
void EraseClickBar(int x, int y)
{
	SetCurrentCursorPos(x, y);
	printf("   ");
}

void PrintClickBar(int x, int y)
{
	if (y <= click_high)
	{
		y = click_high;
	}
	if (y >= click_low)
	{
		y = click_low;
	}
	click_x = x;
	click_y = y;
	SetCurrentCursorPos(x, y);
	printf(">");
}

void PrintGameExplainScreen()
{
	EraseScreen();
	
	Set_Color(YELLOW);
	SetCurrentCursorPos(4, 1);
	for (int i = 0; i < 40; i++)
	{
		printf("□");
	}
	for (int i = 0; i < 39; i++)
	{
		SetCurrentCursorPos(4, 2+i);
		printf("□");
		SetCurrentCursorPos(82, 2 + i);
		printf("□");
	}
	SetCurrentCursorPos(4, 40);
	for (int i = 0; i < 40; i++)
	{
		printf("□");
	}
	Set_Color(WHITE);
	SetCurrentCursorPos(18, 4);
	printf("	  △      : Shift Up");
	SetCurrentCursorPos(18, 4 + 1 * bar_interval);
	printf("   ◁       ▷  : Left / Right");
	SetCurrentCursorPos(18, 4 + 2 * bar_interval);
	printf("	  ▽      : Digging");
	SetCurrentCursorPos(18 , 4 + 3 * bar_interval);
	printf("        SPACE : Interaction");
	SetCurrentCursorPos(18, 4 + 4 * bar_interval);
	printf("        Q   : Bomb");
	SetCurrentCursorPos(18 , 4 + 5 * bar_interval);
	printf("	  W   :  Restore HP Item");
	SetCurrentCursorPos(18 , 4 + 6 * bar_interval);
	printf("	  E   :  Restore O2 Item");
	SetCurrentCursorPos(18 , 4 + 7 * bar_interval);
	printf("	  T   :  Teleport");
	SetCurrentCursorPos(18, 4 + 8 * bar_interval);
	printf("	  I   :  Inventory");
	SetCurrentCursorPos(18 , 4 + 9 * bar_interval);
	printf("	  P   :  Shop");

	SetCurrentCursorPos(18, 4 + 10 * bar_interval);
	Set_Color(SKYBLUE);
	printf("Press Space Button, Back to the menu");
	while (1)
	{
		int key;
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			case SPACE:
				EraseScreen();
				return;
				break;
			default:
				break;
			}
		}
	}
}
void EraseScreen()
{
	SetCurrentCursorPos(0, 0);
	for (int i = 0; i < 80; i++)
	{
		printf("                                                                                                                                                                                                                                 \n");
	}
}