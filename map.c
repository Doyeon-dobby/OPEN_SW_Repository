#include<stdio.h>
#include "map.h"
#include "ConsoleControll.h"
#include "Colors.h"

//#define BLACK 0
//#define DARKBLUE 1
//#define DARKGREEN 2
//#define DARKSKYBLUE 3
//#define DARKRED 4
//#define DARKPURPLE 5
//#define DARKYELLOW 6
//#define GRAY 7
//#define DARKGRAY 8
//#define BLUE 9
//#define GREEN 10
//#define SKYBLUE 11
//#define RED 12
//#define PURPLE 13
//#define YELLOW 14
//#define  WHITE 15

//map_state = -1 광물
//map_state = 0 아무것도 안부셔진 블록 
//map_state = 1 조금 부셔진 블록
//map_state = 2 거의 다 부셔진 블록
//map_state = 3 없어진 블록



//map_info = -1 아무것도 없는 통로
//map_info = 0  뚤리는 기본 땅
// map_info = 1 뚤리지 않는 기본 땅 다이너마이트로만 뚤어야됨
// map_info = 2  동
// map_info = 3  은
// map_info = 4  금
// map_info = 5  크리스탈
// map_info = 6  다이아몬드
// 
// map_info = 7  특수 : 크레튬
// map_info = 8  특수 : 셀라늄
// map_info = 9  특수 : 크립톤
//
// map_info = 10  플레이어
// map_info = 11  몹
// map_info = 12  아이템
// map_info = 13  문

int map_info[5][100][50] = { 0 };
int map_state[5][100][50] = { 0 };
int stage_state = 0;

void ShowStage()
{
	int showStageX = MAP_INFO_X * 3 - 7;
	int showStageY = 0;
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(showStageX, showStageY);
	SetMapColor(0);
	printf("Stage : %d", stage_state + 1);
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

int MapStateRefund(int x, int y)
{
	int result = map_state[stage_state][x][y];

	return result;
}
///////////////////////////////////////
void SetMapStage_0()
{
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//첫번째 줄은 무조건 다 빈칸인 -1으로 만들어 준다
			if (y == 0)
			{
				map_info[0][x][y] = -1;
				if (x == DOOR_LOC)
				{
					map_info[0][x][y] = 13;

				}
				if ((MAP_INFO_X / 2 - 4) <= x && x <= (MAP_INFO_X / 2 + 4)) {
					map_info[0][x][y] = 14;

				}
				continue;
			}
			//안뚫리는 벽 만들기
			//오른쪽 왼쪽 각각 두번째 칸씩은 더이상 안뚫리는 벽을 만든다
			if (x == 0 || x == 1 || x == MAP_INFO_X - 2 || x == MAP_INFO_X - 1)
			{
				map_info[0][x][y] = 1;
			}
			//첫번째 기분으로 중간으로 좌우 5칸씩은 상점이 놓일 공간을 만들어 낸다
			if (y == 1)
			{
				if ((x >= MAP_INFO_X / 2 - 5) && (x <= MAP_INFO_X / 2 + 5))
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 2)
			{

			}
			if (y == 3)
			{
				if (x >= 8 && x <= 12)
				{
					map_info[0][x][y] = 2;
				}

			}
			if (y == 4)
			{
				if (x >= 8 && x <= 12)
				{
					map_info[0][x][y] = 2;
				}
			}
			if (y == 5)
			{
				if (x >= 31 && x <= 40)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 6)
			{
				if (x >= 14 && x <= 18)
				{
					map_info[0][x][y] = 3;
				}
				if (x >= 32 && x <= 40)
				{
					map_info[0][x][y] = 2;
				}
				if (x >= 49 && x <= 51)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 7)
			{
				if (x >= 14 && x <= 18)
				{
					map_info[0][x][y] = 3;
				}
				if (x >= 32 && x <= 40)
				{
					map_info[0][x][y] = 2;
				}
				if (x == 50)
				{
					map_info[0][x][y] = 2;
				}
			}
			if (y == 8)
			{
				if (x == 49)
				{
					map_info[0][x][y] = 2;
				}
				if (x == 50)
				{
					map_info[0][x][y] = 3;
				}
				if (x == 51)
				{
					map_info[0][x][y] = 2;
				}
			}
			if (y == 9)
			{
				if (x == 50)
				{
					map_info[0][x][y] = 2;
				}
			}
			if (y == 10)
			{
				if (x >= 2 && x <= 6)
				{
					map_info[0][x][y] = 4;
				}
				if (x >= 8 && x <= 14)
				{
					map_info[0][x][y] = 3;
				}
				if (x == 50)
				{
					map_info[0][x][y] = 2;
				}
			}
			if (y == 11)
			{
				if (x >= 37 && x <= 42)
				{
					map_info[0][x][y] = 3;
				}
			}
			if (y == 12)
			{
				if (x >= 38 && x <= 43)
				{
					map_info[0][x][y] = 3;
				}
				if (x == 54)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 13)
			{
				if (x >= 4 && x <= 12)
				{
					map_info[0][x][y] = 2;
				}
				if (x >= 18 && x <= 22)
				{
					map_info[0][x][y] = 3;
				}
				if (x >= 24 && x <= 28)
				{
					map_info[0][x][y] = 1;
				}
				if (x == 53)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 14)
			{
				if (x == 52)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 15)
			{
				if (x == 51)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 16)
			{
				if (x >= 8 && x <= 13)
				{
					map_info[0][x][y] = 2;
				}
				if (x >= 14 && x <= 18)
				{
					map_info[0][x][y] = 4;
				}
				if (x >= 28 && x <= 36)
				{
					map_info[0][x][y] = 2;
				}
			}
			if (y == 17)
			{
				if (x == 28 || x == 29)
				{
					map_info[0][x][y] = 5;
				}
			}
			if (y == 18)
			{
				if (x == 27 || x == 28)
				{
					map_info[0][x][y] = 5;
				}
			}
			if (y == 19)
			{
				if (x >= 42 && x <= 46)
				{
					map_info[0][x][y] = 5;
				}
				if (x >= 52 && x <= 58)
				{
					map_info[0][x][y] = 2;
				}
				if (x == 26 || x == 27)
				{
					map_info[0][x][y] = 5;
				}
			}
			if (y == 20)
			{

			}
			if (y == 21)
			{

			}
			if (y == 22)
			{
				if (x == 10)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 23)
			{
				if (x >= 5 && x <= 7)
				{
					map_info[0][x][y] = 4;
				}
				if (x == 10)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 24)
			{
				if (x >= 4 && x <= 6)
				{
					map_info[0][x][y] = 4;
				}
				if (x == 10)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 25)
			{
				if (x >= 3 && x <= 5)
				{
					map_info[0][x][y] = 4;
				}
				if (x == 10)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 26)
			{
				if (x >= 3 && x <= 5)
				{
					map_info[0][x][y] = 4;
				}
				if (x >= 16 && x <= 22)
				{
					map_info[0][x][y] = 2;
				}
				if (x >= 28 && x <= 36)
				{
					map_info[0][x][y] = 3;
				}
				if (x >= 46 && x <= 50)
				{
					map_info[0][x][y] = 5;
				}
				if (x >= 52 && x <= 58)
				{
					map_info[0][x][y] = 4;
				}
				if (x == 10)
				{
					map_info[0][x][y] = 1;
				}
			}
			if (y == 27)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 28)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 29)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 30)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 31)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 32)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 33)
			{
				map_info[0][x][y] = 1;
			}
			if (y == 34)
			{
				map_info[0][x][y] = 1;
			}
		}
	}
}

