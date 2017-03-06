/*
 * 10669. Three Powers
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
enum { BASE = 1000000LL, DIGL = 6 };
#define N 128

char s[0x100];
int x[0x100],n;
i64 *P[N];

void print( i64 *x ) {
	int i;
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) {
		putchar('0'); 
		return ;
	}
	for ( printf("%lld",x[i]); --i; printf("%0*lld",DIGL,x[i]) );
}

i64 *mult( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(*x+*y+2,sizeof *z),i,j;
	for ( i = 1; i <= *x; ++i )
		for ( j = 1; j <= *y; ++j )
			z[i+j-1] += x[i]*y[j];
	*z = *x+*y+1;
	for ( i = 1; i <= *z; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( i = *z; i && !z[i]; --i );
	*z = !i ? 1 : i+1;
	return z;
}

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(4, sizeof *x);
	do { x[++(*x)] = n%BASE; } while ( n /= BASE );
	return x;
}

int main() {
	int i,j,k,r,cs,m;
	i64 *three;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( three = load(3), P[0] = load(1), k = 1; k < N; ++k )
		P[k] = mult(P[k-1],three);
	for (;1 == scanf("%s",s) && !(0[s]=='0'&&1[s]=='\0') && putchar('{'); puts(" }") ) {
		n = strlen(s);
		for ( i = 0; i < 4*n; x[i++] = 0 );
		for ( j = 0; j < 4*n; x[j++] = r )
			for ( r = i = 0; i < n; ++i, r = k ) 
				k = (10*r+s[i]-'0')&1, s[i] = ((10*r+s[i]-'0')>>1)+'0';
		for ( k = 4*n-1; k >= 0 && !x[k]; --k );
		for ( i = 0; i <= k && !x[i]; ++i );
		for ( x[i] = 0, j = 0; j < i; x[j++] = 1 );
		for ( m = k; m >= 0 && !x[m]; --m );
		if ( m < 0 ) {
			continue ;
		}
		for ( cs = i = 0; i <= m; ++i ) 
			if ( x[i] ) {
				if ( ++cs > 1 ) putchar(',');
				putchar(' '), print(P[i]);
			}
	}
	return 0;
}
