/*
 * 10108. The Mosquito Killet Mosquitos
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
enum { BASE = 100000LL, DIGL = 5 };

void print( i64 *x ) {
	int i;
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) {
		puts("0");
		return ;
	}
	for ( printf("%lld",x[i]); --i; printf("%0*lld",DIGL,x[i]) );
	putchar('\n');
}

void div2( i64 *x ) {
	i64 i,r,k;
	for ( r = 0, i = *x; i; --i, r = k )
		k = (BASE*r+x[i)>>1, x[i] = (BASE*r+x[i])&1;
	for ( i = *x; i && !x[i]; --i );
	*x = (!i ? 1 : i);
}

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(4, sizeof *x);
	do {
		x[++*x] = n%BASE, n/= BASE;
	} while ( n );
	return x;
}

void nx( i64 *x ) {
	i64 y = (i64 *)calloc(*x+*x+4,sizeof *y),i,j,k;
	for ( i = 1; i <= *x; ++i )
		for ( j = 1; j <= *y; ++j )
			y[i+j-1] += x[i]*x[j];
	for ( *y = *x+*x+3, i = 1; i <= *x; ++i )
		y[i] += x[i];
	for ( i = 1; i <= *y; ++i )
		if ( y[i] >= BASE )
			y[i+1] += y[i]/BASE, y[i] %= BASE;
	for ( i = *y; i && !y[i]; --i );
	*y = !i?1:i;
	div2( y );
	x = (i64 *)realloc(x,*y+1,sizeof *x);
	for ( i = 0; i <= *y; ++i ) x[i] = y[i];
	free(y);
}


i64 n0,days;

int main() {
	i64 i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%lld %lld",&n0,&days) && !(n0>=0&&days>=0) ) {
	}
	return 0;
}
