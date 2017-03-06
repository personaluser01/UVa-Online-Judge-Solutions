/*
 * 129. Krypton Factor
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 32
typedef long long i64;
#define Q (1 << 13)

int n,L,last_seen[32][Q],ptr[32],idx,ts;
i64 prefix_hash[5][Q],
	p[5] = { 2551, 3769, 3557, 4481, 353 },deg[5][Q],
	ip[5], M = (1LL << 31)-1,
	mypow[5][Q];
char c[Q];

void ext_euclid( i64 *a, i64 *b, i64 x, i64 y, i64 *d ) {
	if ( !y ) *a = 1, *b = 0, *d = x;
	else ext_euclid(b,a,y,x%y,d), *b -= *a*(x/y);
}

i64 inv( i64 p, i64 m ) {
	i64 x,y,d;
	ext_euclid(&x,&y,p,m,&d);
	if ( d < 0 )
		x = -x, y = -y, d = -d;
	assert( d == 1 );
	assert( x*p + y*m == 1 );
	while ( x < 0 ) x += m;
	return x%m;
}

int indeed_equal( int i, int j, int ii, int jj ) {
	int k,kk;
	assert( i <= j );
	assert( ii <= jj );
	assert( i-j == ii-jj );
	for ( k = i, kk = ii; k <= j;)
		if ( c[k++] != c[kk++] )
			return 0;
	return 1;
}

i64 hash( int i, int j, int k ) {
	i64 d = prefix_hash[k][j]-prefix_hash[k][i-1];
	while ( d < 0 ) d += M;
	d %= M, d *= mypow[k][i];
	return d % M;
}

int equal( int i, int j, int ii, int jj ) {
	int k;
	if ( i <= 0 || ii <= 0 )
		return 0;
	assert( i <= j );
	assert( ii <= jj );
	for ( k = 0; k < 5; ++k )
		if ( hash(i,j,k) == hash(ii,jj,k) )
			return indeed_equal(i,j,ii,jj);
	return 0;
}

int ok( int x, int cur ) {
	int i,j,len;
	for ( i = 0; i < ptr[x]; ++i ) {
		j = last_seen[x][i];
		len = cur-j;
		if ( equal(j+1,cur-1,j-len+1,j-1) )
			return 0;
	}
	return 1;
}

int dfs( int x, int cur ) {
	int i,j,len,y;

	if ( idx == n )
		return 1;

	for ( y = 0; y < L; ++y ) {
		if ( y == x ) continue ;
		if ( ok(y,cur) ) {
			last_seen[y][ptr[y]++] = cur, c[cur] = y+'A', c[cur+1] = '\0', ++idx;
			for ( j = 0; j < 5; ++j )
				prefix_hash[j][cur] = prefix_hash[j][cur-1]+((i64)(y+1))*deg[j][cur-1];
			if ( dfs(y,cur+1) )
				return 1;
			--ptr[y];
		}
	}
	return 0;
}

int something_to_print( char *c, int i, int j ) {
	int k;
	for ( k = i; k < j; ++k )
		if ( c[k] != '#' )
			return 1;
	return 0;
}

void printout( char *c ) {
	int len = strlen(c),ans = len,
		blocks,i,j,k,chunks = len/4,
		rem = len & 3,
		first_in_line = 1;

	/*if ( ts++ ) putchar('\n');*/

	if ( rem )
		for ( k = 4-rem, i = len, len = (++chunks)*4 ; k--; c[i++] = '#' );
	for ( i = 0; i < chunks; ++i ) {
		if ( !first_in_line && something_to_print(c,i*4,(i+1)*4) )
			putchar(' ');
		for ( j = i*4; j < (i+1)*4 && j < len; ++j )
			if ( c[j] != '#' ) putchar(c[j]);
		first_in_line = 0;
		if ( ++blocks == 16 ) {
			first_in_line = 1, blocks = 0;
			putchar('\n');
		}
	}
	len = ans;
	if ( first_in_line )
		printf("%d\n",len);
	else printf("\n%d\n",len);
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < 5; ++i ) {
		ip[i] = inv(p[i],M);
		/*printf("The inverse of %lld is %lld\n",p[i],ip[i]);*/
		for ( mypow[i][0] = deg[i][0] = 1, j = 1; j < Q; ++j ) {
			mypow[i][j] = mypow[i][j-1]*ip[i], mypow[i][j] %= M;
			deg[i][j] = deg[i][j-1]*p[i], deg[i][j] %= M;
		}
	}
	while ( 2 == scanf("%d %d",&n,&L) && (n||L) ) {
		idx = 0, memset(ptr,0,sizeof(ptr));
		memset(c,'\0',sizeof(c));
		if ( !dfs(-1,1) )
			puts("\n0");
		else
			printout(c+1);
	}
	return 0;
}

