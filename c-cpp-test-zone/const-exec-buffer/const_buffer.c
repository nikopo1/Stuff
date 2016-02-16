#include <stdio.h>

const unsigned char buf[1000];

void (*shellcode) (void);

noinline void write_memory(unsigned char *address)
{
	unsigned char tmp[1000];
	scanf("%s", tmp);
	memcpy(buf, tmp, sizeof(unsigned char) * 1000);
	shellcode = buf;
	shellcode();
}

int main(void)
{
	printf("%p\n", p);
	write_memory(buf);
	return 0;
}
