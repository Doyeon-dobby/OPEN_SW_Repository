#include "Inventory.h"

#include "map.h"

/*본인이 추가한 헤더*/
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


/*장비*/
Equip cap = { 1,0,0,0,0 };
Equip drill = { 1,5,0,0,1 };
Equip shoes = { 1,0,7,0,2 };

Item inven[INVENTORY_SIZE] = { 0 }; //획득한 아이템을 저장할 구조체 배열(최대 30개 저장 가능)


int show_charaterInfo_x = INVENTORY_SIZE_X * 5 + 5; //캐릭터 정보창 x축 크기
int show_charaterInfo_y = INVENTORY_SIZE_Y;  //캐릭터 정보창 y축 크기

int show_inventory_x = INVENTORY_SIZE_X * 5 + 5; //인벤토리창 x축 크기
int show_inventory_y = INVENTORY_SIZE_Y; //인벤토리창 y축 크기

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

/*캐릭터 정보창틀 만들기*/
void CharacterInfo_format() {

	Set_Color(WHITE); //글자색 흰색 고정
	RemoveCursor(); //커서 삭제

	SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y);

	/*창틀 내부 비우기*/
	for (int y = 0; y < show_charaterInfo_y * 2; y++) {
		for (int x = 0; x < show_charaterInfo_x; x++) {
			SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y + y);
			printf(" ");
		}
	}

	SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y);
	printf("┏");
	for (int x = 1; x < show_charaterInfo_x; x++) {
		SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y);
		printf("─");
	}
	printf("┓");

	SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y + show_charaterInfo_y * 2);
	printf("┗");
	for (int x = 1; x < show_charaterInfo_x; x++) {
		SetCurrentCursorPos(x + inventory_location_x * 3, show_charaterInfo_y * 2 + inventory_location_y);
		printf("─");
	}
	printf("┛");

	for (int y = 1; y < show_charaterInfo_y * 2; y++) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y + y);
		printf("│");
	}

	for (int y = 1; y < show_charaterInfo_y * 2; y++) {
		SetCurrentCursorPos(inventory_location_x * 3 + show_charaterInfo_x, inventory_location_y + y);
		printf("│");
	}
}


/*캐릭터 정보창 출력*/
void showCharacterInfo() {
	CharacterInfo_format();

	/*정보창틀 내부 비우기*/
	for (int y = 1; y < show_charaterInfo_y * 2; y++) {
		for (int x = 1; x < show_charaterInfo_x * 2; x++) {
			SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y + y);
			printf(" ");
		}
	}

	/*캐릭터 정보*/
	SetCurrentCursorPos(inventory_location_x * 3 + show_charaterInfo_x / 2 - 5, inventory_location_y + 1); //글자 위치 조정
	printf("[Inventory]");

	if (cap.level == 2) Set_Color(GREEN);
	if (cap.level == 3) Set_Color(YELLOW);
	SetCurrentCursorPos(inventory_location_x * 3 + 5, inventory_location_y + 3);
	printf("●");
	Set_Color(WHITE);
	if (drill.level == 2)Set_Color(GREEN);
	if (drill.level == 3) Set_Color(YELLOW);
	SetCurrentCursorPos(inventory_location_x * 3 + 5, inventory_location_y + 4);
	printf("▼");
	Set_Color(WHITE);

	/*현재 장착된 장비 (임시 디자인) 장비 관련 변수가 만들어지면 수정하겠습니다(11/26)*/
	SetCurrentCursorPos(inventory_location_x * 3 + 9, inventory_location_y + 3);
	printf("┌ ");
	switch (cap.level) {
	case 1:
		printf(" 나이스 캡");
		break;
	case 2:
		printf(" 메가 캡");
		break;
	case 3:
		printf(" 울트라 캡");
		break;
	}
	SetCurrentCursorPos(inventory_location_x * 3 + 9, inventory_location_y + 4);
	printf("├ ");
	switch (drill.level) {
	case 1:
		printf(" 나이스 드릴");
		break;
	case 2:
		printf(" 메가 드릴");
		break;
	case 3:
		printf(" 울트라 드릴");
		break;
	}
	SetCurrentCursorPos(inventory_location_x * 3 + 9, inventory_location_y + 5);
	printf("└ ");
	switch (shoes.level) {
	case 1:
		printf(" 나이스 슈즈");
		break;
	case 2:
		printf(" 메가 슈즈");
		break;
	case 3:
		printf(" 울트라 슈즈");
		break;
	}

	/*현재 캐릭터 능력치 (임시 디자인) 능력치 관련 변수가 만들어지면 수정하겠습니다(11/26)*/
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 5);
	printf("굴착력 %d", drill.excavation);
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 4);
	printf("부스터 %d", shoes.booster);
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 3);
	printf("방어력 %d", cap.defensive);
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 1);
	printf("                   ");
	SetCurrentCursorPos(inventory_location_x * 3 + 2, inventory_location_y + show_charaterInfo_y * 2 - 1);
	printf("Money: %d", money);
}


