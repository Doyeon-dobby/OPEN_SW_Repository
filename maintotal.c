#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#include "Colors.h"
#include "ConsoleControll.h"
#include "map.h"
#include "blockmodel.h"
#include "Keys.h"
#include "PlayerSetting.h"
#include "Drawing.h"
#include "Score.h"
#include "Item.h"
#include "shop.h"
#include "Inventory.h"
#include "Monster.h"
#include "Startmain.h"
#pragma warning(disable:4996)

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern int block_change_waitingtime;
extern char Player1[][2][6];
extern char DeleteBlock[][2][6];
extern char BasicBlockModel[][2][6];
extern char MineralModel[][2][6];
extern char BombModel[][2][6];

extern int player_x;
extern int player_y;
extern int player_hp;
extern int player_o2;
extern int bomb_x;
extern int bomb_y;
extern int nowUsingBomb;
extern int bomb_flag;
extern int stage_state;
//�÷��̾��� ���� ����
//'0 : ��', '1 : ��', '2 : ��'
extern int player_state;
extern int money;
extern int gameScore;

extern int block_change_waitingtime;
//�Ʒ��� �⺻ �� �⺻ �����Դϴ�.
//�ܼ�â�� �����ϴ� ������ ������ ��Ʈ�� ������ ���缭 ������ ������
// ���ֽñ� �ٶ��ϴ�.
//setting
int console_col = 300;
int console_lines = 75;
// ��� ȭ�� ���� �ð��� ���ϴ� ���Դϴ�.
//�Ʒ� sleep�� ���� �����Դϴ�
extern int interval_sleeptime;
int block_changetime = 500;
int player_down_sleep = 500;
int sleep_time;	//���� ������ �̰� �Ű� �Ƚᵵ �˴ϴ�
int bomb_blink_time = 100;

//�κ��丮�� ������ �ݴ��� ���� �Լ�
int inventory_key = 0;

// �ʿ� ��ȭ�� �ִ����� ���� �Ҹ��� �� 
//'0 : ��ȭ�� �����ϴ�' , ' 1: ��ȭ�� ������ϴ�.'
int change_flag;
int now_inven_show = 0;

int decrease_o2 = 1;
int monster_kill_count = 0;
int start_key;

int monster_speed = 500;
int oxygen_speed = 500;
//���� ����
extern MOB mons[100];
clock_t bombUseTime;
clock_t bomb_start;
clock_t bomb_check;
//������ ���� ���� �� �ܼ�â ��ġ�� ���������� ó���ҷ��� �ϴ� ����������
//������ �� �۵� ����
#define FINALL_X 60
#define FINALL_Y 20

//���� ������ ���
void Delete(int posX, int posY);

//Player Moving �÷��̾� �̵��� ���� �Լ�
int ShiftLeft();
int ShiftRight();
int ShiftDown();
int ShiftUp();

void BaiscDown();
//�κ��丮�� ���� �ݴ� �Լ�
int InventoryKeyChange();

void BombBlinkEffect();

//Ű�� �Է� �޴� �Լ� ��Ʈ������ ���� �Լ��̴�
void ProcessKeyInput();

void ShowPlayerState();

//���� ��������
void NextStage();

//���� ���� �� �����ؾ� �� �͵� ǥ���ϴ� �Լ��̴�.
void GameWin();
void GameOver();

