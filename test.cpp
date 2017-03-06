#include <iostream>
#include <cstdio>
using namespace std;

typedef struct A {
	int i,j,k;
	A(int x, int y, int z ) { i = x, j = y, k = z; }
} A;

int main() {
	A a(1,2,3),
	  b = a;
	printf("%d %d %d\n",b.i,b.j,b.k);
	return 0;
}

