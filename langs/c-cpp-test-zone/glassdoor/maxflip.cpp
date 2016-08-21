#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	unsigned int i, num, bit;
	int digit, maxflip;
	int count = 0, sum = -1, max = 0;

	cin >> num;

	for(unsigned int i = 0; i < num; i++) {
		cin >> bit;
		if(bit == 1) {
			count++;
			digit = -1;
		} else {
			digit = 1;
		}

		if(sum < 0) {
			sum = 0;
		}

		sum += digit;

		if(sum > max) {
			max = sum;
		}
	}

	maxflip = max + count;

	cout << max << endl;
	cout << count << endl;
	cout << maxflip << endl;

	return 0;
}
