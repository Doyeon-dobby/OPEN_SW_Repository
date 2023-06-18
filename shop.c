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

int show_shop_x = 72; //상점 크기는 여러 크기로 조정했을 때 해당 크기가 제일 적당해서 90*6으로 설정하였습니다.
int show_shop_y = 3;


int close_flag = 0; //상점 닫기 여부


shopItem shop_item[SHOP_ITEM_NUM]; //상점 아이템

/*상점 아이템 진열 (초기화시키는 거)*/
void init_shopItem() {
	int i = 0;

	/*상점에 있어야 하는 아이템들을 여기에 모두 적어주시면 됩니다.*/

	/*소모 아이템*/
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

	/*장비 관련 아이템*/
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


/*상점 틀 만들기*/
void shop_format() {

	Set_Color(WHITE); //글자색 흰색 고정
	RemoveCursor(); //커서 삭제

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
					printf("＃");
				}
				else if (x == 7) {
					printf("＃");
				}
				else {
					printf("─");
				}
			}
			else if (y == 2) {
				if (x == 0) {
					printf("＃");
				}
				else if (x == 7) {
					printf("＃");
				}
				else {
					printf("─");
				}
			}
			else {
				if (x == 0 || x == 7) {
					printf("│");
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
			printf("┏");
		}
		else if (x == show_shop_x) {
			printf("┓");
		}
		else {
			int mod = show_shop_x / 4;
			if (x % mod == 0) {
				printf("┬");
			}
			else {
				printf("─");
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
					printf("│");
				}
				else {
					if (x % mod == 0) {
						printf("┼");

					}
					else {
						printf("━");
					}
				}

			}
			else {
				if (x % mod == 0) {
					printf("│");

				}
			}
		}
	}

	for (int x = 0; x <= show_shop_x; x++) {
		SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
			(player_y + 9) + show_shop_y * 2);
		if (x == 0) {
			printf("┗");
		}
		else if (x == show_shop_x) {
			printf("┛");
		}
		else {
			int mod = show_shop_x / 4;
			if (x % mod == 0) {
				printf("┴");
			}
			else {
				printf("─");
			}
		}
	}
}

void show_shopItem() {
	int shop_index = 0;

	int mod = show_shop_x / 4;

	init_shopItem();

	int i = 0;

	/*임시 디자인*/



		/*아이콘 출력*/
	for (int y = 1; y < show_shop_y * 2; y += 3) {
		for (int x = 4; x <= show_shop_x; x += mod, i++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);
			/*아이템 강화*/
			Set_Color(YELLOW);
			if (y == 4 && x == 58) {
				printf("광물 팔기");
			}
			if (y == 4 && x == 4) {
				printf("캡 강화");
			}
			if (y == 4 && x == 22) {
				printf("드릴 강화");
			}
			if (y == 4 && x == 40) {
				printf("슈즈 강화");
			}

			switch (shop_item[i].itemID) {
			case ITEM_O2:
				Set_Color(SKYBLUE);
				printf("◐");
				break;

			case ITEM_BOMB:
				Set_Color(DARKGRAY);
				printf("▩");
				break;

			case ITEM_HEAL:
				Set_Color(RED);
				printf("♥");
				break;

			case ITEM_TELEPORT:
				Set_Color(PURPLE);
				printf("§");
				break;
			}
		}
	}
	i = 0;

	/*가격 출력*/
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

	/*아이템 이름 출력*/
	for (int y = 2; y < show_shop_y * 2; y += 3) {
		for (int x = 4; x <= show_shop_x; x += mod, i++) {
			SetCurrentCursorPos((player_x + show_charaterInfo_x + 2) + x,
				(player_y + 9) + y);
			/*아이템 강화*/
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
				printf("산소 캡슐");
				break;

			case ITEM_BOMB:
				printf("폭탄");
				break;

			case ITEM_HEAL:
				printf("구급 상자");
				break;

			case ITEM_TELEPORT:
				printf("텔레포트");
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

	/*아래부턴 DrawMap 함수와 기능이 거즘 동일, 적용되는 위치와 크기만 다름*/
	int block_state;

	for (int y = 0; y <= show_shop_y * 2 + 1; y++) {
		for (int x = 0; x <= show_shop_x; x++) {

			int re_x = player_x / 3 + x;
			int re_y = player_y / 2 + y - 1;


			if (re_x >= MAP_INFO_X || re_x < 0) { //현재 설정된 맵크기에 넘어가면 작동하지 말 것
				continue;
			}
			if (re_y >= MAP_INFO_Y || re_y < 0) { //현재 설정된 맵크기에 넘어가면 작동하지 말 것
				continue;
			}

			SetCurrentCursorPos(re_x * 3 + GBOARD_ORIGIN_X, re_y * 2 + GBOARD_ORIGIN_Y);

			SetMapColor(map_info[stage_state][re_x][re_y]); //맵 색깔
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

/*아이템 구매*/
void buyItem(shopItem item, int amount) {

	if (money < item.price * amount) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("※경고: 골드가 부족합니다!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                           ");
		Set_Color(WHITE);
		return;//돈 부족
	}
	else {
		if (addItem(item.itemID, amount)) {
			money -= item.price * amount;
		}
	}
	showCharacterInfo(); //정보창 출력
	showInventoryInfo(); //인벤토리 출력
}

/*광물 팔기*/
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
		printf("※경고: 팔 수 있는 광물이 없습니다!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                                     ");
		Set_Color(WHITE);
		return;
	}

	money += price;

	showCharacterInfo(); //정보창 출력
	InventorySort();
	showInventory_list(); //인벤토리 출력

}



void ProcessKey_forshop() { //상점을 위한 키보드 제어
	int key; //입력키

	int move_x = 2; //화살표 초기 좌표 설정
	int move_y = 1; //화살표 초기 좌표 설정

	int mod_x = show_shop_x / 4; //칸 이동
	int mod_y = show_shop_y * 2 / 2; //칸 이동

	int x_index = 0; //몇칸 이동했는가(x축)
	int y_index = 0; //몇칸 이동했는가(y축)

	int selected_index = 0; //선택 중인 아이템 인덱스(shop_item배열 위치)

	//int close_flag = 0; //상점 닫기 여부
	close_flag = 0;

	/*초기 화살표 설정*/
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
				printf(" ");//기존에 있던 화살표를 지웁니다.
				x_index--;


				break;
			case RIGHT:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" ");//기존에 있던 화살표를 지웁니다.
				x_index++;

				break;
			case DOWN:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" ");//기존에 있던 화살표를 지웁니다.
				y_index++;

				break;
			case UP:
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
					((player_y + 9) + move_y) + mod_y * y_index);
				printf(" "); //기존에 있던 화살표를 지웁니다.
				y_index--;

				break;
			case KeyP:
				close_flag = 1;
				break;


			case SPACE: //상호작용 키(선택 키)
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
			//인벤토리 창 닫기
			close_shop(); //상점 닫기
			eraseInventory(); //인벤토리창 닫기
			break;
		}

		/*화살표가 상점 틀을 벗어나는 것을 방지하기 위함*/
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


		/*화살표 이동*/
		SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + move_x) + mod_x * x_index,
			((player_y + 9) + move_y) + mod_y * y_index);
		printf(">");
	}
}