int main()
{
	//�����Լ� ������ ����Ͽ� �ϴ� �������� �ҷ�����
	srand(time(NULL));
	//sleep_time = 50;
	//��ȭ�Լ� 0���� �ʱ�ȭ
	change_flag = 0;

	//�ܼ�â ũ�� �����ϴ� �κ� �Ű� �Ƚᵵ �� �κ� SetConsoleTitle���� �Ű��� �Ƚᵵ �˴ϴ�
	char m_str1[5], m_str2[5];

	sprintf(m_str1, "%d", console_col);
	sprintf(m_str2, "%d", console_lines);

	char system_set_size[50] = "mode con:cols=";
	char m_str3[10] = " lines=";

	strcat(system_set_size, m_str1);
	strcat(system_set_size, m_str3);
	strcat(system_set_size, m_str2);

	system(system_set_size);
	SetConsoleTitle("team_6_Game_Project");
	//�ܼ�â ũ�� �����ϴ� �κ� �Ű� �Ƚᵵ �� �κ� SetConsoleTitle���� �Ű��� �Ƚᵵ �˴ϴ�

	//�ܼ��� �����ϴ� �Լ�
	RemoveCursor();
	do
	{
		start_key = DrawGameSettingBar();

		if (start_key == 1)
		{
			PrintGameExplainScreen();
		}
		if (start_key == 2)
			exit(0);
	} while (start_key != 0);
	//start setting
	//�� ����
	//SetBaiscMap();
	SetMapStage_0();
	SetMapStage_1();
	SetMapStage_2();
	SetMapStage_3();
	SetMapStage_4();
	//stage_state = 3;
	//SetMapStage_0();
	//�÷��̾� ���� �ϴ� ������ �÷��̾� ������ ���߿� �Ѵ�.
	PlayerSetting();
	//�ϴ� ���� �׸���.
	DrawMap();
	ShowQuest();
	clock_t start_time = clock();
	int blink_cnt = 0;

	InitMonster(0, STAGE_1_MONSTER1_SET_X, STAGE_1_MONSTER1_SET_Y, 1);
	InitMonster(1, STAGE_1_MONSTER2_SET_X, STAGE_1_MONSTER2_SET_Y, 1);

	InitMonster(2, STAGE_2_MONSTER3_SET_X, STAGE_2_MONSTER3_SET_Y, 2);
	InitMonster(3, STAGE_2_MONSTER4_SET_X, STAGE_2_MONSTER4_SET_Y, 2);
	InitMonster(4, STAGE_2_MONSTER5_SET_X, STAGE_2_MONSTER5_SET_Y, 2);


	InitMonster(5, STAGE_3_MONSTER6_SET_X, STAGE_3_MONSTER6_SET_Y, 3);
	InitMonster(6, STAGE_3_MONSTER7_SET_X, STAGE_3_MONSTER7_SET_Y, 3);
	InitMonster(7, STAGE_3_MONSTER8_SET_X, STAGE_3_MONSTER8_SET_Y, 3);

	InitMonster(8, STAGE_4_MONSTER9_SET_X, STAGE_4_MONSTER9_SET_Y, 4);
	InitMonster(9, STAGE_4_MONSTER10_SET_X, STAGE_4_MONSTER10_SET_Y, 4);
	InitMonster(10, STAGE_4_MONSTER11_SET_X, STAGE_4_MONSTER11_SET_Y, 4);
	InitMonster(11, STAGE_4_MONSTER12_SET_X, STAGE_4_MONSTER12_SET_Y, 4);
	InitMonster(12, STAGE_4_MONSTER13_SET_X, STAGE_4_MONSTER13_SET_Y, 4);

	while (1)
	{
		int player_redraw_flag = 0;
		int oxgentime = clock();
		int monstertime = clock();
		while (1)
		{
			RedrawMap(player_x, player_y, player_state);
			//���ھ� ������ �����ش�
			ShowSocre();
			//���� �������� ǥ��
			ShowStage();
			NextStage();
			GameOver();
			ShowQuest();
			ShowManual();
			if (clock() - monstertime > monster_speed)
			{
				MonsterMove_ksh();
				monstertime = clock();
			}
			if (player_redraw_flag > 0)
			{
				map_info[stage_state][player_x][player_y] = 10;
				RedrawMap(player_x, player_y, player_state);
			}
			for (int i = 0; i < 3; i++) {
				if (player_x == mons[i].pos_x && player_y == mons[i].pos_y)
				{
					player_redraw_flag += 1;
					if (mons[i].live == 0)
						Mon_Draw_ksh(mons[i].pos_x, mons[i].pos_y, mons[i].direction);
				}
			}
			if (inventory_key) {
				if (now_inven_show == 0)
				{
					ShowInventory(inventory_key);
					now_inven_show = 1;
				}
			}
			if (player_y > 0)
			{
				if (clock() - oxgentime > oxygen_speed)
				{
					if (player_o2 <= 0)
					{
						player_hp -= decrease_o2;
					}
					else
					{
						player_o2 -= decrease_o2;
						if (player_o2 < 0)
						{
							player_o2 = 0;
						}
					}
					oxgentime = clock();
				}
			}
			if (player_y == 0)
				player_o2 = 100;
			if (player_y == 0)
				player_hp = 100;
			ShowPlayerState();
			if (nowUsingBomb == 1)
			{
				if (blink_cnt < 2)
				{
					BombBlinkEffect();
					if (blink_cnt == 1)
					{
						map_info[stage_state][bomb_x][bomb_y] = -1;
						map_state[stage_state][bomb_x][bomb_y] = 0;
						nowUsingBomb = 0;
						blink_cnt = 0;
					}
					else
					{
						blink_cnt++;
					}
				}
				MosterDeath1();
			}
			if (_kbhit()) {
				ProcessKeyInput();
				continue;
			}
			if (!_kbhit()) SleepWork(interval_sleeptime);
		}
	}
	return 0;
}

