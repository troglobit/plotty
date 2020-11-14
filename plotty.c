/* Basic idea for a plotter  [       <---     .....   ]      */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "plotty.h"

#define SPINNER_STYLE "|/-\\"

/* Esc[2J                     - Clear screen */
#define cls()                 fputs("\e[2J", stderr)
/* Esc[Line;ColumnH           - Moves the cursor to the specified position (coordinates) */
#define gotoxy(x,y)           fprintf(stderr, "\e[%d;%dH", (int)(y), (int)(x))
/* Esc[?25l (lower case L)    - Hide Cursor */
#define hidecursor()          fputs("\e[?25l", stderr)
/* Esc[?25h (lower case H)    - Show Cursor */
#define showcursor()          fputs("\e[?25h", stderr)

static char spinner(char *style)
{
	size_t num;
	static unsigned int i = 0;

	if (!style)
		style = SPINNER_STYLE;
	num = strlen(style);

	return style[i++ % num]; /* % Number of states in style */
}

struct plotty *plotty_init(char *title, int width)
{
	struct plotty *p;
	size_t pos;

	if (width < 10) {
		errno = EINVAL;
		return NULL;
	}
	if (!title)
		title = "";

	p = calloc(1, sizeof(*p));
	if (!p)
		return NULL;

	p->p_title = strdup(title);
	if (!p->p_title)
		goto error;

	width -= strlen(title) + 5 + 12;
	p->p_screen = calloc(width, sizeof(char));
	if (!p->p_screen)
		goto error;

	memset(p->p_screen, ' ', width - 1);
	p->p_width = width;
	
	pos = strlen(title) - 1;
	while (pos > 0 && isspace(title[pos]))
	       pos--;
	p->p_spin  = title[pos];

	return p;
error:
	if (p->p_title)
		free(p->p_title);
	if (p->p_screen)
		free(p->p_screen);
	free(p);
	return NULL;
}

void plotty_exit(struct plotty *p)
{
	if (!p) {
		errno = EINVAL;
		return;
	}

	if (p->p_title)
		free(p->p_title);
	if (p->p_screen)
		free(p->p_screen);
	free(p);
}
	
void plotty_plotter(struct plotty *p, int line, int act)
{
	const char *spinner = "|/-\\";
	size_t num = strlen(spinner);

	memmove(p->p_screen, &p->p_screen[1], p->p_width - 1);
	p->p_screen[p->p_width - 2] = act ? '.' : ' ';
	p->p_total += act;

	gotoxy(0, line);
	fprintf(stderr, "\r%s %c [%s] %zu", p->p_title,
		spinner[p->p_spin++ % num], p->p_screen, p->p_total);
}

void plotty_progress(struct plotty *p, int line, int percent)
{
	size_t i, bar;

	bar = percent * (p->p_width - 1) / 100;
	for (i = 0; i < p->p_width - 1; i++) {
		if (i > bar)
			p->p_screen[i] = ' ';
		else if (i == bar)
			p->p_screen[i] = '>';
		else
			p->p_screen[i] = '=';
	}

	gotoxy(0, line);
	fprintf(stderr, "\r%s %c [%s] %3d%%", p->p_title,
		spinner(NULL), p->p_screen, percent);
}

/**
 * Local Variables:
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
