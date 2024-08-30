// SPDX-License-Identifier: BSD-2-Clause

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

int
main(int argc, char **argv)
{
	if (argc != 2) {
		dprintf(2, "%s: missing brightness argument\n", argv[0]);
		return 1;
	}

	int fd = open("/sys/class/backlight/apple-panel-bl/brightness", O_WRONLY);
	if (fd == -1) {
		dprintf(2, "%s: can't open\n", argv[0]);
		return 6;
	}
	ssize_t wl = (write(fd, argv[1], strlen(argv[1])));
	if (wl == -1) {
		dprintf(2, "%s: can't write\n", argv[0]);
		return 7;
	} else if ((size_t)wl == strlen(argv[1])) {
	} else {
		dprintf(2, "%s: incomplete write\n", argv[0]);
		return 8;
	}
	if (close(fd) == -1) {
		dprintf(2, "%s: can't close\n", argv[0]);
		return 9;
	}

	return 0;
}
