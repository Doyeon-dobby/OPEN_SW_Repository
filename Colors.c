#include "Colors.h"

void Set_Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//이건 그냥 하나하나 이름 맞춰서 컬러는 맞춰줄 필요 없이
//편리하게 블록에 대한 정보만 넣어주면 알아서 색깔을 
//그릴수 있게 해주는 함수로 해당 블록 종류에 대한 정보로
//색깔을 그리게 정리하는 함수라고 생각하면 된다.
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
