//#pragma once
#ifndef MAP_H
# define MAP_H

//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>

#pragma warning(disable:4996)

// � ��������� ���� ����
//������ �׸��� ������� MAP_INFO_X ��ó���� ������ 
//�׸��� ������ map_infoũ��� �״� ���߿��մϴ�
	//int map_info[stage_state][100][50] = { 0 };
// �� ����� ��� ���� ���������� ���� ����
	//int map_state[stage_state][100][50] = { 0 };


//���� ������
#define MAP_INFO_X 60
#define MAP_INFO_Y 35

#define DOOR_LOC 58

#define MONSTER1_SET_X 40
#define MONSTER1_SET_Y 5
#define MONSTER2_SET_X 20
#define MONSTER2_SET_Y 5
#define MONSTER3_SET_X 40
#define MONSTER3_SET_Y 9

#define STAGE_1_MONSTER1_SET_X 42
#define STAGE_1_MONSTER1_SET_Y 6
#define STAGE_1_MONSTER2_SET_X 14
#define STAGE_1_MONSTER2_SET_Y 11

#define STAGE_2_MONSTER3_SET_X 51
#define STAGE_2_MONSTER3_SET_Y 10
#define STAGE_2_MONSTER4_SET_X 38
#define STAGE_2_MONSTER4_SET_Y 14
#define STAGE_2_MONSTER5_SET_X 19
#define STAGE_2_MONSTER5_SET_Y 22


#define STAGE_3_MONSTER6_SET_X 45
#define STAGE_3_MONSTER6_SET_Y 15
#define STAGE_3_MONSTER7_SET_X 35
#define STAGE_3_MONSTER7_SET_Y 21
#define STAGE_3_MONSTER8_SET_X 20
#define STAGE_3_MONSTER8_SET_Y 30

#define STAGE_4_MONSTER9_SET_X 5
#define STAGE_4_MONSTER9_SET_Y 12

#define STAGE_4_MONSTER10_SET_X 51
#define STAGE_4_MONSTER10_SET_Y 16

#define STAGE_4_MONSTER11_SET_X 30
#define STAGE_4_MONSTER11_SET_Y 23

#define STAGE_4_MONSTER12_SET_X 22
#define STAGE_4_MONSTER12_SET_Y 27

#define STAGE_4_MONSTER13_SET_X 40
#define STAGE_4_MONSTER13_SET_Y 32


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

//map_state = 0 �ƹ��͵� �Ⱥμ��� ��� 
//map_state = 1 ���� �μ��� ���
//map_state = 2 ���� �� �μ��� ���
//map_state = 3 ������ ���



//map_info = -1 �ƹ��͵� ���� ���
//map_info = 0  �Ը��� �⺻ ��
// map_info = 1 �Ը��� �ʴ� �⺻ �� ���̳ʸ���Ʈ�θ� �Ծ�ߵ�
// map_info = 2  ��
// map_info = 3  ��
// map_info = 4  ��
// map_info = 5  ũ����Ż
// map_info = 6  ���̾Ƹ��
// 
// map_info = 7  Ư�� : ũ��Ƭ
// map_info = 8  Ư�� : ����
// map_info = 9  Ư�� : ũ����
//
// map_info = 10  �÷��̾�
// map_info = 11  ��
// map_info = 12  ������
// map_info = 13  ��
//  map_info = 14  ����
// 
//���� ���۽� ���� ����� ������ �ϴ� ���Դϴ�.
//void SetBaiscMap();
void ShowStage();

int MapStateRefund(int x, int y);

void SetMapStage_0();
void SetMapStage_1();
void SetMapStage_2();

void SetMapStage_3();
void SetMapStage_4();

void ShowQuest();

void ShowManual();

#endif // 