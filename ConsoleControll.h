//#pragma once
#ifndef CONSOLECONTROLL_H
# define CONSOLECONTROLL_H
#include <Windows.h>

//수업시간때 한 기본 코드만 모아둔 것입니다.

//커서 위치를 셋팅하는 함수
void SetCurrentCursorPos(int x, int y);

//커서 위치를 반환하는 함수
COORD GetCurrentCursorPos(void);

//커서를 제거하는 함수
void RemoveCursor(void);

#endif // !CONSOLECONTROLL_H
