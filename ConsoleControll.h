//#pragma once
#ifndef CONSOLECONTROLL_H
# define CONSOLECONTROLL_H
#include <Windows.h>

//�����ð��� �� �⺻ �ڵ常 ��Ƶ� ���Դϴ�.

//Ŀ�� ��ġ�� �����ϴ� �Լ�
void SetCurrentCursorPos(int x, int y);

//Ŀ�� ��ġ�� ��ȯ�ϴ� �Լ�
COORD GetCurrentCursorPos(void);

//Ŀ���� �����ϴ� �Լ�
void RemoveCursor(void);

#endif // !CONSOLECONTROLL_H
