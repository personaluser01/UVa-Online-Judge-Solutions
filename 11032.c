/*
 * 11032. Function Overloading
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 10000002

int ts,cs,L;
char buff[0x440];
i64 m,n;

typedef struct { int x,y; } cell;

int sod( i64 n ) {
	if ( n <= 9 )
		return n;
	return sod(n/10)+(n%10);
}

unsigned char b[N>>3];
#define SET(a,k) (a[(k)>>3] |= (1U << ((k) & 7)))
#define TST(a,k) (a[(k)>>3] & (1U << ((k) & 7)))
int prefix[N+1],fir[N+1];

i64 g( i64 n ) {	
	return prefix[n];
}

i64 h( i64 n ) {
	int low,high,mid;

	/*
	low = 0, high = L-1;
	assert( c[low].y < n && c[high].y >= n );
	while ( low+1 != high ) {
		mid = (low+high)/2;
		if ( c[mid].y < n )
			low = mid;
		else
			high = mid;
	}
	if ( c[high].y == n && c[high].x <= n )
		return c[high].x;
	return -1;
	*/
	return fir[n];
}

int main() {
	int i,j,k,left,right,low,high,bad,good,mid;
	cell u;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( n = 0; n < N; fir[n++] = -1 );
	for ( k = 0, i = 0; i < N; ++i ) {
		if ( (i % 10) <= 9 &&  (i % 10) >= 1 )
			++k;
		else k = sod(i);
		u.x = i, u.y = k+i;
		if ( !TST(b,u.y) )
			fir[u.y] = i;
		SET(b,u.y);
	}
	/*
	for ( n = 1; n < N; ++n ) {
		low = 0, high = L-1;
		assert( c[low].y < n );
		assert( c[high].y >= n );
		while ( low+1 != high ) {
			mid = (low+high)/2;
			if ( c[mid].y < n )
				low = mid;
			else
				high = mid;
		}
		assert( c[low].y < n );
		assert( c[high].y >= n );
		if ( c[high].y > n ) {
			SET(a,n);
			continue ;
		}
		assert( c[high].y == n );
		assert( c[high].x <= n );
	}
	*/
	for ( n = 1; n < N; ++n )
		if ( !TST(b,n) )
			prefix[n] = prefix[n-1]+1;
		else
			prefix[n] = prefix[n-1];
	for ( scanf("%d\n",&ts); ts-- && printf("Case %d: ",++cs); ) {
		fgets(buff,sizeof(buff),stdin);
		if ( 2 == sscanf(buff,"%lld %lld",&m,&n) ) {
			printf("%lld\n",g(n)-g(m-1));
		}
		else {
			assert( 1 == sscanf(buff,"%lld",&m) );
			printf("%lld\n",h(m));
		}
	}
	return 0;
}

