#include "shop.h"
#include "Inventory.h"
#include "Colors.h"
#include "PlayerSetting.h"

#include <conio.h>
#include "Keys.h"

#include "map.h"
#include "Drawing.h"
#include "blockmodel.h"
#include "Item.h"

extern int map_info[5][100][50];
extern int map_state[5][100][50];
extern int stage_state;

extern char Player1[][2][6];
extern char DeleteBlock[][2][6];
extern char BasicBlockModel[][2][6];
extern char MineralModel[][2][6];
extern char ShopNPC[][2][6];
extern int player_x;
extern int player_y;

extern int show_charaterInfo_x;
extern int show_charaterInfo_y;

extern int inventory_location_x;
extern int inventory_location_y;

extern Item inven[INVENTORY_SIZE];
extern int inven_index;

extern int money;

extern Equip cap;
extern Equip drill;
extern Equip shoes;

int show_shop_x = 72; //���� ũ��� ���� ũ��� �������� �� �ش� ũ�Ⱑ ���� �����ؼ� 90*6���� �����Ͽ����ϴ�.
int show_shop_y = 3;


int close_flag = 0; //���� �ݱ� ����


shopItem shop_item[SHOP_ITEM_NUM]; //���� ������

/*���� ������ ���� (�ʱ�ȭ��Ű�� ��)*/
void init_shopItem() {
	int i = 0;

	/*������ �־�� �ϴ� �����۵��� ���⿡ ��� �����ֽø� �˴ϴ�.*/

	/*�Ҹ� ������*/
	shop_item[i].itemID = ITEM_O2;
	shop_item[i].price = 500;
	i++;

	shop_item[i].itemID = ITEM_BOMB;
	shop_item[i].price = 100;
	i++;

	shop_item[i].itemID = ITEM_HEAL;
	shop_item[i].price = 500;
	i++;

	shop_item[i].itemID = ITEM_TELEPORT;
	shop_item[i].price = 1000;
	i++;

	/*��� ���� ������*/
	/*
	shop_item[i].itemID = ITEM_HELMET;
	shop_item[i].price = 300;
	i++;

	shop_item[i].itemID = ITEM_SHOES;
	shop_item[i].price = 500;
	i++;

	shop_item[i].itemID = ITEM_DRILL;
	shop_item[i].price = 300;
	*/
}


/*���� Ʋ �����*/
void shop_format() {

	Set_Color(WHITE); //���ڻ� ��� ����
	RemoveCursor(); //Ŀ�� ����

	for (int y = 0; y <= 2; y++) {
		for (int x = 0; x <= 8; x++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 6) + y);
			printf(" ");
		}
	}

	for (int y = 0; y <= show_shop_y * 2; y++) {
		for (int x = 0; x <= show_shop_x; x++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);
			printf(" ");

		}

	}

	for (int y = 0; y <= 2; y++) {
		for (int x = 0; x < 8; x++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 6) + y);
			if (y == 0) {
				if (x == 0) {
					printf("��");
				}
				else if (x == 7) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			else if (y == 2) {
				if (x == 0) {
					printf("��");
				}
				else if (x == 7) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			else {
				if (x == 0 || x == 7) {
					printf("��");
				}
			}
		}
	}

	SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 3,
		(player_y + 6) + 1);
	printf("SHOP");

	Set_Color(WHITE);
	for (int x = 0; x <= show_shop_x; x++) {
		SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
			(player_y + 9));
		if (x == 0) {
			printf("��");
		}
		else if (x == show_shop_x) {
			printf("��");
		}
		else {
			int mod = show_shop_x / 4;
			if (x % mod == 0) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
	}

	for (int y = 1; y < show_shop_y * 2; y++) {
		for (int x = 0; x <= show_shop_x; x++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);

			int mod = show_shop_x / 4;
			if (y % 3 == 0) {
				if (x == 0 || x == show_shop_x) {
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
			else {
				if (x % mod == 0) {
					printf("��");

				}
			}
		}
	}

	for (int x = 0; x <= show_shop_x; x++) {
		SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
			(player_y + 9) + show_shop_y * 2);
		if (x == 0) {
			printf("��");
		}
		else if (x == show_shop_x) {
			printf("��");
		}
		else {
			int mod = show_shop_x / 4;
			if (x % mod == 0) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
	}
}

