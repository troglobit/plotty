/* text terminal functions */

#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "term.h"


/*
 * This flag is used on *BSD when calling tcsetattr() to prevent it
 * from changing speed, duplex, parity.  GNU says we should use the
 * CIGNORE flag to c_cflag, but that doesn't exist so ... we rely on
 * our initial tcgetattr() and prey that nothing changes on the TTY
 * before we exit and restore with tcsetattr()
 */
#ifndef TCSASOFT
#define TCSASOFT 0
#endif

struct	termios	oldtty;			/* POSIX tty settings. */
struct	termios	newtty;


int ttsize(int *cols, int *rows)
{
	struct pollfd fd = { STDIN_FILENO, POLLIN, 0 };
	struct termios tc, saved;
	int rc;

	/* disable output while probing terminal size */
	rc = tcgetattr(STDERR_FILENO, &tc);
	if (!rc) {
		saved = tc;
		tc.c_cflag |= (CLOCAL | CREAD);
		tc.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
		tcsetattr(STDERR_FILENO, TCSANOW, &tc);
	}

	fprintf(stderr, "\e7\e[r\e[999;999H\e[6n");
	if (poll(&fd, 1, 300) > 0) {
		int row, col;

		if (scanf("\e[%d;%dR", &row, &col) == 2) {
			if (rows)
				*rows = row;
			if (cols)
				*cols = col;
		}
	}

	fprintf(stderr, "\e8");
	if (!rc)
		tcsetattr(STDERR_FILENO, TCSANOW, &saved);

	return rc;
}

/*
 * This function sets the terminal to RAW mode, as defined for the current
 * shell.  This is called both by ttopen() above and by spawncli() to
 * get the current terminal settings and then change them to what
 * mg expects.	Thus, tty changes done while spawncli() is in effect
 * will be reflected in mg.
 */
int ttraw(void)
{
	if (tcgetattr(0, &oldtty) == -1) {
		printf("can't get terminal attributes\n");
		return 1;
	}
	(void)memcpy(&newtty, &oldtty, sizeof(newtty));
	/* Set terminal to 'raw' mode and ignore a 'break' */
	newtty.c_cc[VMIN] = 1;
	newtty.c_cc[VTIME] = 0;
	newtty.c_iflag |= IGNBRK;
	newtty.c_iflag &= ~(BRKINT | PARMRK | INLCR | IGNCR | ICRNL | IXON);
	newtty.c_oflag &= ~OPOST;
	newtty.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);//ISIG

	if (tcsetattr(0, TCSASOFT | TCSADRAIN, &newtty) == -1) {
		printf("can't tcsetattr\n");
		return 1;
	}

	return 0;
}

/*
 * This function restores all terminal settings to their default values,
 * in anticipation of exiting or suspending the editor.
 */
int ttcooked(void)
{
	if (tcsetattr(0, TCSASOFT | TCSADRAIN, &oldtty) == -1) {
		printf("can't tcsetattr\n");
		return 1;
	}
	return 0;
}

