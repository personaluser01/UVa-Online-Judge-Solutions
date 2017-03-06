/*
 * 1252. Twenty Questions
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
#define N 12
#define oo 0xfffful
#define  BIT(k)   (1UL << (k))
#define  MASK(k)  (BIT(k)-1UL)

unsigned int min( unsigned int x, unsigned int y ) { return x<y?x:y; }

int m,n,b[1<<N];
char s[1<<N][N+2];
unsigned int u[1<<N];
unsigned short z[1 << 11][1 << 11];
unsigned short profile[1 << 11][1 << 11];

unsigned short
calc_z( unsigned int asked, unsigned int asked_values ) {
	int i;
	unsigned int v,w,ret = (1UL<<m)-1;
	if ( z[asked][asked_values] < +oo )
		return z[asked][asked_values];
	if ( profile[asked][asked_values] <= 1 )
		return z[asked][asked_values]=0;
	for ( i = 0; i < m; ++i )
		if ( !((asked>>i)&1UL) ) {
			v = (1<<i)|calc_z(asked|(1<<i),asked_values       );
			w = (1<<i)|calc_z(asked|(1<<i),asked_values|(1<<i));
			if ( b[v] > b[w] )
				w = v;
			else v = w;
			if ( b[w] < b[ret] )
				ret = w;
		}
	return z[asked][asked_values] = ret;
}

int main() {
	int i,j,k;
	unsigned int v,w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( v = 0; v < (1 << N); ++v )
		b[v] = b[v>>1]+(v&1);
	while ( 2 == scanf("%d %d",&m,&n) && (m||n) ) {
		assert( n<=(1<<m) );
		for ( i = 0; i < n; ++i )
			for ( scanf("%s",s[i]), u[i]=0, j = 0; j < m; ++j )
				if(s[i][j]=='1')
					u[i]|=(1UL<<j);
		memset(z,0xfful,sizeof(z));
		memset(profile,0,sizeof(profile));
		for ( v = 0; v < (1UL << m); ++v )
			for ( i = 0; i < n; ++i )
				++profile[v][u[i]&v];
		printf("%d\n",b[calc_z(0,0)]);
	}
	return 0;
}

