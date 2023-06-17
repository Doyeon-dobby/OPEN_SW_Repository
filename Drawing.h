//#pragma once
#ifndef DRAWING_H
# define DRAWING_H


//그림을 그리는 관련된 함수를 모아둔 곳이다

#define GBOARD_ORIGIN_X 2	//맵이 시작할 위치를 그리는 시작점 x축값
#define GBOARD_ORIGIN_Y 3	//맵이 시작할 위치를 그리는 시작점 y축값

#define REDRAW_SIZE_X 3		//다시그릴 맵의 사이즈는 플레이어의 기준으로 좌우 2칸
#define REDRAW_SIZE_Y 3		//다시그릴 맵의 사이즈는 플레이어의 기준으로 상하 2칸

#define REDRAW_M_X 1
#define REDRAW_M_Y 1

void DrawMap();



//다시 그리는 함수
//플레이어에 해당하는 것 기준으로만 다시 그린다.
void RedrawMap(int p_x, int p_y, int p_s);

void MonsterRedrawMap(int m_x, int m_y, int m_s);

void Mon_Draw_ksh(int x, int y, int state);

#endif //DRAWING_H // !DRAWING_H
