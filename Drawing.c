#include "Drawing.h"

#include "PlayerSetting.h"
#include "map.h"
#include "Colors.h"
#include "blockmodel.h"
#include "ConsoleControll.h"
#include "Monster.h"

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern char Player1[][2][6];
extern char Monster1[][2][6];
extern char Door1[][2][6];
extern char DeleteBlock[][2][6];
extern char BasicBlockModel[][2][6];
extern char MineralModel[][2][6];
extern char BombModel[][2][6];
extern char ShopNPC[][2][6];

extern int stage_state;

void DrawMap()
{
	//��� ���¸� �޾ƿ��� ����
	int block_state;
	//������ ��ǥ�� �޾Ƽ� ������ �ϰ� ���⼭�� ���� �̰����� �ʿ����� �𸣰�����
	//�׳� ���������� ������ Ŀ�� ��ǥ �޾Ƽ� �Ʒ����� �ٽ� ���󺹱ͽ�Ų��
	COORD curPos = GetCurrentCursorPos();
	for (int x = 0; x < MAP_INFO_X; x++)
	{
		for (int y = 0; y < MAP_INFO_Y; y++)
		{
			//�׸����� �ϴ� �⺻ ĭ�� 3ĭ�̴�. �׷��� x���� ��ĭ�� �׸��µ� 3ĭ�� �ʿ��ϰ� 
			//y���� 2ĭ�� �ʿ�� �Ѵ�.
			SetCurrentCursorPos(x * 3 + GBOARD_ORIGIN_X, y * 2 + GBOARD_ORIGIN_Y);
			//map_info�� ���� ���� ����(�̰� �������� ��ĭ���� �÷��̾������� �Ǵ��ϴ�����, �μ��� ������ ���� ������ ����)
			//�׷��� ���������� ������ �޾ƿͼ� �׿� �ش� �ϴ� �÷��� �޾Ƶ��δ�.
			SetMapColor(map_info[stage_state][x][y]);
			//map_state�� �μ��� ������ ���� ��, �ش� ����� ��� ����� ��Ÿ���ߵǴ��� ǥ���ϴ� �迭�̴�
			block_state = map_state[stage_state][x][y];
			//�������� ���� 0 �̻��̶�� ����� �����ϴ� ���̴�. �� ���ϸ� ����� �����Ƿ� �ƹ��͵� �ȱ׸��� ����� �׸���
			if (map_info[stage_state][x][y] >= 0)
			{
				if (map_info[stage_state][x][y] == 10)//���࿡ ������ 10�̸� �÷��̾��̹Ƿ� �÷��̾ �׸���
				{
					ShowBlock(Player1[block_state]);

				}
				else if (map_info[stage_state][x][y] == 13)
				{
					ShowBlock(Door1);
				}
				else if (map_info[stage_state][x][y] == 14) {
					ShowBlock(ShopNPC);
				}
				else if (map_info[stage_state][x][y] == 15)
				{
					Set_Color(PURPLE);
					ShowBlock(Player1[0]);
				}
				else
				{
					//�װ� �ƴ϶�� ����� ��� ���¿� ���缭 �׸���.
					ShowBlock(BasicBlockModel[block_state]);


				}
			}
			else
			{
				ShowBlock(DeleteBlock[0]);
			}
		}
	}
	Set_Color(WHITE);
	SetCurrentCursorPos(DOOR_LOC * 3 + GBOARD_ORIGIN_X, +GBOARD_ORIGIN_Y);
	ShowBlock(Door1);
	//��ǥ ���󺹱�
	SetCurrentCursorPos(curPos.X, curPos.Y);
}
//�ٽ� �׸��� �Լ�
//�÷��̾ �ش��ϴ� �� �������θ� �ٽ� �׸���.
void RedrawMap(int p_x, int p_y, int p_s)
{
	//�Ȱ��� DrawMap�ռ� ó�� �׸��µ� �� �׸��� ���� �ƴ϶� �÷��̾��� �ֺ��� �ٽ� �׸���.
	int block_state;
	COORD curPos = GetCurrentCursorPos();
	for (int i = 26; i <= 34; i++)
	{
		if (p_y == 0)
		{
			if (i == p_x)
				continue;
			else
				map_info[stage_state][i][0] = 14;
		}
		else
			break;
	}

	//���� 2ĭ ������ 2ĭ
	for (int x = -REDRAW_SIZE_X; x <= REDRAW_SIZE_X; x++)
	{
		//�Ʒ�2ĭ ���� 2ĭ�� �ٽ� �׸���.
		for (int y = -REDRAW_SIZE_Y; y <= REDRAW_SIZE_Y; y++)
		{
			//�ٽ� �׸� x���� y���� �ٽ� ��ǥ�� ����� �Ѵ�
			int re_x = p_x + x;
			int re_y = p_y + y;
			//�̰� �ʿ� �ش��ϴ� ����� �ʰ��� �ϸ� ������
			if (re_y < 0 || re_y >= MAP_INFO_Y)	continue;
			if (re_x < 0 || re_x >= MAP_INFO_X)	continue;

			//��ǥ�� �ش��ϴ� �Ϳ� ���缭 Ŀ���� �ű��
			SetCurrentCursorPos(re_x * 3 + GBOARD_ORIGIN_X, re_y * 2 + GBOARD_ORIGIN_Y);
			SetMapColor(map_info[stage_state][re_x][re_y]);
			block_state = map_state[stage_state][re_x][re_y];


			//�� ������ 0�̻��̸� DrwaMap�� ���������� ����̹Ƿ� �÷��̾�� ����� �ٽ� �׸���.
			if (map_info[stage_state][re_x][re_y] >= 0)
			{
				if (map_info[stage_state][re_x][re_y] == 10)
				{
					ShowBlock(Player1[p_s]);

				}
				else if (map_info[stage_state][re_x][re_y] == 12)
				{
					ShowBlock(BombModel[block_state]);
				}
				else if (map_info[stage_state][re_x][re_y] == 11)
				{
					ShowBlock(Monster1[block_state]);
				}
				else if (map_info[stage_state][re_x][re_y] == 13)
				{
					ShowBlock(Door1);
				}
				else if (map_info[stage_state][re_x][re_y] == 14)
				{

					ShowBlock(ShopNPC);
				}
				else if (map_info[stage_state][re_x][re_y] == 15)
				{
					Set_Color(PURPLE);
					ShowBlock(Player1[0]);
				}
				else
				{
					if (block_state == -1)
					{
						ShowBlock(MineralModel[0]);
					}
					else
					{
						ShowBlock(BasicBlockModel[block_state]);
					}
				}
			}
			else
			{
				ShowBlock(DeleteBlock[0]);
			}
		}
	}

	Set_Color(WHITE);
	SetCurrentCursorPos(DOOR_LOC * 3 + GBOARD_ORIGIN_X, + GBOARD_ORIGIN_Y);
	ShowBlock(Door1);

	//��ǥ ���󺹱�
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void Mon_Draw_ksh(int x, int y, int state)
{
	COORD curPos = GetCurrentCursorPos();

	map_info[stage_state][x][y] = 11;
	SetCurrentCursorPos(x * 3 + GBOARD_ORIGIN_X, y * 2 + GBOARD_ORIGIN_Y);
	SetMapColor(map_info[stage_state][x][y]);	
	ShowBlock(Monster1[state]);

	SetCurrentCursorPos(curPos.X, curPos.Y);

}