void show_shopItem() {
	int shop_index = 0;

	int mod = show_shop_x / 4;

	init_shopItem();

	int i = 0;

	/*�ӽ� ������*/



		/*������ ���*/
	for (int y = 1; y < show_shop_y * 2; y += 3) {
		for (int x = 4; x <= show_shop_x; x += mod, i++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);
			/*������ ��ȭ*/
			Set_Color(YELLOW);
			if (y == 4 && x == 58) {
				printf("���� �ȱ�");
			}
			if (y == 4 && x == 4) {
				printf("ĸ ��ȭ");
			}
			if (y == 4 && x == 22) {
				printf("�帱 ��ȭ");
			}
			if (y == 4 && x == 40) {
				printf("���� ��ȭ");
			}

			switch (shop_item[i].itemID) {
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
			}
		}
	}
	i = 0;

	/*���� ���*/
	for (int y = 1; y < show_shop_y * 2; y += 3) {
		for (int x = 7; x <= show_shop_x; x += mod, i++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);

			Set_Color(WHITE);
			switch (shop_item[i].itemID) {
			case ITEM_O2:
				printf("%d", shop_item[i].price);
				break;

			case ITEM_BOMB:
				printf("%d", shop_item[i].price);
				break;

			case ITEM_HEAL:
				printf("%d", shop_item[i].price);
				break;

			case ITEM_TELEPORT:
				printf("%d", shop_item[i].price);
				break;
			}
		}
	}
	i = 0;

	/*������ �̸� ���*/
	for (int y = 2; y < show_shop_y * 2; y += 3) {
		for (int x = 4; x <= show_shop_x; x += mod, i++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);
			/*������ ��ȭ*/
			if (y == 5 && x == 4) {
				switch (cap.level) {
				case 1:
					printf("500");
					break;
				case 2:
					printf("1000");
					break;
				case 3:
					printf("MAX");
					break;
				}
			}
			if (y == 5 && x == 22) {
				switch (drill.level) {
				case 1:
					printf("500");
					break;
				case 2:
					printf("1000");
					break;
				case 3:
					printf("MAX");
					break;
				}
			}
			if (y == 5 && x == 40) {
				switch (shoes.level) {
				case 1:
					printf("500");
					break;
				case 2:
					printf("1000");
					break;
				case 3:
					printf("MAX");
					break;
				}
			}

			switch (shop_item[i].itemID) {
			case ITEM_O2:
				printf("��� ĸ��");
				break;

			case ITEM_BOMB:
				printf("��ź");
				break;

			case ITEM_HEAL:
				printf("���� ����");
				break;

			case ITEM_TELEPORT:
				printf("�ڷ���Ʈ");
				break;
			}
		}
	}
}

void close_shop() {

	for (int y = 0; y <= 2; y++) {
		for (int x = 0; x <= 8; x++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 6) + y);
			printf(" ");
		}
	}

	for (int y = 0; y <= show_shop_y * 2 + 1; y++) {
		for (int x = 0; x <= show_shop_x; x++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);
			printf(" ");

		}
	}

	/*�Ʒ����� DrawMap �Լ��� ����� ���� ����, ����Ǵ� ��ġ�� ũ�⸸ �ٸ�*/
	int block_state;

	for (int y = 0; y <= show_shop_y * 2 + 1; y++) {
		for (int x = 0; x <= show_shop_x; x++) {

			int re_x = player_x / 3 + x;
			int re_y = player_y / 2 + y - 1;


			if (re_x >= MAP_INFO_X || re_x < 0) { //���� ������ ��ũ�⿡ �Ѿ�� �۵����� �� ��
				continue;
			}
			if (re_y >= MAP_INFO_Y || re_y < 0) { //���� ������ ��ũ�⿡ �Ѿ�� �۵����� �� ��
				continue;
			}

			SetCurrentCursorPos(re_x * 3 + GBOARD_ORIGIN_X, re_y * 2 + GBOARD_ORIGIN_Y);

			SetMapColor(map_info[stage_state][re_x][re_y]); //�� ����
			block_state = map_state[stage_state][re_x][re_y];

			if (map_info[stage_state][re_x][re_y] >= 0) {
				if (map_info[stage_state][re_x][re_y] == 10) {
					ShowBlock(Player1[block_state]);
				}
				else if (map_info[stage_state][re_x][re_y] == 14)
				{
					ShowBlock(ShopNPC[0]);
				}
				else {
					ShowBlock(BasicBlockModel[block_state]);
				}
			}
			else
			{
				ShowBlock(DeleteBlock[0]);
			}
		}
	}
	SetCurrentCursorPos(player_x, player_y);
}

