/*
 * 11248. Frequency Hopping
 * TOPIC: maxflow, finding the mincut, ford-fulkerson
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 0x200
#define MAXE (1<<21)
#define BIT(k) (1ULL<<(k))
#define SET(a,k) (a[(k)>>3] |= BIT((k)&7))
#define CLR(a,k) (a[(k)>>3] &= ~BIT((k)&7))
#define TST(a,k) (a[(k)>>3] & BIT((k)&7))
#define MASK(k) (BIT(k)-1ULL)
#define oo (1LL<<43)
enum { ORIGINAL, RESTORE };
typedef long long i64;
i64 min( i64 x, i64 y ) { return x<y?x:y; }

int cmp( const void *a, const void *b ) { return *((int *)a) - *((int *)b); }

int V,E,last[MAXN],next[MAXE],to[MAXE],cap[MAXE],d[MAXN],visited[MAXN],yes,
	v[MAXE],*ptr,u[MAXE],*qtr,q[MAXN],*head,*tail,seen[MAXN],indeed;
i64 flow[MAXE],mf[MAXN],C,copy_flow[MAXE];
unsigned char is_in_mincut[MAXE>>3];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0;
	flow[i] = flow[j] = 0;
	CLR(is_in_mincut,i);
	CLR(is_in_mincut,j);
}

int bfs( int src, int sink ) {
	int x,y,i;
	for ( head = tail = q,  d[sink] = 0, visited[*tail++ = sink] = ++yes; head < tail; )
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( cap[i^1] > flow[i^1] && visited[y = to[i]] != yes )
				visited[*tail++ = y] = yes, d[y] = d[x]+1;
	return visited[src] == yes;
}

i64 dfs( int x, i64 df, const int sink  ) {
	i64 i,dt,y;
	if ( x == sink ) return df;
	if ( seen[x] == indeed )
		return 0;
	for ( seen[x] = indeed, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] && visited[y=to[i]] == yes && d[y]+1 == d[x] )
			if ( dt = dfs(y,min(df,cap[i]-flow[i]),sink) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

i64 maxflow( int src, int sink, int flag ) {
	i64 F = 0,dt,i;
	if ( src == sink ) return +oo;
	if ( flag == RESTORE )
		for ( i = 0; i < E; ++i )
			copy_flow[i] = flow[i];
	for (;bfs(src,sink);)
		for (;++indeed&&(dt=dfs(src,+oo,sink));F+=dt);
	if ( flag == RESTORE )
		for ( i = 0; i < E; ++i )
			flow[i] = copy_flow[i];
	return F;
}

i64 e[MAXN],D[MAXN];
int cur[MAXN];
#define is_active(x) ((x)!=src && (x)!=sink && e[x]>0 && D[x]<+oo)

int push( int i, int src, int sink ) {
	i64 delta = min(e[to[i^1]],cap[i]-flow[i]);
	int y_active = 0;
	if ( delta > 0 && D[to[i^1]] < +oo && D[to[i^1]]+1 == D[to[i]] ) {
		y_active = is_active(to[i]);
		e[to[i^1]] -= delta, e[to[i]] += delta;
		flow[i] += delta, flow[i^1] -= delta;
		if ( !y_active && is_active(to[i]) )
			*tail++ = to[i];
		return 1;
	}
	return 0;
}

void relabel( int x, int src, int sink ) {
	int i;
	for ( D[x] = +oo, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] )
			D[x] = min(D[x],D[to[i]]+1);
}

void push_relabel( int x, int src, int sink ) {
	int i = cur[x];
	if ( !push(i,src,sink) ) {
		if ( next[i] != -1 )
			cur[x] = next[i];
		else {
			cur[x] = last[x];
			relabel(x,src,sink);
		}
	}
}

void discharge( int src, int sink ) {
	int x;
	i64 old_d;
	while ( head < tail && !is_active(x = *head++) );
	if ( head < tail ) {
		old_d = D[x];
		do {
			push_relabel(x,src,sink);
		} while ( e[x] > 0 && D[x] == old_d );
		if ( is_active(x) ) *tail++ = x;
	}
}

i64 goldberg( const int src, const int sink ) {
	int i;
	for ( i = 0; i < E; copy_flow[i] = flow[i], ++i );
	for ( i = 0; i < V; e[i] = 0, D[i++] = 0 );
	D[src] = V, head = tail = q;
	for ( i = last[src]; i >= 0; i = next[i] )
		if ( cap[i] > 0 ) {
			e[to[i]] += cap[i], flow[i] = cap[i];
			if ( is_active(to[i]) )
				*tail++ = to[i];
		}
	for ( ;head < tail; discharge(src,sink) );
	for ( i = 0; i < E; flow[i] = copy_flow[i], ++i );
}

int main() {
	int i,j,k,edges,flag,cs = 0,x,y;
	i64 mat[0x80][0x80];
	i64 F,fl;
#ifndef ONLINE_JUDGE
	freopen("11248.in","r",stdin);
#endif
	for ( ;3 == scanf("%d %d %lld",&V,&edges,&C) && (V||edges||C) && printf("Case %d: ",++cs); ) {
		for ( E = 0, i = 0; i < V; last[i++] = -1 );
		memset(mat,0,sizeof mat);
		for ( ;edges-- && 3 == scanf("%d %d %d",&i,&j,&k); mat[--i][--j] += k );
		for ( i = 0; i < V; ++i )
			for ( j = 0; j < V; ++j )
				if ( i != j && mat[i][j] > 0 )
					add_arcs(i,j,mat[i][j]);
		if ( (F = maxflow(0,V-1,ORIGINAL)) >= C ) {
			puts("possible");
			continue ;
		}

		/*
		 * find the minimum cut
		 */
		/*
		for ( i = 0; i < E; ++i )
			if ( flow[i] > 0 )
				printf("flow[(%d,%d) = %lld\n",to[i^1]+1,to[i]+1,flow[i]);
				*/

		for ( seen[0] = ++indeed, fl = 0, ptr = v, head = tail = q, visited[*tail++ = 0] = ++yes; head < tail; )
			for ( i = last[x = *head++]; i >= 0; i = next[i] )
				if ( flow[i] < cap[i] && visited[y=to[i]] != yes )
					visited[*tail++ = y] = yes, seen[y] = indeed;

		for ( fl = 0, ptr = v, head = tail = q, visited[*tail++ = 0] = ++yes; head < tail; )
			for ( i = last[x = *head++]; i >= 0; i = next[i] )
				if ( flow[i] < cap[i] && visited[y=to[i]] != yes )
					visited[*tail++ = y] = yes;
				else if ( cap[i] == flow[i] && flow[i] > 0 && !TST(is_in_mincut,i) && seen[to[i]] != indeed )
					*ptr++ = i, SET(is_in_mincut,i), fl += flow[i], 0&&printf("Adding %d-->%d, cap = %d\n",to[i^1],to[i],cap[i]);

		assert( visited[V-1] != yes );
		assert( fl == F );

		for ( i = 0; i < ptr-v; ++i )
			mf[to[v[i]^1]] = maxflow(0,to[v[i]^1],RESTORE);
		for ( i = 0; i < ptr-v; ++i )
			mf[to[v[i]]] = maxflow(to[v[i]],V-1,RESTORE);
		for ( qtr = u, i = 0; i < ptr-v; ++i )
			if ( min(mf[to[v[i]^1]],mf[to[v[i]]])+F >= C ) 
				*qtr++ = (to[v[i]]|(to[v[i]^1]<<7));
		if ( qtr == u ) 
			puts("not possible");
		else {
			qsort(u,qtr-u,sizeof *u,cmp);
			printf("possible option:");
			for ( i = 0; i < qtr-u; ++i )
				printf("(%d,%d)%c",(u[i]>>7)+1,(int)(u[i]&MASK(7))+1,i==qtr-u-1?'\n':',');
		}
	}
	return 0;
}

