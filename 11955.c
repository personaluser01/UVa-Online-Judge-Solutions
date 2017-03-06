/*
 * 11955. Binomial Theorem
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 64
enum { DIGL = 4, BASE = 10000LL, LEN = 0x40 };

char buff[0x400],a[0x400],b[0x400],*ptr;
int ts,cs;
typedef unsigned long long u64;
typedef long long i64;
i64 *C[N][N];

void norm( i64 *x ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		if ( x[i] >= BASE )
			x[i+1] += x[i]/BASE, x[i] %= BASE;
}

void print( i64 *x ) {
	int i;
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) {
		putchar('0');
		return ;
	}
	for ( printf("%lld",x[i]); (--i) >= 0; printf("%0*lld",DIGL,x[i]) );
}

void read_var( char *v ) {
	while ( *ptr && !islower(*ptr)  ) ++ptr;
	while ( *ptr && islower(*ptr) ) *v++ = *ptr++;
	*v = '\0';
}

i64 *add( i64 *x, i64 *y ) {
	int i;
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	for ( i = 0; i < LEN; ++i )
		z[i] = x[i]+y[i];
	norm(z);
	return z;
}

i64 *load( u64 n ) {
	i64 *x = (i64 *)calloc(LEN, sizeof *x);
	int i = 0;
	do { x[i++] = n%BASE; } while ( n /= BASE );
	return x;
}

int equal( i64 *x, i64 *y ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		if ( x[i] != y[i] )
			return 0;
	return 1;
}

i64 *ONE,*Z;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif

	ONE = load(1), Z = load(0);
	for ( i = 0; i < N; ++i ) C[i][0] = ONE;
	for ( i = 1; i < N; ++i )
		C[0][i] = Z;
	for ( i = 0; i < N; ++i )
		for ( j = i+1; j < N; ++j )
			if ( !C[i][j] )
				C[i][j] = Z;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j ) {
			C[i][j] = add(C[i-1][j-1],C[i-1][j]);
		}

	for ( gets(buff), sscanf(buff,"%d",&ts); ts--; ) {
		printf("Case %d: ",++cs);
		gets(buff), ptr = buff;
		read_var(a), read_var(b);
		assert( 1 == sscanf(ptr += 2,"%d",&k) );
		for ( i = k; i >= 0; --i ) {
			if ( i < k ) putchar('+');
			if ( !equal(C[k][i],ONE) )
				print(C[k][i]), putchar('*');
			if ( i > 0 )
				printf("%s",a);
			if ( i > 1 ) printf("^%d",i);
			if ( k-i > 0 && i > 0 )
				putchar('*');
			if ( k-i > 0 )
				printf("%s",b);
			if ( k-i > 1 )
				printf("^%d",k-i);
		}
		putchar('\n');
	}
	return 0;
}

