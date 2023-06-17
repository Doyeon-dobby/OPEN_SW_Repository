#include "Drawing.h"

#include "PlayerSetting.h"
#include "map.h"
#include "Colors.h"
#include "blockmodel.h"
#include "ConsoleControll.h"
#include "Monster.h"

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern char Player1[][2][6];
extern char Monster1[][2][6];
extern char Door1[][2][6];
extern char DeleteBlock[][2][6];
extern char BasicBlockModel[][2][6];
extern char MineralModel[][2][6];
extern char BombModel[][2][6];
extern char ShopNPC[][2][6];

extern int stage_state;

void DrawMap()
{
	//블록 상태를 받아오는 변수
	int block_state;
	//현재의 좌표를 받아소 저장을 하고 여기서는 굳이 이과정이 필요한지 모르겠으나
	//그냥 습과적으로 현재의 커서 좌표 받아서 아래에서 다시 원상복귀시킨다
	COORD curPos = GetCurrentCursorPos();
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//그림판을 일단 기본 칸은 3칸이다. 그래서 x축은 한칸을 그리는데 3칸이 필요하고 
			//y축은 2칸이 필요로 한다.
			SetCurrentCursorPos(x * 3 + GBOARD_ORIGIN_X, y * 2 + GBOARD_ORIGIN_Y);
			//map_info는 현재 맵의 정보(이게 광물인지 빈칸인지 플레이어인지를 판단하는정보, 부서진 정도에 대한 정보는 없다)
			//그래서 맵인포에서 정보를 받아와서 그에 해당 하는 컬러는 받아들인다.
			SetMapColor(map_info[stage_state][x][y]);
			//map_state는 부서진 정도의 정보 등, 해당 블록이 어떠한 모양을 나타내야되는지 표현하는 배열이다
			block_state = map_state[stage_state][x][y];
			//맵인포의 값이 0 이상이라면 블록이 존재하는 것이다. 그 이하면 블록이 없으므로 아무것도 안그리는 블록을 그린다
			if (map_info[stage_state][x][y] >= 0)
			{
				if (map_info[stage_state][x][y] == 10)//만약에 정보가 10이면 플레이어이므로 플레이어를 그린다
				{
					ShowBlock(Player1[block_state]);

				}
				else if (map_info[stage_state][x][y] == 13)
				{
					ShowBlock(Door1);
				}
				else if (map_info[stage_state][x][y] == 14) {
					ShowBlock(ShopNPC);
				}
				else if (map_info[stage_state][x][y] == 15)
				{
					Set_Color(PURPLE);
					ShowBlock(Player1[0]);
				}
				else
				{
					//그게 아니라면 블록을 블록 상태에 맞춰서 그린다.
					ShowBlock(BasicBlockModel[block_state]);


				}
			}
			else
			{
				ShowBlock(DeleteBlock[0]);
			}
		}
	}
	Set_Color(WHITE);
	SetCurrentCursorPos(DOOR_LOC * 3 + GBOARD_ORIGIN_X, +GBOARD_ORIGIN_Y);
	ShowBlock(Door1);
	//좌표 원상복귀
	SetCurrentCursorPos(curPos.X, curPos.Y);
}
//다시 그리는 함수
//플레이어에 해당하는 것 기준으로만 다시 그린다.
void RedrawMap(int p_x, int p_y, int p_s)
{
	//똑같이 DrawMap합수 처럼 그리는데 다 그리는 것이 아니라 플레이어의 주변만 다시 그린다.
	int block_state;
	COORD curPos = GetCurrentCursorPos();
	for (int i = 26; i <= 34; i++)
	{
		if (p_y == 0)
		{
			if (i == p_x)
				continue;
			else
				map_info[stage_state][i][0] = 14;
		}
		else
			break;
	}

	//왼쪽 2칸 오른쪽 2칸
	for (int x = -REDRAW_SIZE_X; x <= REDRAW_SIZE_X; x++)
	{
		//아래2칸 위로 2칸을 다시 그린다.
		for (int y = -REDRAW_SIZE_Y; y <= REDRAW_SIZE_Y; y++)
		{
			//다시 그릴 x값과 y값을 다시 좌표를 계산을 한다
			int re_x = p_x + x;
			int re_y = p_y + y;
			//이게 맵에 해당하는 사이즈를 초과를 하면 끝낸다
			if (re_y < 0 || re_y >= MAP_INFO_Y)	continue;
			if (re_x < 0 || re_x >= MAP_INFO_X)	continue;

			//좌표를 해당하는 것에 맞춰서 커서를 옮긴다
			SetCurrentCursorPos(re_x * 3 + GBOARD_ORIGIN_X, re_y * 2 + GBOARD_ORIGIN_Y);
			SetMapColor(map_info[stage_state][re_x][re_y]);
			block_state = map_state[stage_state][re_x][re_y];


			//멥 정보가 0이상이면 DrwaMap과 마찬가지로 블록이므로 플레이어와 블록을 다시 그린다.
			if (map_info[stage_state][re_x][re_y] >= 0)
			{
				if (map_info[stage_state][re_x][re_y] == 10)
				{
					ShowBlock(Player1[p_s]);

				}
				else if (map_info[stage_state][re_x][re_y] == 12)
				{
					ShowBlock(BombModel[block_state]);
				}
				else if (map_info[stage_state][re_x][re_y] == 11)
				{
					ShowBlock(Monster1[block_state]);
				}
				else if (map_info[stage_state][re_x][re_y] == 13)
				{
					ShowBlock(Door1);
				}
				else if (map_info[stage_state][re_x][re_y] == 14)
				{

					ShowBlock(ShopNPC);
				}
				else if (map_info[stage_state][re_x][re_y] == 15)
				{
					Set_Color(PURPLE);
					ShowBlock(Player1[0]);
				}
				else
				{
					if (block_state == -1)
					{
						ShowBlock(MineralModel[0]);
					}
					else
					{
						ShowBlock(BasicBlockModel[block_state]);
					}
				}
			}
			else
			{
				ShowBlock(DeleteBlock[0]);
			}
		}
	}

	Set_Color(WHITE);
	SetCurrentCursorPos(DOOR_LOC * 3 + GBOARD_ORIGIN_X, + GBOARD_ORIGIN_Y);
	ShowBlock(Door1);

	//좌표 원상복귀
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void Mon_Draw_ksh(int x, int y, int state)
{
	COORD curPos = GetCurrentCursorPos();

	map_info[stage_state][x][y] = 11;
	SetCurrentCursorPos(x * 3 + GBOARD_ORIGIN_X, y * 2 + GBOARD_ORIGIN_Y);
	SetMapColor(map_info[stage_state][x][y]);	
	ShowBlock(Monster1[state]);

	SetCurrentCursorPos(curPos.X, curPos.Y);

}