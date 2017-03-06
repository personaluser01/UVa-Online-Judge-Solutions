/*
 * 1400. Ray, pass me the dishes!
 * TOPIC: interval trees, overloading, algebra, neat
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define N (1<<23)
#define oo (1LL<<59)
typedef long long i64;
using namespace std;

struct cell {
	i64 w;
	int i,j;
	cell() {this->i=N,this->j=-1,this->w=-oo;};
	cell( i64 W, int I, int J ) { this->w=W,this->i=I,this->j=J; };
} ;

bool operator < ( const cell &a, const cell &b ) {
	if ( a.w == b.w ) {
		if ( a.i == b.i ) {
			if ( a.j == b.j ) return false;
			return a.j<b.j;
		}
		return a.i<b.i;
	}
	return a.w>b.w;
}

cell *p[N],*s[N],*t[N],*E = new cell();

cell operator + ( const cell &a, const cell &b ) {
	if ( a.w == -oo || b.w == -oo )
		return *E;
	if ( a.j+1 != b.i ) return b+a;
	assert( a.j+1==b.i );
	cell *r = new cell(a.w+b.w,a.i,b.j);
	return *r;
}

bool cmp( const cell &a, const cell &b ) { return a<b; }

int n;
i64 pref[N],c[N];
i64 sum( int i, int j ) { return pref[j]-pref[i-1]; }
cell SUM( int i, int j ) { return *(new cell(sum(i,j),i,j)); }
cell FSUM( int i, int j, int qi, int qj ) {
	int L = max(qi,i), R = min(qj,j);
	if ( L <= R ) return *(new cell(sum(L,R),L,R));
	return *E;
}

void build( int v, int i, int j ) {
	int left=(v<<1),right=(v<<1)+1,k=(i+j)/2;
	if ( i == j ) {
		p[v] = s[v] = t[v] = new cell(c[i],i,j);
		return ;
	}
	build(left,i,k), build(right,k+1,j);
	t[v] = new cell(), p[v] = new cell(), s[v] = new cell();
	*t[v] = min(min(*t[left],*t[right],cmp),*s[left]+*p[right],cmp);
	*p[v] = min(*p[left],SUM(i,k)+*p[right],cmp);
	*s[v] = min(*s[right],*s[left]+SUM(k+1,j),cmp);
}

cell *qsuffix( int v, int i, int j, int qi, int qj ) {
	int left=(v<<1),right=(v<<1)+1,k=(i+j)/2;
	if ( qi > j || qj < i || qj < j ) return E;
	if ( qi <= i && j <= qj ) return s[v];
	assert( j <= qj );
	cell *r = new cell();
	*r = min(*qsuffix(right,k+1,j,qi,qj),FSUM(k+1,j,qi,qj)+*qsuffix(left,i,k,qi,qj),cmp);
	return r;
}

cell *qprefix( int v, int i, int j, int qi, int qj ) {
	int left=(v<<1),right=(v<<1)+1,k=(i+j)/2;
	if ( qi > j || qj < i || qi > i ) return E;
	if ( qi <= i && j <= qj ) return p[v];
	assert( qi <= i );
	cell *r = new cell();
	*r = min(*qprefix(left,i,k,qi,qj),FSUM(i,k,qi,qj)+*qprefix(right,k+1,j,qi,qj),cmp);
	return r;
}

cell *query_total( int v, int i, int j, int qi, int qj ) {
	int left=(v<<1), right=(v<<1)+1, k = (i+j)/2;
	if ( qi > j || qj < i ) return E;
	if ( qi <= i && j <= qj ) return t[v];
	cell *L = query_total(left,i,k,qi,qj), *R = query_total(right,k+1,j,qi,qj), 
		 M = (*qsuffix(left,i,k,qi,qj)+*qprefix(right,k+1,j,qi,qj)), *r=new cell();
	*r = min(min(*L,*R,cmp),M,cmp);
	return r;
}

int main() {
	int i,j,k,ts = 0,qr;
#ifndef ONLINE_JUDGE
	freopen("b.txt","r",stdin);
#endif
	for ( ;2==scanf("%d %d",&n,&qr) && printf("Case %d:\n",++ts); ) {
		for ( i = 1; i <= n; scanf("%lld",&c[i]), pref[i]=pref[i-1]+c[i], ++i );
		for ( build(1,1,n); qr-- && 2==scanf("%d %d",&i,&j); ) {
			cell *r = query_total(1,1,n,i,j);
			printf("%d %d\n",r->i,r->j);
		}
	}
	return 0;
}

