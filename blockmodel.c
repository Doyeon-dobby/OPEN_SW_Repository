#include "blockmodel.h"

#include "ConsoleControll.h"
#include "map.h"
#include "Drawing.h"
#include "PlayerSetting.h"
#include "Score.h"
#include "Inventory.h"

#include <stdio.h>

extern int map_info[5][100][50];
extern int map_state[5][100][50];

extern int player_x;
extern int player_y;
extern int stage_state;
extern int now_inven_show;
extern int interval_sleeptime;

int block_change_waitingtime = 500;

//플레이어 모양에 대한 정보
char Player1[][2][6]
=
{
	{
		" ●",
		" ▼"
	},
	{
		"◀-",
		"◀-"
	},
	{
		"-▶",
		"-▶"
	},
	{
		" ▲",
		" ♠"
	}

};

//아무것도 없는 블록을 그리기 위한 모양
char DeleteBlock[][2][6]
=
{
	{
		"   ",
		"   "
	}
};

//기본 블록 모양에 대한 정보
char BasicBlockModel[][2][6]
=
{
	{
		// 0 : 아무것도 안부셔진 모양
		"┌ ┐",
		"└ ┘"
	},
	{
		// 1 : 조금 부셔진 모양
		"┌ ┐",
		"└  "
	},
	{
		// 2 : 더 부셔진 모양
		"  ┐",
		"└  "
	},
	{
		// 3 : 다 부셔진 모양 아직은 이것을 굳이 쓸까라는 생각이다.
		"   ",
		"   "
	}
};

//몬스터 모양에 대한 정보
char Monster1[][2][6]
=
{
	{
		"   ",
		"◀-"
	},
	{
		"   ",
		"-▶"
	}

};
char MineralModel[][2][6]
=
{
	{
		"☆ ",
		" ☆"
	}
};

char BombModel[][2][6]
=
{
	{
		"▩ ",
		" ▩"
	},
	{
		"▒ ",
		" ▒"
	}
};
char OxygenModel[][2][6]
=
{
	{
		"◐ ",
		" ◑"
	}
};
char HpItemModel[][2][6]
=
{
	{
		"♥ ",
		" ♥"
	}
};
char TeleportModel[][2][6]
=
{
	{
		"∧ ",
		" ∧"
	}
};
char Door1[][2][6]
=
{
	{
		"┏┳┓",
		"┃┃┃"
	}
};
char ShopNPC[][2][6]
=
{
	{
		" ☎",
		" ▩"
	}
};

void SleepWork(int delay)
{
	int stime = clock();
	while (1) {
		int etime = clock() - stime;
		if (etime > delay) break;
	}
}

//블록을 보여주는 모양이다
void ShowBlock(char blockInfo[2][6])
{
	int y, x;
	COORD curPos = GetCurrentCursorPos();
	//들어온 블록의 첫줄을 쓴다
	printf("%s", blockInfo[0]);
	//다음 줄로 넘어가서
	SetCurrentCursorPos(curPos.X, curPos.Y + 1);
	//들어온 블록이 두번째줄을 쓴다
	printf("%s", blockInfo[1]);
	//커서 위치 원상복귀
	SetCurrentCursorPos(curPos.X, curPos.Y);

}

void ChangeBlock(int p_x, int p_y, int change_x, int change_y, int state)
{
	int change_block_state = map_state[stage_state][change_x][change_y];
	int change_block_info = map_info[stage_state][change_x][change_y];

	//땅이 뚫려있거나				광물 아이템이거나          블럭이 아닐 때
	if (change_block_info == -1 || change_block_state == -1 || change_block_info > 9)
	{
		//광물을 먹었을 때
		if (change_block_state == -1)
		{
			addItem(change_block_info, 1);
			now_inven_show = 0;
			GetSocre(change_block_info);

		}
		player_x = change_x;
		player_y = change_y;
		map_info[stage_state][change_x][change_y] = 10;
		map_info[stage_state][p_x][p_y] = -1;
		map_state[stage_state][p_x][p_y] = 0;
		RedrawMap(player_x, player_y, state);
		SleepWork(interval_sleeptime);
		return;

	}

	if (change_block_info == 0)
	{
		map_state[stage_state][change_x][change_y]++;
		if (map_state[stage_state][change_x][change_y] == 2)
			GetSocre(change_block_info);
		//다뚫려있다면
		if (change_block_state == 2)
		{
			map_info[stage_state][change_x][change_y] = -1;
			map_state[stage_state][change_x][change_y] = 0;

			player_x = change_x;
			player_y = change_y;
			map_info[stage_state][change_x][change_y] = 10;
			map_info[stage_state][p_x][p_y] = -1;
			map_state[stage_state][p_x][p_y] = 0;

			RedrawMap(player_x, player_y, state);
			SleepWork(block_change_waitingtime);
			return;
		}
		RedrawMap(p_x, p_y, state);
		SleepWork(block_change_waitingtime);
		return;
	}

	if (change_block_info == -1 || change_block_info > 9)
	{
		RedrawMap(player_x, player_y, state);
		return;
	}

	if (change_block_info >= 2 && change_block_info <= 9)
	{
		if (change_block_state == 2)
		{
			map_state[stage_state][change_x][change_y] = -1;
			RedrawMap(p_x, p_y, state);
			SleepWork(block_change_waitingtime);
			return;
		}
		map_state[stage_state][change_x][change_y]++;

		RedrawMap(p_x, p_y, state);
		SleepWork(block_change_waitingtime);
		return;
	}
}
