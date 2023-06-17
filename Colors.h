//#pragma once
#ifndef COLORS_H
# define COLORS_H
#include <Windows.h>
//위 헤더파일은 색깔에 관한 함수들입니다.


//이것은 이미 윈도우에서 제공하는 색깔에 관한 값들을 정리한것입니다.
//이것은 굳이 손을 댈 필요가 없습니다
#define BLACK 0					//
#define DARKBLUE 1				//
#define DARKGREEN 2				//
#define DARKSKYBLUE 3			//
#define DARKRED 4				
#define DARKPURPLE 5			//
#define DARKYELLOW 6			//
#define GRAY 7					//
#define DARKGRAY 8
#define BLUE 9					//
#define GREEN 10				//
#define SKYBLUE 11				//
#define RED 12					//
#define PURPLE 13		
#define YELLOW 14				//
#define  WHITE 15				//
//아래 함수는 색깔을 변화을 시켜주는 함수 입니다. 
//해당하는 색깔이름을 int color에 넣으면 글씨를 쓰는 
//붓 색깔이 변한다고 생각하면 된다.
void Set_Color(int color);

//이건 그냥 하나하나 이름 맞춰서 컬러는 맞춰줄 필요 없이
//편리하게 블록에 대한 정보만 넣어주면 알아서 색깔을 
//그릴수 있게 해주는 함수로 해당 블록 종류에 대한 정보로
//색깔을 그리게 정리하는 함수라고 생각하면 된다.
void SetMapColor(int block_color);

#endif // !COLORS_H