void SetMapStage_1()
{
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//첫번째 줄은 무조건 다 빈칸인 -1으로 만들어 준다
			if (y == 0)
			{
				map_info[1][x][y] = -1;
				if ((MAP_INFO_X / 2 - 4) <= x && x <= (MAP_INFO_X / 2 + 4)) {
					map_info[1][x][y] = 14;

				}
				if (x == DOOR_LOC)
					map_info[1][x][y] = 13;
				continue;
			}
			//안뚫리는 벽 만들기
			//오른쪽 왼쪽 각각 두번째 칸씩은 더이상 안뚫리는 벽을 만든다
			if (x == 0 || x == 1 || x == MAP_INFO_X - 2 || x == MAP_INFO_X - 1)
			{
				map_info[1][x][y] = 1;
			}
			//첫번째 기분으로 중간으로 좌우 5칸씩은 상점이 놓일 공간을 만들어 낸다
			if (y == 1)
			{
				if ((x >= MAP_INFO_X / 2 - 5) && (x <= MAP_INFO_X / 2 + 5))
				{
					map_info[1][x][y] = 1;
				}
			}
			if (y == 2)
			{
				if (x >= 4 && x <= 6)
				{
					map_info[1][x][y] = 2;
				}
				if (x >= 24 && x <= 30)
				{
					map_info[1][x][y] = 2;
				}
			}
			if (y == 3)
			{
				if (x >= 9 && x <= 11)
				{
					map_info[1][x][y] = 3;
				}
				if (x >= 30 && x <= 34)
				{
					map_info[1][x][y] = 3;
				}
				if (x >= 54 && x <= 57)
				{
					map_info[1][x][y] = 3;
				}
			}
			if (y == 4)
			{
				if (x == 10 || x == 12)
					map_info[1][x][y] = 3;
				if (x == 11)
					map_info[1][x][y] = 2;
				if (x >= 42 && x <= 47)
					map_info[1][x][y] = 2;
				if (x >= 54 && x <= 57)
					map_info[1][x][y] = 3;
			}
			if (y == 5)
			{
				if (x >= 11 && x <= 13)
				{
					map_info[1][x][y] = 3;
				}
				if (x >= STAGE_1_MONSTER1_SET_X - 2 && x <= STAGE_1_MONSTER1_SET_X + 7)
				{
					map_info[1][x][y] = -1;
				}
				if (x >= 54 && x <= 57)
					map_info[1][x][y] = 3;

			}
			if (y == 6)
			{
				if (x >= STAGE_1_MONSTER1_SET_X - 2 && x <= STAGE_1_MONSTER1_SET_X + 7)
				{
					map_info[1][x][y] = -1;
				}
				if (x >= 54 && x <= 56)
					map_info[1][x][y] = 2;
			}
			if (y == 7)
			{
				if (x >= STAGE_1_MONSTER1_SET_X - 2 && x <= STAGE_1_MONSTER1_SET_X + 7)
				{
					map_info[1][x][y] = 1;
				}
				if (x >= 54 && x <= 56)
					map_info[1][x][y] = 2;

			}
			if (y == 8)
			{
				if (x == 22)
					map_info[1][x][y] = 1;
				if (x == 27)
					map_info[1][x][y] = 1;
				if (x >= 54 && x <= 56)
					map_info[1][x][y] = 2;
			}
			if (y == 9)
			{
				if (x == 21)
					map_info[1][x][y] = 1;
				if (x >= 22 && x <= 27)
					map_info[1][x][y] = 4;
				if (x == 28)
					map_info[1][x][y] = 1;
			}
			if (y == 10)
			{
				if (x >= STAGE_1_MONSTER2_SET_X - 4 && x <= STAGE_1_MONSTER2_SET_X + 4)
				{
					map_info[1][x][y] = -1;
				}
			}
			if (y == 11)
			{
				if (x >= STAGE_1_MONSTER2_SET_X - 4 && x <= STAGE_1_MONSTER2_SET_X + 4)
				{
					map_info[1][x][y] = -1;
				}
			}
			if (y == 12)
			{
				if (x >= STAGE_1_MONSTER2_SET_X - 4 && x <= STAGE_1_MONSTER2_SET_X + 4)
				{
					map_info[1][x][y] = 1;
				}
			}
			if (y == 13)
			{
				if (x >= 12 && x <= 17)
				{
					map_info[1][x][y] = 1;
				}
			}
			if (y == 14)
			{

				if (x >= 14 && x <= 16)
				{
					map_info[1][x][y] = 6;
				}
				if (x == 17)
				{
					map_info[1][x][y] = 1;
				}
			}
			if (y == 15)
			{
				if (x >= 12 && x <= 17)
				{
					map_info[1][x][y] = 1;
				}
				if (x == 24 || x == 32 || x == 40)
				{
					map_info[1][x][y] = 1;
				}
			}
			if (y == 16)
			{
				if (x >= 23 && x <= 25)
				{
					map_info[1][x][y] = 1;
				}
				if (x >= 31 && x <= 34)
				{
					map_info[1][x][y] = 1;
				}
				if (x >= 38 && x <= 41)
				{
					map_info[1][x][y] = 1;
				}
			}
			if (y == 17)
			{
				if (x >= 30 && x <= 34)
				{
					map_info[1][x][y] = 4;
				}
				if (x == 35)
					map_info[1][x][y] = 1;
				if (x == 37)
					map_info[1][x][y] = 1;
				if (x >= 38 && x <= 42)
				{
					map_info[1][x][y] = 5;
				}
			}
			if (y == 18)
			{
				if (x >= 31 && x <= 35)
					map_info[1][x][y] = 4;
				if (x == 36)
					map_info[1][x][y] = 1;
				if (x >= 37 && x <= 41)
					map_info[1][x][y] = 5;
			}
			if (y == 19)
			{
				if (x == 32)
					map_info[1][x][y] = 1;
				if (x == 40)
					map_info[1][x][y] = 1;
				if (x >= 33 && x <= 36)
					map_info[1][x][y] = 4;
				if (x >= 37 && x <= 39)
					map_info[1][x][y] = 5;
			}
			if (y == 20)
			{
				if (x >= 12 && x <= 20)
				{
					map_info[1][x][y] = 5;
				}
				if (x == 33)
					map_info[1][x][y] = 1;
				if (x >= 34 && x <= 38)
					map_info[1][x][y] = 2;
				if (x == 39)
					map_info[1][x][y] = 1;
			}
			if (y == 21)
			{
				if (x == 34 || x == 35)
					map_info[1][x][y] = 1;
				if (x == 37 || x == 38)
					map_info[1][x][y] = 1;
				if (x == 36)
					map_info[1][x][y] = 2;
				if (x >= 12 && x <= 20)
				{
					map_info[1][x][y] = 6;
				}
				if (x >= 49)
					map_info[1][x][y] = 1;
			}
			if (y == 22)
			{
				if (x == 36)
					map_info[1][x][y] = 1;
				if (x >= 53)
					map_info[1][x][y] = 1;
				if (x == 52)
					map_info[1][x][y] = 8;
			}
			if (y == 23)
			{
				if (x >= 2 && x <= 8)
					map_info[1][x][y] = 1;
			}
			if (y == 24)
			{
				if (x >= 2 && x <= 8)
					map_info[1][x][y] = 1;
			}
			if (y == 25)
			{
				if (x >= 2 && x <= 8)
					map_info[1][x][y] = 1;
			}
			if (y == 26)
			{

			}
			if (y == 27)
			{

			}
			if (y == 28)
			{
				if (x >= 5 && x <= 10)
				{
					map_info[1][x][y] = 1;
				}
				if (x >= 15 && x <= 30)
					map_info[1][x][y] = 1;
			}
			if (y == 29)
			{
				if (x >= 5 && x <= 9)
				{
					map_info[1][x][y] = 7;
				}
				if (x == 10)
				{
					map_info[1][x][y] = 1;
				}
				if (x == 47)
				{
					map_info[1][x][y] = 7;
				}
				if (x >= 15 && x <= 30)
					map_info[1][x][y] = 1;
			}
			if (y == 30)
			{
				if (x >= 5 && x <= 9)
				{
					map_info[1][x][y] = 7;
				}
				if (x == 10)
				{
					map_info[1][x][y] = 1;
				}
				if (x >= 46 && x <= 48)
				{
					map_info[1][x][y] = 6;
				}
				if (x >= 15 && x <= 30)
					map_info[1][x][y] = 1;
			}
			if (y == 31)
			{
				if (x >= 45 && x <= 49)
				{
					map_info[1][x][y] = 5;
				}
				if (x >= 15 && x <= 30)
					map_info[1][x][y] = 1;
			}
			if (y == 32)
			{
				if (x >= 46 && x <= 48)
				{
					map_info[1][x][y] = 6;
				}
				if (x >= 15 && x <= 30)
					map_info[1][x][y] = 1;
			}
			if (y == 33)
			{
				if (x == 47)
				{
					map_info[1][x][y] = 7;
				}
				if (x >= 15 && x <= 30)
					map_info[1][x][y] = 1;


			}
			if (y == 34)
			{
				map_info[1][x][y] = 1;

			}
		}
	}
}

