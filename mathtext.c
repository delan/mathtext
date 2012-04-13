#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void putchar_unicode(long c) {
	if (c < 0x80) {
		putchar(c);
	} else if (c < 0x800) {
		putchar((c >> 6) | 0xc0);
		putchar((c & 0x3f) | 0x80);
	} else if (c < 0x10000) {
		putchar((c >> 12) | 0xe0);
		putchar((c >> 6 & 0x3f) | 0x80);
		putchar((c & 0x3f) | 0x80);
	} else {
		putchar((c >> 18) | 0xf0);
		putchar((c >> 12 & 0x3f) | 0x80);
		putchar((c >> 6 & 0x3f) | 0x80);
		putchar((c & 0x3f) | 0x80);
	}
}
int help(void) {
	puts("mathtext: write styled text with Unicode plain text");
	puts("Usage: mathtext [type]");
	puts("[type] can be one of:");
	puts("    serifb      serifi      serifbi     sans");
	puts("    sansb       sansi       sansbi      mono");
	puts("    script      scriptb     double      fraktur");
	puts("    frakturb    fullwidth");
	return 1;
}
void transpose_alphanum(long s, long caps, long lower, long num) {
	if (s >= 'A' && s <= 'Z')
		putchar_unicode(s + caps);
	else if (s >= 'a' && s <= 'z')
		putchar_unicode(s + lower);
	else if (s >= '0' && s <= '9')
		putchar_unicode(s + num);
	else putchar(s);
}
void transpose_block(long s, long min, long max, long delta) {
		if (s >= min && s <= max)
			putchar_unicode(s + delta);
		else putchar(s);
}
int main(int argc, char** argv) {
	long transpose_type = 0,
		caps, lower, num,
		min, max, delta,
		c;
	if (argc < 2)
		return help();
	if (!strcmp(argv[1], "serifb")) {
		transpose_type = 0;
		caps = 119808 - 'A';
		lower = 119834 - 'a';
		num = 120782 - '0';
	} else if (!strcmp(argv[1], "serifi")) {
		transpose_type = 0;
		caps = 119860 - 'A';
		lower = 119886 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "serifbi")) {
		transpose_type = 0;
		caps = 119912 - 'A';
		lower = 119938 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "sans")) {
		transpose_type = 0;
		caps = 120224 - 'A';
		lower = 120250 - 'a';
		num = 120802 - '0';
	} else if (!strcmp(argv[1], "sansb")) {
		transpose_type = 0;
		caps = 120276 - 'A';
		lower = 120302 - 'a';
		num = 120812 - '0';
	} else if (!strcmp(argv[1], "sansi")) {
		transpose_type = 0;
		caps = 120328 - 'A';
		lower = 120354 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "sansbi")) {
		transpose_type = 0;
		caps = 120380 - 'A';
		lower = 120406 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "mono")) {
		transpose_type = 0;
		caps = 120432 - 'A';
		lower = 120458 - 'a';
		num = 120822 - '0';
	} else if (!strcmp(argv[1], "script")) {
		transpose_type = 0;
		caps = 119964 - 'A';
		lower = 119990 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "scriptb")) {
		transpose_type = 0;
		caps = 120016 - 'A';
		lower = 120042 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "double")) {
		transpose_type = 0;
		caps = 120120 - 'A';
		lower = 120146 - 'a';
		num = 120792 - '0';
	} else if (!strcmp(argv[1], "fraktur")) {
		transpose_type = 0;
		caps = 120068 - 'A';
		lower = 120094 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "frakturb")) {
		transpose_type = 0;
		caps = 120172 - 'A';
		lower = 120198 - 'a';
		num = 0;
	} else if (!strcmp(argv[1], "fullwidth")) {
		transpose_type = 1;
		min = '!';
		max = '~';
		delta = 65281 - '!';
	} else return help();
	while ((c = getchar()) != EOF) {
		switch (transpose_type) {
			case 0:
				transpose_alphanum(c, caps, lower, num);
				break;
			case 1:
				transpose_block(c, min, max, delta);
				break;
		}
	}
	return 0;
}
