#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <string.h>

#include "perf.h"

using namespace std;

unsigned int MAX_SIZE;

static inline bool binary_search(volatile const int v[], int value, unsigned int &index)
{
	long int mid;
	long int start = 0;
	long int end = MAX_SIZE - 1;

	while(start <= end) {
		mid = (end - start) / 2;
		mid = mid + start;

		if(v[mid] == value) {
			index = mid;
			return true;
		}
		if(v[mid] < value) {
			start = mid + 1;
		} else {
			end = mid - 1;
		}
	}

	return false;
}

static inline bool linear_search(volatile const int v[], int value, unsigned int &index)
{
	for(unsigned int i = 0; i < MAX_SIZE; i++) {
		if(v[i] == value) {
			index = i;
			return true;
		}
	}
	return false;
}

void fill_ascending(volatile int v[])
{
	for(unsigned int i = 0; i < MAX_SIZE; i++) {
		v[i] = i;
	}
}

void fill_random(volatile int v[])
{
	int aux;
	unsigned int j;

	fill_ascending(v);

	for(unsigned int i = MAX_SIZE; i > 0; i--) {
		j = rand() % i;
		aux = v[i - 1];
		v[i - 1] = v[j];
		v[j] = aux;
	}
}

ostream& operator<< (ostream& os, const int v[])
{
	for(unsigned int i = 0; i < MAX_SIZE; i++) {
		os << v[i] << " ";
	}
	return os;
}

int main(int argc, char* argv[])
{
	volatile int v[4 * 1024 * 1024];
	unsigned int index;
	bool found;
	bool linear = false;
	long long count, average = 0;
	int value, perf_fd;

	if(argc != 3) {
		cerr << "Usage %s (binary|linear) vector_size" << endl;
		return -1;
	}

	if(strcmp(argv[1], "linear") == 0) {
		linear = true;
	} else if(strcmp(argv[1], "binary") == 0) {
		linear = false;
	}

	MAX_SIZE = static_cast<unsigned int>(strtoul(argv[2], NULL, 10));

	srand(time(NULL));

	fill_ascending(v);

//	value = rand() % MAX_SIZE;

	perf_fd = perf_ref_cpu_cycle_counter();

	for(unsigned int i = 0; i < MAX_SIZE; i++) {

		value = rand() % MAX_SIZE;

		perf_start(perf_fd);
		found = binary_search(v, value, index);
		perf_stop(perf_fd);

		count = perf_read_counter(perf_fd);

		average += (count - average) / (i + 1ll);
	}

	cout << "binary search average = " << average << endl;

	average = 0;

	for(unsigned int i = 0; i < MAX_SIZE; i++) {

		value = rand() % MAX_SIZE;

		perf_start(perf_fd);
		found = linear_search(v, value, index);
		perf_stop(perf_fd);

		count = perf_read_counter(perf_fd);

		average += (count - average) / (i + 1ll);

	}

	cout << "linear search average = " << average << endl;

	return 0;
}
