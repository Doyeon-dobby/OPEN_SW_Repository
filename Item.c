#include "Item.h"
#include <Windows.h>
#include <time.h>
#include "PlayerSetting.h"
#include "blockmodel.h"
#include "Colors.h"
#include "ConsoleControll.h"
#include "map.h"
#include "Drawing.h"
#include "Inventory.h"

extern int player_hp;
extern int player_o2;
extern int player_x;
extern int player_y;
extern int player_state;
extern char DeleteBlock[][2][6];
extern char BombModel[][2][6];
extern char OxygenModel[][2][6];
extern char HpItemModel[][2][6];

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern int stage_state;
extern int now_inven_show;

extern Item inven[INVENTORY_SIZE];

//폭탄이 터지고 있음을 알려주는 변수
int bomb_flag = 0;

int nowUsingBomb = 0;
double bombTimer = 0.0f;
int bomb_x;
int bomb_y;

void UseMedicalItem()
{
	PlayerHPPlus(100);
}
void UseOxygenItem()
{
	PlayerO2Plus(50);
}

int find_item(int itemID) {
	int sum = 0;
	for (int i = 0; i < inven_index; i++) {
		if (itemID == inven[i].itemID) {
			sum += inven[i].amount;
		}
	}
	return sum;
}

void UseBomb(int player_state)
{
	if (find_item(ITEM_BOMB) == 0)
		return;
	//이미 폭탄이 사용 되어있다면  폭탄을 또 사용할수
	//없도록 제약을 걸어둔다
	if (nowUsingBomb == 1)
		return;
	nowUsingBomb = 1;


	if (player_state == 1)
	{
		bomb_x = player_x - 1;
		bomb_y = player_y;
	}
	else if (player_state == 2)
	{
		bomb_x = player_x + 1;
		bomb_y = player_y;
	}
	else if (player_state == 3)
	{
		bomb_x = player_x;
		bomb_y = player_y - 1;
	}
	else
	{
		return;
	}
	if (map_info[stage_state][bomb_x][bomb_y] != -1)
	{
		return;
	}
	map_info[stage_state][bomb_x][bomb_y] = 12;
	map_state[stage_state][bomb_x][bomb_y] = 1;
	COORD curPos = GetCurrentCursorPos();

	SetCurrentCursorPos(bomb_x * 3 + GBOARD_ORIGIN_X, bomb_y * 2 + GBOARD_ORIGIN_Y);
	Set_Color(DARKPURPLE);

	ShowBlock(BombModel[0]);
	Sleep(400);


	SetCurrentCursorPos(curPos.X, curPos.Y);
	//nowUsingBomb = 0;
	useitem(ITEM_BOMB);
	now_inven_show = 0;
}


void PlayerHPPlus(int hp)
{
	if (find_item(ITEM_HEAL) == 0)
		return;
	player_hp += hp;
	if (player_hp >= 100)
	{
		player_hp = 100;
	}
	useitem(ITEM_HEAL);
	now_inven_show = 0;
}
void PlayerO2Plus(int o2)
{
	if (find_item(ITEM_O2) == 0)
		return;
	player_o2 += o2;
	if (player_o2 >= 100)
	{
		player_o2 = 100;
	}
	useitem(ITEM_O2);
	now_inven_show = 0;
}

void UseTeleport()
{
	if (find_item(ITEM_TELEPORT) == 0)
		return;
	int teleport_player_x = PLAYER_ORIGIN_X;
	int teleport_player_y = PLAYER_ORIGIN_Y;
	int temp_x = player_x;
	int temp_y = player_y;
	ChangeBlock(player_x, player_y, teleport_player_x, teleport_player_y, player_state);
	RedrawMap(temp_x, temp_y, player_state);
	useitem(ITEM_TELEPORT);
	now_inven_show = 0;
}