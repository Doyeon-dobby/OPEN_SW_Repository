#include "Inventory.h"

#include "map.h"

/*������ �߰��� ���*/
#include "ConsoleControll.h"
#include "PlayerSetting.h"
#include "Colors.h"
#include "Drawing.h"
#include "blockmodel.h"
#include "Item.h"

int o2 = 0;
int bomb = 0;
int heal = 0;
int teleport = 0;
int dynamite = 0;
int decrease_damage = 0;
int interval_sleeptime = 500;

money = 0;

inven_index = 0;


/*���*/
Equip cap = { 1,0,0,0,0 };
Equip drill = { 1,5,0,0,1 };
Equip shoes = { 1,0,7,0,2 };

Item inven[INVENTORY_SIZE] = { 0 }; //ȹ���� �������� ������ ����ü �迭(�ִ� 30�� ���� ����)


int show_charaterInfo_x = INVENTORY_SIZE_X * 5 + 5; //ĳ���� ����â x�� ũ��
int show_charaterInfo_y = INVENTORY_SIZE_Y;  //ĳ���� ����â y�� ũ��

int show_inventory_x = INVENTORY_SIZE_X * 5 + 5; //�κ��丮â x�� ũ��
int show_inventory_y = INVENTORY_SIZE_Y; //�κ��丮â y�� ũ��

int inventory_location_x = MAP_INFO_X + 3;
int inventory_location_y = 10;

extern int player_x;
extern int player_y;

extern int player_hp;
extern int player_o2;

extern int map_info[100][50];
extern int map_state[100][50];
extern char Player1[][2][6];
extern char DeleteBlock[][2][6];
extern char BasicBlockModel[][2][6];
extern char MineralModel[][2][6];

extern int block_change_waitingtime;

/*ĳ���� ����âƲ �����*/
void CharacterInfo_format() {

	Set_Color(WHITE); //���ڻ� ��� ����
	RemoveCursor(); //Ŀ�� ����

	SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y);

	/*âƲ ���� ����*/
	for (int y = 0; y < show_charaterInfo_y * 2; y++) {
		for (int x = 0; x < show_charaterInfo_x; x++) {
			SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y + y);
			printf(" ");
		}
	}

	SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y);
	printf("��");
	for (int x = 1; x < show_charaterInfo_x; x++) {
		SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y);
		printf("��");
	}
	printf("��");

	SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y + show_charaterInfo_y * 2);
	printf("��");
	for (int x = 1; x < show_charaterInfo_x; x++) {
		SetCurrentCursorPos(x + inventory_location_x * 3, show_charaterInfo_y * 2 + inventory_location_y);
		printf("��");
	}
	printf("��");

	for (int y = 1; y < show_charaterInfo_y * 2; y++) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y + y);
		printf("��");
	}

	for (int y = 1; y < show_charaterInfo_y * 2; y++) {
		SetCurrentCursorPos(inventory_location_x * 3 + show_charaterInfo_x, inventory_location_y + y);
		printf("��");
	}
}


