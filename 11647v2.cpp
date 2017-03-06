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
#define Q (1<<14)
#define  N 	    0x200
#define  MAXN 	N
#define  MAXE   0x400
#define tol 1e-11
#define MAXC (1000001)
#define oo (1LL << 25)
#define is_active(x) (e[x]>0)
#ifndef ONLINE_JUDGE
#define DBG 1
#else
#define DBG 0
#endif
typedef long long i64;
enum { NOTHING, PUSH, RELABEL };
using namespace std;
#include <set>

int m,n,ts,cs,to[MAXE],last[MAXN],cur[MAXN],src,E,V,EE,next[MAXE],dominated[N],parent[MAXE],seen[MAXN],yes;
i64 cost[MAXE],e[N],cap[MAXE],low[MAXE],flow[MAXE],COST;
long double lambda,pi[MAXE],d[MAXE],epsilon,D[N][N];

int gr( long double a, long double b ) { return a >= b+tol; }

void add_arcs( int x, int y, i64 c, i64 l, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, cap[i] =  c, low[i] =  l, flow[i] = 0, next[i] = last[x], last[x] = i, cost[i] =  w;
	to[j] = x, cap[j] = -l, low[j] = -c, flow[j] = 0, next[j] = last[y], last[y] = j, cost[j] = -w;
}

long double min_mean_weight_cycle() {
	int i,j,k,l;
	long double ans=+INF,w;
	for ( i = 0; i < V; ++i )
		for ( k = 0; k <= V; D[k++][i] = INF );
	for ( D[0][src]=0, k = 1; k <= V; ++k )
		for ( l = 0; l < E; ++l ) 
			if ( flow[l]<cap[l] && D[k-1][i=to[l^1]]<INF && D[k-1][i=to[l^1]]+cost[l]<D[k][j=to[l]] )
				D[k][j]=D[k-1][i]+cost[l];
	for ( i = 0; i < V; ++i ) {
		if ( D[V][i] == +INF )
			continue ;
		for ( w = -INF, k = 0; k < V; ++k )
			if ( D[V][i] < +INF && D[k][i] < +INF )
				w = max(w,(D[V][i]-D[k][i])/(V-k));
		if ( w > -INF ) 
			ans = min(ans,w);
	}
	assert( ans < INF );
	return ans;
}

void update_pi() {
	int i,j,k,l,x,y;
	set<pair<long double,int> > s;
	for ( i = 0; i < V; d[i++] = +INF );
	for ( d[src] = 0, k = 0; k < V-1; ++k )
		for ( l = 0; l < E; ++l )
			if ( flow[l] < cap[l] && d[i=to[l^1]] < INF )
				d[j=to[l]] = min(d[j=to[l]],d[i]+(cost[l]+lambda));
	/*
	for ( s.clear(), s.insert(make_pair(d[src]=0,src)); !s.empty(); ) {
		set<pair<long double,int> >::iterator it = s.begin();
		x = it->second, s.erase(*it);
		for ( i = last[x]; i >= 0; i = next[i] )
			if ( flow[i]<cap[i] && gr(d[y=to[i]],d[x]+cost[i]+lambda) )
				d[y]=d[x]+cost[i]+lambda, s.insert(make_pair(d[y],y));
	}
	*/
	/*
	for ( l = 0; l < E; ++l )
		if ( flow[l] < cap[l] && d[i=to[l^1]] < +INF ) {
			assert( d[j = to[l]] < +INF );
			if ( gr(d[j=to[l]],d[i]+cost[l]+lambda) )
				printf("These %d %d %lld %lld %Lf, %Lf %Lf\n",j,i,flow[l],cap[l],cost[l]+lambda,d[j],d[i]);

			assert( !gr(d[j=to[l]],d[i]+cost[l]+lambda) );
		}
	*/

	for ( i = 0; i < V; pi[i++] = d[i] );
}