/*������ ����*/
void buyItem(shopItem item, int amount) {

	if (money < item.price * amount) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("�ذ��: ��尡 �����մϴ�!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                           ");
		Set_Color(WHITE);
		return;//�� ����
	}
	else {
		if (addItem(item.itemID, amount)) {
			money -= item.price * amount;
		}
	}
	showCharacterInfo(); //����â ���
	showInventoryInfo(); //�κ��丮 ���
}

/*���� �ȱ�*/
void sellMineral() {
	int price = 0;
	int flag = 1;
	int size = inven_index;


	for (int i = 0; i < size; i++) {

		if (ITEM_COPPER <= inven[i].itemID && inven[i].itemID <= ITEM_S_CRIPTON) {
			switch (inven[i].itemID) {
			case ITEM_COPPER:
				price += inven[i].amount * 100;

				break;

			case ITEM_SILVER:
				price += inven[i].amount * 200;

				break;

			case ITEM_GOLD:
				price += inven[i].amount * 300;


				break;

			case ITEM_CRYSTAL:
				price += inven[i].amount * 500;

				break;

			case ITEM_DIAMOND:
				price += inven[i].amount * 1000;

				break;

			case ITEM_S_CRAETUM:
				price += inven[i].amount * 2000;
				flag = 0;
				break;

			case ITEM_S_SELANUM:
				price += inven[i].amount * 3000;

				break;

			case ITEM_S_CRIPTON:
				price += inven[i].amount * 4000;

				break;

			}
			flag = 0;
			inven[i].amount = 0;
			inven[i].itemID = 0;
			inven_index--;
		}
	}

	if (flag == 1) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("�ذ��: �� �� �ִ� ������ �����ϴ�!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                                     ");
		Set_Color(WHITE);
		return;
	}

	money += price;

	showCharacterInfo(); //����â ���
	InventorySort();
	showInventory_list(); //�κ��丮 ���

}



void ProcessKey_forshop() { //������ ���� Ű���� ����
	int key; //�Է�Ű

	int move_x = 2; //ȭ��ǥ �ʱ� ��ǥ ����
	int move_y = 1; //ȭ��ǥ �ʱ� ��ǥ ����

	int mod_x = show_shop_x / 4; //ĭ �̵�
	int mod_y = show_shop_y * 2 / 2; //ĭ �̵�

	int x_index = 0; //��ĭ �̵��ߴ°�(x��)
	int y_index = 0; //��ĭ �̵��ߴ°�(y��)

	int selected_index = 0; //���� ���� ������ �ε���(shop_item�迭 ��ġ)

	//int close_flag = 0; //���� �ݱ� ����
	close_flag = 0;

	/*�ʱ� ȭ��ǥ ����*/
	SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + move_x,
		(player_y + 9) + move_y);
	printf(">");


	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case LEFT:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" ");//������ �ִ� ȭ��ǥ�� ����ϴ�.
				x_index--;


				break;
			case RIGHT:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" ");//������ �ִ� ȭ��ǥ�� ����ϴ�.
				x_index++;

				break;
			case DOWN:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" ");//������ �ִ� ȭ��ǥ�� ����ϴ�.
				y_index++;

				break;
			case UP:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" "); //������ �ִ� ȭ��ǥ�� ����ϴ�.
				y_index--;

				break;
			case KeyP:
				close_flag = 1;
				break;


			case SPACE: //��ȣ�ۿ� Ű(���� Ű)
				if (y_index == 1 && x_index == 3) {
					sellMineral();
				}
				else if (y_index == 1 && x_index == 0) {
					upgradeEquip(&cap);
					SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 4,
						(player_y + 9) + 5);
					printf("     ");
					if (cap.level == 1) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 4,
							(player_y + 9) + 5);
						printf("500");
					}
					else if (cap.level == 2) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 4,
							(player_y + 9) + 5);
						printf("1000");
					}
					else if (cap.level == 3) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 4,
							(player_y + 9) + 5);
						printf("MAX");
					}
				}
				else if (y_index == 1 && x_index == 1) {
					upgradeEquip(&drill);
					SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 22,
						(player_y + 9) + 5);
					printf("     ");
					if (drill.level == 1) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 22,
							(player_y + 9) + 5);
						printf("500");
					}
					else if (drill.level == 2) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 22,
							(player_y + 9) + 5);
						printf("1000");
					}
					else if (drill.level == 3) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 22,
							(player_y + 9) + 5);
						printf("MAX");
					}
				}
				else if (y_index == 1 && x_index == 2) {
					upgradeEquip(&shoes);
					SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 40,
						(player_y + 9) + 11);
					printf("    ");
					if (shoes.level == 1) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 40,
							(player_y + 9) + 5);
						printf("500");
					}
					else if (shoes.level == 2) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 40,
							(player_y + 9) + 5);
						printf("1000");
					}
					else if (shoes.level == 3) {
						SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + 40,
							(player_y + 9) + 5);
						printf("MAX");
					}
				}
				else {
					ProcessKey_forselectedItem(x_index, y_index, selected_index);
				}
				break;

			}
		}
		if (close_flag == 1) {
			//�κ��丮 â �ݱ�
			close_shop(); //���� �ݱ�
			eraseInventory(); //�κ��丮â �ݱ�
			break;
		}

		/*ȭ��ǥ�� ���� Ʋ�� ����� ���� �����ϱ� ����*/
		if (x_index > 3) {
			x_index = 3;
		}
		if (x_index < 0) {
			x_index = 0;
		}
		if (y_index > 1) {
			y_index = 1;
		}
		if (y_index < 0) {
			y_index = 0;
		}

		selected_index = 4 * y_index + x_index;


		/*ȭ��ǥ �̵�*/
		SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
			((player_y + 9) + move_y) + mod_y * y_index);
		printf(">");
	}
}

