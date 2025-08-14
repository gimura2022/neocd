/* Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

/* neocd0 - program for generating path for cd using custom arguments */

/* includes */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* change directory */
static void cd(const char* path)
{
	printf("%s\n", path);
}

/* function for process custom parametrs */
static void custom_cd(const char* path)
{
	/* try to resolve one symboil arguments */
	if (strlen(path) == 1) switch (*path) {
#	define cd_case(x) cd(x); break;
	
	/* if symboil not found try to cd by default */
	default:
		cd(path);
		break;

#	undef cd_case
	} else
		cd(path); /* multisymboil args by default redirects to cd */
}

#define USAGE_SMALL	"usage: source neocd1 [-h] directory\n"
#define USAGE		"	-h		display help message\n"	\
			"	directory	new directory to change old\n" 

/* display help message */
static void usage(FILE* stream, bool small)
{
	fprintf(stream, small ? USAGE_SMALL : USAGE_SMALL USAGE);
}

/* main function */
int main(int argc, char* argv[])
{
	int c;

	/* process flags */
	opterr = 0;
	while ((c = getopt(argc, argv, "h")) != -1) switch (c) {
	case 'h':
		usage(stdout, false);
		exit(0);	/* 0 exit code means not changing directory */
	
	case '?':
		usage(stderr, true);
		exit(1);	/* 1 exit code means error and we are not changing directory */
	}

	/* if no given args try to move up in directory tree */
	if (argv[optind] == NULL)
		cd("..");
	/* else process custom cd */
	else
		custom_cd(argv[optind]);

	return 2;	/* two exit code means changing dirertory */

}
