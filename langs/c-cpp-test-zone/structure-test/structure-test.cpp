class Test {
	int x;
	struct cell {
		int a;
		float b;
	} info;
public:
	Test(int _x): x{_x} {}
	Test(int a, float b): info{a, b} {}
	int number(void) { return 0;}
};

// As expected, will cause error. Wanted to be sure about this stuff in Fiasco.
// inline char Test::letter(void) { return 'a'; }

typedef struct experiment_t {
	int info;
	struct experiment_t *next;
} experiment_t;

int main(void)
{
	experiment_t exp;
	return 0;
}
