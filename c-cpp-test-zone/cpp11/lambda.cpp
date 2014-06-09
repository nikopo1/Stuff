#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(void)
{
	vector<int> numbers{4, 6, 8, -1, -5, -10, 20};

	for_each(numbers.begin(), numbers.end(), [](int &number) { cout << number << endl; });

	return 0;
}
