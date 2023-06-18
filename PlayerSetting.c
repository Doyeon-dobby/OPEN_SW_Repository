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

//���� ���۽� �÷��̾ ���� ������ �ʱ�ȭ�ϴ� �Լ��̴�
void PlayerSetting()
{
	//�÷��̾� ��ġ�� ������ ���� ��Ƽ�� �Ѵ�
	player_x = PLAYER_ORIGIN_X;
	player_y = PLAYER_ORIGIN_Y;
	//�÷��̾� �� 10�̶�� ���ڷ� ���Ǹ� �Ѵ�.
	map_info[stage_state][player_x][player_y] = 10;
	//�ش��ϴ� �÷��̾ �׸���.
	SetCurrentCursorPos(player_x * 3 + GBOARD_ORIGIN_X, player_y * 2 + GBOARD_ORIGIN_Y);
}
int PlayerDetectCollision(int curX, int curY) //curX �浹 �˻��� x��ǥ curY �浹 �˻��� y��ǥ
{
	if (map_info[stage_state][curX][curY] == 1)//���� �� ���� ���̸� �浹
	{
		return 1;
	}
	if (map_info[stage_state][curX][curY] >= 0)//��� ���� ���� �浹(ShiftUp���� ���)
	{
		return 2;
	}
	else                        //�����̸� ����� �����Ƿ� �������
	{
		return 0; 
	}
}

//�÷��̾� ��ġ�� ���� �ϴ� �Լ�
//�� �Լ��� �÷��̾� ��ġ�� �������� 
//�� ���� ���� ������ ���� �����ϸ� ���̻� �̵���
//���ϰ� �����ش�
int PlayerShiftX(int x)
{
	//���� ��(0)�� ������ �ϸ� ���̻� ���ʿ� ������ ���´�
	if (x < 0)
		return 0;
	//������ ��(index = MAP_INFO_X)�� ���� �� �̻� ���������� ���� ���� ���´�.
	if (x >= MAP_INFO_X)
		return MAP_INFO_X - 1;
	//�ش� ���� ��ȯ
	//�ش� ���� �ƴϸ� �׳� �� ��ȯ
	return x;
}
//�÷��̾ ���� ��ġ�� ����� ���ϰ��ϴ� �Լ�
int PlayerShiftY(int y)
{
	//�÷��̾ ���� ��������ϸ� 0�� ���� ��ȯ�� �Ѵ�
	if (y < 0)
		return 0;
	//�÷��̾ ���� ������� �ϸ� �� ������ �ε��� ���� ��ȯ�� �Ѵ�
	if (y >= MAP_INFO_Y)
		return MAP_INFO_Y - 1;
	//�װ� �ƴ϶�� �׳� �� ��ȯ
	return y;
}