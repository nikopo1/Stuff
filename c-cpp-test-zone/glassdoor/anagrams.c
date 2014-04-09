#include <string.h>
#include <stdio.h>
#include <limits.h>

int count_anagram_occurances(char *word, char *text)
{
	int matching = 0;
	int num[UCHAR_MAX -1];
	int i, n_word, n_text;
	unsigned char c, old;
	int count = 0;

	memset(num, 0, sizeof(num));

	n_word = strlen(word);
	for(i = 0; i < n_word; i++) {
		c = (unsigned char) word[i];
		num[c]++;
	}

	n_text = strlen(text);
	for(i = 0; i < n_text; i++) {
		c = (unsigned char) text[i];
		num[c]--;
		if(num[c] < 0)
			matching--;
		else
			matching++;

		if(i >= n_word) {
			old = (unsigned char) text[i - n_word];
			num[old]++;
			if(num[old] > 0)
				matching--;
			else
				matching++;
		}

		if(matching == n_word) {
			printf("Occurance at %d\n", i);
			count++;
		}
	}

	return count;
}

int main(void)
{
	char word[] = "for";
	char text[] = "forxxorfxdofr";
	int count;

	count = count_anagram_occurances(word, text);

	printf("Number of anagram occurances of \"%s\" in \"%s\" is %d\n", word, text, count);
	return 0;
}
