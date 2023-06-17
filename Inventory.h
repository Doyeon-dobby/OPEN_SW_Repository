//#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H


//�κ��丮 ����ũ��
#define INVENTORY_SIZE 30
#define INVENTORY_SIZE_X 5
#define INVENTORY_SIZE_Y 6
#define INVENTORY_LOCATE_Y INVENTORY_SIZE_Y * 2 //�κ��丮 ��� ��ġ ����


/*
�� �� �� �� ��  ���� ���� ��ĭ���� ������ 16���� �� �� �ְ�
�� �� �� �� ��  �������� ���� 1������ ����.
�� �� �� �� ��
�� �� �� �� ��
�� �� �� �� ��
�� �� �� �� ��
*/
#define INVERNTORY_MINERAL_SIZE 16

void CharacterInfo_format(); //ĳ���� ����âƲ

void showCharacterInfo(); //ĳ���� ����â ���

void ShowInventory(int key); //�κ��丮 ��� ����

void InventorySort(); //�κ��丮 ���� (�ٵ� ���� ������ ���? �ϴ� ������ �����߽��ϴ�.

void Inventory_format(); //�κ��丮â Ʋ

void showInventoryInfo(); //�κ��丮 �����ֱ�

int addItem(int itemID, int amount); //�κ��丮�� ������ �߰�

void showInventory_list();

void eraseInventory();

int open_inven; //�κ��丮 ���� ����

int money; //���

int inven_index;

int useitem(int itemID);

/*������ ������ ���� ����ü*/
typedef struct Item {
	int itemID; //������ID (������ ����)
	int amount; //������ ���� (�ִ� 16��)
}Item;

typedef struct Equip {
	int level; //��� ����
	int excavation; //������
	int booster; //�ν���
	int defensive; //����
	int id; //��� ���� 0:ĸ 1:�帱 2:����
}Equip;
Item inven[INVENTORY_SIZE];

int isFull();

void upgradeEquip(Equip* e);



#endif // !INVENTORY_H

