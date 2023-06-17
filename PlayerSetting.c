#include "PlayerSetting.h"
#include "Keys.h"
#include "map.h"
#include "Drawing.h"

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern int stage_state;

int player_x;
int player_y;

int player_state = 0;

int player_hp = PLAYER_MAX_HP;
int player_o2 = PLAYER_MAX_O2;

//게임 시작시 플레이어에 관한 모든것을 초기화하는 함수이다
void PlayerSetting()
{
	//플레이어 위치를 다음과 같이 셋티을 한다
	player_x = PLAYER_ORIGIN_X;
	player_y = PLAYER_ORIGIN_Y;
	//플레이어 는 10이라는 숫자롱 정의를 한다.
	map_info[stage_state][player_x][player_y] = 10;
	//해당하는 플레이어를 그린다.
	SetCurrentCursorPos(player_x * 3 + GBOARD_ORIGIN_X, player_y * 2 + GBOARD_ORIGIN_Y);
}
int PlayerDetectCollision(int curX, int curY) //curX 충돌 검사할 x좌표 curY 충돌 검사할 y좌표
{
	if (map_info[stage_state][curX][curY] == 1)//뚫을 수 없는 땅이면 충돌
	{
		return 1;
	}
	if (map_info[stage_state][curX][curY] >= 0)//모든 블럭에 대해 충돌(ShiftUp에서 사용)
	{
		return 2;
	}
	else                        //음수이면 블록이 없으므로 통과가능
	{
		return 0; 
	}
}

//플레이어 위치를 조절 하는 함수
//이 함수는 플레이어 위치가 일정범위 
//즉 왼쪽 끝과 오른쪽 끝에 도달하면 더이상 이동을
//못하게 막아준다
int PlayerShiftX(int x)
{
	//왼쪽 끝(0)에 도달을 하면 더이상 왼쪽에 못가게 막는다
	if (x < 0)
		return 0;
	//오른쪽 끝(index = MAP_INFO_X)가 오면 더 이상 오른쪽으로 가는 것을 막는다.
	if (x >= MAP_INFO_X)
		return MAP_INFO_X - 1;
	//해당 값을 반환
	//해당 값이 아니면 그냥 값 반환
	return x;
}
//플레이어가 일정 위치를 벗어나지 못하게하는 함수
int PlayerShiftY(int y)
{
	//플레이어가 맵을 벗어날려고하면 0의 값을 반환을 한다
	if (y < 0)
		return 0;
	//플레이어가 맵을 벗어날려고 하면 맵 마지막 인덱스 값을 반환을 한다
	if (y >= MAP_INFO_Y)
		return MAP_INFO_Y - 1;
	//그게 아니라면 그냥 값 반환
	return y;
}