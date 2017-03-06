/*
 * 1630. Folding
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define oo 0xfffffffful

int n;
unsigned int z[N][N],p[N][N];
char s[N],digl[N];

int is_period( int left, int right, int k ) {
	int i,j;
	for ( i = left; i <= left+k-1; ++i ) {
		for ( j = i+k; j <= right && s[i] == s[j]; j += k );
		if ( j <= right ) return 0;
	}
	return 1;
}

void dump( int i, int j ) {
	int d;
	assert( i <= j );
	if ( i == j ) {
		putchar(s[i]);
		return ;
	}
	if ( p[i][j] == +oo ) {
		for ( d = i; d <= j; putchar(s[d++]) );
		return ;
	}
	if ( 1&p[i][j] ) {
		d = p[i][j]>>1;
		printf("%d(",(j-i+1)/d), dump(i,i+d-1), putchar(')');
		return ;
	}
	dump(i,p[i][j]>>1), dump((p[i][j]>>1)+1,j);
}

int main() {
	int i,j,k,t,d;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i <= 9; digl[i++] = 1 );
	for ( i = 10; i <= 99; digl[i++] = 2 );
	for ( i = 100; i < N; digl[i++] = 3 );
	for (;fgets(s,sizeof s,stdin); ) {
		for ( n = 0; s[n] && s[n] != '\n'; ++n );
		memset(z,0xff,sizeof z);
		for ( i = 0; i < n; z[i][i] = 1ULL, ++i );
		for ( k = 2; k <= n; ++k )
			for ( i = 0; (j=i+k-1) < n; ++i ) {
				for ( t = i; t <= j-1; ++t )
					if ( z[i][t]+z[t+1][j]<z[i][j] )
						z[i][j]=z[i][t]+z[t+1][j], p[i][j]=(0|(t<<1));
				for ( d = 1; d <= k-1; ++d )
					if ( 0 == (k%d) && is_period(i,j,d) )
						if ( digl[k/d]+2+z[i][i+d-1] < z[i][j] )
							z[i][j] = digl[k/d]+2+z[i][i+d-1], p[i][j] = (1|(d<<1));
				if ( k < z[i][j] ) z[i][j] = k, p[i][j] = +oo;
			}
		dump(0,n-1), putchar('\n');
	}
	return 0;
}

