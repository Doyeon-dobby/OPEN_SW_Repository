#include "Keys.h"
#include <Windows.h>

void ClearKeyBuf(void) {
	while (kbhit()) getch();
}