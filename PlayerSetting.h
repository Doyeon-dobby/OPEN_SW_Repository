//#pragma once
#ifndef PLAYERSETTING
# define PLAYERSETTING

//위 헤더파일은 
//플레이어에 관한 함수들을 모아둔 것입니다.

// 플레이어의 좌표
//int player_x;
//int player_y;
//플레이어의 피와 산소게이지 최대치를 정한다
#define PLAYER_MAX_HP 100;
#define PLAYER_MAX_O2 100;

//플레이어 초기 위치
#define PLAYER_ORIGIN_X 40;
#define PLAYER_ORIGIN_Y 0;

//게임 시작시 플레이어에 관한 모든것을 초기화하는 함수이다
void PlayerSetting();
int PlayerDetectCollision(int curX, int curY); //curX 충돌 검사할 x좌표 curY 충돌 검사할 y좌표
//플레이어 위치를 조절 하는 함수
//이 함수는 플레이어 위치가 일정범위 
//즉 왼쪽 끝과 오른쪽 끝에 도달하면 더이상 이동을
//못하게 막아준다
int PlayerShiftX(int x);
//플레이어가 일정 위치를 벗어나지 못하게하는 함수
int PlayerShiftY(int y);

#endif // !PLAYERSETTING
