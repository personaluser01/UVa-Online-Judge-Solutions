/*
 * 1258. Nowhere Money
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LIM 1000000001LL
#define N (1 << 8)
typedef long long i64;
typedef unsigned long long u64;
enum { DIGL = 5, BASE = 100000LL, LEN = 0x40 };

int is_neg(i64 *x) { return x[LEN - 1] >= BASE / 2; }

void negate(i64 *x) {
	int i;
	for (i = 0; i < LEN; ++i) x[i] = BASE-1-x[i];
	for (i = 0; i < LEN && x[i] == BASE - 1; ++i)
		x[i] = 0;
	++x[i];
}

i64 *load( i64 n ) {
	int i = 0, sig = 1;
	i64 *x = (i64 *)calloc(LEN, sizeof *x);
	if (n < 0) sig = -1, n = -n;
	do { x[i++] = n%BASE; } while (n /= BASE);
	if (sig == -1) negate(x);
	return x;
}

void norm(i64 *x) {
	int i;
	assert( x );
	for (i = 0; i < LEN-1; ++i)
		if (x[i] >= BASE)
			x[i + 1] += x[i] / BASE, x[i] %= BASE;
}

void add(i64 *x, i64 *y) {
	int i;
	for (i = 0; i < LEN; ++i)
		x[i] += y[i];
	norm(x);
}

void subtr(i64 *x, i64 *y) { negate(y), add(x, y), negate(y); }

void print(i64 *x) {
	int i;
	if (is_neg(x)) {
		putchar('-'), negate(x), print(x), negate(x);
		return;
	}
	for (i = LEN - 1; i >= 0 && !x[i]; --i);
	if (i < 0) {
		putchar('0');
		return;
	}	
	for ( printf("%lld", x[i]); --i >= 0; printf("%0*lld", DIGL,x[i]) );
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
	for (i = 0; i < k / DIGL; ++i) 
		for (j = (i + 1)*DIGL - 1; j >= i*DIGL; --j)
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

/*
 * Works only for non-negatives!
 */
int is_less(i64 *x, i64 *y) {
	int i;
	for (i = 0; i < LEN; ++i)
		if (x[i] < y[i])
			return 1;
	return 0;
}

void zeckendorf(i64 *x) {
	int i, j, k;

	if (is_equal(x,ZERO))
		return;
	for (i = 0, j = N - 1; i + 1 < j;)
		is_less(F[k = (i + j) >> 1], x) ? (i = k) : (j = k);

	if (is_equal(F[j], x)) {
		*++top = j;
		return;
	}
	subtr(x, F[i]);
	zeckendorf(x);
	*++top = i;
}

int main() {
	int i, j, k,n;
	i64 *x;
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	for ( F[0] = ZERO = load(0), F[1] = ONE = load(1), n = 2; n < N; ++n) {
		F[n] = (i64 *)calloc(LEN, sizeof *F[n]);
		for (i = 0; i < LEN; ++i)
			F[n][i] = F[n - 1][i];
		add(F[n], F[n - 2]);
	}
	
	while (gets(s)) {
		for (i = 0; s[i] && isdigit(s[i]); ++i);
		s[i] = '\0';
		x = read_num(s);
		top = st, zeckendorf(x);
		puts(s);
		for (i = 1; i <= top - st; ++i) {
			if (i > 1) putchar(' ');
			printf("%d", st[i]);
		}
		putchar('\n');
		for (i = 1; i <= top - st; ++i) {
			if (i > 1) putchar(' ');
			print(F[st[i]]);
		}
		puts("\n");
	}
	return 0;
}