void SetMapStage_2()
{
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//첫번째 줄은 무조건 다 빈칸인 -1으로 만들어 준다

			if (y == 0)
			{

				map_info[2][x][y] = -1;
				if ((MAP_INFO_X / 2 - 4) <= x && x <= (MAP_INFO_X / 2 + 4)) {
					map_info[2][x][y] = 14;

				}
				if (x == DOOR_LOC)
				{
					map_info[2][x][y] = 13;

				}
				continue;
			}

			//안뚫리는 벽 만들기
			//오른쪽 왼쪽 각각 두번째 칸씩은 더이상 안뚫리는 벽을 만든다
			if (x == 0 || x == 1 || x == MAP_INFO_X - 2 || x == MAP_INFO_X - 1)
			{
				map_info[2][x][y] = 1;
			}
			//첫번째 기분으로 중간으로 좌우 5칸씩은 상점이 놓일 공간을 만들어 낸다
			if (y == 1)
			{
				if ((x >= MAP_INFO_X / 2 - 5) && (x <= MAP_INFO_X / 2 + 5))
				{
					map_info[2][x][y] = 1;
				}
			}
			if (y == 2)
			{

			}
			if (y == 3)
			{

			}
			if (y == 4)
			{
				if (x >= 30 && x <= 31)
				{
					map_info[2][x][y] = 9;
				}
				if (x == 29 || x == 32)
				{
					map_info[2][x][y] = 1;
				}


				if (x == 7) { //1
					map_info[2][x][y] = 5;
				}

				if (x == 16) { //4
					map_info[2][x][y] = 3;
				}


				if (40 <= x && x <= 46) { //=
					map_info[2][x][y] = 2;
				}


			}
			if (y == 5)
			{
				if (x >= 30 && x <= 31)
				{
					map_info[2][x][y] = 1;
				}


				if (x == 6 || x == 7) { //1
					map_info[2][x][y] = 2;
				}

				if (x == 16 || x == 17) { //4
					map_info[2][x][y] = 3;
				}
			}
			if (y == 6)
			{
				if (x == 52)
				{
					map_info[2][x][y] = 4;
				}

				if (40 <= x && x <= 46) { //=
					map_info[2][x][y] = 2;
				}


				if (x == 5 || x == 7) { //1
					map_info[2][x][y] = 2;
				}

				if (x == 16 || x == 18) { //4
					map_info[2][x][y] = 4;
				}

			}
			if (y == 7)
			{
				if (x == 52)
				{
					map_info[2][x][y] = 4;
				}


				if (x == 7) { //1
					map_info[2][x][y] = 5;
				}

				if (x == 16 || x == 19) { //4
					map_info[2][x][y] = 3;
				}
			}
			if (y == 8)
			{
				if (x == 52)
				{
					map_info[2][x][y] = 4;
				}


				if (x == 7) { //1
					map_info[2][x][y] = 5;
				}

				if (12 <= x && x <= 20) { //4
					map_info[2][x][y] = 4;
				}
			}
			if (y == 9)
			{
				if (x >= STAGE_2_MONSTER3_SET_X - 9 && x <= STAGE_2_MONSTER3_SET_X + 1)
				{
					map_info[2][x][y] = -1;
				}

				if (5 <= x && x <= 9) { //1
					map_info[2][x][y] = 2;
				}

				if (x == 16) { //4
					map_info[2][x][y] = 3;
				}
			}
			if (y == 10)
			{
				if (x >= STAGE_2_MONSTER3_SET_X - 9 && x <= STAGE_2_MONSTER3_SET_X + 1)
				{
					map_info[2][x][y] = -1;
				}

				if (x == 16) { //4
					map_info[2][x][y] = 3;
				}

				if (23 <= x && x <= 25) { //2
					map_info[2][x][y] = 4;
				}
			}
			if (y == 11)
			{
				if (x >= STAGE_2_MONSTER3_SET_X - 9 && x <= STAGE_2_MONSTER3_SET_X + 1)
				{
					map_info[2][x][y] = 1;
				}
				if (x == 22 || x == 26) { //2
					map_info[2][x][y] = 5;
				}
			}
			if (y == 12)
			{
				if (x == 22 || x == 26) { //2
					map_info[2][x][y] = 5;
				}
			}
			if (y == 13)
			{
				if (x >= STAGE_2_MONSTER4_SET_X - 3 && x <= STAGE_2_MONSTER4_SET_X + 5)
				{
					map_info[2][x][y] = -1;
				}
				if (x == 25) { //2
					map_info[2][x][y] = 5;
				}
			}
			if (y == 14)
			{
				if (x >= STAGE_2_MONSTER4_SET_X - 3 && x <= STAGE_2_MONSTER4_SET_X + 5)
				{
					map_info[2][x][y] = -1;
				}
				if (6 <= x && x <= 10) { //5
					map_info[2][x][y] = 2;
				}
				if (x == 24) { //2
					map_info[2][x][y] = 5;
				}
			}
			if (y == 15)
			{
				if (x >= STAGE_2_MONSTER4_SET_X - 3 && x <= STAGE_2_MONSTER4_SET_X + 5)
				{
					map_info[2][x][y] = 1;
				}
				if (x == 6) { //5
					map_info[2][x][y] = 3;
				}
				if (x == 23) { //2
					map_info[2][x][y] = 3;
				}
			}
			if (y == 16)
			{
				if (x == 6) { //5
					map_info[2][x][y] = 2;
				}
				if (x == 22) { //2
					map_info[2][x][y] = 3;
				}
			}
			if (y == 17)
			{
				if (6 <= x && x <= 10) { //5
					map_info[2][x][y] = 3;
				}
				if (22 <= x && x <= 27) { //2
					map_info[2][x][y] = 4;
				}
			}
			if (y == 18)
			{
				if (x >= 23 && x <= 35)
				{
					map_info[2][x][y] = 1;
				}

				if (x == 11) { //5
					map_info[2][x][y] = 2;
				}
				if (40 <= x && x <= 41 || 50 <= x && x <= 51) { //:)
					map_info[2][x][y] = 6;
				}

			}
			if (y == 19)
			{

				if (x == 11) { //5
					map_info[2][x][y] = 2;
				}

				if (40 <= x && x <= 41 || 50 <= x && x <= 51) { //:)
					map_info[2][x][y] = 6;
				}

			}
			if (y == 20)
			{

				if (6 <= x && x <= 10) { //5
					map_info[2][x][y] = 3;
				}
			}
			if (y == 21)
			{
				if (x >= STAGE_2_MONSTER5_SET_X - 4 && x <= STAGE_2_MONSTER5_SET_X + 6)
				{
					map_info[2][x][y] = -1;
				}

			}
			if (y == 22)
			{
				if (x >= STAGE_2_MONSTER5_SET_X - 4 && x <= STAGE_2_MONSTER5_SET_X + 6)
				{
					map_info[2][x][y] = -1;
				}
				if (x == 39 || x == 52) { //:)
					map_info[2][x][y] = 2;
				}
			}
			if (y == 23)
			{
				if (x >= STAGE_2_MONSTER5_SET_X - 4 && x <= STAGE_2_MONSTER5_SET_X + 6)
				{
					map_info[2][x][y] = 1;
				}
				if (x == 40 || x == 51) { //:)
					map_info[2][x][y] = 2;
				}
			}
			if (y == 24)
			{
				if (41 <= x && x <= 50) { //:)
					map_info[2][x][y] = 2;
				}
			}
			if (y == 25)
			{
				if (x >= 6 && x <= 12)
				{
					map_info[2][x][y] = 4;
				}
				if (x >= 23 && x <= 27)
				{
					map_info[2][x][y] = 5;
				}
			}
			if (y == 26)
			{
				if (x >= 6 && x <= 12)
				{
					map_info[2][x][y] = 4;
				}
				if (x >= 23 && x <= 26)
				{
					map_info[2][x][y] = 5;
				}
			}
			if (y == 27)
			{
				if (x >= 40 && x <= 47)
				{
					map_info[2][x][y] = 5;
				}
				if (x >= 51 && x <= 53)
				{
					map_info[2][x][y] = 6;
				}
			}
			if (y == 28)
			{
				if (x >= 40 && x <= 45)
				{
					map_info[2][x][y] = 5;
				}
				if (x >= 52 && x <= 54)
				{
					map_info[2][x][y] = 6;
				}
			}
			if (y == 29)
			{

			}
			if (y == 30)
			{

			}
			if (y == 31)
			{

			}
			if (y == 32)
			{

			}
			if (y == 33)
			{

			}
			if (y == 34)
			{
				map_info[2][x][y] = 1;

			}

		}
	}
}

