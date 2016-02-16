#include <stdio.h>
#include <stdlib.h>

#define NUM_BUCKETS	4
#define BUCKET_SIZE	(1024 * 1024)
#define WORD_BIT_SIZE	(sizeof(unsigned long) * 8)

#define ffsl(word)	__builtin_ffsl(word)

typedef void* vaddr_t;

struct pkmem_bucket {
	unsigned int num_entries;
	unsigned int entry_size;
	unsigned int free_entries;
	unsigned long *bitmap;

	vaddr_t address;
};

struct pkmem_bucket pkmem[NUM_BUCKETS];

static inline unsigned long get_bitmap_words(unsigned int num_entries)
{
	if (num_entries % WORD_BIT_SIZE == 0)
		return num_entries / WORD_BIT_SIZE;
	else
		return num_entries / WORD_BIT_SIZE + 1;
}

void pkmem_init(vaddr_t heap_base)
{
	unsigned int i, bucket_num_entries;
	unsigned long bucket_bitmap_offset = 0;

	pkmem[0].entry_size = 128;
	pkmem[1].entry_size = 256;
	pkmem[2].entry_size = 512;
	pkmem[3].entry_size = 4096;

	for (i = 0; i < NUM_BUCKETS; i++) {
		bucket_num_entries = BUCKET_SIZE / pkmem[i].entry_size;

		pkmem[i].num_entries = bucket_num_entries;
		pkmem[i].free_entries = bucket_num_entries;
		pkmem[i].bitmap = heap_base + bucket_bitmap_offset;

		/* compute offset for next bucket */
		bucket_bitmap_offset += get_bitmap_words(bucket_num_entries) * 8;
	}

	for (i = 0; i < NUM_BUCKETS; i++) {
		pkmem[i].address = heap_base + bucket_bitmap_offset;
		pkmem[i].address += i * BUCKET_SIZE;
	}
}

vaddr_t pkmalloc_bucket(struct pkmem_bucket *bucket)
{
	unsigned long word_idx, bit_idx, entry_idx;
	unsigned long bitmap_words = get_bitmap_words(bucket->num_entries);
	vaddr_t ret = NULL;

	for (word_idx = 0; word_idx < bitmap_words; word_idx++) {
		if (bucket->bitmap[word_idx] != ~0UL) {
			printf("1:bitmap[%lu]=%lx\n", word_idx, bucket->bitmap[word_idx]);
			bit_idx = ffsl(~bucket->bitmap[word_idx]) - 1;
			printf("2:setting bit %lu\n", bit_idx);
			bucket->bitmap[word_idx] |= (1UL << bit_idx);
			printf("3:bitmap[%lu]=%lx\n", word_idx, bucket->bitmap[word_idx]);

			entry_idx = word_idx * WORD_BIT_SIZE + bit_idx;
			ret = bucket->address + entry_idx * bucket->entry_size;
			bucket->free_entries--;
			break;
		}
	}

	return ret;
}

void pkfree_bucket(struct pkmem_bucket *bucket, vaddr_t addr)
{
	unsigned long entry_idx, word_idx, bit_idx;

	/* insert 'offset alignment to entry size' check here */

	entry_idx = (addr - bucket->address) / bucket->entry_size;
	word_idx = entry_idx / WORD_BIT_SIZE;
	bit_idx = entry_idx % WORD_BIT_SIZE;

	/* insert 'memory is allocated' check here */

	bucket->bitmap[word_idx] &= ~(1UL << bit_idx);
	bucket->free_entries++;
}

vaddr_t pkmalloc(unsigned long size)
{
	unsigned int index;

	for (index = 0; index < NUM_BUCKETS; index++) {
		if (size <= pkmem[index].entry_size) {
			if (pkmem[index].free_entries == 0)
				return NULL;

			return pkmalloc_bucket(&pkmem[index]);
		}
	}

	return NULL;
}

void pkfree(vaddr_t addr)
{
	unsigned int index;

	for (index = 0; index < NUM_BUCKETS; index++) {
		if (pkmem[index].address < addr &&
		    addr < pkmem[index].address + BUCKET_SIZE) {
			pkfree_bucket(&pkmem[index], addr);
			break;
		}
	}
}

void fill_bucket(unsigned int bucket)
{
	int i;
	if (bucket >= NUM_BUCKETS)
		return;

	for (i = 0; i <= pkmem[bucket].num_entries; i++) {
		printf("Allocating %d\n", i);
		vaddr_t res = pkmalloc(pkmem[bucket].entry_size);
		printf("at %p\n\n", res);
	}
}

int main(void)
{
	int i;
	vaddr_t heap = malloc(5 * 1024 * 1024);
	if (heap == NULL) {
		perror("malloc heap");
		exit(-1);
	}

	pkmem_init(heap);

	for (i = 0; i < NUM_BUCKETS; i++) {
		printf("bucket[%d]:\n", i);
		printf("\tnum_entries  = %u\n", pkmem[i].num_entries);
		printf("\tentry_size   = %u\n", pkmem[i].entry_size);
		printf("\tfree_entries = %u\n", pkmem[i].free_entries);
		printf("\tbitmap       = %p\n", pkmem[i].bitmap);
		printf("\taddress      = %p\n", pkmem[i].address);
		printf("\n");

		fill_bucket(i);
	}

	return 0;
}
