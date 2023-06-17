#ifndef SHOP_H
#define SHOP_H

#define SHOP_ITEM_NUM 7


int show_shop_x;
int show_shop_y;

/*상점 아이템 전용 구조체*/
typedef struct shopItem {
	int itemID; //아이템 이름
	int price; //가격
}shopItem;

void init_shopItem(); //상점 아이템 설정(상점 아이템 초기화)
void shop_format(); //상점 틀 만들기
void show_shopItem(); //아이템 진열
void show_shop(); //상점 출력
void ProcessKey_forshop(); //
void ProcessKey_forselectedItem(int x_index, int y_index, int selected_index);
void close_shop(); //인벤토리창 닫기
void buyItem(shopItem item, int amount); //아이템 구매
void sellMineral();

#endif