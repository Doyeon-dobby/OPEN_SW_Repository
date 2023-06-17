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
//플레이어의 방향 상태
//'0 : 하', '1 : 우', '2 : 좌'
extern int player_state;
extern int money;
extern int gameScore;

extern int block_change_waitingtime;
//아래는 기본 중 기본 셋팅입니다.
//콘솔창의 조절하느 것으로 개인의 노트북 사정에 맞춰서 사진을 변경을
// 해주시길 바랍니다.
//setting
int console_col = 300;
int console_lines = 75;
// 잠시 화면 슬립 시간을 정하는 것입니다.
//아래 sleep은 임의 변수입니다
extern int interval_sleeptime;
int block_changetime = 500;
int player_down_sleep = 500;
int sleep_time;	//임의 변수로 이건 신경 안써도 됩니다
int bomb_blink_time = 100;

//인벤토리를 여는지 닫는지 쓰는 함수
int inventory_key = 0;

// 맵에 변화가 있는지에 대한 불리언 값 
//'0 : 변화가 없습니다' , ' 1: 변화가 생겼습니다.'
int change_flag;
int now_inven_show = 0;

int decrease_o2 = 1;
int monster_kill_count = 0;
int start_key;

int monster_speed = 500;
int oxygen_speed = 500;
//몬스터 생성
extern MOB mons[100];
clock_t bombUseTime;
clock_t bomb_start;
clock_t bomb_check;
//마지막 게임 오버 후 콘솔창 위치를 마지막으로 처리할려고 하는 변수이지만
//아직은 잘 작동 안함
#define FINALL_X 60
#define FINALL_Y 20

//현재 삭제할 블록
void Delete(int posX, int posY);

//Player Moving 플레이어 이동에 관한 함수
int ShiftLeft();
int ShiftRight();
int ShiftDown();
int ShiftUp();

void BaiscDown();
//인벤토리를 열고 닫는 함수
int InventoryKeyChange();

void BombBlinkEffect();

//키를 입력 받는 함수 테트리스때 쓰던 함수이다
void ProcessKeyInput();

void ShowPlayerState();

//다음 스테이지
void NextStage();

//게임 끝날 때 정리해야 될 것들 표시하는 함수이다.
void GameWin();
void GameOver();

int main()
{
	//랜덤함수 쓸때를 대비하여 일단 랜덤씨드 불러오기
	srand(time(NULL));
	//sleep_time = 50;
	//변화함수 0으로 초기화
	change_flag = 0;

	//콘솔창 크기 설정하는 부분 신경 안써도 될 부분 SetConsoleTitle까지 신경은 안써도 됩니다
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
	//콘솔창 크기 설정하는 부분 신경 안써도 될 부분 SetConsoleTitle까지 신경은 안써도 됩니다

	//콘솔을 삭제하는 함수
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
	//땅 셋팅
	//SetBaiscMap();
	SetMapStage_0();
	SetMapStage_1();
	SetMapStage_2();
	SetMapStage_3();
	SetMapStage_4();
	//stage_state = 3;
	//SetMapStage_0();
	//플레이어 생성 일단 무조건 플레이어 생성을 나중에 한다.
	PlayerSetting();
	//일단 맵을 그린다.
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
			//스코어 점수를 보여준다
			ShowSocre();
			//현재 스테이지 표시
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

//이 함수는 익숙하지쇼?
//테트리스할때 일정시간마다 입력 키를 받아 작동하는 함수입니다.
//일단 기본적인 키는 위 아래 좌 우로 움직입을 구현일 했습니다
//스페이스 바는 상호작용키로 나중에 추가적으로 구현을 하겠습니다.
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
		//	//치트키
		//case KeyY:
		//	player_x = MAP_INFO_X - 12;
		//	player_y = MAP_INFO_Y - 7;
		//	break;
		//	//z 는 맵넘김
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

//왼쪽으로 움직이는 함수입니다.
int ShiftLeft()
{
	//현재 플레이어의 좌표를 받아옵니다.
	int x = player_x;
	int y = player_y;

	//아래 땅이 없다면 올라가는 중에는 옆에 땅을 팔 수가 없다
	if (map_info[stage_state][x][y + 1] == -1)
	{
		if (map_info[stage_state][x - 1][y] != -1 && map_state[stage_state][x - 1][y] >= 0)
			return;
	}
	//변화가 있었으니 체인지 플레그르 1로 만들어 변화 있음을 알려줍니다.
	change_flag = 1;
	//플레이어가 왼쪽을 바라봄
	player_state = 1;

	//플레이어가 왼쪽으로 움직일텐데 왼쪽 한칸이 블록 이 있으면 움직이지 못하게 막는 함수입니다.
	if (PlayerDetectCollision(x - 1, y) == 1)
	{
		RedrawMap(player_x, player_y, player_state);
		return 1;//충돌 반환
	}
	ChangeBlock(x, y, x - 1, y, player_state);
	//충돌이 없음을 반환을 합니다
	return 0;
}


//오른쪽도 왼쪽과 마찬가지로 구현했습니다. 방향만 반대로 구현을 했습니다.
int ShiftRight()
{
	int x = player_x;
	int y = player_y;
	//아래 땅이 없다면 옆에 땅을 팔 수 가 없다.
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
		return 1;//충돌 반환
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
		return 1;//충돌 반환
	}
	player_y = PlayerShiftY(y - 1);
	map_info[stage_state][player_x][player_y] = 10;
	map_info[stage_state][x][y] = -1;
	RedrawMap(player_x, player_y, player_state);
	Sleep(interval_sleeptime);
	return 0;
}