void SetMapStage_3()
{
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//첫번째 줄은 무조건 다 빈칸인 -1으로 만들어 준다
			if (y == 0)
			{

				map_info[3][x][y] = -1;
				if ((MAP_INFO_X / 2 - 4) <= x && x <= (MAP_INFO_X / 2 + 4)) {
					map_info[3][x][y] = 14;

				}
				if (x == DOOR_LOC)
				{
					map_info[3][x][y] = 13;
				}
				continue;
			}
			//안뚫리는 벽 만들기
			//오른쪽 왼쪽 각각 두번째 칸씩은 더이상 안뚫리는 벽을 만든다
			if (x == 0 || x == 1 || x == MAP_INFO_X - 2 || x == MAP_INFO_X - 1)
			{
				map_info[3][x][y] = 1;
			}
			//첫번째 기분으로 중간으로 좌우 5칸씩은 상점이 놓일 공간을 만들어 낸다
			if (y == 1)
			{
				if ((x >= MAP_INFO_X / 2 - 5) && (x <= MAP_INFO_X / 2 + 5))
				{
					map_info[3][x][y] = 1;
				}
			}
			if (y == 2)
			{
				if (x >= 4 && x <= 6)
				{
					map_info[3][x][y] = 1;
				}
				if (x >= 24 && x <= 30)
				{
					map_info[3][x][y] = 2;
				}
				if (x == 9 || x == 10)
					map_info[3][x][y] = 1;
			}
			if (y == 3)
			{
				if (x >= 30 && x <= 31)
					map_info[3][x][y] = 1;
				if (x >= 4 && x <= 7)
					map_info[3][x][y] = 4;
				if (x == 11 || x == 10)
					map_info[3][x][y] = 1;

			}
			if (y == 4)
			{
				if (x >= 30 && x <= 31)
					map_info[3][x][y] = 9;
				if (x == 29 || x == 32 || x == 52)
					map_info[3][x][y] = 1;
				if (x >= 5 && x <= 8)
					map_info[3][x][y] = 4;
				if (x == 11 || x == 12)
					map_info[3][x][y] = 1;
			}
			if (y == 5)
			{
				if (x >= 30 && x <= 31)
					map_info[3][x][y] = 1;
				if (x >= 4 && x <= 7)
					map_info[3][x][y] = 4;
				if (x == 51)
					map_info[3][x][y] = 1;
				if (x >= 43 && x <= 46)
					map_info[3][x][y] = 1;
			}
			if (y == 6)
			{
				if (x == 52)
				{
					map_info[3][x][y] = 4;
				}
				if (x == 50 || x == 42)
					map_info[3][x][y] = 1;
				if (x >= 43 && x <= 46)
					map_info[3][x][y] = 2;
			}
			if (y == 7)
			{
				if (x == 52)
					map_info[3][x][y] = 4;
				if (x == 49 || x == 41)
					map_info[3][x][y] = 1;
				if (x >= 43 && x <= 46)
					map_info[3][x][y] = 2;

			}
			if (y == 8)
			{
				if (x == 52)
				{
					map_info[3][x][y] = 4;
				}
				if (x == 50 || x == 40)
					map_info[3][x][y] = 1;
				if (x >= 43 && x <= 46)
					map_info[3][x][y] = 2;
				if (x >= 34 && x <= 40)
					map_info[3][x][y] = 1;
			}
			if (y == 9)
			{
				if (x >= 19 && x <= 23)
				{
					map_info[3][x][y] = 1;
				}
				if (x == 52)
				{
					map_info[3][x][y] = 4;
				}
				if (x == 51 || x == 40)
					map_info[3][x][y] = 1;
				if (x >= 4 && x <= 9)
					map_info[3][x][y] = 1;
				if (x >= 35 && x <= 39)
					map_info[3][x][y] = 3;
			}
			if (y == 10)
			{
				if (x >= 19 && x <= 23)
				{
					map_info[3][x][y] = 5;
				}
				if (x == 52)
				{
					map_info[3][x][y] = 4;
				}
				if (x == 24 || x == 50 || x == 40)
				{
					map_info[3][x][y] = 1;
				}
				if (x >= 35 && x <= 39)
					map_info[3][x][y] = 3;
			}
			if (y == 11)
			{
				if (x >= 19 && x <= 21)
				{
					map_info[3][x][y] = 5;
				}
				if (x == 25 || x == 49)
				{
					map_info[3][x][y] = 1;
				}
			}
			if (y == 12)
			{
				if (x >= 4 && x <= 6)
					map_info[3][x][y] = 6;
				if (x == 26 || x == 15 || x == 48)
					map_info[3][x][y] = 1;
			}
			if (y == 13)
			{
				if (x == 13)
					map_info[3][x][y] = 1;
				if (x >= STAGE_3_MONSTER6_SET_X - 5 && x <= STAGE_3_MONSTER6_SET_X + 6)
					map_info[3][x][y] = 1;
				if (x == 27)
					map_info[3][x][y] = 1;
			}
			if (y == 14)
			{
				if (x >= STAGE_3_MONSTER6_SET_X - 5 && x <= STAGE_3_MONSTER6_SET_X + 6)
					map_info[3][x][y] = -1;
				if (x == 14 || x == 12)
					map_info[3][x][y] = 1;
				if (x == 28)
					map_info[3][x][y] = 1;
			}
			if (y == 15)
			{
				if (x >= STAGE_3_MONSTER6_SET_X - 5 && x <= STAGE_3_MONSTER6_SET_X + 6)
				{
					map_info[3][x][y] = -1;
				}
				if (x == 29 || x == 11 || x == 18)
				{
					map_info[3][x][y] = 1;
				}
			}
			if (y == 16)
			{
				if (x >= STAGE_3_MONSTER6_SET_X - 5 && x <= STAGE_3_MONSTER6_SET_X + 6)
				{
					map_info[3][x][y] = 1;
				}
				if (x == 30 || x == 10 || x == 19)
				{
					map_info[3][x][y] = 1;
				}
			}
			if (y == 17)
			{
				if (x == 31 || x == 9 || x == 20)
				{
					map_info[3][x][y] = 1;
				}
			}
			if (y == 18)
			{
				if (x == 32 || x == 8 || x == 21)
				{
					map_info[3][x][y] = 1;
				}

			}
			if (y == 19)
			{
				if (x >= STAGE_3_MONSTER7_SET_X - 5 && x <= STAGE_3_MONSTER7_SET_X + 4)
				{
					map_info[3][x][y] = 1;
				}
				if (x == 11 || x == 17)
					map_info[3][x][y] = 1;

			}
			if (y == 20)
			{
				if (x >= STAGE_3_MONSTER7_SET_X - 5 && x <= STAGE_3_MONSTER7_SET_X + 4)
				{
					map_info[3][x][y] = -1;
				}
				if (x == 12 || x == 16)
					map_info[3][x][y] = 1;
				if (x >= 13 && x <= 15)
					map_info[3][x][y] = 6;
				if (x == 47 || x == 49)
					map_info[3][x][y] = 5;
			}
			if (y == 21)
			{
				if (x >= STAGE_3_MONSTER7_SET_X - 5 && x <= STAGE_3_MONSTER7_SET_X + 4)
				{
					map_info[3][x][y] = -1;
				}
				if (x == 13 || x == 15)
					map_info[3][x][y] = 1;
				if (x == 14)
					map_info[3][x][y] = 7;
				if (x == 47 || x == 49)
					map_info[3][x][y] = 5;
			}
			if (y == 22)
			{
				if (x >= STAGE_3_MONSTER7_SET_X - 5 && x <= STAGE_3_MONSTER7_SET_X + 4)
				{
					map_info[3][x][y] = 1;
				}
				if (x == 14)
					map_info[3][x][y] = 1;
				if (x >= 46 && x <= 50)
					map_info[3][x][y] = 5;
			}
			if (y == 23)
			{
				if (x == 47||x==49)
					map_info[3][x][y] = 5;
				if (x == 18)
					map_info[3][x][y] = 1;
			}
			if (y == 24)
			{
				if(x==17)
					map_info[3][x][y] = 1;
			}
			if (y == 25)
			{
				if (x >= 6 && x <= 12)
				{
					map_info[3][x][y] = 4;
				}
				if (x >= 23 && x <= 27)
				{
					map_info[3][x][y] = 5;
				}
				if (x == 36 || x == 44 || x == 52 || x == 16)
					map_info[3][x][y] = 1;
			}
			if (y == 26)
			{
				if (x >= 6 && x <= 12)
				{
					map_info[3][x][y] = 4;
				}
				if (x >= 23 && x <= 26)
				{
					map_info[3][x][y] = 5;
				}
				if (x == 35 || x == 43 || x == 51 || x == 15)
					map_info[3][x][y] = 1;
			}
			if (y == 27)
			{
				if (x >= 40 && x <= 47)
				{
					map_info[3][x][y] = 5;
				}
				if (x >= 51 && x <= 53)
				{
					map_info[3][x][y] = 6;
				}
				if (x == 34 || x == 42 || x == 50||x==14)
					map_info[3][x][y] = 1;
			}
			if (y == 28)
			{
				if (x >= 40 && x <= 45)
				{
					map_info[3][x][y] = 5;
				}
				if (x >= 52 && x <= 54)
				{
					map_info[3][x][y] = 6;
				}
				if (x >= STAGE_3_MONSTER8_SET_X - 3 && x <= STAGE_3_MONSTER8_SET_X + 7)
				{
					map_info[3][x][y] = 1;
				}
				if (x == 33 || x == 41 || x == 49)
					map_info[3][x][y] = 1;
			}
			if (y == 29)
			{
				if (x >= STAGE_3_MONSTER8_SET_X - 3 && x <= STAGE_3_MONSTER8_SET_X + 7)
				{
					map_info[3][x][y] = -1;
				}
				if (x == 32 || x == 40 || x == 48)
					map_info[3][x][y] = 1;
			}
			if (y == 30)
			{
				if (x >= STAGE_3_MONSTER8_SET_X - 3 && x <= STAGE_3_MONSTER8_SET_X + 7)
				{
					map_info[3][x][y] = -1;
				}
				if (x == 31 || x == 39 || x == 47)
					map_info[3][x][y] = 1;
			}
			if (y == 31)
			{
				if (x >= STAGE_3_MONSTER8_SET_X - 3 && x <= STAGE_3_MONSTER8_SET_X + 7)
				{
					map_info[3][x][y] = 1;
				}
				if (x == 30 || x == 38 || x == 46)
					map_info[3][x][y] = 1;
			}
			if (y == 32)
			{
				if (x >= STAGE_3_MONSTER8_SET_X - 2 && x <= STAGE_3_MONSTER8_SET_X + 4)
				{
					map_info[3][x][y] = 7;
				}
				if (x >= 3 && x <= 7)
				{
					map_info[3][x][y] = 9;
				}
			}
			if (y == 33)
			{
				if (x >= STAGE_3_MONSTER8_SET_X - 1 && x <= STAGE_3_MONSTER8_SET_X + 1)
				{
					map_info[3][x][y] = 8;
				}
				if (x >= 3 && x <= 5)
				{
					map_info[3][x][y] = 9;
				}
			}
			if (y == 34)
			{
				map_info[3][x][y] = 1;
			}

		}
	}
}


