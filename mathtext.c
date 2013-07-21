/*
	Mapped characters:
	*	U+0021..U+007E (printable ASCII)
	Would map these characters if I implemented Unicode input:
	*	U+0131 (LATIN SMALL LETTER DOTLESS I)
	*	U+0237 (LATIN SMALL LETTER DOTLESS J)
	*	U+0391..U+03C9 (Greek)
	*	U+03D1 (GREEK THETA SYMBOL)
	*	U+03D5 (GREEK PHI SYMBOL)
	*	U+03D6 (GREEK PI SYMBOL)
	*	U+03DC (GREEK LETTER DIGAMMA)
	*	U+03DD (GREEK SMALL LETTER DIGAMMA)
	*	U+03F0 (GREEK KAPPA SYMBOL)
	*	U+03F1 (GREEK RHO SYMBOL)
	*	U+03F5 (GREEK LUNATE EPSILON SYMBOL)
	*	U+2202 (PARTIAL DIFFERENTIAL)
	*	U+2207 (NABLA)
	Treating input as ASCII for now, the table is a mapping from
	bytes, not Unicode codepoints, to Unicode codepoints.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

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
	int i;
	puts("mathtext: write styled text with Unicode plain text");
	printf("Usage: mathtext [type]\n[type] can be one of:");
	for (i = 0; i < ARRAY_SIZE(table_names); i++) {
		if (i % 4 == 0)
			printf("\n\t");
		printf("%-16s", table_names[i]);
	}
	putchar('\n');
	return 1;
}
int remap(long *table) {
	int c;
	while ((c = getchar()) != EOF) {
		if (table[c] == -1)
			putchar_unicode(c);
		else
			putchar_unicode(table[c]);
	}
	return 0;
}
int main(int argc, char **argv) {
	int i;
	if (argc != 2)
		return help();
	for (i = 0; i < ARRAY_SIZE(table_names); i++)
		if (!strcmp(table_names[i], argv[1]))
			return remap(tables[i]);
	return help();
}
