#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;

char bts[1 << 16];

int dist( int i, int j, int n ) {
	int x,y,k,l;
	assert( i != j );
	for ( k = 0, x = i, y = j; x != y; ++x, x %= n, ++k );
	for ( l = 0, x = i, y = j; x != y; --x, x += n, x %= n, ++l );
	k -= 1, l -= 1;
	if ( k < l ) return k;
	return l;
}

int f( int n, int m, int k, unsigned int u ) {
	int pos[0x400],i,j;
	for ( j = 0, i = 0; i < n; ++i )
		if ( (u>>i) & 1 )
			pos[j++] = i;
	if ( j != k )
		return 0;
	assert( j == k );
	for ( i = 0; i < k; ++i )
		if ( dist(pos[i],pos[(i+1)%k],n) < m )
			return 0;
	return 1;
}

#define N 50
typedef long long i64;
i64 c[N][N],fac[N],acc;

int H( unsigned int u, int n ) {
	int digs[3] = {0};
	for ( int i = 0; i < n; ++i ) {
		++digs[u % 3], u /= 3;
	}
	if ( digs[0] < digs[2] )
		return 1;
	return 0;
}

int is_ascending( unsigned int u ) {
	int d[16],i,j,k;
	for ( i = 0; u; d[i++] = u % 10, u /= 10 );
	for ( j = 0; j < i; ++j )
		for ( k = j+1; k < i; ++k )
			if ( d[k] >= d[j] )
				return 0;
	return 1;
}

int gcd( int x, int y ) {
	if ( !y ) return x;
	return gcd(y, x %y);
}

int main() {
	unsigned int u,v;
	int m,n,k,i,j,ax;

	set<int> s;
	for ( i = 1; i < 999; ++i ) {
		s.insert(i/gcd(i,999));
	}
	printf("%u\n",s.size());
	return 0;

	for ( ax = 0, i = 1; i <= 100; ++i )
		for ( j = i+1; j <= 100; ++j )
			if ( !(((i+j)%4)) ) ++ax;
			else if ( ((j-i)%4) == 2 ) ++ax;
	printf("%d\n",ax);
	return 0;
	ax = 0;
	for ( i = 1; i <= 2310; ++i )
		for ( j = i+1; j <= 2310; ++j )
			for ( k = j+1; k <= 2310; ++k )
				if ( i*j*k == 2310 )
						++ax;
	printf("%d\n",ax);
	return 0;

	for ( i = 0; i < N; c[i++][0] = 1 );
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j] + c[i-1][j-1];
	for ( n = 5; n < 20; ++n )
		for ( m = 1; m <= n; ++m ) {
			printf("m = %d, n = %d, ",m,n);
			for ( acc = 0, k = m; k <= n; ++k )
				if ( (k+m) & 1 )
					acc -= c[n][k]*c[k][m];
				else
					acc += c[n][k]*c[k][m];
			printf("%lld\n",acc);
		}
	return 0;
	fac[0] = 1;
	for ( i64 K = 1; K < N; ++K )
		fac[K] = fac[K-1]*K;
	for ( n = 1; n < 10; ++n ) {
		i64 w = 0;
		for ( k = 1; k <= n; ++k ) {
			i64 ww = 0;
			for ( i = 0; i <= n-k; ++i )
				if ( i & 1 )
					ww -= c[i+k][i]*(fac[n]/fac[i+k]);
				else 
					ww += c[i+k][i]*(fac[n]/fac[i+k]);
			w += k*k*ww;
		}
		printf("%lld %lld\n",w,2*fac[n]);
	}
	for ( u = 0; u < (1 << 16); ++u )
		bts[u] = bts[u>>1]+(u&1);
	n = 12, m = 2, k = 3;
	n = 16, m = 3, k = 4;
	for ( ax = 0, u = 0; u < (1UL << n); ++u )
		if ( bts[u] == k )
			ax += f(n,m,k,u);
	printf("n = %d, m = %d, k = %d, ax = %d\n",n,m,k,ax);
	for ( ax = 0, u = 0; u < (1 << 20); ++u ) {
		for ( k = 0, i = 0; i < 20; ++i )
			if ( (u>>i) & 1 )
				k += i+1;
		if ( !(k % 5) ) ++ax;
	}
	printf("%d %d\n",ax,((1<<20)+(1<<6))/5);

	for ( v = 1, i = 0; i < 6; ++i ) v = v*3;
	for ( ax = 0, u = 0; u < v; ++u ) {
		ax += H(u,6);
	}
	printf("%d\n",ax);
	return 0;
}


