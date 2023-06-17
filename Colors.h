//#pragma once
#ifndef COLORS_H
# define COLORS_H
#include <Windows.h>
//�� ��������� ���� ���� �Լ����Դϴ�.


//�̰��� �̹� �����쿡�� �����ϴ� ���� ���� ������ �����Ѱ��Դϴ�.
//�̰��� ���� ���� �� �ʿ䰡 �����ϴ�
#define BLACK 0					//
#define DARKBLUE 1				//
#define DARKGREEN 2				//
#define DARKSKYBLUE 3			//
#define DARKRED 4				
#define DARKPURPLE 5			//
#define DARKYELLOW 6			//
#define GRAY 7					//
#define DARKGRAY 8
#define BLUE 9					//
#define GREEN 10				//
#define SKYBLUE 11				//
#define RED 12					//
#define PURPLE 13		
#define YELLOW 14				//
#define  WHITE 15				//
//�Ʒ� �Լ��� ������ ��ȭ�� �����ִ� �Լ� �Դϴ�. 
//�ش��ϴ� �����̸��� int color�� ������ �۾��� ���� 
//�� ������ ���Ѵٰ� �����ϸ� �ȴ�.
void Set_Color(int color);

//�̰� �׳� �ϳ��ϳ� �̸� ���缭 �÷��� ������ �ʿ� ����
//���ϰ� ��Ͽ� ���� ������ �־��ָ� �˾Ƽ� ������ 
//�׸��� �ְ� ���ִ� �Լ��� �ش� ��� ������ ���� ������
//������ �׸��� �����ϴ� �Լ���� �����ϸ� �ȴ�.
void SetMapColor(int block_color);

#endif // !COLORS_H