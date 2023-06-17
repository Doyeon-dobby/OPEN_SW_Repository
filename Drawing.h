//#pragma once
#ifndef DRAWING_H
# define DRAWING_H


//�׸��� �׸��� ���õ� �Լ��� ��Ƶ� ���̴�

#define GBOARD_ORIGIN_X 2	//���� ������ ��ġ�� �׸��� ������ x�ప
#define GBOARD_ORIGIN_Y 3	//���� ������ ��ġ�� �׸��� ������ y�ప

#define REDRAW_SIZE_X 3		//�ٽñ׸� ���� ������� �÷��̾��� �������� �¿� 2ĭ
#define REDRAW_SIZE_Y 3		//�ٽñ׸� ���� ������� �÷��̾��� �������� ���� 2ĭ

#define REDRAW_M_X 1
#define REDRAW_M_Y 1

void DrawMap();



//�ٽ� �׸��� �Լ�
//�÷��̾ �ش��ϴ� �� �������θ� �ٽ� �׸���.
void RedrawMap(int p_x, int p_y, int p_s);

void MonsterRedrawMap(int m_x, int m_y, int m_s);

void Mon_Draw_ksh(int x, int y, int state);

#endif //DRAWING_H // !DRAWING_H
