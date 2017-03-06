/*
 * 11930. Rectangles
 * TOPIC: scc, 2-sat
 * status: Accepted
 */
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define var(i) ((i)<<1)
#define neg(i) (var(i)|1)
typedef long long i64;
struct cell { i64 x,y; cell() {}; cell( i64 a, i64 b ) {x=a,y=b;} };
#define MAXE (1<<19)
#define N (1<<12)
#include <iostream>
using namespace std;
enum { D, T };

bool operator < ( const cell &a, const cell &b ) {
	if ( a.x == b.x ) 
		return a.y < b.y;
	return a.x < b.x;
}
bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); }

cell operator - ( const cell &a, const cell &b ) {
	return cell(a.x-b.x,a.y-b.y);
}

cell c[N][4];
int n,to[2][MAXE],_next[2][MAXE],last[2][N],E[2],scc[N],st[N],*top,seen[N],yes,mark;

i64 operator , ( const cell &a, const cell &b ) { return a.x*b.x + a.y*b.y; }
i64 operator ^ ( const cell &a, const cell &b ) { return a.x*b.y - a.y*b.x; }

void add_arcs( int x, int y ) {
	int i = E[D]++, j = E[T]++;
	to[D][i] = y, _next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, _next[T][j] = last[T][y], last[T][y] = j;
}

int inside( cell p, cell a, cell b ) {
	cell m,n;
	if ( p == a || p == b ) return 1;
	m = p-a, n = p-b;
	return (m,n) < 0 && (m^n) == 0;
}

int intersect( cell a, cell b, cell p, cell q ) {
	cell m = b-a,n = q-p,w = p-a;
	i64 det,dt,dtau;
	double t,tau;

	det = -m.x*n.y+n.x*m.y;

	if ( det == 0 ) 
		return inside(p,a,b) || inside(q,a,b) || inside(a,p,q) || inside(b,p,q);

	dtau = m.x*w.y-m.y*w.x;
	dt = -n.y*w.x+w.y*n.x;
	if ( det > 0 && dt >= 0 && dtau >= 0 || det < 0 && dt <= 0 && dtau <= 0 ) 
		return labs(dt) <= labs(det) && labs(dtau) <= labs(det);
	else return 0;
	t = ((double)dt)/det;
	tau = ((double)dtau)/det;
	return 0<=t&&t<=1&&0<=tau&&tau<=1;
}

void dfs( int t, int x ) {
	int i,y;
	assert( seen[x] != yes );
	for ( seen[x] = yes, i = last[t][x]; i >= 0; i = _next[t][i] )
		if ( seen[y = to[t][i]] != yes )
			dfs(t,y);
	if ( t ) *++top = x;
	else scc[x] = mark;
}

int parallel( cell a, cell b, cell c, cell d ) {
	cell m = b-a,n = d-c;
	return (m^n) == 0;
}

int is_rectangle( cell &a, cell &b, cell &c, cell &d ) {
	cell m = b-a, n = c-d,
		 p = d-a, q = c-b;
	return m == n && p == q;
}

int main() {
	int i,j,k,ok;
	cell tmp;
#ifndef ONLINE_JUDGE
	freopen("11930.in","r",stdin);
#endif
	for ( ;1==scanf("%d",&n) && n>0; ) {
		for ( i = 0; i < n; ++i ) {
			for ( j = 0; j < 4; ++j )
				assert( 2 == scanf("%lld %lld",&c[i][j].x,&c[i][j].y) );
			sort(c[i],c[i]+4);
			do {
				if ( is_rectangle(c[i][0],c[i][1],c[i][2],c[i][3]) ) break ;
				//printf("(%lld,%lld) -- (%lld,%lld) -- (%lld,%lld) -- (%lld,%lld)\n",c[i][0].x,c[i][0].y,c[i][1].x,c[i][1].y,c[i][2].x,c[i][2].y,c[i][3].x,c[i][3].y);
			} while ( next_permutation(c[i],c[i]+4) );
			assert( is_rectangle(c[i][0],c[i][1],c[i][2],c[i][3]) );
			//printf("(%lld,%lld) -- (%lld,%lld) -- (%lld,%lld) -- (%lld,%lld)\n",c[i][0].x,c[i][0].y,c[i][1].x,c[i][1].y,c[i][2].x,c[i][2].y,c[i][3].x,c[i][3].y);
		}
		for ( E[D]=E[T]=0, i=0; i<n; ++i ) {
			k = var(i), last[D][k] = last[T][k] = -1;
			k = neg(i), last[D][k] = last[T][k] = -1;
		}
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < i; ++j ) {
				if ( intersect(c[i][0],c[i][2],c[j][0],c[j][2]) )
					add_arcs(var(i),neg(j)), add_arcs(var(j),neg(i));
				if ( intersect(c[i][1],c[i][3],c[j][0],c[j][2]) )
					add_arcs(neg(i),neg(j)), add_arcs(var(j),var(i));
				if ( intersect(c[i][0],c[i][2],c[j][1],c[j][3]) )
					add_arcs(var(i),var(j)), add_arcs(neg(j),neg(i));
				if ( intersect(c[i][1],c[i][3],c[j][1],c[j][3]) )
					add_arcs(neg(i),var(j)), add_arcs(neg(j),var(i));
			}
		for ( ++yes, top = st, i = 0; i < n; ++i ) {
			if ( seen[var(i)] != yes ) dfs(T,var(i));
			if ( seen[neg(i)] != yes ) dfs(T,neg(i));
		}
		for ( mark = 0, ++yes; top > st; )
			if ( seen[i = *top--] != yes )
				dfs(D,i), ++mark;
		for ( ok = 1, i = 0; i < n && ok; ++i )
			if ( scc[var(i)] == scc[neg(i)] ) ok = 0;
		puts(ok?"YES":"NO");
	}
	return 0;
}

