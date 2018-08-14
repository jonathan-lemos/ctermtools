/** @file ctermtools.h
 * Copyright (c) 2018 Jonathan Lemos
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef __CTERMTOOLS_H
#define __CTERMTOOLS_H

#include <stdint.h>

#if defined(_MSC_VER)
	#ifdef TT_EXPORTING
		#define TT_API __declspec(dllexport)
	#else
		#define TT_API __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#ifdef TT_EXPORTING
		#define TT_API __attribute__((visibility("default")))
	#else
		#define TT_API
	#endif
#else
#define TT_API
#error Unknown dynamic link export/import notation
#endif

#define TT_NORMAL     (0)       /**< Normal attribute. Only valid by itself. */
#define TT_BOLD       (1 << 0)  /**< Make colors more visible. @deprecated attroff(TT_BOLD) does not work on xterm. */
#define TT_UNDERLINE  (1 << 1)  /**< Underline. Typically not supported in pure text environments. */
#define TT_BLINK      (1 << 2)  /**< Blinking text. Does not work on Windows. */
#define TT_INVERT     (1 << 3)  /**< Swap the foreground and background */

#define TT_FG_DEFAULT (1 << 4)  /**< Default foreground (text) color */
#define TT_FG_BLACK   (1 << 5)  /**< Black foreground */
#define TT_FG_RED     (1 << 6)  /**< Red foreground */
#define TT_FG_GREEN   (1 << 7)  /**< Green foreground */
#define TT_FG_YELLOW  (1 << 8)  /**< Yellow foreground */
#define TT_FG_BLUE    (1 << 9)  /**< Blue foreground */
#define TT_FG_MAGENTA (1 << 10) /**< Magenta foreground */
#define TT_FG_CYAN    (1 << 11) /**< Cyan foreground */
#define TT_FG_WHITE   (1 << 12) /**< White foreground */
#define TT_FG_BRIGHT  (1 << 13) /**< Combine with another foreground color to brighten it. Not supported on all terminals. */

#define TT_BG_DEFAULT (1 << 14) /**< Default background color */
#define TT_BG_BLACK   (1 << 15) /**< Black foreground */
#define TT_BG_RED     (1 << 16) /**< Red foreground */
#define TT_BG_GREEN   (1 << 17) /**< Green foreground */
#define TT_BG_YELLOW  (1 << 18) /**< Yellow foreground */
#define TT_BG_BLUE    (1 << 19) /**< Blue foreground */
#define TT_BG_MAGENTA (1 << 20) /**< Magenta foreground */
#define TT_BG_CYAN    (1 << 21) /**< Cyan foreground */
#define TT_BG_WHITE   (1 << 22) /**< White foreground */
#define TT_BG_BRIGHT  (1 << 23) /**< Combine with any other background color to brighten it. Not supported on all terminals. */

/**
 * Turns terminal attributes on.
 * The effects are only applied to text printed after this function is called.
 * @see tt_attroff()
 *
 * @param attr The attributes to turn on.<br>
 * These can be combined with the '|' operator like below:<br>
 * ```C
 * tt_attron(TT_UNDERLINE | TT_FG_RED | TT_FG_BRIGHT);
 * ```
 * This command would apply an underline and a bright red foreground color to all text printed afterwards.
 */
void TT_API tt_attron(uint_fast32_t attr);

/**
 * Turns terminal attributes off.
 * The effects are only applied to text printed after this function is called.
 * @see tt_attron()
 *
 * @param attr The attributes to turn off.<br>
 * These can be combined with the '|' operator like below:<br>
 * ```C
 * tt_attroff(TT_UNDERLINE | TT_FG_RED);
 * ```
 * This command would remove any underlining and set the color back to default for all text printed afterwards.<br>
 * If said attributes are not already on, this function does nothing.
 *
 * @bug tt_attroff(TT_FG_BRIGHT) does not revert to normal version of color.
 * @bug tt_attroff(TT_BOLD) does not work on xterm.
 */
void TT_API tt_attroff(uint_fast32_t attr);

/**
 * Turns all terminal attributes off.
 * @see tt_attron()
 */
void TT_API tt_attrclear(void);

/**
 * Gets the number of columns (width) of the current terminal window.
 *
 * @return The width of the current terminal window in columns.
 */
int TT_API tt_getcols(void);

/**
 * Gets the number of rows (height) of the current terminal window.
 *
 * @return The height of the current terminal window in rows.
 */
int TT_API tt_getrows(void);

/**
 * Shows or hides the terminal cursor.
 *
 * @param enable This should be 1 to show the cursor and 0 to hide it.<br>
 * Other values result in undefined behavior.
 */
void TT_API tt_showcursor(int enable);

/**
 * Disables or enables echoing of user input.
 * Disabling echo is what happens when you type a sudo password.
 *
 * @param enable This should be 1 to enable echo and 0 to suppress it.<br>
 * Other values result in undefined behavior.
 *
 * @return 0 on success, negative on failure.
 */
int TT_API tt_setecho(int enable);

/**
 * Sets the cursor position on the screen.
 * (0, 0) is the upper-left corner of the screen.<br>
 * If negative values are passed or if the values are outside the terminal window, undefined behavior results.
 * @see tt_getrows()
 * @see tt_getcols()
 *
 * @param row The row to set the cursor's position to.
 * @param col The column to set the cursor's position to.
 */
void TT_API tt_setcursorpos(int row, int col);

/**
 * Moves the cursor relative to its current position.
 *
 * @param row_delta How many rows to move the cursor downward.<br>
 * If a negative value is passed, the cursor moves upward instead.
 *
 * @param col_delta How many columns to move the cursor to the right.<br>
 * If a negative value is passed, the cursor moves to the left instead.
 */
void TT_API tt_movecursorpos(int row_delta, int col_delta);

/**
 * Clears the screen.
 */
void TT_API tt_clear(void);

#define KEY_UP        (-2)     /**< Up arrow */
#define KEY_DOWN      (-3)     /**< Down arrow */
#define KEY_RIGHT     (-4)     /**< Right arrow */
#define KEY_LEFT      (-5)     /**< Left arrow */
#define KEY_ENTER     ('\n')   /**< Enter key */
#define KEY_BACKSPACE ('\x7F') /**< Backspace */
/**
 * Gets a keypress from the terminal.
 * This function can read arrow keys, enter, and backspace in addition to the regular keys.<br>
 *
 * @pre Before use, stdin must be emptied after any previous usage of stdin.<br>
 * This can be done with the following command:<br>
 * ```C
 * #include <stdio.h>
 *
 * int c;
 * while ((c = getchar()) != '\n' && c != EOF);
 * ```
 *
 * @return A character corresponding to the character read.
 * @see KEY_UP
 * @see KEY_DOWN
 * @see KEY_RIGHT
 * @see KEY_LEFT
 * @see KEY_ENTER
 * @see KEY_BACKSPACE
 */
int TT_API tt_getch(void);

#endif