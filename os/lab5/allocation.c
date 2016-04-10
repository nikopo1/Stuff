#include <stdio.h>
#include <stdlib.h>

int a1 = 0xdeadbeef; /* .data, global, initialized, different from 0 */
int a2;              /* .bss, global, uninitialized */

int main(void) {
	static int b1 = 0xdeadbeaf; /* .data, static local, initialized, different from 0 */
	static int b2 = 0;          /* .bss, static local, initialized, equal to 0 */

	char buffer[10];            /* on stack */
	char *c = malloc(sizeof(char) * 10); /* pointer stored on stack, malloc memory in heap */

	free(c);
	return 0;
}
