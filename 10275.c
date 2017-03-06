/*
 * 10275. Guess The Number
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
enum { BASE = 1000000LL, DIGL = 6, LEN = 84000 };
typedef long long i64;

char s[LEN*DIGL];

i64 *read_int() {
	int i,j,k,n = strlen(s);
	x = (i64 *)calloc(n/DIGL+128,sizeof *x);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	return 0;
}
