/* --------------------------------------------------------------------------
 *
 * Commands for NanoPi OLED Hat
 * Copyright (C) 2018, Anthony Lee, All Rights Reserved
 *
 * This software is a freeware; it may be used and distributed according to
 * the terms of The MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: oled_capture.c
 * Description:
 *
 * --------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define DEFAULT_DEVICE		"/dev/oled-003c"
#define OLED_SCREEN_WIDTH	128
#define OLED_SCREEN_HEIGHT	64

static void show_usage(void)
{
	printf("oled_capture - Capture content of OLED and write to an xpm\n\n");
	printf("Usage: oled_capture [-D device] xpm_filename\n\
    device                path of device, default value is: %s\n", DEFAULT_DEVICE);
}

const char xpm_header1[] = "\
/* XPM */\n\
static char *t_xpm[] = {\n\
\" ";

const char xpm_header2[] = "\
 2 1\",\n\
\".\tc #FFFFFF\",\n\
\"+\tc #000000\",\n";

#ifdef CMD_ALL_IN_ONE
int cmd_capture(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
	int n, f, out, err = 0;
	const char *dev_name = DEFAULT_DEVICE;
	void *buffer;
	size_t len = OLED_SCREEN_WIDTH * (OLED_SCREEN_HEIGHT >> 3);
	const uint8_t *bits;
	int x, y;
	uint8_t c;
	uint8_t str[OLED_SCREEN_WIDTH + 4];

	for (n = 1; n < argc; n++) {
		if (n < argc - 1 && strcmp(argv[n], "-D") == 0) {
			dev_name = argv[++n];
		} else {
			break;
		}
	}
	argc -= (--n);

	if (argc != 2) {
		show_usage();
		exit(1);
	}

	if ((f = open(dev_name, O_RDWR)) < 0) {
		perror("Open device");
		exit(1);
	}

	if ((out = open(argv[n + 1], O_CREAT | O_TRUNC | O_RDWR, 0600)) < 0) {
		perror("Open output");
		exit(1);
	}

	buffer = mmap(NULL, len, PROT_READ, MAP_SHARED, f, 0);
	if(buffer == MAP_FAILED)
	{
		close(out);
		close(f);
		perror("mmap");
		exit(1);
	}

	memset(str, 0, sizeof(str));
	sprintf((char*)str, "%d %d", OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);

	do {
		if ((err = write(out, xpm_header1, strlen(xpm_header1))) < 0) break;
		if ((err = write(out, str, strlen((char*)str))) < 0) break;
		if ((err = write(out, xpm_header2, strlen(xpm_header2))) < 0) break;

		str[0] = '"';
		memcpy(str + OLED_SCREEN_WIDTH + 1, "\",\n", 3);

		for (y = 0; y < OLED_SCREEN_HEIGHT; y++) {
			bits = (uint8_t*)buffer + OLED_SCREEN_WIDTH * (y >> 3);

			for (x = 0; x < OLED_SCREEN_WIDTH; x++) {
				c = ((*bits++) >> (y & 0x07)) & 0x01;
				str[x + 1] = (c == 0 ? '+' : '.');
			}

			if ((err = write(out, str, OLED_SCREEN_WIDTH + 4)) < 0) break;
		}

		err = write(out, "};\n", 3);
	} while(0);

	if (err < 0)
		perror("write");

	if (munmap(buffer, len) != 0)
		perror("munmap");

	close(out);
	close(f);

	return(err < 0 ? err : 0);
}

