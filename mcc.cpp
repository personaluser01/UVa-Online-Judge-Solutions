/*
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cfloat>
#include <climits>
#include <queue>
#define INF (DBL_MAX-1024)
#define  N 	    0x200
#define  MAXN 	N
#define  MAXE   0x400
#define IN(x)  (((x)<<1)+1)
#define OUT(x) (((x)<<1)+2)
#define tol 1e-9
#define MAXC (1000001)
#define oo (1LL << 43)
#define is_active(x) (e[x]>0)
#ifndef ONLINE_JUDGE
#define DBG 1
#else
#define DBG 0
#endif
typedef long long i64;
enum { NOTHING, PUSH, RELABEL };
using namespace std;

int m,n,ts,cs,to[MAXE],last[MAXN],cur[MAXN],src,E,V,EE,next[MAXE];
i64 cost[MAXE],e[N],cap[MAXE],low[MAXE],flow[MAXE],COST;
double lambda,pi[MAXE],d[MAXE],epsilon,D[N][N];

void add_arcs( int x, int y, i64 c, i64 l, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, cap[i] =  c, low[i] =  l, flow[i] = 0, next[i] = last[x], last[x] = i, cost[i] =  w;
	to[j] = x, cap[j] = -l, low[j] = -c, flow[j] = 0, next[j] = last[y], last[y] = j, cost[j] = -w;
}

double min_mean_weight_cycle() {
	int i,j,k,l;
	double ans=+INF,w;
	for ( i = 0; i < V; ++i )
		for ( k = 0; k <= V; D[k++][i] = INF );
	for ( D[0][src] = 0, k = 1; k <= V; ++k )
		for ( l = 0; l < E; ++l ) 
			if ( flow[l] < cap[l] && D[k-1][i=to[l^1]] < INF && D[k-1][i]+cost[l] < D[k][j=to[l]] )
				D[k][j] = D[k-1][i]+cost[l];
	for ( i = 0; i < V; ++i, ans = min(ans,w) ) 
		for ( w = -INF, k = 0; k < V; ++k )
			w = max(w,(D[V][i]-D[k][i])/(V-k));
	return ans;
}

void update_pi() {
	int i,j,k,l;
	for ( i = 0; i < V; d[i++] = +INF );
	for ( d[src] = 0, k = 0; k < V-1; ++k )
		for ( l = 0; l < E; ++l )
			if ( flow[l] < cap[l] && d[i=to[l^1]] < INF )
				d[j=to[l]] = min(d[j=to[l]],d[i]+(cost[l]+lambda));
	for ( i = 0; i < V; pi[i++] = d[i] );
}

void relabel( const int x ) {
	int i,y;
	double w = -INF;

	for ( i = last[x]; i >= 0; i = next[i] ) {
		if ( flow[i] == cap[i] ) continue ;
		assert( flow[i] < cap[i] );
		assert( pi[y=to[i]]-pi[x]-cost[i] <= 0 );
		w = max(w,pi[y]-cost[i]);
	}
	pi[x] = w-epsilon;
}

int push_relabel( const int x ) {
	int i = cur[x],y;
	i64 dt;

	if ( flow[i] < cap[i] && pi[y=to[i]]-pi[x]-cost[i] > 0 ) {
		dt = min(cap[i]-flow[i],e[x]);
		flow[i] += dt, flow[i^1] -= dt, e[x] -= dt, e[y] += dt;
		return PUSH;
	}
	else {
		cur[x] = next[i];
		if ( cur[x] == -1 ) {
			cur[x] = last[x];
			relabel(x);
			return RELABEL;
		}
		return NOTHING;
	}
}

int discharge( const int x ) {
	int op = NOTHING;
	assert( e[x] > 0 );
	for (;e[x]>0 && op!=RELABEL; op=push_relabel(x) );
	return op;
}

void refine() {
	int i,j,k,t,x,y;
	deque<int> q[2];
	i64 dt;

	for ( x = 0; x < V; ++x )
		assert( e[x] == 0 );

	for ( epsilon /= 2, i = 0; i < E; ++i )
		if ( flow[i] < cap[i] && pi[y=to[i]]-pi[x=to[i^1]]-cost[i] > 0 )
			dt = cap[i]-flow[i], flow[i] += dt, flow[i^1] -= dt, e[x] -= dt, e[y] += dt;
	for ( t = 0, x = 0; x < V; q[t].push_back(x++) );
	for ( j = 1; j; t ^= 1 ) 
		for ( j = 0, q[t^1].clear(), i = 0; i < (int)q[t].size(); ++i ) {
			if ( !is_active(x=q[t][i]) ) { q[t^1].push_back(x); continue ; }
			k = discharge(x), ++j;
			if ( k == RELABEL )
				q[t^1].push_front(x);
			else q[t^1].push_back(x);
		}
}

void mcc() {
	for ( epsilon = MAXC; epsilon > 0; epsilon = lambda ) 
		if ( (lambda = max(0.00,-min_mean_weight_cycle())) > 0 )
			update_pi(), epsilon = lambda, refine();
		else update_pi();
}

int main() {
	int i,j,k,l,t,sc[N],xx[N],yy[N],gg[N],
		judge[N],mid[N],w,conn[N],score_so_far[N];
	i64 df;
#if DBG
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; putchar('\n') ) {
		scanf("%d %d",&m,&n), V = 2*n+1, E = 0;
		for ( i = 0; i < V; last[i] = -1, e[i] = 0, pi[i] = 0, ++i );
		for ( i = 0; i < n; scanf("%d",&sc[i++]) );
		for ( l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k), xx[l] = --i, yy[l] = --j, gg[l] = k;
			add_arcs(OUT(j),IN(i),+oo,0,(i64)k), judge[l] = (E-2);
		}
		for ( src = 0, i = 0; i < n; ++i )
			add_arcs(src,IN(i),+oo,0,0), add_arcs(src,OUT(i),+oo,0,0);
		for ( i = 0; i < n; ++i ) {
			add_arcs(IN(i),OUT(i),+oo,sc[i],0), mid[i] = (E-2), score_so_far[i] = 0;
			if ( i < n-1 ) add_arcs(OUT(i),IN(i+1),+oo,0,0), conn[i] = (E-2);
		}
		for ( i = 0; i < V; ++i ) cur[i] = last[i];
		/* initial circulation */
		for ( l = 0; l < m; ++l ) {
			for ( i = xx[l], j = yy[l], df = 0, k = i; k <= j; ++k )
				df = max(df,low[mid[k]]-flow[mid[k]]);
			if ( df == 0 ) continue ;
			assert( df > 0 );
			for ( k = i; k <= j; ++k ) {
				t = mid[k], flow[t] += df, flow[t^1] -= df, score_so_far[k] += df;
				if ( k < j )
					t = conn[k], flow[t] += df, flow[t^1] -= df;
			}
			t = judge[l], flow[t] += df, flow[t^1] -= df;
		}
		/* validity of the greedy assignment ~ feasibility of the problem */
		for ( i = 0; i < n; ++i )
			assert( score_so_far[i] >= sc[i] );
		for ( i = 0; i < E; ++i )
			assert( low[i] <= flow[i] && flow[i] <= cap[i] );
		/* optimal circulation */
		for ( mcc(), COST = 0, l = 0; l < E; ++l ) 
			if ( flow[l] > 0 ) COST += flow[l]*cost[l];
		for ( printf("Case %d:[%lld]",++cs,COST), l = 0; l < -1; printf(" %lld",flow[judge[l++]]) );
	}
    return 0;
}


