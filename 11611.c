/*
 * 11611. Colored Tiles
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef unsigned long long u64;
enum { Red, Grey, Blue, Green, Brown, Pink, Black, EMPTY, BROKEN };
#define MOD 50431
#define N 0x10
#define M 0x20
#define C (1 << 10)
#define L(u) ((u)&((~(u))+1UL))
#define MASK(k) ((1UL<<(k))-1UL)
int match( int x, int y ) { return (x==EMPTY)||(x==y); }
#define TST(u,i) ((u) & BIT(i))
#define BIT(i) (1UL<<(i))

char g[0x400][0x400],mp[256],*alp = "RGBNWPL",c[0x400][0x400],who[1 << 16];
unsigned int  mask[16],row[0x400],
			  T = 1, D = 2, B = 4, O = 8,
			  z[25][C],e[1 << 20],*ptr;
int m,n,ts,cs;

void f( const int r, unsigned int u, unsigned int v ) {
	int i,j;
	if ( !u ) {
		/*assert( !(v&(row[r+1]&MASK(n))) );*/
		*ptr++ = v;
		return ;
	}
	i = who[L(u)];
	for ( j = Red; j <= Black; ++j ) {
		if ( j == Green ) {
			assert( TST(u,i) );
			if ( !match(c[i][r],j) ) continue ;
			if ( TST(row[r+1],i+1)||TST(v,i)||TST(v,i+1) )
				continue ;
			if ( !match(c[i][r+1],j)||!match(c[i+1][r+1],j) )
				continue ;
			f(r,u-L(u),v|(3<<i));
			continue ;
		}
		if ( j == Red ) {
			if ( (~u & (3<<i)) )
				continue ;
			if ( TST(row[r],i+1)||!match(c[i][r],j)||!match(c[i+1][r],j) )
				continue ;
			if ( TST(row[r+1],i+1)||TST(v,i+1) ) continue ;
			if ( !match(c[i+1][r+1],j) ) continue ;
			f(r,u-L(u)-L(u-L(u)),v|BIT(i+1));
			continue ;
		}
		if ( j == Blue ) {
			if ( (~u & (3<<i)) )
				continue ;
			if ( TST(row[r],i+1)||!match(c[i][r],j)||!match(c[i+1][r],j) )
				continue ;
			if ( TST(row[r+1],i)||TST(v,i) ) continue ;
			if ( !match(c[i][r+1],j) ) continue ;
			f(r,u-L(u)-L(u-L(u)),v|BIT(i));
			continue ;
		}
		if ( j == Grey ) {
			assert( TST(u,i) );
			if ( !match(c[i][r],j) ) continue ;
			if ( !i||TST(v,i)||TST(v,i-1) )
				continue ;
			if ( !match(c[i-1][r+1],j)||!match(c[i][r+1],j) )
				continue ;
			f(r,u-L(u),v|(3<<(i-1)));
			continue ;
		}
		if ( j == Brown ) {
			if ( ~u & (3<<i) ) continue ;
			if ( TST(row[r],i+1)||!match(c[i][r],j)||!match(c[i+1][r],j) ) continue ;
			f(r,u-L(u)-L(u-L(u)),v);
			continue ;
		}
		if ( j == Pink ) {
			assert( TST(u,i) );
			if ( TST(v,i) ) continue ;
			if ( !match(c[i][r],j)||!match(c[i][r+1],j) ) continue ;
			f(r,u-L(u),v|BIT(i));
			continue ;
		}
		if ( j == Black ) {
			assert( TST(u,i) );
			if ( !match(c[i][r],j) ) continue ;
			f(r,u-L(u),v);
			continue ;
		}
	}
}

int main() {
	int i,j;
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	mp['R']=Red, mp['G']=Grey, mp['B']=Blue, mp['N']=Green, mp['W']=Brown, mp['P']=Pink, mp['L']=Black;
	mp['#'] = BROKEN, mp['.'] = EMPTY;
	for ( i = 0; i < 16; ++i ) who[1 << i] = i;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n); ) {
		for ( i = 0; i < m; scanf("%s",g[i++]) );
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( islower(g[i][j]) )
					g[i][j] = toupper(g[i][j]);
		for ( i = 0; i <= m+1; ++i )
			for ( j = 0; j <= n+1; c[i][j++] = BROKEN );
		for ( i = 0; i < n; ++i ) for ( j = 0; j < m; ++j )
			if ( isupper(g[j][i]) )
				c[j][i] = mp[g[j][i]];
			else if ( g[j][i] == '.' )
				c[j][i] = EMPTY;
		for ( j = 0; j <= n; ++j ) for ( row[j] = BIT(m), i = 0; i <= m; ++i )
			if ( (c[i][j]==BROKEN) && (row[j]|=(1UL<<i)) );
		for ( j = 0; j <= n; ++j ) for ( u = 0; u < (1ul<<m); z[j][u++] = 0 );
		for ( z[0][row[0]&MASK(m)] = 1, i = 0; i < n; ++i ) 
			for ( u = 0; u < (1ul<<m); ++u )
				if ( z[i][u] ) {
					assert( !(~u&(row[i]&MASK(m))) );
					for ( ptr = e, f(i,(~u&MASK(m)),row[i+1]&MASK(m)), j = 0; j < ptr-e; ++j )
						z[i+1][e[j]] += z[i][u], z[i+1][e[j]] %= MOD;
				}
		printf("Case %d: %u\n",++cs,z[n][MASK(m)]);
	}
	return 0;
}

