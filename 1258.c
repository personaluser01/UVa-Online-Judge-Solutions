/*
 * 1258. Nowhere Money
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LIM 1000000001LL
#define N (1 << 7)
typedef long long i64;
typedef unsigned long long u64;
enum { DIGL = 6, BASE = 1000000LL, LEN = 0x30 };

i64 *load( i64 n ) {
	int i = 0, sig = 1;
	i64 *x = (i64 *)calloc(LEN, sizeof *x);
	if (n < 0) sig = -1, n = -n;
	do { x[i++] = n%BASE; } while (n /= BASE);
	return x;
}

void norm(i64 *x) {
	int i;
	for (i = 0; i < LEN; ++i)
		if (x[i] >= BASE)
			x[i+1]+=x[i]/BASE, x[i]%=BASE;
}

void add(i64 *x, i64 *y) {
	int i;
	for (i = 0; i < LEN; ++i)
		x[i] += y[i];
	norm(x);
}

void subtr(i64 *x, i64 *y) {
	int i;
	for ( i = 0; i < LEN; ++i )
		x[i] -= y[i];
	for ( i = 0; i < LEN; ++i )
		while ( x[i] < 0 )
			--x[i+1], x[i] += BASE;
	for ( i = 0; i < LEN; ++i )
		assert( x[i] >= 0 );
}

void print(i64 *x) {
	int i;
	for (i = LEN - 1; i >= 0 && !x[i]; --i);
	if (i < 0) {
		putchar('0');
		return;
	}	
	for ( printf("%lld", x[i]); (--i) >= 0; printf("%0*lld",DIGL,x[i]) );
}

i64 *ZERO, *ONE;
i64 *F[N];
char s[0x400];
int *top, st[N];

i64 *read_num(char *t) {
	i64 *x = (i64 *)calloc(LEN, sizeof *x);
	char s[0x400],e;
	int i, j, k;
	strcpy(s, t);
	k = strlen(s);
	for (i = 0, j = k - 1; i < j; ++i, --j)
		e = s[i], s[i] = s[j], s[j] = e;
	while (k % DIGL) s[k++] = '0';
	s[k] = '\0';
	for (i = 0; i < k/DIGL; ++i) 
		for (j = (i+1)*DIGL-1; j >= i*DIGL; --j)
			x[i] = 10 * x[i] + ((i64)(s[j] - '0'));
	return x;
}

int is_equal(i64 *x, i64 *y) {
	int i;
	for (i = 0; i < LEN; ++i)
		if (x[i] != y[i])
			return 0;
	return 1; 
}

int is_less(i64 *a, i64 *b) {
	int i;

	for (i = LEN-1; i >= 0; --i)
		if (a[i] < b[i])
			return 1;
		else if ( a[i] > b[i] )
			return 0;
	return 0;
}

void zeckendorf(i64 *x, int m) {
	int i, j, k;
	if (is_equal(x,ZERO)) return;
	assert( m >= 1 );
	for(i=0,j=m;i+1<j;is_less(x,F[k=(i+j)>>1])?(j=k):(i=k));
	if (is_equal(F[i],x)) { *++top = i; return; }
	assert( is_less(F[i],x) );
	subtr(x,F[i]), zeckendorf(x,j), *++top = i;
}

int main() {
	int i, j, k,n;
	char t[0x400];
	i64 *x,*y;
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	ZERO = load(0);
	for ( F[0] = F[1] = ONE = load(1), n = 2; n < N; ++n) {
		F[n] = (i64 *)calloc(LEN, sizeof *F[n]);
		for (i = 0; i < LEN; ++i)
			F[n][i] = F[n-1][i];
		add(F[n],F[n-2]);
	}

	while (gets(s)) {
		strcpy(t,s);
		for (i = 0; s[i] && isdigit(s[i]); ++i);
		s[i] = '\0';
		x = read_num(s);
		top = st, zeckendorf(x,N-1), puts(t);
		for (i = top-st; i >= 1; --i) {
			/*if (i != top-st) putchar(' ');*/
			printf("%d ", st[i]);
		}
		putchar('\n');
		for (i = top-st; i >= 1; --i) {
			/*if (i != top-st) putchar(' ');*/
			print(F[st[i]]), putchar(' ');
		}
		puts("\n");
	}
	return 0;
}