/*ĳ���� ����â ���*/
void showCharacterInfo() {
	CharacterInfo_format();

	/*����âƲ ���� ����*/
	for (int y = 1; y < show_charaterInfo_y * 2; y++) {
		for (int x = 1; x < show_charaterInfo_x * 2; x++) {
			SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y + y);
			printf(" ");
		}
	}

	/*ĳ���� ����*/
	SetCurrentCursorPos(inventory_location_x * 3 + show_charaterInfo_x / 2 - 5, inventory_location_y + 1); //���� ��ġ ����
	printf("[Inventory]");

	if (cap.level == 2) Set_Color(GREEN);
	if (cap.level == 3) Set_Color(YELLOW);
	SetCurrentCursorPos(inventory_location_x * 3 + 5, inventory_location_y + 3);
	printf("��");
	Set_Color(WHITE);
	if (drill.level == 2)Set_Color(GREEN);
	if (drill.level == 3) Set_Color(YELLOW);
	SetCurrentCursorPos(inventory_location_x * 3 + 5, inventory_location_y + 4);
	printf("��");
	Set_Color(WHITE);

	/*���� ������ ��� (�ӽ� ������) ��� ���� ������ ��������� �����ϰڽ��ϴ�(11/26)*/
	SetCurrentCursorPos(inventory_location_x * 3 + 9, inventory_location_y + 3);
	printf("�� ");
	switch (cap.level) {
	case 1:
		printf(" ���̽� ĸ");
		break;
	case 2:
		printf(" �ް� ĸ");
		break;
	case 3:
		printf(" ��Ʈ�� ĸ");
		break;
	}
	SetCurrentCursorPos(inventory_location_x * 3 + 9, inventory_location_y + 4);
	printf("�� ");
	switch (drill.level) {
	case 1:
		printf(" ���̽� �帱");
		break;
	case 2:
		printf(" �ް� �帱");
		break;
	case 3:
		printf(" ��Ʈ�� �帱");
		break;
	}
	SetCurrentCursorPos(inventory_location_x * 3 + 9, inventory_location_y + 5);
	printf("�� ");
	switch (shoes.level) {
	case 1:
		printf(" ���̽� ����");
		break;
	case 2:
		printf(" �ް� ����");
		break;
	case 3:
		printf(" ��Ʈ�� ����");
		break;
	}

	/*���� ĳ���� �ɷ�ġ (�ӽ� ������) �ɷ�ġ ���� ������ ��������� �����ϰڽ��ϴ�(11/26)*/
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 5);
	printf("������ %d", drill.excavation);
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 4);
	printf("�ν��� %d", shoes.booster);
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 3);
	printf("���� %d", cap.defensive);
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 1);
	printf("                   ");
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 1);
	printf("Money: %d", money);
}


/*�κ��丮âƲ �����*/
void Inventory_format() {

	/*âƲ ���� ����*/
	for (int y = 1; y <= show_inventory_y * 2; y++) {
		for (int x = 0; x < show_inventory_x; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + y);
			printf(" ");
		}
	}
	for (int x = 0; x <= show_inventory_x; x++) {
		SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + 1);
		if (x == 0) {
			printf("��");
		}
		else if (x == show_inventory_x) {
			printf("��");
		}
		else {
			int mod = show_inventory_x / 5;
			if (x % mod == 0) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
	}
	for (int y = 0; y < show_inventory_y * 2 - 1; y++) {
		for (int x = 0; x <= show_inventory_x; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + 2 + y);
			int mod = show_inventory_x / 5;
			if (y % 2 == 0) {
				if (x % mod == 0) {
					printf("��");

				}
			}
			else {
				if (x == 0) {
					printf("��");
				}
				else if (x == show_inventory_x) {
					printf("��");
				}
				else {
					if (x % mod == 0) {
						printf("��");

					}
					else {
						printf("��");
					}
				}
			}
		}
	}
	for (int x = 0; x <= show_inventory_x; x++) {
		SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + 2 * INVENTORY_LOCATE_Y + 1);
		if (x == 0) {
			printf("��");
		}
		else if (x == show_inventory_x) {
			printf("��");
		}
		else {
			int mod = show_inventory_x / 5;
			if (x % mod == 0) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
	}
}

/*�κ��丮â ���*/
void showInventoryInfo() {
	Inventory_format();
	showInventory_list();
}

