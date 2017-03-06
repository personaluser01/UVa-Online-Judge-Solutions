/*
 * 10149. Yahtzee
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define N 16
#include <string.h>

int n = 5,w[N][N],m[1 << 13],hand[16],b[1 << 13];
unsigned int z[1 << 13],
			 bon[1 << 13];

void printout( unsigned int u, int len ) {
	if ( len ) {
		printout(u>>1,len-1);
		putchar((u&1)+'0');
	}
}

int sum_of( int *c, int t ) {
	int i,ax = 0;
	for ( i = 0; i < n; ++i )
		if ( c[i] == t )
			ax += c[i];
	return ax;
}

int sum_all( int *c ) {
	int i,ax = 0;
	for ( i = 0; i < n; ++i )
		ax += c[i];
	return ax;
}

int of_a_kind( int *c, int t ) {
	int i,ax = 0,b[7];
	memset(b,0,sizeof(b));
	for ( i = 0; i < n; ++b[c[i++]] );
	for ( i = 1; i <= 6; ++i )
		if ( b[i] >= t ) 
			return sum_all(c);
	return 0;
}

int five_of_a_kind( int *c, int t ) {
	int i,ax = 0,b[7];
	memset(b,0,sizeof(b));
	for ( i = 0; i < n; ++b[c[i++]] );
	for ( i = 1; i <= 6; ++i )
		if ( b[i] >= n ) 
			return 50;
	return 0;
}

int short_straight( int *c ) {
	int i,ax = 0,is[7];
	memset(is,0,sizeof(is));
	for ( i = 0; i < n; is[c[i++]] = 1 );
	if ( is[1] && is[2] && is[3] && is[4] )
		return 25;
	if ( is[2] && is[3] && is[4] && is[5] )
		return 25;
	if ( is[3] && is[4] && is[5] && is[6] )
		return 25;
	return 0;
}

int long_straight( int *c ) {
	int i,ax = 0,is[7];
	memset(is,0,sizeof(is));
	for (  i = 0; i < n; is[c[i++]] = 1 );
	if ( is[1] && is[2] && is[3] && is[4] && is[5] ) 
		return 35;
	if ( is[2] && is[3] && is[4] && is[5] && is[6] ) 
		return 35;
	return 0;
}

int full_house( int *c ) {
	int i,j,ax = 0,b[7] = {0},is[7] = {0};
	for ( i = 0; i < n; is[c[i++]] = 1 );
	for ( i = 0; i < n; ++b[c[i++]] );
	for ( i = 1; i <= 6; ++i )
		for ( j = i+1; j <= 6; ++j ) {
			if ( b[i] == 2 && b[j] == 3 )
				return 40;
			if ( b[j] == 2 && b[i] == 3 )
				return 40;
		}
	return 0;
}

int read_throw( int *c ) {
	int i;
	for ( i = 0; i < n; ++i )
		if ( scanf("%d",c+i) != 1 )
			return 0;
	return 1;
}

unsigned int 
bonus( unsigned int u ) {
	unsigned int ax = 0,v,j,k,i = b[u];
	if ( i < 6 )
		return 0;
	if ( i > 6 )
		return bonus(u&(~(1UL<<m[u])));
	assert( i == 6 );
	assert( b[u] == 6 );
	for ( v = u, k = i; k; --k ) {
		if ( m[v] < 0 ) {
			printout(u,13);
			puts("");
			printout(v,13);
			puts("");
			while ( 1 );
		}
		assert( m[v] >= 0 );
		assert( (v>>m[v]) & 1 );
		ax += w[m[v]][k];
		v &= (~(1UL<<m[v]));
	}
	assert( v == 0 );
	if ( ax >= 63 )
		return 35;
	return 0;
}

void dump( unsigned int u ) {
	if ( u ) {
		assert( m[u] >= 0 );
		dump(u&~(1UL<<m[u]));
		hand[b[u]] = w[m[u]][b[u]];
	}
}

int main() {
	int i,j,k,c[N][N];
	unsigned int ww,tmp,u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( u = 1; u < (1 << 13); ++u )
		b[u] = b[u>>1]+(u&1);
	while ( read_throw(c[0]) ) {
		for ( i = 1; i < 13; read_throw(c[i++]) );
		memset(w,0,sizeof(w));
		for ( i = 0; i < 13; ++i ) {
			for ( j = 1; j <= 6; ++j )
				w[i][j] = sum_of(c[i],j);
			w[i][7] = sum_all(c[i]);
			w[i][8] = of_a_kind(c[i],3);
			w[i][9] = of_a_kind(c[i],4);
			w[i][10] = five_of_a_kind(c[i],5);
			w[i][11] = short_straight(c[i]);
			w[i][12] = long_straight(c[i]);
			w[i][13] = full_house(c[i]);
		}
		for ( u = 0; u < (1ul << 13); ++u ) 	
				for ( bon[u] = 0, z[u] = 0, m[u] = -1, i = b[u], j = 0; j < 13; ++j )
					if ( (u >> j) & 1ul ) {
						k = m[u], m[u] = j;
						tmp = bon[u], bon[u] = bonus(u);
						ww = z[u&(~(1ul<<j))]+w[j][i]+bon[u];
						if ( ww < bon[u&~(1ul<<j)] ) {
							m[u] = k, bon[u] = tmp;
							continue ;
						}
						ww -= bon[u&(~(1ul<<j))];
						if ( z[u] <= ww )
							z[u] = ww;
						else m[u] = k, bon[u] = tmp;
					}
		u = (1ul << 13)-1ul;
		assert( b[u] == 13 );
		dump(u);
		for ( i = 1; i <= 13; ++i )
			printf("%d ",hand[i]);
		printf("%u %u\n",bon[u],z[u]);
	}
	return 0;
}

