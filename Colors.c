#include "Colors.h"

void Set_Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//�̰� �׳� �ϳ��ϳ� �̸� ���缭 �÷��� ������ �ʿ� ����
//���ϰ� ��Ͽ� ���� ������ �־��ָ� �˾Ƽ� ������ 
//�׸��� �ְ� ���ִ� �Լ��� �ش� ��� ������ ���� ������
//������ �׸��� �����ϴ� �Լ���� �����ϸ� �ȴ�.
void SetMapColor(int block_color)
{
	switch (block_color)
	{
	case -1:
		Set_Color(BLACK);
		break;
	case 0:
		Set_Color(WHITE);
		break;
	case 1:
		Set_Color(RED);
		break;
	case 2:
		Set_Color(DARKYELLOW);
		break;
	case 3:
		Set_Color(GRAY);
		break;
	case 4:
		Set_Color(YELLOW);
		break;
	case 5:
		Set_Color(BLUE);
		break;
	case 6:
		Set_Color(SKYBLUE);
		break;
	case 7:
		Set_Color(DARKBLUE);
		break;
	case 8:
		Set_Color(DARKGREEN);
		break;
	case 9:
		Set_Color(PURPLE);
		break;
	case 10:
		Set_Color(BLUE);
		break;
	case 11:
		Set_Color(DARKYELLOW);
		break;
	case 12:
		Set_Color(DARKPURPLE);
		break;
	case 13:
		Set_Color(WHITE);
		break;
	case 14:
		Set_Color(DARKSKYBLUE);
		break;
	case 15:
		Set_Color(DARKRED);
		break;
	default:
		break;
	}
}
