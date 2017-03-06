/*
 * 10261. Ferry Loading
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define M 100008

int L,c[N],n,total,m,a[N][M],yes,idx[N];
unsigned char z[2][M>>3];
#define SET(t,k) (z[t][(k)>>3]|=(1UL<<((k)&7)))
#define CLR(t,k) (z[t][(k)>>3]&=~(1UL<<((k)&7)))
#define TST(t,k) (z[t][(k)>>3]&(1UL<<((k)&7)))

void dump( int w, int k ) {
	if ( !w ) { return ; }
	assert( a[k][w] == yes );
	for (;k && (c[k-1]>w||a[k-1][w-c[k-1]]!=yes); --k );
	assert( k );
	assert( c[k-1] <= w && a[k-1][w-c[k-1]] == yes );
	idx[k-1] = yes, dump(w-c[k-1],k-1);
}

int main() {
	int i,j,k,ts,w,T,left,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d",&L);) {
		for ( L = 100*L, total = n = 0; 1 == scanf("%d",c+n) && c[n]; total += c[n++] );
		for (;n&&total>2*L;total-=c[--n]);
		if ( !n ) goto nx;
		for ( t = 0; t <= 1; ++t )
			for ( k = 0; k <= total; ++k )
				CLR(t,k);
		for ( w = 0, T = 0, t=0, SET(t,0), i=0; i<n; ++i ) {
			t ^= 1, memcpy(z[t],z[t^1],sizeof z[t]), T += c[i];
			for ( k = 0; k+c[i] <= T; ++k )
				if (TST(t^1,k)) SET(t,k+c[i]);
			for ( k = 0; k <= T && k <= L; ++k )
				if ( TST(t,k) ) {
					assert( TST(t,T-k) );
					if ( T-k <= L )
						w = T, left = k, m = i+1;
				}
		}
		if ( !w ) goto nx;
		for ( a[0][0] = ++yes, i = 0; i < m; ++i ) {
			for ( k = 0; k <= w; ++k )
				a[i+1][k] = a[i][k];
			for ( k = 0; k+c[i] <= w; ++k )
				if ( a[i][k] == yes )
					a[i+1][k+c[i]] = yes;
		}
		assert( a[m][left] == yes );
		printf("%d\n",m);
		dump(left,m);
		for ( i = 0; i < m; ++i ) 
			puts(idx[i]!=yes?"port":"starboard");
		if ( ts ) putchar('\n');
		continue ;
		nx: puts("0");
			if ( ts ) putchar('\n');
	}
	return 0;
}
