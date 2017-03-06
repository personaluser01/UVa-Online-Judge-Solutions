/*
 * 753. Plug for UNIX
 * status: Accepted
 */
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
enum { RCP, DEVS, ADS };
#include <queue>
#define N 0x200
#define oo 0xfffffffful
#define is_active(x) (x != src && x != sink && excess[x] > 0 && d[x] < 3*V)

typedef struct edge {
	struct edge *back_edge;
	int x,y; 
	int capacity, flow;
} edge;

int n[3],m[3],ct[3][N],demand[N],ad[N][N],V,
	src,sink,M,excess[N],d[N],cur[N],supply[N];
map<string,int> q[3];
edge e[1 << 16];
vector<int> adj[N];
queue<int> Q;

edge *init_e( edge *e, int x, int y, int cap, int fl ) {
	e->x = x, e->y = y, e->capacity = cap, e->flow = fl;
	return e;
}

int Push( edge *e ) {
	edge *pe = e,
		 *qe = e->back_edge;
	if ( !is_active(e->x) )
		return 0;
	if ( d[e->x] != d[e->y]+1 )
		return 0;
	if ( e->capacity == e->flow )
		return 0;
	int delta = min(excess[e->x],e->capacity-e->flow);
	assert( delta > 0 );
	int pre = is_active(e->y);
	excess[e->x] -= delta, excess[e->y] += delta;
	pe->flow += delta, qe->flow -= delta;
	int post = is_active(e->y);
	if ( post && !pre )
		Q.push(e->y);
	return 1;
}

void Relabel( int x ) {
	int i,y,j,k,w = (1 << 29);
	if ( !is_active(x) )
		return ;
	assert( is_active(x) );
	for ( i = 0; i < (int)adj[x].size(); ++i ) {
		j = adj[x][i], y = e[j].y;
		if ( e[j].flow == e[j].capacity )
			continue ;
		assert( d[e[j].x] <= d[e[j].y] );
		w = min(d[e[j].y]+1,w);
	}
	d[x] = ((w==(1<<29))?2*V:w);
}

void push_relabel( int x ) {
	if ( !Push(e+adj[x][cur[x]]) ) 
		if ( (++cur[x]), (cur[x] %= adj[x].size()) == 0 )
			Relabel(x);
}

int main() {
	string tmp;
	int i,j,k,t,ts,D,x,y,old_d;
	edge *pe,*qe;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		memset(ct,0,sizeof(ct));
		memset(m,0,sizeof(m));
		memset(supply,0,sizeof(supply));
		for ( t = RCP; t <= RCP; ++t ) {
			scanf("%d",n+t), q[t].clear();
			for (  k = 0; k < n[t]; ++k ) {
				cin >> tmp;
				if ( q[t].find(tmp) == q[t].end() )
					q[t][tmp]=m[t]++;
				++ct[t][q[t][tmp]];
				++supply[q[t][tmp]];
			}
		}
		memset(demand,0,sizeof(demand)),D = 0;
		for ( t = DEVS, scanf("%d",n+t), q[t].clear(), k = 0; k < n[t]; ++k ) {
			string a,b;
			cin >> a >> b;
			if ( q[RCP].find(b) == q[RCP].end() )
				q[RCP][b] = m[RCP]++;
			if ( q[DEVS].find(a) == q[DEVS].end() )
				q[DEVS][a] = m[DEVS]++;
			++demand[q[RCP][b]], ++D;
		}
		memset(ad,0,sizeof(ad));
		for ( t = ADS,  scanf("%d",n+t), q[t].clear(), k = 0; k < n[t]; ++k ) {
			string a,b;
			cin >> a >> b;
			if ( q[RCP].find(a) == q[RCP].end() )
				q[RCP][a] = m[RCP]++;
			if ( q[RCP].find(b) == q[RCP].end() )
				q[RCP][b] = m[RCP]++;
			i = q[RCP][a], j = q[RCP][b];
			ad[i][j] = 1;
		}
		/*
		for ( k = 0; k < m[RCP]; ++k )
			for ( i = 0; i < m[RCP]; ++i )
				for ( j = 0; j < m[RCP]; ++j )
					if ( ad[i][k] && ad[k][j] )
						ad[i][j] = 1;
						*/
		V = m[RCP]+2, src = m[RCP], sink = m[RCP]+1;
		for ( M = 0, k = 0; k < m[RCP]; ++k ) {
			if ( excess[k] = demand[k] ) {
				e[i = M].x = src, e[M].y = k, e[M].capacity = demand[k], e[M].flow =  demand[k], ++M;
				e[j = M].x = k, e[M].y = src, e[M].capacity = 0,         e[M].flow = -demand[k], ++M;
				e[i].back_edge = e+j, e[j].back_edge = e+i;
			}
			if ( supply[k] ) {
				e[i = M].x = k, e[M].y = sink, e[M].capacity = supply[k], e[M].flow = 0, ++M;
				e[j = M].x = sink, e[M].y = k, e[M].capacity = 0,         e[M].flow = 0, ++M;
				e[i].back_edge = e+j, e[j].back_edge = e+i;
			}
		}
		excess[src] = excess[sink] = 0;
		for ( i = 0; i < m[RCP]; ++i )
			for ( j = 0; j < m[RCP]; ++j )
				if ( ad[i][j] ) {
					pe = init_e(e+M,i,j,D,0), ++M;
					qe = init_e(e+M,j,i,0,0), ++M;
					pe->back_edge = qe, qe->back_edge = pe;
				}
		memset(d,0,sizeof(d)), d[src] = V;
		for ( i = 0; i < V; ++i ) adj[i].clear(), cur[i] = 0;
		for ( i = 0; i < M; ++i )
			adj[e[i].x].push_back(i);
		for ( i = 0; i < V; ++i )
			if ( is_active(i) )
				Q.push(i);
		for ( ;!Q.empty(); ) {
			for ( x = Q.front(), Q.pop(), old_d = d[x]; excess[x] > 0 && old_d == d[x]; push_relabel(x) );
			if ( is_active(x) ) Q.push(x);
		}
		printf("%d\n",D-excess[sink]);
		if ( ts ) putchar('\n');
	}
	return 0;
}
