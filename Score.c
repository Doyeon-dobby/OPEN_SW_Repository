#include "Score.h"

#include <stdio.h>
#include "ConsoleControll.h"
#include "Colors.h"

int gameScore = 0;


int GetSocre(int info)
{
	int score = ReturnScore(info);
	gameScore += score;
	return gameScore;
}


void ShowSocre()
{
	int showScoreX = 3;
	int showScoreY = 0;
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(showScoreX, showScoreY);
	SetMapColor(0);
	printf("Score : %d", gameScore);
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

int ReturnScore(int action)
{
	int a = 0;
	switch (action)
	{
	case 0:
		a = BASICBLOCK;
		break;
	case 1:
		a = 0;
		break;
	case 2:
		a = COPPER;
		break;
	case 3:
		a = SILVER;
		break;
	case 4:
		a = GOLD;
		break;
	case 5:
		a = CRYSTAL;
		break;
	case 6:
		a = DIAMOND;
		break;
	case 7:
		a = S_CRAETUM;
		break;
	case 8:
		a = S_SELANUM;
		break;
	case 9:
		a = S_CRIPTON;
		break;
	case 10://monster kill
		a = MOSTERKILL;
		break;
	case 11://stage clear
		a = 5000;
		break;
	case 12:
		a = 10000;
		break;
	case 13:
		a = 15000;
		break;
	case 14:
		a = 20000;
		break;
	case 15://stage clear
		a = 25000;
		break;
	default:
		break;
	}
	return a;
}