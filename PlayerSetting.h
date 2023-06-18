//#pragma once
#ifndef PLAYERSETTING
# define PLAYERSETTING

//�� ��������� 
//�÷��̾ ���� �Լ����� ��Ƶ� ���Դϴ�.

// �÷��̾��� ��ǥ
//int player_x;
//int player_y;
//�÷��̾��� �ǿ� ��Ұ����� �ִ�ġ�� ���Ѵ�
#define PLAYER_MAX_HP 100;
#define PLAYER_MAX_O2 100;

//�÷��̾� �ʱ� ��ġ
#define PLAYER_ORIGIN_X 40;
#define PLAYER_ORIGIN_Y 0;

//���� ���۽� �÷��̾ ���� ������ �ʱ�ȭ�ϴ� �Լ��̴�
void PlayerSetting();
int PlayerDetectCollision(int curX, int curY); //curX �浹 �˻��� x��ǥ curY �浹 �˻��� y��ǥ
//�÷��̾� ��ġ�� ���� �ϴ� �Լ�
//�� �Լ��� �÷��̾� ��ġ�� �������� 
//�� ���� ���� ������ ���� �����ϸ� ���̻� �̵���
//���ϰ� �����ش�
int PlayerShiftX(int x);
//�÷��̾ ���� ��ġ�� ����� ���ϰ��ϴ� �Լ�
int PlayerShiftY(int y);

#endif // !PLAYERSETTING
