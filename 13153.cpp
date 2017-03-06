/*
 * 13153. Number of Connected Components
 * TOPIC: union-find, neat, graphs
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
using namespace std;
typedef unsigned long long u64;
#define BIT(k) (1ULL<<(k))
#define M Q
#define Q (1000002)
#define N (100002)

int m,n,Rank[N],parent[N],c[N],
	repr[M];
long long p[M];
bool isprime[Q],isfather[N];

void make_set( int x ) { Rank[parent[x] = x] = 0; }
void link( int x, int y ) {
	if ( Rank[x] > Rank[y] )
		parent[y] = x;
	else {
		parent[x] = y;
		if ( Rank[x] == Rank[y] )
			++Rank[y];
	}
}
int find( int x ) {
	return parent[x]=(parent[x]==x?x:find(parent[x]));
}
void merge( int x, int y ) {
	link(find(x),find(y));
}

int idx[Q];

int main() {
	int i,j,k,l,cs = 0,ts,ones;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 3; i < Q; i += 2 ) isprime[i] = true ;
	for ( isprime[2] = true, i = 3; i < Q; i += 2 )
		for ( j = i+i; j < Q && isprime[i]; j += i )
			isprime[j] = false ;
	for ( m = 0, i = 0; i < Q; ++i )
		if ( isprime[i] ) ++m;
	for ( k = 0, i = 0; i < Q; ++i )
		if ( isprime[i] ) 
			p[k++] = i;
	for ( i = 0; i < m; ++i )
		idx[p[i]] = i;
	for ( scanf("%d",&ts); ts--; ) {
		set<int> h;
		for ( scanf("%d",&n), ones = i = 0; i < n; ++i ) {
			scanf("%d",&k), h.insert(k);
			if ( k == 1 ) ++ones;
		}
		n = 0;
		for ( set<int>::iterator it = h.begin(); it != h.end(); c[n++] = *it++ );
		for ( i = 0; i < m; repr[i++] = -1 );
		for ( i = 0; i < n; make_set(i++) );
		for ( i = 0; i < n; ++i ) {
			for ( k = c[i], l = 0; l < m && p[l]*p[l] <= k; ++l )
				if ( 0 == (k%p[l]) ) {
					for ( ;0 == (k%p[l]); k /= p[l] );
					if ( repr[l] == -1 ) repr[l] = i;
					else merge(repr[l],i), 0&&printf("merging %d %d\n",c[repr[l]],c[i]);
				}
			if ( k > 1 ) {
				assert( isprime[k] );
				l = idx[k];
				if ( repr[l] == -1 ) repr[l] = i;
				else merge(repr[l],i), 0&&printf("merging %d %d\n",c[repr[l]],c[i]);
			}
		}
		for ( i = 0; i < n; ++i )
			isfather[i] = find(i)==i;
		for ( k = 0, i = 0; i < n; ++i )
			if ( isfather[i] ) ++k;
		printf("Case %d: %d\n",++cs,k+max(0,ones-1));
	}
	return 0;
}

