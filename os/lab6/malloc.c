#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>

int main(void)
{
	struct rusage before, after;
	int ret, i;
	long minor_pf, major_pf;

	char *p = malloc(100 * 1024);
	if(p == NULL) {
		printf("error malloc\n");
		return -1;
	}

	ret = getrusage(RUSAGE_SELF, &before);
	if(ret != 0)
		printf("error getrusage before\n");

	for(i = 0; i < 102400; i++)
		p[i] = 0;

	p[0]    = 'a';
	p[1024] = 'b';
	p[4096] = 'c';

	ret = getrusage(RUSAGE_SELF, &after);
	if(ret != 0)
		printf("error getrusage after\n");

	printf("[%p]: %c\n", &p[0], p[0]);
	printf("[%p]: %c\n", &p[1024], p[1024]);
	printf("[%p]: %c\n", &p[4096], p[4096]);

	minor_pf = after.ru_minflt - before.ru_minflt;
	major_pf = after.ru_majflt - before.ru_majflt;

	printf("page size is %d\n", getpagesize());
	
	printf("minor page faults %ld, major page faults %ld\n", minor_pf, major_pf);

	return 0;
}