/*선택된 아이템 */
void ProcessKey_forselectedItem(int x_index, int y_index, int selected_index) {
	int print_arrow_x = 16;
	int print_arrow_y = 1;

	int print_amount_x = 13;
	int print_amount_y = 1;

	int item_amount = 0;

	int mod_x = show_shop_x / 4; //칸 이동
	int mod_y = show_shop_y * 2 / 2; //칸 이동

	int selected_flag = 0; //아이템 선택 빠져나오기

	SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
		((player_y + 9) + print_arrow_y) + mod_y * y_index);
	printf("△");
	print_arrow_y = 2;
	SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
		((player_y + 9) + print_arrow_y) + mod_y * y_index);
	printf("▽");


	int key;
	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case UP: //윗키
				/*화살표 출력*/
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("▽");
				print_arrow_y = 1;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("▲");

				item_amount++; //아이템 수량 +1
				break;

			case DOWN://아래키
				/*화살표 출력*/
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("△");
				print_arrow_y = 2;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("▼");


				item_amount--; //아이템 수량 -1
				break;

			case SPACE:
				//인벤토리에 저장하기
				if (item_amount > 0) {
					buyItem(shop_item[selected_index], item_amount);
				}
				selected_flag = 1;
				break;

			case KeyP: //상점창 닫기
				selected_flag = 1;
				close_flag = 1;
				break;

			}

			if (selected_flag == 1) {

				/*화살표 지우기*/
				print_arrow_y = 1;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);
				printf("  ");

				print_arrow_y = 2;
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_arrow_x) + mod_x * x_index,
					((player_y + 9) + print_arrow_y) + mod_y * y_index);

				printf("  ");

				/*숫자 지우기*/
				SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_amount_x) + mod_x * x_index,
					((player_y + 9) + print_amount_y) + mod_y * y_index);
				printf("  ");

				break; //빠져나오기
			}

			if (item_amount < 0) { //최소 0개
				item_amount = 0;
			}

			if (item_amount > 16) { //최대 16개
				item_amount = 16;
			}

			/*아이템 수량 출력하기*/
			SetCurrentCursorPos(((player_x + show_charaterInfo_x + 2) + print_amount_x) + mod_x * x_index,
				((player_y + 9) + print_amount_y) + mod_y * y_index);
			printf("%02d", item_amount);
		}
	}
}

void show_shop() {

	shop_format();

	showCharacterInfo(); //정보창 출력
	showInventoryInfo(); //인벤토리 출력

	show_shopItem();

	ProcessKey_forshop();

}