//�� �Լ��� �ͼ�������?
//��Ʈ�����Ҷ� �����ð����� �Է� Ű�� �޾� �۵��ϴ� �Լ��Դϴ�.
//�ϴ� �⺻���� Ű�� �� �Ʒ� �� ��� �������� ������ �߽��ϴ�
//�����̽� �ٴ� ��ȣ�ۿ�Ű�� ���߿� �߰������� ������ �ϰڽ��ϴ�.
void ProcessKeyInput()
{
	//SetCurrentCursorPos(40, 0);
	//printf("%d", monster_kill_count);
	int key;
	key = _getch();
	if (key == DIRECTION) {
		key = _getch();
		switch (key)
		{
		case LEFT:
			ShiftLeft();
			break;
		case RIGHT:
			ShiftRight();
			break;
		case UP:
			ShiftUp();
			break;
		case DOWN:
			ShiftDown();
			break;
		default:
			break;
		}
	}
	else {
		switch (key)
		{
		case SPACE:
			break;
		case KeyQ:
			UseBomb(player_state);
			break;
		case KeyW:
			PlayerHPPlus(20);
			break;
		case KeyE:
			PlayerO2Plus(20);
			break;
		case KeyI:
			ShowInventory(InventoryKeyChange());
			break;
		case KeyP:
			if ((player_x >= MAP_INFO_X / 2 - 4) && (player_x <= MAP_INFO_X / 2 + 4) && player_y == 0) {
				show_shop();
			}
			break;
		case KeyT:
			UseTeleport();
			break;
		//	//ġƮŰ
		//case KeyY:
		//	player_x = MAP_INFO_X - 12;
		//	player_y = MAP_INFO_Y - 7;
		//	break;
		//	//z �� �ʳѱ�
		//case KeyZ:
		//	if (stage_state < 5)
		//		stage_state++;
		//	else
		//		stage_state = 5;
		//	PlayerSetting();
		//	DrawMap();
		//	break;
		//case KeyM:
		//	money += 10000;
		//	break;
		//case KeyS:
		//	gameScore += 1000;
		//	break;
		//case KeyX:
		//	monster_kill_count += 1;
		//	break;
		default:
			break;
		}
	}
}

//�������� �����̴� �Լ��Դϴ�.
int ShiftLeft()
{
	//���� �÷��̾��� ��ǥ�� �޾ƿɴϴ�.
	int x = player_x;
	int y = player_y;

	//�Ʒ� ���� ���ٸ� �ö󰡴� �߿��� ���� ���� �� ���� ����
	if (map_info[stage_state][x][y + 1] == -1)
	{
		if (map_info[stage_state][x - 1][y] != -1 && map_state[stage_state][x - 1][y] >= 0)
			return;
	}
	//��ȭ�� �־����� ü���� �÷��׸� 1�� ����� ��ȭ ������ �˷��ݴϴ�.
	change_flag = 1;
	//�÷��̾ ������ �ٶ�
	player_state = 1;

	//�÷��̾ �������� �������ٵ� ���� ��ĭ�� ��� �� ������ �������� ���ϰ� ���� �Լ��Դϴ�.
	if (PlayerDetectCollision(x - 1, y) == 1)
	{
		RedrawMap(player_x, player_y, player_state);
		return 1;//�浹 ��ȯ
	}
	ChangeBlock(x, y, x - 1, y, player_state);
	//�浹�� ������ ��ȯ�� �մϴ�
	return 0;
}


