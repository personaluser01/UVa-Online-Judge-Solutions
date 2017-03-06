/*
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cfloat>
#include <map>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
#define M(k) ((1ULL << (k))-1ULL)
#define N 32
#define tol 1e-9
#define oo (DBL_MAX-1024)
typedef unsigned long long u64;
int rank[N],parent[N],card[N],n,yes,bcc,seen[N];
#define Last(i) ((i)&((~(i))+1))
u64 cnt[N];

int which( unsigned int u ) {
	int i,j,k;
	i = 0, j = 30;
	if ( (1UL << j) == u )
		return j;
	if ( (1 << i) == u )
		return i;
	for(;i+1 != j; (1UL<<(k=(i+j)/2))<u?(i=k):(j=k));
	assert( (1UL << j) == u );
	return j;
}

void make_set( int x ) { card[x] = 1, rank[parent[x] = x] = 0; }
void link( int x, int y ) {
	if ( x == y ) return ;
	if ( rank[x] > rank[y] )
		parent[y] = x, card[x] += card[y];
	else {
		parent[x] = y;
		if ( rank[x] == rank[y] )
			++rank[y];
		card[y] += card[x];
	}
}
int find( int x ) { return parent[x]=(parent[x]==x?x:find(parent[x])); }
void merge( int x, int y ) { link(find(x),find(y)); }

map<unsigned int,long double> z;

long double calc_z( unsigned int u ) {
	unsigned int v,i;
	long double res = 0,
				L = 0;
	if ( z.find(u) != z.end() )
		return z[u];
	if ( u == 0 )
		return z[u] = 0;
	for ( v = u; v; v &= ~Last(v) ) {
		i = which(Last(v));
		res += cnt[i]*calc_z(u & ~Last(v));
		L += cnt[i];
	}
	assert( fabs(L) > tol );
	return z[u] = (n-1)/L + res/L;
}

int main() {
	int i,j,k,ts,cs = 0;
	for ( scanf("%d",&ts); ts-- && ++yes; ) {
		scanf("%d %d",&n,&k);
		for ( i = 0; i < n; make_set(i++) );
		for (;k-- && scanf("%d %d",&i,&j) == 2;)
			if ( find(i-1) != find(j-1) )
				merge(i-1,j-1);
		for ( bcc = 0, i = 0; i < n; ++i )
			if ( find(0) != find(i) )
				if ( seen[find(i)] != yes ) {
					cnt[bcc++] = card[find(i)];
					seen[find(i)] = yes;
				}
		z.clear();
		printf("Case %d: %.8Lf\n",++cs,calc_z(M(bcc)));
	}
	return 0;
}
