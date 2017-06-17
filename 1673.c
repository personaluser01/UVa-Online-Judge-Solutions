/*
 * 1673. str2int
 * TOPIC: dp on suffix automata
 * status:
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M (10100)
#define N (1<<18)
#define A 9
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1))

typedef struct cell {
	unsigned int map;
} cell;
 
int m,n,str[N],which[BIT(20)];

int main() {
	int i,j,k;
	for ( ;1 == scanf("%d",&n); ) {
	}
	return 0;
}