//블록 그림 삭제하는 함수
// posX 는 삭제할 블록 좌표 x,  posY 는 삭제할 블록 좌표 y
void Delete(int posX, int posY)
{
	//현재 좌표를 저장하고
	COORD curPos = GetCurrentCursorPos();
	//해당 좌표로 이동을하고
	SetCurrentCursorPos(posX * 3 + GBOARD_ORIGIN_X, posY * 2 + GBOARD_ORIGIN_Y);
	//아무것도 없는 블록 그림 그리기
	ShowBlock(DeleteBlock[0]);
	//좌표 원상복귀
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

//게임 종료시 어떻게 할지 정하는 함수로 일단은 보류
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
	printf("                                    10초뒤 창이 닫힙니다.!   ");
	Sleep(10000);
	SetCurrentCursorPos(FINALL_X, FINALL_Y + 1);
	printf("YOU WIN");
	exit(-1);
}

//게임 종료시 어떻게 할지 정하는 함수로 일단은 보류
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
		printf("                                    10초뒤 창이 닫힙니다.!   ");
		Sleep(10000);
		SetCurrentCursorPos(FINALL_X, FINALL_Y + 1);
		printf("GAME OVER");
		exit(-1);
	}

}
void ShowPlayerState()
{
	Set_Color(WHITE);
	/*현재 캐릭터 상태 (임시 디자인) 캐릭터 상태 관련 변수가 만들어지면 수정하겠습니다(11/26)*/
	SetCurrentCursorPos(MAP_INFO_X * 3 + 2, 2);
	printf("HP: ");
	for (int i = 0; i < player_hp / 10; i++) {
		printf("─");
	}
	for (int i = player_hp / 10; i <= 10; i++) {
		printf("  ");
	}
	SetCurrentCursorPos(MAP_INFO_X * 3 + 20, 2);

	printf("%03d/100", player_hp);
	SetCurrentCursorPos(MAP_INFO_X * 3 + 2, 4);
	printf("O2: ");
	for (int i = 0; i < player_o2 / 10; i++) {
		printf("─");
	}
	for (int i = player_o2 / 10; i <= 10; i++) {
		printf("  ");
	}
	SetCurrentCursorPos(MAP_INFO_X * 3 + 20, 4);
	printf("%03d/100", player_o2);

}