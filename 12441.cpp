/*
 * 12441. Superb Sequence
 * TOPIC: DP, greedy, tricky, nontrivial
 * status: Accepted
 */
#include <iostream>
#include <map>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 0x80
#define N (302)
#define MOD 1000000007LL
#define oo (1LL<<50)
#define INF (1<<29)
#include <vector>
typedef long long i64;
using namespace std;

i64 min( i64 x, i64 y ) { return x<y?x:y; }

int p,q,r,z[M][M][N],e[M][M][N];
char a[N],b[N],c[N],*ptr,out[1<<21];
i64 ways[M][M][N];
map<char,vector<int> > m;

int calc_z( int i, int j, int k ) {

	assert( i >= 0 && j >= 0 && k >= 0 );

	if ( z[i][j][k] < INF )
		return z[i][j][k];

	if ( i == 0 && j == 0 ) 
		return z[i][j][k] = 0;

	if ( k == 0 && (i >= 1 || j >= 1) ) 
		return z[i][j][k] = INF/2;

	if ( i == 0 && j >= 1 && k >= 1 ) {
		if ( b[j] == c[k] ) 
			return z[i][j][k] = min(1+calc_z(i,j-1,k-1),calc_z(i,j,k-1));
		return z[i][j][k] = calc_z(i,j,k-1);
	}
	if ( i >= 1 && j == 0 && k >= 1 ) {
		if ( a[i] == c[k] ) 
			return z[i][j][k] = min(1+calc_z(i-1,j,k-1),calc_z(i,j,k-1));
		return z[i][j][k] = calc_z(i,j,k-1);
	}

	assert( i >= 1 && j >= 1 && k >= 1 );
	if ( a[i] == b[j] && b[j] == c[k] ) 
		return z[i][j][k] = min(calc_z(i,j,k-1),1+calc_z(i-1,j-1,k-1));

	if ( a[i] == b[j] && a[i] != c[k] ) 
		return z[i][j][k] = calc_z(i,j,k-1);

	if ( a[i] != b[j] && a[i] == c[k] ) 
		return z[i][j][k] = min(calc_z(i,j,k-1),1+calc_z(i-1,j,k-1));

	if ( a[i] != b[j] && b[j] == c[k] ) 
		return z[i][j][k] = min(calc_z(i,j,k-1),1+calc_z(i,j-1,k-1));

	assert( a[i] != b[j] && b[j] != c[k] && a[i] != c[k] );
	return z[i][j][k] = calc_z(i,j,k-1);
}

int bs( vector<int> &v, int key ) {
	int i,j,k;
	if ( v[0] > key ) return 0;
	if ( v[v.size()-1] <= key ) return v[v.size()-1];
	for ( i = 0, j = v.size()-1; i+1<j; v[k=(i+j)/2] <= key?(i=k):(j=k) );
	return v[i];
}

int f( int i, int j, int k, int len ) {
	int t;
	if ( i == 0 && j == 0 )
		return len == 0;
	if ( calc_z(i,j,k) > len ) return 0;
	assert( calc_z(i,j,k) == len );
	assert( i >= 1 || j >= 1 );
	assert( k >= i && k >= j );
	if ( i == 0 ) {
		// for ( t = k; t >= 1 && c[t] != b[j]; --t );
		t = bs(m[b[j]],k);
		assert( t >= 1 );
		*ptr++ = b[j];
		assert( f(i,j-1,t-1,len-1) );
		return 1;
	}
	if ( j == 0 ) {
		// for ( t = k; t >= 1 && c[t] != a[i]; --t );
		t = bs(m[a[i]],k);
		assert( t >= 1 );
		*ptr++ = a[i];
		assert( f(i-1,j,t-1,len-1) );
		return 1;
	}
	assert( i >= 1 && j >= 1 );
	if ( a[i] == b[j] ) {
		// for ( t = k; t >= 1 && c[t] != a[i]; --t );
		t = bs(m[a[i]],k);
		assert( t >= 1 );
		*ptr++ = a[i];
		if ( f(i-1,j-1,t-1,len-1) ) return 1;
		--ptr, *ptr++ = a[i];
		if ( f(i-1,j,t-1,len-1) ) return 1;
		--ptr, *ptr++ = b[j];
		if ( f(i,j-1,t-1,len-1) ) return 1;
		--ptr;
	}
	if ( a[i] < b[j] ) {
		// for ( t = k; t >= 1 && c[t] != a[i]; --t );
		t = bs(m[a[i]],k);
		assert( t >= 1 );
		*ptr++ = a[i];
		if ( f(i-1,j,t-1,len-1) ) return 1;
		--ptr;
	}
	//for ( t = k; t >= 1 && c[t] != b[j]; --t );
	t = bs(m[b[j]],k);
	assert( t >= 1 );
	*ptr++ = b[j];
	if ( f(i,j-1,t-1,len-1) ) return 1;
	--ptr;
	if ( a[i] > b[j] ) {
		// for ( t = k; t >= 1 && c[t] != a[i]; --t );
		t = bs(m[a[i]],k);
		assert( t >= 1 );
		*ptr++ = a[i];
		if ( f(i-1,j,t-1,len-1) ) return 1;
		--ptr;
	}
	return 0;
}

