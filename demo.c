/* demo application, taken from the mcjoin project */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "plotty.h"
#include "term.h"

static void restore(void)
{
	ttcooked();
	showcursor();
	puts("");
}

static void cb(int signo)
{
	(void)signo;
	exit(0);
}

int main(void)
{
	char *title = "mcjoin :: receiving multicast";
	char hostname[80];
	time_t now, start;
	char *snow;
	struct plotty *g1;
	struct plotty *g2;
	struct plotty *g3;
	struct plotty *g4;
	struct plotty *g5;
	struct plotty *g6;
	int height, width;
	int i;

	signal(SIGINT, cb);
	ttraw();
	hidecursor();
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	atexit(restore);

	ttsize(&width, &height);
	cls();
	gotoxy((width - strlen(title)) / 2, 1);
	printf("\e[1m%s\e[0m", title);

	srand48(time(NULL));
	g1 = plotty_init("225.1.2.1      ", width);
	g2 = plotty_init("225.1.2.2      ", width);
	g3 = plotty_init("225.1.2.3      ", width);
	g4 = plotty_init("225.1.2.4      ", width);
	g5 = plotty_init("225.1.2.5      ", width);
	gotoxy(0, 3);
	printf("\e[7mGROUP             PLOTTER%*sPACKETS     \e[0m", width - 37, " ");
	start = time(NULL);
	while (1) {
		gethostname(hostname, sizeof(hostname));
		now = time(NULL);
		snow = ctime(&now);
		gotoxy(0, 2);
		printf("%s (IPADDR)", hostname);
		gotoxy(width - strlen(snow) + 2, 2);
		puts(snow);

		plotty_plotter(g1, 4, lrand48() % 42);
		plotty_plotter(g2, 5, lrand48() % 42);
		plotty_plotter(g3, 6, lrand48() % 42);
		plotty_plotter(g4, 7, lrand48() % 42);
		plotty_plotter(g5, 8, lrand48() % 42);
		usleep(60000);

		if (now - start >= 5)
			break;
	}

	g6 = plotty_init("225.1.2.10     ", width);
	for (i = 0; i <= 100; i++) {
		plotty_progress(g6, 9, i);
		usleep(30000);
	}

	return 0;
}

/**
 * Local Variables:
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
