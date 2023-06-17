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

//�÷��̾� ��翡 ���� ����
char Player1[][2][6]
=
{
	{
		" ��",
		" ��"
	},
	{
		"��-",
		"��-"
	},
	{
		"-��",
		"-��"
	},
	{
		" ��",
		" ��"
	}

};

//�ƹ��͵� ���� ����� �׸��� ���� ���
char DeleteBlock[][2][6]
=
{
	{
		"   ",
		"   "
	}
};

//�⺻ ��� ��翡 ���� ����
char BasicBlockModel[][2][6]
=
{
	{
		// 0 : �ƹ��͵� �Ⱥμ��� ���
		"�� ��",
		"�� ��"
	},
	{
		// 1 : ���� �μ��� ���
		"�� ��",
		"��  "
	},
	{
		// 2 : �� �μ��� ���
		"  ��",
		"��  "
	},
	{
		// 3 : �� �μ��� ��� ������ �̰��� ���� ������ �����̴�.
		"   ",
		"   "
	}
};

//���� ��翡 ���� ����
char Monster1[][2][6]
=
{
	{
		"   ",
		"��-"
	},
	{
		"   ",
		"-��"
	}

};
char MineralModel[][2][6]
=
{
	{
		"�� ",
		" ��"
	}
};

char BombModel[][2][6]
=
{
	{
		"�� ",
		" ��"
	},
	{
		"�� ",
		" ��"
	}
};
char OxygenModel[][2][6]
=
{
	{
		"�� ",
		" ��"
	}
};
char HpItemModel[][2][6]
=
{
	{
		"�� ",
		" ��"
	}
};
char TeleportModel[][2][6]
=
{
	{
		"�� ",
		" ��"
	}
};
char Door1[][2][6]
=
{
	{
		"������",
		"������"
	}
};
char ShopNPC[][2][6]
=
{
	{
		" ��",
		" ��"
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

//����� �����ִ� ����̴�
void ShowBlock(char blockInfo[2][6])
{
	int y, x;
	COORD curPos = GetCurrentCursorPos();
	//���� ����� ù���� ����
	printf("%s", blockInfo[0]);
	//���� �ٷ� �Ѿ��
	SetCurrentCursorPos(curPos.X, curPos.Y + 1);
	//���� ����� �ι�°���� ����
	printf("%s", blockInfo[1]);
	//Ŀ�� ��ġ ���󺹱�
	SetCurrentCursorPos(curPos.X, curPos.Y);

}

void ChangeBlock(int p_x, int p_y, int change_x, int change_y, int state)
{
	int change_block_state = map_state[stage_state][change_x][change_y];
	int change_block_info = map_info[stage_state][change_x][change_y];

	//���� �շ��ְų�				���� �������̰ų�          ���� �ƴ� ��
	if (change_block_info == -1 || change_block_state == -1 || change_block_info > 9)
	{
		//������ �Ծ��� ��
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
		//�ٶշ��ִٸ�
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