//�����ʵ� ���ʰ� ���������� �����߽��ϴ�. ���⸸ �ݴ�� ������ �߽��ϴ�.
int ShiftRight()
{
	int x = player_x;
	int y = player_y;
	//�Ʒ� ���� ���ٸ� ���� ���� �� �� �� ����.
	if (map_info[stage_state][x][y + 1] == -1)
	{
		if (map_info[stage_state][x + 1][y] != -1 && map_state[stage_state][x + 1][y] >= 0)
			return;
	}
	change_flag = 1;
	player_state = 2;
	if (PlayerDetectCollision(x + 1, y) == 1)
	{
		RedrawMap(player_x, player_y, player_state);
		return 1;//�浹 ��ȯ
	}
	ChangeBlock(x, y, x + 1, y, player_state);
	return 0;
}
int ShiftDown()
{
	int x = player_x;
	int y = player_y;
	player_state = 0;
	if (y + 1 >= MAP_INFO_Y)
	{
		return;
	}
	if (PlayerDetectCollision(x, y + 1) == 1)
	{
		RedrawMap(player_x, player_y, player_state);
		return 1;
	}
	ChangeBlock(x, y, x, y + 1, player_state);
	return 0;
}
int ShiftUp()
{
	int x = player_x;
	int y = player_y;

	change_flag = 1;
	player_state = 3;

	if (y == 0)
		return 1;
	if (PlayerDetectCollision(x, y - 1) >= 1)
	{
		RedrawMap(player_x, player_y, player_state);
		return 1;//�浹 ��ȯ
	}
	player_y = PlayerShiftY(y - 1);
	map_info[stage_state][player_x][player_y] = 10;
	map_info[stage_state][x][y] = -1;
	RedrawMap(player_x, player_y, player_state);
	Sleep(interval_sleeptime);
	return 0;
}

