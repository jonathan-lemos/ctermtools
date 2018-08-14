/** @file ctermtools.c
 *
 * Copyright (c) 2018 Jonathan Lemos
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#define TT_EXPORTING
#include "../ctermtools.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <conio.h>

void tt_attron(uint_fast32_t attr) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	if (attr & TT_UNDERLINE) {
		csbi.wAttributes |= COMMON_LVB_UNDERSCORE;
	}
	if (attr & TT_INVERT) {
		csbi.wAttributes |= COMMON_LVB_REVERSE_VIDEO;
	}

	if (attr & TT_FG_BRIGHT) {
		csbi.wAttributes |= FOREGROUND_INTENSITY;
	}
	if (attr & TT_FG_DEFAULT) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY);
		csbi.wAttributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	if (attr & TT_FG_BLACK) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	if (attr & TT_FG_RED) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		csbi.wAttributes |= FOREGROUND_RED;
	}
	if (attr & TT_FG_GREEN) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		csbi.wAttributes |= FOREGROUND_GREEN;
	}
	if (attr & TT_FG_YELLOW) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		csbi.wAttributes |= FOREGROUND_RED | FOREGROUND_GREEN;
	}
	if (attr & TT_FG_BLUE) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		csbi.wAttributes |= FOREGROUND_BLUE;
	}
	if (attr & TT_FG_MAGENTA) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		csbi.wAttributes |= FOREGROUND_BLUE | FOREGROUND_RED;
	}
	if (attr & TT_FG_CYAN) {
		csbi.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		csbi.wAttributes |= FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	if (attr & TT_FG_WHITE) {
		csbi.wAttributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}

	if (attr & TT_BG_BRIGHT) {
		csbi.wAttributes |= BACKGROUND_INTENSITY;
	}
	if (attr & TT_BG_DEFAULT) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		csbi.wAttributes |= BACKGROUND_INTENSITY;
	}
	if (attr & TT_BG_BLACK) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	if (attr & TT_BG_RED) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		csbi.wAttributes |= BACKGROUND_RED;
	}
	if (attr & TT_BG_GREEN) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		csbi.wAttributes |= BACKGROUND_GREEN;
	}
	if (attr & TT_BG_YELLOW) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		csbi.wAttributes |= BACKGROUND_RED | BACKGROUND_GREEN;
	}
	if (attr & TT_BG_BLUE) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		csbi.wAttributes |= BACKGROUND_BLUE;
	}
	if (attr & TT_BG_MAGENTA) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		csbi.wAttributes |= BACKGROUND_BLUE | BACKGROUND_RED;
	}
	if (attr & TT_BG_CYAN) {
		csbi.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		csbi.wAttributes |= BACKGROUND_GREEN | BACKGROUND_BLUE;
	}
	if (attr & TT_BG_WHITE) {
		csbi.wAttributes |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}

	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

void tt_attroff(uint_fast32_t attr){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}
	
	if (attr & TT_UNDERLINE){
		csbi.wAttributes &= ~(COMMON_LVB_UNDERSCORE);
	}
	if (attr & TT_INVERT){
		csbi.wAttributes &= ~(COMMON_LVB_REVERSE_VIDEO);
	}

	if (attr & (TT_FG_RED | TT_FG_GREEN | TT_FG_YELLOW | TT_FG_BLUE | TT_FG_MAGENTA | TT_FG_CYAN | TT_FG_WHITE)){
		tt_attron(TT_FG_DEFAULT);
	}

	if (attr & (TT_BG_RED | TT_BG_GREEN | TT_BG_YELLOW | TT_BG_BLUE | TT_BG_MAGENTA | TT_BG_CYAN | TT_BG_WHITE)){
		tt_attron(TT_BG_DEFAULT);
	}

	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

void tt_attrclear(void) {
	tt_attroff(TT_UNDERLINE | TT_INVERT | TT_FG_WHITE | TT_BG_WHITE);
}

int tt_getrows(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return -1;
	}

	return csbi.dwSize.X;
}

int tt_getcols(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return -1;
	}

	return csbi.dwSize.Y;
}

void tt_showcursor(int enable) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;

	if (!hConsole || !GetConsoleCursorInfo(hConsole, &cci)) {
		return;
	}

	cci.bVisible = enable;
	SetConsoleCursorInfo(hConsole, &cci) ? 0 : -1;
}

int tt_setecho(int enable) {
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dwMode;

	if (!hConsole || !GetConsoleMode(hConsole, &dwMode)) {
		return -1;
	}

	dwMode = (dwMode & ~(ENABLE_ECHO_INPUT)) | (ENABLE_ECHO_INPUT * enable);
	return SetConsoleMode(hConsole, dwMode) ? 0 : -1;
}

void tt_setcursorpos(int row, int col) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwCursorPosition = { col, row };

	if (!hConsole) {
		return;
	}

	SetConsoleCursorPosition(hConsole, dwCursorPosition);
}

void tt_movecursorpos(int row_delta, int col_delta) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int row_max = tt_getrows();
	int col_max = tt_getcols();

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	csbi.dwCursorPosition.Y += row_delta;
	csbi.dwCursorPosition.X += col_delta;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void tt_clear(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordHome = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD cCharsWritten;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', csbi.dwSize.X * csbi.dwSize.Y, coordHome, &cCharsWritten)) {
		return;
	}
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coordHome, &cCharsWritten)) {
		return;
	}

	SetConsoleCursorPosition(hConsole, coordHome);
}

int tt_getch(void) {
	int c = 0;
	do {
		c = _getch();
		if (c == 224) {
			c = _getch();
			switch (c) {
			case 72:
				return KEY_UP;
			case 80:
				return KEY_DOWN;
			case 75:
				return KEY_LEFT;
			case 77:
				return KEY_RIGHT;
			}
		}
		if (c == '\r') {
			return KEY_ENTER;
		}
		if (c == 8) {
			return KEY_BACKSPACE;
		}
	} while (c == 0);
	return c;
}