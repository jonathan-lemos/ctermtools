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

static uint_fast32_t attr_cur = 0;

static void invert(int enabled, HANDLE hConsole, LPWORD word_ptr) {
	static int on = 0;
	DWORD fg_col = 0;
	DWORD bg_col = 0;

	if (enabled == on) {
		return;
	}
	on = enabled;
	
	if ((*word_ptr) & FOREGROUND_RED) {
		bg_col |= BACKGROUND_RED;
	}
	if ((*word_ptr) & FOREGROUND_GREEN) {
		bg_col |= BACKGROUND_GREEN;
	}
	if ((*word_ptr) & FOREGROUND_BLUE) {
		bg_col |= BACKGROUND_BLUE;
	}
	if ((*word_ptr) & FOREGROUND_INTENSITY) {
		bg_col |= BACKGROUND_INTENSITY;
	}
	if ((*word_ptr) & BACKGROUND_RED) {
		fg_col |= FOREGROUND_RED;
	}
	if ((*word_ptr) & BACKGROUND_GREEN) {
		fg_col |= FOREGROUND_GREEN;
	}
	if ((*word_ptr) & BACKGROUND_BLUE) {
		fg_col |= FOREGROUND_BLUE;
	}
	if ((*word_ptr) & BACKGROUND_INTENSITY) {
		fg_col |= FOREGROUND_INTENSITY;
	}
	(*word_ptr) &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY |
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

	(*word_ptr) |= (fg_col | bg_col);
}

static void tt_apply(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	if (!hConsole) {
		return;
	}

	if (attr_cur & TT_FG_DEFAULT) {
		wAttributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	if (attr_cur & TT_FG_BLACK) {
		wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	if (attr_cur & TT_FG_RED) {
		wAttributes &= ~(FOREGROUND_GREEN | FOREGROUND_BLUE);
		wAttributes |= FOREGROUND_RED;
	}
	if (attr_cur & TT_FG_GREEN) {
		wAttributes &= ~(FOREGROUND_RED | FOREGROUND_BLUE);
		wAttributes |= FOREGROUND_GREEN;
	}
	if (attr_cur & TT_FG_YELLOW) {
		wAttributes &= ~(FOREGROUND_BLUE);
		wAttributes |= FOREGROUND_RED | FOREGROUND_GREEN;
	}
	if (attr_cur & TT_FG_BLUE) {
		wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN);
		wAttributes |= FOREGROUND_BLUE;
	}
	if (attr_cur & TT_FG_MAGENTA) {
		wAttributes &= ~(FOREGROUND_GREEN);
		wAttributes |= FOREGROUND_BLUE | FOREGROUND_RED;
	}
	if (attr_cur & TT_FG_CYAN) {
		wAttributes &= ~(FOREGROUND_RED);
		wAttributes |= FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	if (attr_cur & TT_FG_WHITE) {
		wAttributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	if (attr_cur & (TT_FG_BRIGHT | TT_BOLD)) {
		wAttributes |= FOREGROUND_INTENSITY;
	}

	if (attr_cur & TT_BG_DEFAULT) {
		wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	}
	if (attr_cur & TT_BG_BLACK) {
		wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	if (attr_cur & TT_BG_RED) {
		wAttributes &= ~(BACKGROUND_GREEN | BACKGROUND_BLUE);
		wAttributes |= BACKGROUND_RED;
	}
	if (attr_cur & TT_BG_GREEN) {
		wAttributes &= ~(BACKGROUND_RED | BACKGROUND_BLUE);
		wAttributes |= BACKGROUND_GREEN;
	}
	if (attr_cur & TT_BG_YELLOW) {
		wAttributes &= ~(BACKGROUND_BLUE);
		wAttributes |= BACKGROUND_RED | BACKGROUND_GREEN;
	}
	if (attr_cur & TT_BG_BLUE) {
		wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN);
		wAttributes |= BACKGROUND_BLUE;
	}
	if (attr_cur & TT_BG_MAGENTA) {
		wAttributes &= ~(BACKGROUND_GREEN);
		wAttributes |= BACKGROUND_BLUE | BACKGROUND_RED;
	}
	if (attr_cur & TT_BG_CYAN) {
		wAttributes &= ~(BACKGROUND_RED);
		wAttributes |= BACKGROUND_GREEN | BACKGROUND_BLUE;
	}
	if (attr_cur & TT_BG_WHITE) {
		wAttributes |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}
	if (attr_cur & TT_BG_BRIGHT) {
		wAttributes |= BACKGROUND_INTENSITY;
	}

	invert(attr_cur & TT_INVERT ? 1 : 0, hConsole, &wAttributes);
	SetConsoleTextAttribute(hConsole, wAttributes);
}

void tt_attron(uint_fast32_t attr) {
	attr_cur |= attr;
	tt_apply();
}

void tt_attroff(uint_fast32_t attr) {
	attr_cur &= ~(attr);
	tt_apply();
}

void tt_attrclear(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	attr_cur = TT_FG_DEFAULT | TT_BG_DEFAULT;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int tt_getrows(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return -1;
	}

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int tt_getcols(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!hConsole || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return -1;
	}

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
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