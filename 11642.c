/*
 * 11642. Bangladesh Premier League
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 64
#define MAXV (N+N*(N-1)/2)
#define M    (1 << 17)
#define oo 0xfffffffful
typedef unsigned long long u64;
#define L(u) ((u)&((~(u))+1))
#define IS_GAME(x) (n+1 <= (x) && (x) != sink)
#define IS_TEAM(x) (1 <= (x) && (x) <= n)

int min( int x, int y ) { return x<y?x:y; }

int n,wins[N],games_left[N][N],src,sink,cs,V,E,q[MAXV],*head,*tail,gid[N][N],
	to[M],next[M],last[MAXV],cap[M],flow[M],seen[MAXV],yes,max_capacity,
	*ptr,out[MAXV],visited[MAXV],indeed;
char tname[N][0x30],e[MAXV][2];
unsigned int d[MAXV];

int dfs( int x, int df ) {
	int i,y,t;
	if ( x == sink )
		return df;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( seen[y = to[i]] != yes && visited[y] == indeed && d[y]+1 == d[x] )
			if ( flow[i] < cap[i] )
				if ( t = dfs(y,min(df,cap[i]-flow[i])) ) {
					flow[i] += t, flow[i^1] -= t;
					return t;
				}
	return 0;
}

int bfs() {
	int x,y,i;
	head = tail = q;
	visited[sink] = ++indeed;
	for ( d[*tail++ = sink] = 0; head < tail;)
		for ( i = last[x = *head++]; i >= 0 ; i = next[i] )
			if ( cap[i^1] > flow[i^1] && visited[y = to[i]] != indeed )
				visited[*tail++ = y] = indeed, d[y] = d[x]+1;
	return visited[src]==indeed;
}

int maxflow() {
	int ax = 0,t,i;
	for ( i = 0; i < E; ++i ) flow[i] = 0;
	for(;bfs();)
		for (++yes;(t=dfs(src,max_capacity+1)); ax += t );
	return ax;
}

void add_arcs( int x, int y, int c ) {
	int i,j;
	if ( c <= 0 ) return ;
	i = E++, j = E++;
	to[i]=y,cap[i]=c,next[i]=last[x],last[x]=i;
	to[j]=x,cap[j]=0,next[j]=last[y],last[y]=j;
	flow[i] = flow[j] = 0;
	assert( (i^1) == j );
	assert( (j^1) == i );
}

unsigned char bt[1 << 20];

int who( u64 u ) {
	u64 i,j,k;
	assert( !(u&(u-1)) );
	if ( u < (1 << 20) )
		return bt[u];
	if ( u < (1ULL<<40) )
		return 20+bt[u>>20];
	return 40+bt[u>>40];
}

void collect( int x, int team_id, u64 *u ) {
	int y,i,t;
	visited[x] = indeed;
	if ( IS_TEAM(x) ) *u |= (1ull<<x);
	for ( i = last[x]; i >= 0; i = next[i] )
		if ( visited[y = to[i]] != indeed && flow[i] < cap[i] && y != sink && y != src )
			if ( y != team_id )
				collect(y,team_id,u);
}

void decide( int team_id ) {
	int i,j,k,l,t,x,y,
		optimistically_won = 0,
		undecided_games = 0,
		total = 0,T,m;
	u64 u,v,w;

	for ( j = 1; j <= n; ++j )
		optimistically_won += games_left[team_id][j];

	max_capacity = wins[team_id]+optimistically_won;

	for ( i = 1; i <= n; ++i )
		if ( i != team_id && wins[i] > max_capacity ) {
			printf("Team %s is eliminated.\n",tname[team_id]);
			printf("They can win at most %d + %d = %d games.\n",wins[team_id],optimistically_won,max_capacity);
			printf("%s have won a total of %d games.\n",tname[i],wins[i]);
			printf("They play each other %d times.\n",games_left[i][i]);
printf("So, on average, each of the teams wins (%d+%d)/1 = %d games which is greater than %d.\n\n",wins[i],games_left[i][i],wins[i],max_capacity);
			return ;
		}

	for ( i = 1; i <= n; ++i )
		if ( i != team_id ) 
		for ( j = i+1; j <= n; ++j )
			if ( j != team_id )
				if ( games_left[i][j] && (total += games_left[i][j]) )
					++undecided_games;

	E = 0, V = 1+undecided_games+n+1;

	for ( i = 0; i < V; last[i++] = -1 );
	for ( src = 0, sink = V-1, i = 1; i <= n; ++i )
		if ( i != team_id )
			add_arcs(i,sink,max_capacity-wins[i]);
	for ( k = n+1, i = 1; i <= n; ++i )
		if ( i != team_id )
		for ( j = i+1; j <= n; ++j )
			if ( j != team_id )
				if ( games_left[i][j] ) {
					assert( i != j );
					gid[i][j] = x = k++;
					/*add_arcs(x,y,games_left[i][j]);*/
					add_arcs(src,x,games_left[i][j]);
					add_arcs(x,e[x][0] = i,games_left[i][j]);
					add_arcs(x,e[x][1] = j,games_left[i][j]);
				}
	assert( k == sink );

	assert( (l=maxflow()) <= total );
	if ( l == total )
		return ;

	assert( l < total );
	/*
	 * Now the fun begins
	 */
	for ( l = 0; l < E; ++l )
		if(IS_GAME(to[l])&&to[l^1]==src&&flow[l]<cap[l]){
			if ( e[to[l]][0]==team_id||e[to[l]][1]==team_id )
				continue ;
			u = (1ull<<e[to[l]][0])|(1ull<<e[to[l]][1]);
			for ( ++indeed; u; u -= L(u) )
				if ( visited[x = who(L(u))] != indeed ) {
					v = (1ull<<e[to[l]][0])|(1ull<<e[to[l]][1]);
					collect(x,team_id,&v);
					for ( ptr = out, w = v; w; *ptr++ = who(L(w)), w -= L(w) );
					for ( m = ptr-out, T = 0, i = 0; i < m; ++i )
						for ( j = i+1; j < m; ++j )
							T += games_left[out[i]][out[j]];
					for ( total = 0, i = 0; i < m; ++i )
						total += wins[out[i]];

					if ( total+T <= m*max_capacity )
						continue ;

					printf("Team %s is eliminated.\n",tname[team_id]);
					printf("They can win at most %d + %d = %d games.\n",wins[team_id],optimistically_won,max_capacity);
					for ( i = 0; i < m-2; ++i )
						printf("%s, ",tname[out[i]]);
					printf("%s and %s have won a total of %d games.\n",tname[out[i]],tname[out[i+1]],total);
					printf("They play each other %d times.\n",T);
					printf("So, on average, each of the teams wins (%d+%d)/%d = %.8Lf games which is greater than %d.\n\n",total,T,m,((long double)total+T+0.0)/m,max_capacity);
					return ;
				}
		}
}

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 0; k < 20; ++k ) bt[1 << k] = k;
	for(;1==scanf("%d",&n)&&n!=-1&&printf("Case %d:\n",++cs);putchar('\n')) {
		for ( i = 1; i <= n; ++i ) {
			scanf("%s %d %d %d",tname[i],wins+i,&j,&k);
			for ( j = 1; j <= n; scanf("%d",&games_left[i][j++]) );
			for ( j = 1; j <= n; ++j )
				k -= games_left[i][j];
			assert( !k );
		}
		for ( i = 1; i <= n; decide(i++) );
	}
	return 0;
}