/*인벤토리창틀 만들기*/
void Inventory_format() {

	/*창틀 내부 비우기*/
	for (int y = 1; y <= show_inventory_y * 2; y++) {
		for (int x = 0; x < show_inventory_x; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + y);
			printf(" ");
		}
	}
	for (int x = 0; x <= show_inventory_x; x++) {
		SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + 1);
		if (x == 0) {
			printf("┏");
		}
		else if (x == show_inventory_x) {
			printf("┓");
		}
		else {
			int mod = show_inventory_x / 5;
			if (x % mod == 0) {
				printf("┬");
			}
			else {
				printf("─");
			}
		}
	}
	for (int y = 0; y < show_inventory_y * 2 - 1; y++) {
		for (int x = 0; x <= show_inventory_x; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + 2 + y);
			int mod = show_inventory_x / 5;
			if (y % 2 == 0) {
				if (x % mod == 0) {
					printf("│");

				}
			}
			else {
				if (x == 0) {
					printf("├");
				}
				else if (x == show_inventory_x) {
					printf("┤");
				}
				else {
					if (x % mod == 0) {
						printf("┼");

					}
					else {
						printf("─");
					}
				}
			}
		}
	}
	for (int x = 0; x <= show_inventory_x; x++) {
		SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + 2 * INVENTORY_LOCATE_Y + 1);
		if (x == 0) {
			printf("┗");
		}
		else if (x == show_inventory_x) {
			printf("┛");
		}
		else {
			int mod = show_inventory_x / 5;
			if (x % mod == 0) {
				printf("┴");
			}
			else {
				printf("─");
			}
		}
	}
}

/*인벤토리창 출력*/
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
	/*인벤토리 임시 디자인*/
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
						/*광물*/
					case ITEM_COPPER:
						//Set_Color(DARKRED);
						printf("☆");
						break;
					case ITEM_SILVER:
						//Set_Color(GRAY);
						printf("☆");
						break;
					case ITEM_GOLD:
						//Set_Color(YELLOW);
						printf("☆");
						break;
					case ITEM_CRYSTAL:
						//Set_Color(SKYBLUE);
						printf("☆");
						break;
					case ITEM_DIAMOND:
						//Set_Color(GREEN);
						printf("☆");
						break;
					case ITEM_S_CRAETUM:
						//Set_Color(RED);
						printf("☆");
						break;
					case ITEM_S_SELANUM:
						//Set_Color(PURPLE);
						printf("☆");
						break;
					case ITEM_S_CRIPTON:
						//Set_Color(DARKGRAY);
						printf("☆");
						break;
						/*소모 아이템*/
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
						/*장비*/
					case ITEM_HELMET:
						Set_Color(YELLOW);
						printf("●");
						break;
					case ITEM_SHOES:
						Set_Color(DARKRED);
						printf("♠");
						break;
					case ITEM_DRILL:
						Set_Color(GRAY);
						printf("▼");
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

