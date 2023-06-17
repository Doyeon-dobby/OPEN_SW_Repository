//#pragma once
#ifndef ITEM_H
#define ITEM_H


#define ITEM_COPPER 2
#define ITEM_SILVER 3
#define ITEM_GOLD 4
#define ITEM_CRYSTAL 5
#define ITEM_DIAMOND 6
#define ITEM_S_CRAETUM 7
#define ITEM_S_SELANUM 8
#define ITEM_S_CRIPTON 9

#define ITEM_O2 11
#define ITEM_BOMB 12
#define ITEM_HEAL 13
#define ITEM_TELEPORT 14

#define ITEM_HELMET 21
#define ITEM_SHOES 22
#define ITEM_DRILL 23

void UseMedicalItem();
void UseOxygenItem();
void UseBomb(int player_state);


void PlayerHPPlus(int hp);
void PlayerO2Plus(int o2);

void UseTeleport();

int find_item(int itemID);

#endif