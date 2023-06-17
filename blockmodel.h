//#pragma once
#ifndef BLOCKMODEL_H
# define BLOCKMODEL_H


//블록 모양을 바꾸어주는 함수이다
void ChangeBlock(int p_x, int p_y, int change_x, int change_y, int state);
//블록을 보여주는 모양이다
void ShowBlock(char blockInfo[2][6]);

#endif // !BLOCKMODEL_H