int isFull() { //아이템이 꽉찼는지 확인
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		if (inven[i].amount < INVERNTORY_MINERAL_SIZE) {
			return 0;
		}
	}
	return 1;
}



/*인벤토리에 아이템 추가*/
int addItem(int itemID, int amount) {
	int min_index = 0;
	int min = 16;
	int flag = 0;
	/*인벤토리가 꽉차면 경고메세지 출력*/
	if (isFull() == 1) {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("※경고: 인벤토리가 꽉찼습니다!");
		Sleep(800);
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		printf("                                  ");
		Set_Color(WHITE);
		return 0;
	}
	if (inven_index == 0) { //인벤토리가 비어있으면...
		inven[inven_index].itemID = itemID;
		inven[inven_index].amount = amount;
		inven_index++;
		InventorySort();
		return 1;
	}
	for (int i = 0; i < inven_index; i++) {
		if (inven[i].itemID == itemID) { //이미 해당 아이템이 저장된 슬롯이 있을 때
			if (min >= inven[i].amount) { //가장 적게 저장된 인덱스 찾기
				min_index = i;
				min = inven[i].amount;
				flag = 1;
			}
		}
	}
	if (flag == 1) {
		if (inven[min_index].amount + amount > INVERNTORY_MINERAL_SIZE) { //가장 적게 저장된 칸에 저장된 아이템 수 + 현재 저장하려는 아이템수 > 16이면
			if (inven_index == INVENTORY_SIZE) { //인벤토리 칸이 꽉찼으면
				SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
				Set_Color(YELLOW);
				printf("※경고: 인벤토리가 꽉찼습니다!");
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

void upgradeEquip(Equip* e) { //장비 업그레이드
	if (e->level == 1) {
		if (money < 500) {
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			Set_Color(YELLOW);
			printf("※경고: 골드가 부족합니다!");
			Sleep(800);
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			printf("                           ");
			Set_Color(WHITE);
			return;//돈 부족
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
			printf("※경고: 골드가 부족합니다!");
			Sleep(800);
			SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
			printf("                           ");
			Set_Color(WHITE);
			return;//돈 부족
		}
		money -= 1000;
		if (e->id == 0) decrease_damage += 10;
		if (e->id == 1) block_change_waitingtime -= 200;
		if (e->id == 2) interval_sleeptime -= 200;
	}
	else {
		SetCurrentCursorPos(inventory_location_x * 3, inventory_location_y - 1);
		Set_Color(YELLOW);
		printf("※경고: 만렙입니다!");
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


/*인벤토리 보여주기/지우기*/
void ShowInventory(int key)
{
	//0의 값이 들어 오면 
	//인벤토리를 닫는다
	if (key == 0)
	{

		eraseInventory(); //인벤토리 삭제
	}
	//1이 들어오면
	//인벤토리를 연다.
	if (key == 1)
	{
		showCharacterInfo(); //정보창 출력
		showInventoryInfo(); //인벤토리 출력
	}
}

/*인벤토리 정렬*/
void InventorySort()
{
	/*선택정렬 사용*/
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
	/*정보창틀 내부 비우기*/
	for (int y = 0; y <= show_charaterInfo_y * 2; y++) {
		for (int x = 0; x <= show_charaterInfo_x * 2; x++) {
			SetCurrentCursorPos(x + inventory_location_x * 3, inventory_location_y + y);
			printf(" ");
		}
	}
	/*인벤토리 창틀 내부 비우기*/
	for (int y = 0; y <= show_inventory_y * 2; y++) {
		for (int x = 0; x <= show_inventory_x * 2; x++) {
			SetCurrentCursorPos(inventory_location_x * 3 + x, inventory_location_y + INVENTORY_LOCATE_Y + y + 1);
			printf(" ");
		}
	}
	SetCurrentCursorPos(player_x, player_y);
}


