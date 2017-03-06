/*
 * 10380. Shogi Tournament
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <queue>
#include <set>
#include <map>
#define DIM 51
#define N DIM
#define Q (1 << 15)
#define oo 0xfffffffful
using namespace std;

char game[DIM][DIM][3],*ptr[DIM][DIM];
int m,n,person,src,sink,score[N],V,E,
	vx[Q],vy[Q],v[DIM][DIM][DIM],p[Q];

typedef struct edge { 
	struct edge *back_edge; 
	int x,y, capacity, flow; 
} edge;
edge e[Q],*ee[Q];
queue<int> q;
unsigned int d[Q];
vector<int> adj[Q];

void add_arcs( int x, int y, int c ) {
	int i,j;
	e[i = E].x = x, e[i].y = y, e[i].capacity = c, e[i].flow = 0, ++E;
	e[j = E].x = y, e[j].y = x, e[j].capacity = 0, e[j].flow = 0, ++E;
	(e[i].back_edge = e+j)->back_edge = e+i;
}

int bfs() {
	int x,y,i,j,k;
	for ( x = 0; x < V; ++x ) d[x] = +oo;
	for (q.push(src),d[src]=0;!q.empty()&&d[sink]==+oo;)
		for ( x = q.front(), q.pop(), i = 0; i < (int)adj[x].size(); ++i )
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( d[y = e[j].y] > d[x]+1 )
					q.push(y), d[y] = d[x]+1, p[y] = x, ee[y] = e+j;
	for (;!q.empty(); q.pop() );
	return d[sink]<+oo;
}

int retrace( int x, int df ) {
	if ( x != src )
		return retrace(p[x],min(df,ee[x]->capacity-ee[x]->flow));
	return df;
}

void update( int x, int df ) {
	if ( x != src )
		ee[x]->flow += df, ee[x]->back_edge->flow -= df, update(p[x],df);
}

int maxflow( int w ) {
	int i,j,k;
	for ( E = 0, src = n+m+1, sink = n+m, V = m+n+2, i = 0; i < m; ++i ) 
		add_arcs(src,i+n,1), add_arcs(i+n,vx[i],1), add_arcs(i+n,vy[i],1);
	for ( i = 0; i < n; ++i )
		if ( i != person )
			if ( score[person]-score[i]-w > 0 )
				add_arcs(i,sink,score[person]-score[i]-w);
	for ( i = 0; i < V; adj[i++].clear() );
	for ( i = 0; i < E; adj[e[i].x].push_back(i), ++i );
	for(;bfs();update(sink,retrace(sink,(1<<29))) );
	for ( k = 0, i = 0; i < E; ++i )
		if ( e[i].y == sink )
			k += e[i].flow;
	return k;
}

int main() {
	int i,j,k,l,t,ts,cs,
		good,bad,mid,maxdiff;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&person);) {
		for ( --person, i = 0; i < n; ++i )
			for ( j = 0; j < n; scanf("%s",game[i][j++]) );
		memset(score,0,sizeof(score)), m = 0;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				ptr[i][j] = NULL;
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				for ( k = 0; k < 2; ++k )
					if ( game[i][j][k] == '0' )      ++score[j];
					else if ( game[i][j][k] == '1' ) ++score[i];
					else if ( i == person )
						++score[i], game[i][j][k] = '1', game[j][i][k] = '0';
					else if ( j == person )
						++score[j], game[i][j][k] = '0', game[j][i][k] = '1';
					else {
						vx[m] = i, vy[m++] = j;
						if ( !ptr[i][j] ) {
							ptr[i][j] = game[i][j]+k;
							ptr[j][i] = game[j][i]+k;
						}
					}
		for ( i = 0; i < n; ++i )
			if ( i != person && score[i] > score[person] ) {
				Bad: printf("Player %d can't win!\n",person+1);
				if ( 1||ts ) putchar('\n');
				goto next;
			}
		if ( !m ) {
			printf("Player %d can win with %d point(s).\n\n",person+1,0);
			goto print_output;
		}
		if ( maxflow(good = 0) < m ) goto Bad;
		assert( maxflow(bad=(1<<29)) < m );
		for (;good+1 != bad; maxflow(mid=(good+bad)/2)<m?(bad=mid):(good=mid) );
		printf("Player %d can win with %d point(s).\n\n",person+1,good);
		assert( maxflow(good) == m );
		for ( k = 0; k < E; ++k ) {
			if ( e[k].flow != 1 ) continue ;
			i = e[k].x, j = e[k].y;
			if ( n <= i && i < n+m )
				if ( 0 <= j && j < n ) {
					l = vx[i-n], t = vy[i-n];
					assert( ptr[l][t] );
					if ( j == l )
						*ptr[l][t]++ = '1', *ptr[t][l]++ = '0';
					else 
						*ptr[l][t]++ = '0', *ptr[t][l]++ = '1';
					++score[j];
				}
		}
		print_output:
		for ( i = 0; i < n; printf("%s: %d\n",game[i][j],score[i]), ++i )
			for ( j = 0; j < n-1; printf("%s ",game[i][j++]) );
		if ( 1||ts ) putchar('\n');
		next: continue ;
	}
	return 0;
}