void relabel( const int x ) {
	int i,y;
	long double w = -INF;

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

int q[2][Q],head[2],tail[2],sz[2];

void refine() {
	int i,j,k,t,x,y,l;
	i64 dt;

	for ( x = 0; x < V; ++x )
		assert( e[x] == 0 );

	for ( epsilon /= 2, i = 0; i < E; ++i )
		if ( flow[i] < cap[i] && pi[y=to[i]]-pi[x=to[i^1]]-cost[i] > 0 )
			dt = cap[i]-flow[i], flow[i] += dt, flow[i^1] -= dt, e[x] -= dt, e[y] += dt;

	sz[0] = sz[1] = 0, head[0] = head[1] = tail[0] = tail[1] = 0;
	for ( t = 0, x = 0; x < V; ++x ) 
		q[t][tail[t]++] = x, tail[t] &= (Q-1), ++sz[t];

	for ( j = 1; j; t ^= 1 ) 
		for ( j = 0, sz[t^1] = 0, head[t^1] = tail[t^1] = 0, l = sz[t], i = head[t]; l--; ++i, i &= (Q-1) ) {
			if ( !is_active(x=q[t][i]) ) { q[t^1][tail[t^1]++] = x, tail[t^1] &= (Q-1), ++sz[t^1]; continue ; }
			k = discharge(x), ++j;
			if ( k == RELABEL )
				--head[t^1], head[t^1] += Q, head[t^1] &= (Q-1), ++sz[t^1], q[t^1][head[t^1]] = x;
			else q[t^1][tail[t^1]++] = x, ++sz[t^1], tail[t^1] &= (Q-1);
		}
}

void mcc() {
	for ( epsilon = MAXC; epsilon*V >= 1.0; epsilon = lambda ) 
		if ( (lambda = max((long double)0.00,-min_mean_weight_cycle())) > 0 )
			update_pi(), epsilon = lambda, refine();
		else update_pi();
}

int bellman_ford( int *v ) {
	int i,k,x,y;
	for ( x = 0; x < V; d[x++] = +INF );
	for ( d[src] = 0, i = 0; i < V-1; ++i )
		for ( k = 0; k < E; ++k ) 
			if ( flow[k] < cap[k] && d[x=to[k^1]]<+oo && d[y=to[k]]>d[x]+cost[k] ) 
				d[y]=d[x]+cost[k],parent[y]=k;
	for ( k = 0; k < E; ++k )
		if ( flow[k] < cap[k] && d[x=to[k^1]]<+oo && d[y=to[k]]>d[x]+cost[k] ) {
			d[y]=d[x]+cost[k],parent[*v=y]=k;
			return 1;
		}
	return 0;
}

int main() {
	int i,j,k,l,t,sc[N],xx[N],yy[N],gg[N],
		judge[N],mid[N],w,score_so_far[N];
	i64 df;
	long double ee;
#if DBG
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; putchar('\n') ) {
		scanf("%d %d",&m,&n), V = n+2, E = 0;
		for ( i = 0; i < V; last[i] = -1, e[i] = 0, pi[i] = 0, ++i );
		for ( i = 1; i <= n; scanf("%d",&sc[i++]) );
		for ( l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k), xx[l] = i, yy[l] = j, gg[l] = k;
			// add_arcs(OUT(j),IN(i),+oo,0,(i64)k), judge[l] = (E-2);
		}
		for ( i = 0; i < m; ++i ) dominated[i] = 0;
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < m && !dominated[i]; ++j )
				if ( i != j && xx[i] <= xx[j] && yy[j] <= yy[i] )
					if ( gg[i] <= gg[j] )
						dominated[j] = 1;
		for ( l = 0; l < m; ++l )
			if ( !dominated[l] )
				add_arcs(yy[l]+1,xx[l],+oo,0,(i64)gg[l]), judge[l] = (E-2);

		for ( src = 0, i = 1; i <= n+1; ++i )
			add_arcs(src,i,+oo,0,0);
		for ( i = 1; i <= n; ++i ) {
			score_so_far[i] = 0, add_arcs(i,i+1,+oo,sc[i],0), mid[i] = (E-2);
		}
		for ( i = 0; i < V; cur[i] = last[i], ++i );
		/* initial circulation */
		for ( l = 0; l < m; ++l ) {
			if ( dominated[l] ) continue ;
			for ( i = xx[l], j = yy[l], df = 0, k = i; k <= j; ++k )
				df = max(df,low[mid[k]]-flow[mid[k]]);
			if ( df == 0 ) continue ;
			assert( df > 0 );
			for ( k = i; k <= j; ++k ) {
				t = mid[k], flow[t] += df, flow[t^1] -= df, score_so_far[k] += df;
			}
			t = judge[l], flow[t] += df, flow[t^1] -= df;
		}
		/* validity of the greedy assignment ~ feasibility of the problem */
		for ( i = 1; i <= n; ++i )
			assert( score_so_far[i] >= sc[i] );
		for ( i = 0; i < E; ++i )
			assert( low[i] <= flow[i] && flow[i] <= cap[i] );
		/* optimal circulation */
		for ( int cn = 0; cn < -1 && bellman_ford(&i); ++cn ) {
			for(seen[i]=++yes,k=parent[i],i=to[k^1];seen[i]!=yes;seen[i]=yes,k=parent[i],i=to[k^1]);
			for ( ee = 0, df = +oo, j = i, k = parent[i], ee+=cost[k], df = min(df,cap[k]-flow[k]), i = to[k^1]; i != j; k = parent[i], df = min(df,cap[k]-flow[k]), i = to[k^1], ee += cost[k] );
			assert( df > 0 );
			assert( ee < 0 );
			/* printf("[e = %lld] Flow along this cycle %d\n",e,df); */
			for ( k = parent[i], i = to[k^1], flow[k] += df, flow[k^1] -= df; i != j; k = parent[i], flow[k] += df, flow[k^1] -= df, i = to[k^1] );
		}

		for ( mcc(), COST = 0, l = 0; l < E; ++l ) 
			if ( flow[l] > 0 ) COST += flow[l]*cost[l];
#if DBG
		for ( printf("Case %d:[%lld]",++cs,COST), l = 0; l < -1; printf(" %lld",flow[judge[l++]]) );
#else
		for ( printf("Case %d:",++cs), l = 0; l < m; ++l )
			if ( !dominated[l] )
				printf(" %lld",flow[judge[l]] );
			else 
				printf(" 0");
#endif
	}
    return 0;
}


