#include "ctermtools.h"
#include <stdio.h>

void test_attron(void){
	printf("attron()/attroff() test:\n");

	tt_attron(TT_UNDERLINE);
	printf("UNDERLINE");
	tt_attroff(TT_UNDERLINE);
	printf("\n");

	tt_attron(TT_BLINK);
	printf("BLINK");
	tt_attroff(TT_BLINK);
	printf("\n");

	tt_attron(TT_INVERT);
	printf("INVERT");
	tt_attroff(TT_INVERT);
	printf("\n");

	tt_attron(TT_FG_BLACK);
	printf("FG_BLACK");
	tt_attroff(TT_FG_BLACK);
	printf("\n");

	tt_attron(TT_FG_RED);
	printf("FG_RED");
	tt_attroff(TT_FG_RED);
	printf("\n");

	tt_attron(TT_FG_GREEN);
	printf("FG_GREEN");
	tt_attroff(TT_FG_GREEN);
	printf("\n");

	tt_attron(TT_FG_YELLOW);
	printf("FG_YELLOW");
	tt_attroff(TT_FG_YELLOW);
	printf("\n");

	tt_attron(TT_FG_MAGENTA);
	printf("FG_MAGENTA");
	tt_attroff(TT_FG_MAGENTA);
	printf("\n");

	tt_attron(TT_FG_CYAN);
	printf("FG_CYAN");
	tt_attroff(TT_FG_CYAN);
	printf("\n");

	tt_attron(TT_FG_WHITE);
	printf("FG_WHITE");
	tt_attroff(TT_FG_WHITE);
	printf("\n");

	tt_attron(TT_FG_BLACK | TT_FG_BRIGHT);
	printf("FG_BRIGHT_BLACK");
	tt_attroff(TT_FG_BLACK | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_RED | TT_FG_BRIGHT);
	printf("FG_BRIGHT_RED");
	tt_attroff(TT_FG_RED | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_GREEN | TT_FG_BRIGHT);
	printf("FG_BRIGHT_GREEN");
	tt_attroff(TT_FG_GREEN | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_YELLOW | TT_FG_BRIGHT);
	printf("FG_BRIGHT_YELLOW");
	tt_attroff(TT_FG_YELLOW | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_BLUE | TT_FG_BRIGHT);
	printf("FG_BRIGHT_BLUE");
	tt_attroff(TT_FG_BLUE | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_MAGENTA | TT_FG_BRIGHT);
	printf("FG_BRIGHT_MAGENTA");
	tt_attroff(TT_FG_MAGENTA | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_CYAN | TT_FG_BRIGHT);
	printf("FG_BRIGHT_CYAN");
	tt_attroff(TT_FG_CYAN | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_WHITE | TT_FG_BRIGHT);
	printf("FG_BRIGHT_WHITE");
	tt_attroff(TT_FG_WHITE | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_BLACK);
	printf("BG_BLACK");
	tt_attroff(TT_BG_BLACK);
	printf("\n");

	tt_attron(TT_BG_RED);
	printf("BG_RED");
	tt_attroff(TT_BG_RED);
	printf("\n");

	tt_attron(TT_BG_GREEN);
	printf("BG_GREEN");
	tt_attroff(TT_BG_GREEN);
	printf("\n");

	tt_attron(TT_BG_YELLOW);
	printf("BG_YELLOW");
	tt_attroff(TT_BG_YELLOW);
	printf("\n");

	tt_attron(TT_BG_MAGENTA);
	printf("BG_MAGENTA");
	tt_attroff(TT_BG_MAGENTA);
	printf("\n");

	tt_attron(TT_BG_CYAN);
	printf("BG_CYAN");
	tt_attroff(TT_BG_CYAN);
	printf("\n");

	tt_attron(TT_BG_WHITE);
	printf("BG_WHITE");
	tt_attroff(TT_BG_WHITE);
	printf("\n");

	tt_attron(TT_BG_BLACK | TT_FG_BRIGHT);
	printf("BG_BRIGHT_BLACK");
	tt_attroff(TT_BG_BLACK | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_RED | TT_FG_BRIGHT);
	printf("BG_BRIGHT_RED");
	tt_attroff(TT_BG_RED | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_GREEN | TT_FG_BRIGHT);
	printf("BG_BRIGHT_GREEN");
	tt_attroff(TT_BG_GREEN | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_YELLOW | TT_FG_BRIGHT);
	printf("BG_BRIGHT_YELLOW");
	tt_attroff(TT_BG_YELLOW | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_BLUE | TT_FG_BRIGHT);
	printf("BG_BRIGHT_BLUE");
	tt_attroff(TT_BG_BLUE | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_MAGENTA | TT_FG_BRIGHT);
	printf("BG_BRIGHT_MAGENTA");
	tt_attroff(TT_BG_MAGENTA | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_CYAN | TT_FG_BRIGHT);
	printf("BG_BRIGHT_CYAN");
	tt_attroff(TT_BG_CYAN | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_BG_WHITE | TT_FG_BRIGHT);
	printf("BG_BRIGHT_WHITE");
	tt_attroff(TT_BG_WHITE | TT_FG_BRIGHT);
	printf("\n");

	tt_attron(TT_FG_RED | TT_BG_CYAN | TT_BLINK);
	printf("FG_RED + BG_CYAN + BLINK");
	tt_attrclear();
	printf("\n");
}

void test_getcolsrows(void){
	printf("tt_getcols(): %d\ntt_getrows(): %d\n", tt_getcols(), tt_getrows());
}

void test_clear(void){
	int c;
	tt_clear();
	printf("tt_clear() test: This should be the first line on the screen.\nPress ENTER to continue...");
	while ((c = getchar()) != '\n' && c != EOF);
}

void test_showcursorecho(void){
	int c;
	/* stops the cursor from blinking */
	tt_showcursor(0);
	/* disables terminal echo */
	tt_setecho(0);
	printf("tt_showcursor()/tt_setecho() test: cursor should be hidden and characters should not be echoed\nPress ENTER to continue...\n");
	while ((c = getchar()) != '\n' && c != EOF);
	tt_showcursor(1);
	tt_setecho(1);
}

void test_getch(void){
	char c;
	printf("Getch test:\nPress ENTER to continue...\n");
	do{
		c = tt_getch();
		switch (c){
		case KEY_UP:
			printf("[UP ARROW]");
			break;
		case KEY_DOWN:
			printf("[DOWN ARROW]");
			break;
		case KEY_LEFT:
			printf("[LEFT ARROW]");
			break;
		case KEY_RIGHT:
			printf("[RIGHT ARROW]");
			break;
		case KEY_BACKSPACE:
			printf("[BACKSPACE]");
			break;
		case '\033':
			printf("[ESCAPE]");
			break;
		case KEY_ENTER:
			break;
		default:
			printf("%c", c);
		}
	}while (c != KEY_ENTER);
	printf("\n");
}

int main(void){
	test_clear();
	test_showcursorecho();
	test_getch();
	test_attron();
	test_getcolsrows();
	return 0;
}
