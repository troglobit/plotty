#ifndef PLOTTY_H_
#define PLOTTY_H_

#include <stdlib.h>

struct plotty {
	char   *p_title;
	char   *p_screen;
	size_t  p_width;
	size_t  p_spin;
	size_t  p_total;
};

struct plotty *plotty_init (char *title, int width);
void           plotty_exit (struct plotty *p);

void           plotty_plotter  (struct plotty *p, int line, int act);
void           plotty_progress (struct plotty *p, int line, int percent);

#endif /* PLOTTY_H_ */
