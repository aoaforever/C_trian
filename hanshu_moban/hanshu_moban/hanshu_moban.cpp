#include <iostream>

using namespace std;


template <class T>
void allprint(T* a, int size) {
	for (int i = 0; i < size; i++) {
		cout << a[i];
		if (i < (size - 1)) {
			cout << ", ";
		}
	}
	cout << endl;
}




int main() {
	const int MAX = 5;
	int a[MAX] = { 1, 2, 3, 4, 5 };
	double b[MAX] = { 1.1,2.2,3.3,4.4,5.5 };
	const char* c[MAX] = { "abcd","cdef","dwdw","adad","adwd" };

	allprint(a, MAX);
	allprint(b, MAX);
	allprint(c, MAX);

	return 0;
}