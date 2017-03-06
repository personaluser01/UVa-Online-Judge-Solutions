/*
 * 13022. Sheldon Numbers
 * TOPIC: number theory. maths, binary search, bit operations
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef unsigned long long u64;
typedef long long i64;

u64 a,b;
set<u64> s;

u64 g( int n ) {
	u64 u = 0;
	for ( int i = 0; i < n; ++i )
		u |= (1ULL<<i);
	return u;
}

u64 f( int p, int m, int n, int k ) {
	u64 res = 0, msk = g(n);
	for ( int l = 0; l < k; ++l ) 
		res |= (msk<<(l*(m+n)));
	return res|(g(p)<<(k*(m+n)));
}

u64 h( int p, int m, int n, int k, int q ) {
	u64 res = 0, msk = g(n);
	for ( int l = 0; l < k; res|=(msk<<(q+l*(m+n))), ++l );
	return res|(g(p)<<(q+k*(m+n)));
}

vector<u64> v;

int main() {
	i64 i,j,k,m,n,low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("13022.in","r",stdin);
#endif
	for ( n = 1; n <= 63; ++n )
		for ( m = 0; m <= 63-n; ++m )
			for ( k = 0; n+k*(m+n) <= 63; ++k )
				s.insert(f(n,m,n,k));
	for ( n = 1; n <= 63; ++n )
		for ( m = 0; m <= 63-n; ++m )
			for ( k = 0; n+k*(m+n)+m <= 63; ++k )
				s.insert(h(n,m,n,k,m));
	for ( set<u64>::iterator it = s.begin(); it != s.end(); ++it )
		v.push_back(*it);
	n = v.size();
	for ( ;2 == scanf("%llu %llu",&a,&b) && (1||(a||b)); ) {
		if ( a > v[n-1] || b < v[0] ) { puts("0"); continue ; }
		if ( v[0] > a ) low = 0;
		else {
			assert( v[0] <= a );
			if ( a == v[n-1] ) {
				puts("1");
				continue ;
			}
			assert( a < v[n-1] );
			for ( low = 0, high = n-1; low+1 < high; ) {
				mid = (low+high)/2;
				if ( v[mid] <= a ) low = mid;
				else high = mid;
			}
		}
		if ( v[low] < a ) ++low;
		i = low;
		assert( i == 0 || v[i-1] < a && v[i] >= a );

		if ( v[n-1] <= b ) low = n-1;
		else {
			assert( v[n-1] > b );
			assert( b >= v[0] );
			for ( low = 0, high = n-1; low+1 < high; ) {
				mid = (low+high)/2;
				if ( v[mid] <= b ) low = mid;
				else high = mid;
			}
		}
		j = low;
		printf("%d\n",j-i+1);
	}
	return 0;
}

