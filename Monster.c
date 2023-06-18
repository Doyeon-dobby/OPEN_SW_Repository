#include "Monster.h"
#include "map.h"
#include "Drawing.h"
#include "Item.h"
#include "blockmodel.h"
#include "ConsoleControll.h"
#include "Score.h"
#include "Inventory.h"

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern char DeleteBlock[][2][6];
extern int change_flag;
extern int nowUsingBomb;
extern int bomb_x;
extern int bomb_y;
extern int stage_state;
extern int player_hp;
extern int player_state;
extern int monster_kill_count;
extern int decrease_damage;
int monster_num = 100;
MOB mon = { 0, };
MOB mons[100] = { 0, };

void MonsterDrawing()
{
	COORD curPos = GetCurrentCursorPos();
	int x, y;
	if (stage_state == 0)
		return;
	for (int i = 0; i < monster_num; i++)
	{

		if (mons[i].live == 1)
			continue;
		if (mons[i].stage != stage_state)
			continue;
		x = mons[i].pos_x;
		y = mons[i].pos_y;
		Mon_Draw_ksh(x, y, mons[i].direction);
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void InitMonster(int monster_idx, int p_x, int p_y, int state)
{
	mons[monster_idx].live = 0;
	mons[monster_idx].pos_x = p_x;
	mons[monster_idx].pos_y = p_y;
	mons[monster_idx].stage = state;
	map_info[state][p_x][p_y] = 11;
}

int MonsterDetectCollision(int curX, int curY) //curX 충돌 검사할 x좌표 curY 충돌 검사할 y좌표
{
	if (map_info[stage_state][curX][curY] == 10)//모든 블럭에 대해 충돌
	{
		return 2;
	}
	if (map_info[stage_state][curX][curY] >= 0)//모든 블럭에 대해 충돌
	{
		return 1;
	}
	else                        //음수이면 블록이 없으므로 통과가능
	{
		return 0;
	}
}

//다중 몬스터 컨트롤
void MonsterMove_ksh()
{
	if (stage_state == 0)
		return;
	COORD curPos = GetCurrentCursorPos();
	int x, y, mon_state;
	for (int i = 0; i < monster_num; i++)
	{
		if (mons[i].live == 1)
			continue;
		if (mons[i].stage != stage_state)
			continue;
		x = mons[i].pos_x;
		y = mons[i].pos_y;
		mon_state = mons[i].direction;
		if (mons[i].direction == 0)
		{
			//플레이어 피격
			if (MonsterDetectCollision(x - 1, y) == 2) {
				player_hp -= 50 - decrease_damage;
			}
			if (MonsterDetectCollision(x - 1, y) == 1 || MonsterDetectCollision(x - 1, y + 1) == 0)
			{
				Mon_Draw_ksh(x, y, mon_state);
				mons[i].direction = 1;
				map_state[stage_state][x][y] = 1;
				continue;
			}
			map_info[stage_state][x - 1][y] = 11;
			map_state[stage_state][x - 1][y] = 0;
			map_info[stage_state][x][y] = -1;
			mons[i].pos_x -= 1;
			SetCurrentCursorPos(x * 3 + GBOARD_ORIGIN_X, y * 2 + GBOARD_ORIGIN_Y);
			ShowBlock(DeleteBlock[0]);
			Mon_Draw_ksh(mons[i].pos_x, mons[i].pos_y, mon_state);

		}
		else if (mons[i].direction == 1)
		{
			//플레이어 피격
			if (MonsterDetectCollision(x + 1, y) == 2) {
				player_hp -= 50 - decrease_damage;
			}
			if (MonsterDetectCollision(x + 1, y) == 1 || MonsterDetectCollision(x + 1, y + 1) == 0)
			{
				Mon_Draw_ksh(x, y, mon_state);
				mons[i].direction = 0;
				map_state[stage_state][x][y] = 0;
				continue;
			}
			map_info[stage_state][x + 1][y] = 11;
			map_state[stage_state][x + 1][y] = 1;
			map_info[stage_state][x][y] = -1;
			mons[i].pos_x += 1;
			SetCurrentCursorPos(x * 3 + GBOARD_ORIGIN_X, y * 2 + GBOARD_ORIGIN_Y);
			ShowBlock(DeleteBlock[0]);
			Mon_Draw_ksh(mons[i].pos_x, mons[i].pos_y, mon_state);
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}


void MosterDeath1()
{
	COORD curPos = GetCurrentCursorPos();
	for (int i = 0; i < monster_num; i++)
	{
		if (mons[i].stage != stage_state)
			continue;
		//mon live가 0이라면 지금 살아있는 것이고
		if (mons[i].live == 0)
		{
			//폭탄이 지금 설치가 되었다면
			if (nowUsingBomb == 1)
			{
				if (bomb_y == mons[i].pos_y)
				{
					if (bomb_x - BOMB_SCOPE <= mons[i].pos_x && bomb_x + BOMB_SCOPE >= mons[i].pos_x)
					{
						mons[i].live = 1;

						map_info[stage_state][mons[i].pos_x][mons[i].pos_y] = -1;
						map_info[stage_state][bomb_x][bomb_y] = -1;
						RedrawMap(mons[i].pos_x, mons[i].pos_y, player_state);

						nowUsingBomb = 0;
						monster_kill_count++;
						GetSocre(10);
					}
				}
			}
			else
			{
				return;
			}
		}
		//죽었으면 다음 몬스터로 넘어간다
		else
		{
			continue;
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}