void showInventory_list() {
	int i = 0;

	for (int y = 0; y < show_inventory_y * 2 - 1; y++) {
		for (int x = 0; x <= show_inventory_x; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + 2 + y);
			int mod = show_inventory_x / 5;
			if (y % 2 == 0) {
				if (x % mod == 1) {
					printf("  ");
				}
				else if (x % mod == mod - 2) {
					printf("  ");
				}
			}
		}
	}
	/*�κ��丮 �ӽ� ������*/
	for (int y = 0; y < show_inventory_y * 2 - 1; y++) {
		for (int x = 0; x <= show_inventory_x; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + 2 + y);
			int mod = show_inventory_x / 5;
			if (y % 2 == 0) {
				if (inven[i].itemID == 0) {
					continue;
				}
				if (x % mod == 1) {
					SetMapColor(inven[i].itemID);
					switch (inven[i].itemID) {
						/*����*/
					case ITEM_COPPER:
						//Set_Color(DARKRED);
						printf("��");
						break;
					case ITEM_SILVER:
						//Set_Color(GRAY);
						printf("��");
						break;
					case ITEM_GOLD:
						//Set_Color(YELLOW);
						printf("��");
						break;
					case ITEM_CRYSTAL:
						//Set_Color(SKYBLUE);
						printf("��");
						break;
					case ITEM_DIAMOND:
						//Set_Color(GREEN);
						printf("��");
						break;
					case ITEM_S_CRAETUM:
						//Set_Color(RED);
						printf("��");
						break;
					case ITEM_S_SELANUM:
						//Set_Color(PURPLE);
						printf("��");
						break;
					case ITEM_S_CRIPTON:
						//Set_Color(DARKGRAY);
						printf("��");
						break;
						/*�Ҹ� ������*/
					case ITEM_O2:
						Set_Color(SKYBLUE);
						printf("��");
						break;
					case ITEM_BOMB:
						Set_Color(DARKGRAY);
						printf("��");
						break;
					case ITEM_HEAL:
						Set_Color(RED);
						printf("��");
						break;
					case ITEM_TELEPORT:
						Set_Color(PURPLE);
						printf("��");
						break;
						/*���*/
					case ITEM_HELMET:
						Set_Color(YELLOW);
						printf("��");
						break;
					case ITEM_SHOES:
						Set_Color(DARKRED);
						printf("��");
						break;
					case ITEM_DRILL:
						Set_Color(GRAY);
						printf("��");
						break;
					}
				}
				else if (x % mod == mod - 2) {
					Set_Color(WHITE);
					printf("%02d", inven[i].amount);
					i++;
				}
			}
		}
	}
}

int isFull() { //�������� ��á���� Ȯ��
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		if (inven[i].amount < INVERNTORY_MINERAL_SIZE) {
			return 0;
		}
	}
	return 1;
}



/*�κ��丮�� ������ �߰�*/
int addItem(int itemID, int amount) {
	int min_index = 0;
	int min = 16;
	int flag = 0;
	/*�κ��丮�� ������ ���޼��� ���*/
	if (isFull() == 1) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("�ذ��: �κ��丮�� ��á���ϴ�!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                                  ");
		Set_Color(WHITE);
		return 0;
	}
	if (inven_index == 0) { //�κ��丮�� ���������...
		inven[inven_index].itemID = itemID;
		inven[inven_index].amount = amount;
		inven_index++;
		InventorySort();
		return 1;
	}
	for (int i = 0; i < inven_index; i++) {
		if (inven[i].itemID == itemID) { //�̹� �ش� �������� ����� ������ ���� ��
			if (min >= inven[i].amount) { //���� ���� ����� �ε��� ã��
				min_index = i;
				min = inven[i].amount;
				flag = 1;
			}
		}
	}
	if (flag == 1) {
		if (inven[min_index].amount + amount > INVERNTORY_MINERAL_SIZE) { //���� ���� ����� ĭ�� ����� ������ �� + ���� �����Ϸ��� �����ۼ� > 16�̸�
			if (inven_index == INVENTORY_SIZE) { //�κ��丮 ĭ�� ��á����
				SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
				Set_Color(YELLOW);
				printf("�ذ��: �κ��丮�� ��á���ϴ�!");
				Sleep(800);
				SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
				printf("                                  ");
				Set_Color(WHITE);
				return 0;
			}
			else {
				inven[inven_index].itemID = itemID;
				inven[inven_index].amount = (inven[min_index].amount + amount - INVERNTORY_MINERAL_SIZE);
				inven[min_index].amount = INVERNTORY_MINERAL_SIZE;
				inven_index++;
				InventorySort();
				return 1;
			}

		}
		else {
			inven[min_index].amount += amount;
			InventorySort();
			return 1;
		}
	}
	else {
		inven[inven_index].itemID = itemID;
		inven[inven_index].amount = amount;
		inven_index++;
		InventorySort();
		return 1;
	}
}