i64 w( int i, int j, int k, int len ) {
	int t,l;

	if ( calc_z(i,j,k) > len )
		return ways[i][j][k] = 0;

	assert( calc_z(i,j,k) == len );

	if ( ways[i][j][k] < +oo )
		return ways[i][j][k];

	if ( i == 0 && j == 0 ) {
		if ( len == 0 )
			return ways[i][j][k] = 1;
		return ways[i][j][k] = 0;
	}
	if ( i == 0 || j == 0 ) {
		assert( k >= i && k >= j );
		assert( i || j );
		return ways[i][j][k] = 1;
	}
	assert( i >= 1 && j >= 1 );
	//if ( a[i] != c[k] && b[j] != c[k] )
	//	return ways[i][j][k] = w(i,j,k-1,len);
	ways[i][j][k] = 0;
	if ( a[i] == b[j] ) {
		//for ( t = k; t >= 1 && c[t] != a[i]; --t );
		t = bs(m[a[i]],k);
		assert( t >= 1 );
		assert( calc_z(i-1,j-1,t-1)+1 == len );
		ways[i][j][k] += w(i-1,j-1,t-1,len-1), ways[i][j][k] %= MOD;
		/*
		if ( calc_z(i-1,j-1,t-1)+1 != len ) {
			assert( 0 );
			if ( calc_z(i-1,j,t-1)+1 == len )
				ways[i][j][k] += w(i-1,j,t-1,len-1), ways[i][j][k] %= MOD;
			else if ( calc_z(i,j-1,t-1)+1 == len )
				ways[i][j][k] += w(i,j-1,t-1,len-1), ways[i][j][k] %= MOD;
		}
		*/
		/*ways[i][j][k] += w(i-1,j,t-1,len-1), ways[i][j][k] %= MOD;
		ways[i][j][k] += w(i,j-1,t-1,len-1), ways[i][j][k] %= MOD;*/
		return ways[i][j][k];
	}
	assert( a[i] != b[j] );
	t = bs(m[a[i]],k), l = bs(m[b[j]],k);
	if ( calc_z(i-1,j,t-1) <= calc_z(i,j-1,l-1) ) {
		//for ( t = k; t >= 1 && c[t] != a[i]; --t );
		assert( t >= 1 );
		ways[i][j][k] += w(i-1,j,t-1,len-1), ways[i][j][k] %= MOD;
	}
	if ( calc_z(i,j-1,l-1) <= calc_z(i-1,j,t-1) ) {
		//for ( t = k; t >= 1 && c[t] != b[j]; --t );
		assert( t >= 1 );
		ways[i][j][k] += w(i,j-1,l-1,len-1), ways[i][j][k] %= MOD;
	}
	return ways[i][j][k];
}

int main() {
	int i,j,k,cs = 0,ts,len;
#ifndef ONLINE_JUDGE
	freopen("12441.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case %d: ",++cs); ) {
		scanf("%s %s %s",a+1,b+1,c+1), p = strlen(a+1), q = strlen(b+1), r = strlen(c+1), m.clear();
		for ( i = 1, j = p; i < j; ++i, --j )
			k = a[i], a[i] = a[j], a[j] = k;
		for ( i = 1, j = q; i < j; ++i, --j )
			k = b[i], b[i] = b[j], b[j] = k;
		for ( i = 1, j = r; i < j; ++i, --j )
			k = c[i], c[i] = c[j], c[j] = k;
		for ( i = 1; i <= p; ++i )
			if ( m.find(a[i]) == m.end() )
				m[a[i]] = vector<int>();
		for ( i = 1; i <= q; ++i )
			if ( m.find(b[i]) == m.end() )
				m[b[i]] = vector<int>();
		for ( i = 1; i <= r; ++i )
			if ( m.find(c[i]) != m.end() )
				m[c[i]].push_back(i);
		for ( i = 0; i <= p; ++i )
			for ( j = 0; j <= q; ++j )
				for ( k = 0; k <= r; ++k )
					e[i][j][k] = z[i][j][k] = INF, ways[i][j][k] = +oo;
		if ( (len = calc_z(p,q,r)) < INF/2 ) {
			printf("%lld\n",w(p,q,r,len));
			ptr = out;
			assert( f(p,q,r,len) );
			*ptr = '\0', puts(out);
		}
		else puts("0\nNOT FOUND");
	}
	return 0;
}