//��� �׸� �����ϴ� �Լ�
// posX �� ������ ��� ��ǥ x,  posY �� ������ ��� ��ǥ y
void Delete(int posX, int posY)
{
	//���� ��ǥ�� �����ϰ�
	COORD curPos = GetCurrentCursorPos();
	//�ش� ��ǥ�� �̵����ϰ�
	SetCurrentCursorPos(posX * 3 + GBOARD_ORIGIN_X, posY * 2 + GBOARD_ORIGIN_Y);
	//�ƹ��͵� ���� ��� �׸� �׸���
	ShowBlock(DeleteBlock[0]);
	//��ǥ ���󺹱�
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void BaiscDown()
{
	int x = player_x;
	int y = player_y;
	int down_block = y + 1;
	if (map_info[stage_state][player_x][down_block] == -1)
	{
		player_y = PlayerShiftY(y - 1);
		map_info[stage_state][player_x][player_y] = 10;
		map_info[stage_state][x][y] = -1;
		RedrawMap(player_x, player_y, 0);
		Sleep(player_down_sleep);
		return;
	}
}
int InventoryKeyChange()
{
	if (inventory_key == 0)
	{
		inventory_key = 1;
	}
	else
	{
		inventory_key = 0;
	}
	now_inven_show = 0;
	return inventory_key;
}
void BombBlinkEffect()
{
	if (nowUsingBomb == 0)
		return;
	COORD curPos = GetCurrentCursorPos();

	SetCurrentCursorPos(bomb_x * 3 + GBOARD_ORIGIN_X, bomb_y * 2 + GBOARD_ORIGIN_Y);
	Set_Color(RED);
	ShowBlock(BombModel[1]);
	Sleep(bomb_blink_time);
	ShowBlock(DeleteBlock[0]);
	Sleep(bomb_blink_time);
	SetCurrentCursorPos(curPos.X, curPos.Y);

}

void NextStage() {
	if (stage_state == 0)
	{
		if (gameScore <= 1000)
			return;
	}
	else if (stage_state == 1)
	{
		if (monster_kill_count < 1)
			return;
	}
	else if (stage_state == 2)
	{
		if (monster_kill_count < 2)
			return;
	}
	else if (stage_state == 3)
	{
		if (monster_kill_count < 2)
			return;
	}
	else// if (stage_state == 4)
	{
		if (monster_kill_count < 4)
			return;
	}
	if (player_x == DOOR_LOC && player_y == 0||(stage_state==4&&player_x==20&&player_y==31)) {
		stage_state += 1;
		monster_kill_count = 0;
		monster_speed -= 100;
		oxygen_speed -= 100;
		GetSocre(10 + stage_state);
		if (stage_state == 5) {
			GameWin();
		}
		else {
			PlayerSetting();
			DrawMap();
		}
	}

}

//���� ����� ��� ���� ���ϴ� �Լ��� �ϴ��� ����
void GameWin()
{
	EraseScreen();
	Set_Color(YELLOW);
	SetCurrentCursorPos(0, 8);
	printf("\n\n");
	printf("                  ############     ###                    ##################        #############       #############        ########  \n");
	printf("                ##                 ###                    ##################      ###           ###    ###          ###      ########  \n");
	printf("              ##                   ###                    ###                     ###           ###    ###          ###      ########  \n");
	printf("              ##                   ###                    ###                     #################    ###          ###      ########  \n");
	printf("              ##                   ###                    ##################      #################    ##############         ######   \n");
	printf("              ##                   ###                    ##################      ####         ####    ###          ###       ######   \n");
	printf("              ##                   ###                    ###                     ####         ####    ###          ###        ####    \n");
	printf("              ##                   ###                    ###                     ####         ####    ###          ###        ####    \n");
	printf("              ##                   ###                    ###                     ####         ####    ###          ###                \n");
	printf("               ##                  ###                    ##################      ####         ####    ###          ###         ###    \n");
	printf("                 #############     #################      ##################      ####         ####    ###          ###         ###    \n");
	printf("\n\n\n\n\n\n");
	printf("                                    10�ʵ� â�� �����ϴ�.!   ");
	Sleep(10000);
	SetCurrentCursorPos(FINALL_X, FINALL_Y + 1);
	printf("YOU WIN");
	exit(-1);
}

//���� ����� ��� ���� ���ϴ� �Լ��� �ϴ��� ����
void GameOver()
{

	if (player_hp <= 0) {
		EraseScreen();
		Set_Color(DARKRED);
		SetCurrentCursorPos(0, 8);
		printf("\n\n");
		printf("                  ########               ###             ###      ##################        ##############       \n");
		printf("                ##        ##             ###             ###      ##################      ###           ###      \n");
		printf("              ##            ##           ###             ###      ###                     ###           ###      \n");
		printf("              ##            ##           ###             ###      ###                     ###           ###      \n");
		printf("              ##            ##           ###             ###      ##################      ##############         \n");
		printf("              ##            ##           ###             ###      ##################      ###          ###       \n");
		printf("              ##            ##           ###             ###      ###                     ###          ###       \n");
		printf("              ##            ##             ###          ###       ###                     ###          ###       \n");
		printf("              ##            ##               ##       ##          ###                     ###          ###       \n");
		printf("               ##          ##                 ##     ##           ###################     ###          ###       \n");
		printf("                 ##########                      ####             ###################     ###          ###       \n");
		printf("\n");
		printf("\n\n\n\n\n\n");
		printf("                                    10�ʵ� â�� �����ϴ�.!   ");
		Sleep(10000);
		SetCurrentCursorPos(FINALL_X, FINALL_Y + 1);
		printf("GAME OVER");
		exit(-1);
	}

}
void ShowPlayerState()
{
	Set_Color(WHITE);
	/*���� ĳ���� ���� (�ӽ� ������) ĳ���� ���� ���� ������ ��������� �����ϰڽ��ϴ�(11/26)*/
	SetCurrentCursorPos(MAP_INFO_X * 3 + 2, 2);
	printf("HP: ");
	for (int i = 0; i < player_hp / 10; i++) {
		printf("��");
	}
	for (int i = player_hp / 10; i <= 10; i++) {
		printf("  ");
	}
	SetCurrentCursorPos(MAP_INFO_X * 3 + 20, 2);

	printf("%03d/100", player_hp);
	SetCurrentCursorPos(MAP_INFO_X * 3 + 2, 4);
	printf("O2: ");
	for (int i = 0; i < player_o2 / 10; i++) {
		printf("��");
	}
	for (int i = player_o2 / 10; i <= 10; i++) {
		printf("  ");
	}
	SetCurrentCursorPos(MAP_INFO_X * 3 + 20, 4);
	printf("%03d/100", player_o2);

}