void SetMapStage_4()
{
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//첫번째 줄은 무조건 다 빈칸인 -1으로 만들어 준다
			if (y == 0)
			{

				map_info[4][x][y] = -1;
				if ((MAP_INFO_X / 2 - 4) <= x && x <= (MAP_INFO_X / 2 + 4)) {
					map_info[4][x][y] = 14;

				}
				/*if (x == DOOR_LOC)
				{
					map_info[4][x][y] = 13;

				}*/
				continue;
			}

			//안뚫리는 벽 만들기
			//오른쪽 왼쪽 각각 두번째 칸씩은 더이상 안뚫리는 벽을 만든다
			if (x == 0 || x == 1 || x == MAP_INFO_X - 2 || x == MAP_INFO_X - 1)
			{
				map_info[4][x][y] = 1;
			}
			//첫번째 기분으로 중간으로 좌우 5칸씩은 상점이 놓일 공간을 만들어 낸다
			if (y == 1)
			{
				if ((x >= MAP_INFO_X / 2 - 5) && (x <= MAP_INFO_X / 2 + 5))
				{
					map_info[4][x][y] = 1;
				}
			}
			if (y == 2)
			{

			}
			if (y == 3)
			{
				if (x >= 23 && x <= 24)
					map_info[4][x][y] = 5;
			}
			if (y == 4)
			{
				if (x >= 12 && x <= 17)
					map_info[4][x][y] = 3;
				if (x >= 23 && x <= 24)
					map_info[4][x][y] = 5;
				if (x >= 52 && x <= 55)
					map_info[4][x][y] = 4;
				if (x == 4 || x == 23)
					map_info[4][x][y] = 5;
			}
			if (y == 5)
			{
				if (x >= 12 && x <= 17)
					map_info[4][x][y] = 3;
				if (x >= 32 && x <= 37)
					map_info[4][x][y] = 6;
				if (x >= 52 && x <= 55)
					map_info[4][x][y] = 4;
				if (x == 42)
					map_info[4][x][y] = 6;
			}
			if (y == 6)
			{
				if (x >= 12 && x <= 17)
					map_info[4][x][y] = 3;
				if (x >= 52 && x <= 55)
					map_info[4][x][y] = 4;
				if (x == 33)
					map_info[4][x][y] = 7;
			}
			if (y == 7)
			{
				if (x == 24 || x == 34 || x == 44)
					map_info[4][x][y] = 1;
			}
			if (y == 8)
			{
				if (x == STAGE_4_MONSTER9_SET_X + 8 || x == STAGE_4_MONSTER9_SET_X + 9)
					map_info[4][x][y] = 1;
				if (x == 23 || x == 33 || x == 43)
					map_info[4][x][y] = 1;
			}
			if (y == 9)
			{
				if (x == STAGE_4_MONSTER9_SET_X + 7 || x == STAGE_4_MONSTER9_SET_X + 8)
					map_info[4][x][y] = 1;
				if (x == 22 || x == 32 || x == 42)
					map_info[4][x][y] = 1;
			}
			if (y == 10)
			{
				if (x >= STAGE_4_MONSTER9_SET_X - 3 && x <= STAGE_4_MONSTER9_SET_X + 6)
				{
					map_info[4][x][y] = 1;
				}
				if (x == 21 || x == 31 || x == 41)
					map_info[4][x][y] = 1;
			}
			if (y == 11)
			{
				if (x >= STAGE_4_MONSTER9_SET_X - 3 && x <= STAGE_4_MONSTER9_SET_X + 6)
				{
					map_info[4][x][y] = -1;
				}
				if (x == STAGE_4_MONSTER9_SET_X + 8 || x == STAGE_4_MONSTER9_SET_X + 9 || x == 20 || x == 30 || x == 40)
					map_info[4][x][y] = 1;
				if (x >= 24 && x <= 26)
					map_info[4][x][y] = 4;
				if (x >= 34 && x <= 36)
					map_info[4][x][y] = 5;
			}
			if (y == 12)
			{
				if (x >= STAGE_4_MONSTER9_SET_X - 3 && x <= STAGE_4_MONSTER9_SET_X + 6)
				{
					map_info[4][x][y] = -1;
				}
				if (x == STAGE_4_MONSTER9_SET_X + 7 || x == STAGE_4_MONSTER9_SET_X + 8)
					map_info[4][x][y] = 1;
				if (x == STAGE_4_MONSTER10_SET_X - 6 || x == STAGE_4_MONSTER10_SET_X - 7)
					map_info[4][x][y] = 1;
				if (x >= 24 && x <= 26)
					map_info[4][x][y] = 4;
				if (x >= 34 && x <= 36)
					map_info[4][x][y] = 5;
			}
			if (y == 13)
			{
				if (x >= STAGE_4_MONSTER9_SET_X - 3 && x <= STAGE_4_MONSTER9_SET_X + 6)
				{
					map_info[4][x][y] = 1;
				}
				if (x == STAGE_4_MONSTER10_SET_X - 6 || x == STAGE_4_MONSTER10_SET_X - 5)
					map_info[4][x][y] = 1;

			}
			if (y == 14)
			{
				if (x >= STAGE_4_MONSTER10_SET_X - 4 && x <= STAGE_4_MONSTER10_SET_X + 4)
				{
					map_info[4][x][y] = 1;
				}

			}
			if (y == 15)
			{
				if (x >= STAGE_4_MONSTER10_SET_X - 4 && x <= STAGE_4_MONSTER10_SET_X + 4)
				{
					map_info[4][x][y] = -1;
				}
				if (x == STAGE_4_MONSTER10_SET_X - 7 || x == STAGE_4_MONSTER10_SET_X + 5)
					map_info[4][x][y] = 1;
				if (x == 15 || x == 25 || x == 35)
					map_info[4][x][y] = 1;


			}
			if (y == 16)
			{
				if (x >= STAGE_4_MONSTER10_SET_X - 4 && x <= STAGE_4_MONSTER10_SET_X + 4)
				{
					map_info[4][x][y] = -1;
				}
				if (x == STAGE_4_MONSTER10_SET_X - 6 || x == STAGE_4_MONSTER10_SET_X - 5 || x == STAGE_4_MONSTER10_SET_X - 7 || x == STAGE_4_MONSTER10_SET_X + 5)
					map_info[4][x][y] = 1;
				if (x == 16 || x == 26 || x == 36)
					map_info[4][x][y] = 1;
			}
			if (y == 17)
			{
				if (x >= STAGE_4_MONSTER10_SET_X - 4 && x <= STAGE_4_MONSTER10_SET_X + 4)
				{
					map_info[4][x][y] = 1;
				}
				if (x == 17 || x == 27 || x == 37)
					map_info[4][x][y] = 1;
			}
			if (y == 18)
			{
				if (x == 18 || x == 28 || x == 38)
					map_info[4][x][y] = 1;
				if (x >= 23 && x <= 25)
					map_info[4][x][y] = 6;
				if (x >= 33 && x <= 35)
					map_info[4][x][y] = 7;
			}
			if (y == 19)
			{
				if (x == 10)
					map_info[4][x][y] = 1;
				if (x >= 23 && x <= 25)
					map_info[4][x][y] = 6;
				if (x >= 33 && x <= 35)
					map_info[4][x][y] = 7;
			}
			if (y == 20)
			{
				if (x == 9 || x == 41)
					map_info[4][x][y] = 1;
			}
			if (y == 21)
			{
				if (x >= STAGE_4_MONSTER11_SET_X - 7 && x <= STAGE_4_MONSTER11_SET_X + 2)
				{
					map_info[4][x][y] = 1;
				}
				if (x == 8 || x == 40)
					map_info[4][x][y] = 1;
			}
			if (y == 22)
			{
				if (x >= STAGE_4_MONSTER11_SET_X - 7 && x <= STAGE_4_MONSTER11_SET_X + 2)
				{
					map_info[4][x][y] = -1;
				}
				if (x == STAGE_4_MONSTER11_SET_X - 8)
					map_info[4][x][y] = 1;
				if (x == 7 || x == 39 || x == 48)
					map_info[4][x][y] = 1;

			}
			if (y == 23)
			{
				if (x >= STAGE_4_MONSTER11_SET_X - 7 && x <= STAGE_4_MONSTER11_SET_X + 2)
				{
					map_info[4][x][y] = -1;
				}
				if (x == STAGE_4_MONSTER11_SET_X - 8)
					map_info[4][x][y] = 1;
				if (x == 6 || x == 38 || x == 47)
					map_info[4][x][y] = 1;
				if (x >= 2 && x <= 5)
					map_info[4][x][y] = 8;
				if (x >= 40 && x <= 42)
					map_info[4][x][y] = 8;
			}
			if (y == 24)
			{
				if (x >= STAGE_4_MONSTER11_SET_X - 7 && x <= STAGE_4_MONSTER11_SET_X + 2)
				{
					map_info[4][x][y] = 1;
				}
				if (x == 5 || x == 46)
					map_info[4][x][y] = 1;
				if (x >= 2 && x <= 4)
					map_info[4][x][y] = 8;

			}
			if (y == 25)
			{
				if (x >= STAGE_4_MONSTER12_SET_X - 5 && x <= STAGE_4_MONSTER12_SET_X + 3)
				{
					map_info[4][x][y] = 1;
				}
				if (x >= 26 && x <= 32)
					map_info[4][x][y] = 1;
				if (x == 4 || x == 45)
					map_info[4][x][y] = 1;
				if (x == 2 || x == 3)
					map_info[4][x][y] = 9;
			}
			if (y == 26)
			{
				if (x >= STAGE_4_MONSTER12_SET_X - 5 && x <= STAGE_4_MONSTER12_SET_X + 3)
				{
					map_info[4][x][y] = -1;
				}
				if (x == 33 || x == 3 || x == 50)
					map_info[4][x][y] = 1;
				if (x == 2)
					map_info[4][x][y] = 9;
			}
			if (y == 27)
			{
				if (x >= STAGE_4_MONSTER12_SET_X - 5 && x <= STAGE_4_MONSTER12_SET_X + 3)
				{
					map_info[4][x][y] = -1;
				}
				if (x == 34)
					map_info[4][x][y] = 1;
				if (x == 2 || x == 10 || x == 51)
					map_info[4][x][y] = 1;
			}
			if (y == 28)
			{
				if (x >= STAGE_4_MONSTER12_SET_X - 5 && x <= STAGE_4_MONSTER12_SET_X + 3)
				{
					map_info[4][x][y] = 1;
				}
				if (x == 35 || x == 11 || x == 52)
					map_info[4][x][y] = 1;
				if (x == 10)
					map_info[4][x][y] = 8;
			}
			if (y == 29)
			{
				if (x >= 25 && x <= 27)
					map_info[4][x][y] = 1;
				if (x == 36 || x == 10 || x == 53)
					map_info[4][x][y] = 1;
				if (x == 11)
					map_info[4][x][y] = 9;
			}
			if (y == 30)
			{
				if (x >= STAGE_4_MONSTER13_SET_X - 3 && x <= STAGE_4_MONSTER13_SET_X + 4)
				{
					map_info[4][x][y] = 1;
				}
				if (x >= 25 && x <= 29)
					map_info[4][x][y] = 1;
				if (x == 11)
					map_info[4][x][y] = 1;
				if (x >= 19 && x <= 21)
					map_info[4][x][y] = 6;
			}
			if (y == 31)
			{
				if (x >= STAGE_4_MONSTER13_SET_X - 3 && x <= STAGE_4_MONSTER13_SET_X + 4)
				{
					map_info[4][x][y] = -1;
				}
				if (x >= 25 && x <= 31)
					map_info[4][x][y] = 1;
				if (x == 12)
					map_info[4][x][y] = 1;
				if (x >= 10 && x <= 11)
					map_info[4][x][y] = 7;
				if (x >= 19 && x <= 21)
					map_info[4][x][y] = 6;
				if (x == 20)
					map_info[4][x][y] = 15;
			}
			if (y == 32)
			{
				if (x >= STAGE_4_MONSTER13_SET_X - 3 && x <= STAGE_4_MONSTER13_SET_X + 4)
				{
					map_info[4][x][y] = -1;
				}
				if (x >= 25 && x <= 34)
					map_info[4][x][y] = 1;
				if (x == 13)
					map_info[4][x][y] = 1;
				if (x >= 10 && x <= 12)
					map_info[4][x][y] = 7;
				if (x >= 19 && x <= 21)
					map_info[4][x][y] = 6;
				if (x >= 56 && x <= 57)
					map_info[4][x][y] = 9;
			}
			if (y == 33)
			{
				if (x >= STAGE_4_MONSTER13_SET_X - 3 && x <= STAGE_4_MONSTER13_SET_X + 4)
				{
					map_info[4][x][y] = 1;
				}
				if (x >= 25 && x <= 36)
					map_info[4][x][y] = 1;
				if (x == 14)
					map_info[4][x][y] = 1;
				if (x >= 10 && x <= 13)
					map_info[4][x][y] = 7;

			}
			if (y == 34)
			{
				map_info[4][x][y] = 1;

			}

		}
	}
}

void ShowQuest()
{
	Set_Color(WHITE);
	SetCurrentCursorPos(40, 0);
	if (stage_state == 0)
		printf("퀘스트 : 1000점을 만드시오!");
	else
		printf("퀘스트 : 몬스터를 모두 죽이시오!");


}
void ShowManual()
{
	Set_Color(WHITE);
	SetCurrentCursorPos(85, 0);
	printf("Q : Bomb    W : HP_Plus     E : O2_Plus    T : Teleport   I : Inventory   ");
}