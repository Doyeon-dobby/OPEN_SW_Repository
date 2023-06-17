//#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H


//인벤토리 가방크기
#define INVENTORY_SIZE 30
#define INVENTORY_SIZE_X 5
#define INVENTORY_SIZE_Y 6
#define INVENTORY_LOCATE_Y INVENTORY_SIZE_Y * 2 //인벤토리 출력 위치 선정


/*
ㅁ ㅁ ㅁ ㅁ ㅁ  여기 ㅁ의 한칸에는 광물이 16개가 들어갈 수 있고
ㅁ ㅁ ㅁ ㅁ ㅁ  아이템은 각각 1개씩만 들어간다.
ㅁ ㅁ ㅁ ㅁ ㅁ
ㅁ ㅁ ㅁ ㅁ ㅁ
ㅁ ㅁ ㅁ ㅁ ㅁ
ㅁ ㅁ ㅁ ㅁ ㅁ
*/
#define INVERNTORY_MINERAL_SIZE 16

void CharacterInfo_format(); //캐릭터 정보창틀

void showCharacterInfo(); //캐릭터 정보창 출력

void ShowInventory(int key); //인벤토리 출력 여부

void InventorySort(); //인벤토리 정렬 (근데 정렬 기준을 어떻게? 일단 개수로 진행했습니다.

void Inventory_format(); //인벤토리창 틀

void showInventoryInfo(); //인벤토리 보여주기

int addItem(int itemID, int amount); //인벤토리에 아이템 추가

void showInventory_list();

void eraseInventory();

int open_inven; //인벤토리 열림 여부

int money; //골드

int inven_index;

int useitem(int itemID);

/*아이템 저장을 위한 구조체*/
typedef struct Item {
	int itemID; //아이템ID (아이템 구별)
	int amount; //아이템 수량 (최대 16개)
}Item;

typedef struct Equip {
	int level; //장비 레벨
	int excavation; //굴착력
	int booster; //부스터
	int defensive; //방어력
	int id; //장비 종류 0:캡 1:드릴 2:슈즈
}Equip;
Item inven[INVENTORY_SIZE];

int isFull();

void upgradeEquip(Equip* e);



#endif // !INVENTORY_H