int useitem(int itemID) {
	for (int i = inven_index - 1; i >= 0; i--) {
		if (itemID == inven[i].itemID) {
			inven[i].amount--;
			if (inven[i].amount == 0) {
				inven[i].itemID = 0;
				InventorySort();
			}
			return;
		}
	}
}

void upgradeEquip(Equip* e) { //��� ���׷��̵�
	if (e->level == 1) {
		if (money < 500) {
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			Set_Color(YELLOW);
			printf("�ذ��: ��尡 �����մϴ�!");
			Sleep(800);
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			printf("                           ");
			Set_Color(WHITE);
			return;//�� ����
		}
		money -= 500;
		if (e->id == 0) decrease_damage += 10;
		if (e->id == 1) block_change_waitingtime -= 200;
		if (e->id == 2) interval_sleeptime -= 200;
	}
	else if (e->level == 2) {
		if (money < 1000) {
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			Set_Color(YELLOW);
			printf("�ذ��: ��尡 �����մϴ�!");
			Sleep(800);
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			printf("                           ");
			Set_Color(WHITE);
			return;//�� ����
		}
		money -= 1000;
		if (e->id == 0) decrease_damage += 10;
		if (e->id == 1) block_change_waitingtime -= 200;
		if (e->id == 2) interval_sleeptime -= 200;
	}
	else {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("�ذ��: �����Դϴ�!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                           ");
		Set_Color(WHITE);
		return;
	}
	e->level++;
	e->excavation++;
	e->booster++;
	e->defensive++;
	showCharacterInfo();
}


/*�κ��丮 �����ֱ�/�����*/
void ShowInventory(int key)
{
	//0�� ���� ��� ���� 
	//�κ��丮�� �ݴ´�
	if (key == 0)
	{

		eraseInventory(); //�κ��丮 ����
	}
	//1�� ������
	//�κ��丮�� ����.
	if (key == 1)
	{
		showCharacterInfo(); //����â ���
		showInventoryInfo(); //�κ��丮 ���
	}
}

/*�κ��丮 ����*/
void InventorySort()
{
	/*�������� ���*/
	for (int i = 0; i < inven_index - 1; i++) {

		Item min = inven[i];
		int index = i;

		for (int j = i + 1; j < inven_index; j++) {
			if (min.amount < inven[j].amount) {
				min = inven[j];
				index = j;
			}
		}
		Item tmp;
		tmp.itemID = inven[i].itemID;
		tmp.amount = inven[i].amount;

		inven[i].itemID = inven[index].itemID;
		inven[i].amount = inven[index].amount;

		inven[index].itemID = tmp.itemID;
		inven[index].amount = tmp.amount;
	}
}


void eraseInventory() {
	/*����âƲ ���� ����*/
	for (int y = 0; y <= show_charaterInfo_y * 2; y++) {
		for (int x = 0; x <= show_charaterInfo_x * 2; x++) {
			SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y + y);
			printf(" ");
		}
	}
	/*�κ��丮 âƲ ���� ����*/
	for (int y = 0; y <= show_inventory_y * 2; y++) {
		for (int x = 0; x <= show_inventory_x * 2; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + y + 1);
			printf(" ");
		}
	}
	SetCurrentCursorPos(player_x, player_y);
}


