/*
 * 10238. Throw the Dice
 * status: Accepted
 * KEYWORDS: Long integer, DP, Probability
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 51
#define S 4001
#define xchg(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
enum { BASE = 1000000000000LL, DIGL = 12, LEN = 11 };
typedef long long i64;
#define DBG(x) (x)

i64 max( i64 x, i64 y ) {
	if ( x < y ) return y;
	return x;
}

i64 T[LEN];

void add( i64 *x, i64 *y ) {
	int i,j;
	for ( i = 0; i < LEN; ++i ) T[i] = 0;
	for ( i = 1; i <= *x && i <= *y; ++i )
		T[i] = x[i]+y[i];
	for ( ;i <= *x; T[i] += x[i], ++i );
	for ( ;i <= *y; T[i] += y[i], ++i );
	for ( *T = max(*x,*y)+1, T[*T+1] = T[*T+2] = 0, i = 1; i <= *T; ++i )
		if ( T[i] >= BASE )
			T[i+1] += T[i]/BASE, T[i] %= BASE;
	for ( i = *T; i && !T[i]; --i );
	if ( !i ) *T = 1;
	else *T = i;
	for ( i = 0; i < LEN; ++i )
		x[i] = T[i];
}

void print( i64 *x ) {
	int i;
	for ( i = *x; i > 0 && !x[i]; --i );
	if ( !i ) {
		putchar('0');
		return ;
	}
	for(printf("%lld",x[i]);--i;printf("%0*lld",DIGL,x[i]));
}

int n,F,score;
i64 *z[2][S];

i64 *load( i64 u ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	int k = 0,i,j;
	for(;u; z[++k] = u % BASE, u /= BASE );
	*z = k;
	if ( !k ) *z = 1;
	return z;
}

void mult( i64 *x, i64 *y ) {
	i64 z[LEN] = {0};
	int i,j,k;
	for ( i = 1; i <= *x; ++i )
		for ( j = 1; j <= *y; ++j )
			z[i+j-1] += x[i]*y[j];
	for ( *z = *x+*y+2, i = 1; i <= *z; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( i = *z; i && !z[i]; --i );
	if ( !i ) *z = 1;
	else *z = i;
	for ( i = 0; i < LEN; ++i )
		x[i] = z[i];
}

i64 *f( int F, int n ) {
	i64 *ax = load(1),
		*x  = load(F),i;
	for ( i = 0; i < n; ++i )
		mult(ax,x);
	return ax;
}

void load2( i64 *x, int u ) {
	int i;
	assert( u >= 0 );
	for ( i = 0; i < LEN; x[i++] = 0 );
	for( i = 0; u; x[++i] = u % BASE, u /= BASE );
	if ( !i ) *x = 1;
	else 	  *x = i;
}

int main() {
	int i,j,k,t;
	i64 *m,*ax;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( t = 0; t <= 1; ++t )
		for ( k = 0; k < S; ++k ) 
			assert( z[t][k] = (i64 *)calloc(LEN, sizeof *z[t][k]) );
	for (;3==scanf("%d %d %d",&F,&n,&score);) {
		if ( n > score || F*n < score ) {
			printf("0/");
			goto nx;
		}
		k = (F+1)*n-score;
		if ( k < score ) score = k;
		for ( t = 0, load2(z[t][0],1), k = 1; k <= score; load2(z[t][k++],0) );
		for ( i = 1; i <= n; ++i )
			for ( t ^= 1, j = 0; j <= score; ++j ) 
				for ( load2(z[t][j],0), k = 1; k <= F && k <= j; ++k )
					add(z[t][j],z[t^1][j-k]);
		print(z[t][score]);
		putchar('/');
		nx: print(ax = f(F,n));
		free(ax);
		puts("");
	}
	return 0;
}

