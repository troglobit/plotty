#ifndef PLOTTY_TERM_H_
#define PLOTTY_TERM_H_

#include <stdio.h>

/* Esc[2J                     - Clear screen */
#define cls()                 fputs("\e[2J", stderr)

/* Esc[Line;ColumnH           - Moves the cursor to the specified position (coordinates) */
#define gotoxy(x,y)           fprintf(stderr, "\e[%d;%dH", (int)(y), (int)(x))

/* Esc[?25l (lower case L)    - Hide Cursor */
#define hidecursor()          fputs("\e[?25l", stderr)

/* Esc[?25h (lower case H)    - Show Cursor */
#define showcursor()          fputs("\e[?25h", stderr)

int ttsize   (int *cols, int *rows);
int ttraw    (void);
int ttcooked (void);

#endif /* PLOTTY_TERM_H_ */
