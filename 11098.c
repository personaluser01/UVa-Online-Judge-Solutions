/*
 * 11098. Battle II
 * TOPIC: dfs, scc
 * status: Accepted
 */
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 0x200
#define oo (1LL<<61)
#define S(k) ((k)*(k))
#define tol 1e-9
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
enum { D, T };
typedef long long i64;
i64 min( i64 x, i64 y ) { if ( x < y ) return x; return y; }

i64 e[N],E[N],cost[N];
int deg[2][N],adj[2][N][N],n,st[N],*top,seen[N],yes,scc[N],mark,taken[N],pos[N],cand[N],
	g[N][N],indeed,best[N],v[N],*ptr,indeg[N],
	Adj[2][N][N],Deg[2][N];

void dfs( int t, int x ) {
	int i,y;
	assert( seen[x] != yes );
	for ( seen[x]=yes, i=0; i<deg[t][x]; ++i )
		if ( seen[y=adj[t][x][i]]!=yes )
			dfs(t,y);
	if ( t ) *++top = x;
	else scc[x] = mark;
}

void init() {
	i64 x[N],y[N],r[N];
	int i,j,k,t;
	for ( scanf("%d",&n), i = 0; i < n; ++i ) 
		for ( t = D; t <= T; deg[t++][i] = 0 );
	for ( i = 0; i < n; ++i )
		scanf("%lld %lld %lld %lld",x+i,y+i,r+i,e+i);
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			if ( i != j )
				if ( S(e[i]+r[i]+r[j]) >= S(x[i]-x[j])+S(y[i]-y[j]) )
					adj[D][i][deg[D][i]++] = j, adj[T][j][deg[T][j]++] = i;
	for ( t = D; t <= T; ++t )
		for ( i = 0; i < n; ++i )
			for ( Deg[t][i] = 0, j = 0; j < deg[t][i]; ++j )
				Adj[t][i][Deg[t][i]++] = adj[t][i][j];
}

void floodfill( int x ) {
	int i,y;
	assert( seen[x]!=yes );
	for ( seen[x]=yes, i=0; i<Deg[D][x]; ++i )
		if ( seen[y=Adj[D][x][i]]!=yes )
			floodfill(y),g[scc[x]][scc[y]]=indeed;
		else g[scc[x]][scc[y]] = indeed;
}

void construct_dag() {
	int i,j,k,t;
	for ( top = st, ++yes, i = 0; i < n; ++i )
		if ( seen[i] != yes )
			dfs(T,i);
	for (mark=0,++yes;top>st;)
		if ( seen[i=*top--]!=yes )
			dfs(D,i), indeg[mark] = 0, E[mark++] = +oo;
	for ( ++indeed, ++yes, i = 0; i < n; ++i )
		if ( seen[i] != yes )
			floodfill(i);
	for ( i = 0; i < n; ++i )
		for ( t = 0; t < 2; deg[t++][i] = 0 );
	for ( i = 0; i < mark; ++i )
		for ( j = 0; j < mark; ++j )
			if ( i != j && g[i][j] == indeed )
				adj[D][i][deg[D][i]++] = j, adj[T][j][deg[T][j]++] = i, ++indeg[j];
	for ( i = 0; i < n; ++i )
		if ( E[scc[i]] > e[i] )
			E[scc[i]] = e[i], best[scc[i]] = i;
	for ( i = 0; i < mark; ++i )
		assert( E[i] < +oo );
}

void depth_first( int x ) {
	int i,y;
	assert( seen[x] != yes );
	for ( seen[x] = yes, i = 0; i < deg[D][x]; ++i )
		if ( seen[y = adj[D][x][i]] != yes )
			depth_first(y);
	*++top = x;
}

void topological_sort() {
	int x;
	for ( top = st, x = 0, ++yes; x < mark; ++x )
		if ( seen[x] != yes )
			depth_first(x);
	for ( ptr = v; top > st; *ptr++ = *top-- );
}

void check_correctness() {
	int i,j;
	for ( i = 0; i < ptr-v; ++i )
		for ( j = i+1; j < ptr-v; ++j )
			assert( g[v[j]][v[i]] != indeed );
	for ( i = 0; i < ptr-v; pos[v[i]] = i, ++i );
}

int covered( int *v, int m ) {
	int i,j,k,x,y,q[N],*head,*tail,cnt = 0,used[N] = {0};

	for ( k = 0; k < m; ++k ) {
		assert( !used[v[k]] );
		for ( head = tail = q, used[*tail++ = v[k]] = 1; head < tail; )
			for ( x = *head++, ++cnt, i = 0; i < Deg[D][x]; ++i ) 
				if ( !used[y=Adj[D][x][i]] ) 
					used[*tail++=y]=1;
	}
	return cnt;
}

int assignment( int *ans, int *k ) {
	i64 s = 0,w;
	int i,j,K,m=0,x[N];
	static int used[N] = {0}, aha = 0;

	for ( ++aha, K = 0, i = 0; i < ptr-v; ++i )
		if ( used[v[i]] != aha && !indeg[v[i]] )
			used[x[m]=v[i]]=aha, s+=E[x[m++]];
		else cand[K] = v[i], cost[K++] = E[v[i]];
	for ( j = 1; j; )
		for ( i = j = 0; i < K-1; ++i )
			if ( cost[i]>cost[i+1] )
				xchg(cost[i],cost[i+1]),xchg(cand[i],cand[i+1]), ++j;
	for ( i = 0; i < K; ++i ) 
		if ( (s+cost[i])*m<(m+1)*s ) 
			used[x[m++]=cand[i]]=aha, s+=cost[i];
	if ( k ) 
		for ( *k=m, i=0; i<m; ans[i]=x[i], ++i );
	return 1;
}

int main() {
	int i,j,k,ts,cs = 0,x[N],m,flag,vx[N];
	double good,bad,mid,Total;
#ifndef ONLINE_JUDGE
	freopen("11098.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; puts("") ) {
		init(), construct_dag(), topological_sort(), check_correctness();
		/*
		for ( Total = 0, i = 0; i < ptr-v; Total += E[v[i++]] );
		assert( can_find(Total/(ptr-v),NULL,NULL) );
		assert( !can_find(0,NULL,NULL) );
		for(good=Total/(ptr-v),bad=0;fabs(good-bad)>tol;can_find(mid=(good+bad)/2,NULL,NULL)?(good=mid):(bad=mid));
		assert( can_find(good,x,&m) );
		*/
		for ( assignment(x,&m), j = 1; j; )
			for ( j = i = 0; i < m-1; ++i )
				if ( pos[x[i]] < pos[x[i+1]] )
					++j, k = x[i], x[i] = x[i+1], x[i+1] = k;
		for ( i = 0; i < m-1; ++i )
			assert( pos[x[i]] > pos[x[i+1]] );
		for(k=0,printf("Case #%d:",++cs),i=0;i<m;printf(" %d",vx[k++]=best[x[i++]]));
		assert( covered(vx,k) == n );
		/*printf("     %lf\n",brute_force());*/
	}
	return 0;
}

