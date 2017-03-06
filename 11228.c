/*
 * 11228. Transportation System
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define N 0x400
#define S(x) ((x)*(x))
#define oo (DBL_MAX-1024)
#define A(x) ((x)<0?-(x):(x))

typedef long long i64;

int n,ts,cs,adj[N][N],deg[N],ts,heap[2*N],pos[N],cnt,
	seen[N],yes,m,cc[N],p[N];
long double R,xx[N],yy[N],dist[N][N],d[N],weight,w;

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i = (j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,r = heap[0];
	pos[*heap] = -1;
	if ( --cnt )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] <= d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return r;
}

void dfs( int x ) {
	int y,i;
	assert( seen[x] != yes );
	for ( cc[x] = m, seen[x] = yes, i = 0; i < deg[x]; ++i )
		if ( seen[y=adj[x][i]]!=yes )
			dfs(y);
}

i64 F( long double x ) {
	i64 dx = (i64)x,
		ux = ((i64)x)+1;
	return A(x-dx)<A(ux-x)?dx:ux;
}

void upd( int x ) {
	if ( !p[x]||seen[x] == yes ) return ;
	seen[x] = yes;
	if ( cc[p[x]] != cc[x] )
		weight += d[x];
	else
		w += d[x];
}

int main() {
	int i,j,k,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		assert( 2 == scanf("%d %Lf",&n,&R) );
		for ( i = 1; i <= n; ++i )
			scanf("%Lf %Lf",xx+i,yy+i), deg[i] = 0;
		for ( i = 1; i <= n; ++i )
			for ( j = i+1; j <= n; ++j )
				if ( (dist[i][j] = dist[j][i] = sqrt(S(xx[i]-xx[j])+S(yy[i]-yy[j]))) <= R )
					adj[i][deg[i]++] = j, adj[j][deg[j]++] = i;
		for ( x = 1; x <= n; ++x ) d[x] = +oo, pos[x] = -1;
		for ( m = 0, ++yes, x = 1; x <= n; ++x )
			if ( seen[x] != yes )
				++m, dfs(x);
		for ( ++yes, weight = w = 0, p[1] = 0, cnt = 0, d[1] = 0, k = 1, push(1); cnt && k < n; )
			for ( upd(x = pop()), y = 1; y <= n; ++y )
				if ( y != x && d[y] > dist[x][y] ) 
					p[y] = x, d[y]=dist[x][y],push(y);
		printf("Case #%d: %d %lld %lld\n",++cs,m,F(w),F(weight));
	}
	return 0;
}

