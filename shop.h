#ifndef SHOP_H
#define SHOP_H

#define SHOP_ITEM_NUM 7


int show_shop_x;
int show_shop_y;

/*���� ������ ���� ����ü*/
typedef struct shopItem {
	int itemID; //������ �̸�
	int price; //����
}shopItem;

void init_shopItem(); //���� ������ ����(���� ������ �ʱ�ȭ)
void shop_format(); //���� Ʋ �����
void show_shopItem(); //������ ����
void show_shop(); //���� ���
void ProcessKey_forshop(); //
void ProcessKey_forselectedItem(int x_index, int y_index, int selected_index);
void close_shop(); //�κ��丮â �ݱ�
void buyItem(shopItem item, int amount); //������ ����
void sellMineral();

#endif