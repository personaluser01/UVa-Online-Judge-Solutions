/*
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
using namespace std;
#define M(k) ((1ULL << (k))-1ULL)
#define N 32
#define tol 1e-9
#define oo (DBL_MAX-1024)

typedef unsigned long long u64;
typedef struct { u64 u[3]; } state;
int rank[N],parent[N],card[N],n,is_dad[N],yes,cc;
u64 cnt[N];

void make_set( int x ) { card[x] = 1, rank[parent[x] = x] = 0; }
void link( int x, int y ) {
	if ( rank[x] > rank[y] )
		parent[y] = x, card[x] += card[y];
	else {
		parent[x] = y;
		if ( rank[x] == rank[y] )
			++rank[y];
		card[y] += card[x];
	}
}
int find( int x ) { return parent[x] = (parent[x]==x?x:find(parent[x])); }
void merge( int x, int y ) { link(find(x),find(y)); }
int F( state &s, int k ) { return (s.u[(k-1)/12] >> (((k-1)%12)*5)) & M(5); }
void dec( state &s, int k ) { 
	u64 x = F(s,k);
	assert( x > 0 );
	s.u[(k-1)/12] &= ~(M(5) << (((k-1)%12)*5));
	s.u[(k-1)/12] |= ((x-1) << (((k-1)%12)*5));
}
int Sum( state &s ) {
	int ax = 0,i;
	for ( i = 1; i <= n; ++i ) ax += F(s,i);
	return ax;
}

bool operator<(const state &a, const state &b ) {
	int i;
	for ( i = 0; i < 3; ++i )
		if ( a.u[i] < b.u[i] )
			return true;
	return false;
}

map<state,int> m;
int V;
long double *z;

int is_nil( state &s ) { return !s.u[0] && !s.u[1] && !s.u[2]; }

long double f( state &s ) {
	long double res,ax,w,L;
	state ns;
	int k;
	if ( m.find(s) == m.end() ) 
		m[s] = V++;
	if ( is_nil(s) ) { return z[m[s]] = 0; }
	if ( z[m[s]] < +oo )
		return z[m[s]];
	ax = Sum(s), res = 1, L = n-1;
	for ( k = 1; k <= n; ++k ) {
		w = F(s,k);
		if ( fabs(w) < tol )
			continue ;
		ns = s, dec(ns,k);
		res += (w*k*f(ns))/(n-1);
		L -= w*k;
	}
	return z[m[s]] = res/(1-L/(n-1));
}

int main() {
	int i,j,k,ts,cs = 0;
	state s;
	for ( scanf("%d",&ts); ts-- && ++yes; ) {
		scanf("%d %d",&n,&k);
		for ( i = 0; i < n; make_set(i++) );
		for (;k-- && scanf("%d %d",&i,&j) == 2; merge(i-1,j-1) );
		memset(cnt,0,sizeof(cnt));
		for ( i = 0; i < n; ++i )
			is_dad[i] = (find(i) == i);
		for ( i = 0; i <= n; ++i )
			if ( is_dad[i] && find(0) != find(i) && ++cc )
				++cnt[card[i]];
		for ( memset(s.u,0,sizeof(s.u)), i = 1; i <= n; ++i ) 
			s.u[(i-1)/12] |= (cnt[i]<<(((i-1)%12)*5));
		/*
		assert( cc <= 21 );
		*/
		z = (long double *)calloc((1 << cc),sizeof *z);
		for ( i = 0; i < (1 << cc); ++i ) z[i] = +oo;
		m.clear(), V = 0;
		printf("%Lf\n",f(s));
	}
	return 0;
}
