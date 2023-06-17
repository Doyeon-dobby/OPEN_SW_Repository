#ifndef MONSTER_H
#define MONSTER_H

#define BOMB_SCOPE 5

typedef struct Mob
{
	int idx;
	int direction;
	int pos_x;
	int pos_y;
	int live;
	int stage;
}MOB, * MMOB;

void MonsterDrawing();

void MonsterSetting(MMOB mon);

void InitMonster(int monster_idx, int p_x, int p_y, int state);

int MonsterDetectCollision(int curX, int curY);

void MosterMove(MMOB mon);

int MosterDirection(MMOB mon);

void MosterDeath(MMOB mon);



#endif // !MONSTER_H