/*���õ� ������ */
void ProcessKey_forselectedItem(int x_index, int y_index, int selected_index) {
	int print_arrow_x = 16;
	int print_arrow_y = 1;

	int print_amount_x = 13;
	int print_amount_y = 1;

	int item_amount = 0;

	int mod_x = show_shop_x / 4; //ĭ �̵�
	int mod_y = show_shop_y * 2 / 2; //ĭ �̵�

	int selected_flag = 0; //������ ���� ����������

	SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
		((player_y + 9) + print_arrow_y) + mod_y * y_index);
	printf("��");
	print_arrow_y = 2;
	SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
		((player_y + 9) + print_arrow_y) + mod_y * y_index);
	printf("��");


	int key;
	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case UP: //��Ű
				/*ȭ��ǥ ���*/
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("��");
				print_arrow_y = 1;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("��");

				item_amount++; //������ ���� +1
				break;

			case DOWN://�Ʒ�Ű
				/*ȭ��ǥ ���*/
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("��");
				print_arrow_y = 2;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("��");


				item_amount--; //������ ���� -1
				break;

			case SPACE:
				//�κ��丮�� �����ϱ�
				if (item_amount > 0) {
					buyItem(shop_item[selected_index], item_amount);
				}
				selected_flag = 1;
				break;

			case KeyP: //����â �ݱ�
				selected_flag = 1;
				close_flag = 1;
				break;

			}

			if (selected_flag == 1) {

				/*ȭ��ǥ �����*/
				print_arrow_y = 1;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("  ");

				print_arrow_y = 2;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);

				printf("  ");

				/*���� �����*/
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_amount_x) + mod_x * x_index,
					((player_y + 9) + print_amount_y) + mod_y * y_index);
				printf("  ");

				break; //����������
			}

			if (item_amount < 0) { //�ּ� 0��
				item_amount = 0;
			}

			if (item_amount > 16) { //�ִ� 16��
				item_amount = 16;
			}

			/*������ ���� ����ϱ�*/
			SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_amount_x) + mod_x * x_index,
				((player_y + 9) + print_amount_y) + mod_y * y_index);
			printf("%02d", item_amount);
		}
	}
}

void show_shop() {

	shop_format();

	showCharacterInfo(); //����â ���
	showInventoryInfo(); //�κ��丮 ���

	show_shopItem();

	ProcessKey_forshop();

}