#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	int max = 0;
	int num = atoi(argv[1]);
	for (int i=0; i<=num; i++) {
		cout << "(" << i << "," << num - i << ")" << endl;
		if(i*(num-i) > max) max = i*(num-i);
	}
	cout << max << endl;
	return 0;
}

