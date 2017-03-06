/*
 * 1514. Piece it Together
 * TOPIC: 2-SAT
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define H 0x200
#define MAXV (1<<21)
#define MAXE (1<<21)
#define Q (1<<22)
enum { S, T };
enum { NORTH, WEST, SOUTH, EAST };
#define P(x) (0|((x)<<1))
#define N(x) (1|((x)<<1))
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

int m,n,V,E,to[2][MAXE],next[2][MAXE],last[2][MAXV],W,B,id[Q],
	dx[] = {-1,0,1,0},
	dy[] = {0,-1,0,1},
	*ptr,e[4],
	*top,st[MAXV],scc[MAXV],mark,
	seen[MAXV],yes;
char g[H][H];

void add_arcs( int x, int y ) {
	int i = E++;
	to[S][i] = y, next[S][i] = last[S][x], last[S][x] = i;
	to[T][i] = x, next[T][i] = last[T][y], last[T][y] = i;
}

void add_clause( int x, int y ) {
	add_arcs(x^1,y), add_arcs(y^1,x);
}

void dfs( int x, const int t ) {
	int i;
	if ( seen[x] == yes ) return ;
	for ( seen[x] = yes, i = last[t][x]; i >= 0; dfs(to[t][i],t), i = next[t][i] );
	if ( t ) *++top = x;
	else scc[x] = mark;
}

int main() {
	int i,j,k,l,ts,ni,nj,x,y,ok;
#ifndef ONLINE_JUDGE
	freopen("1514.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d %d",&m,&n) == 2; ) {
		for ( B = W = 0, i = 0; i < m; ++i )
			for ( scanf("%s",g[i]), j = 0; j < n; ++j )
				if ( g[i][j] == 'W' ) ++W;
				else if ( g[i][j] == 'B' ) ++B;
		if ( W != 2*B ) {
			puts("NO");
			continue ;
		}
		memset(id,-1,sizeof id);
		for ( V = 0, i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j ) 
				for ( k = NORTH; g[i][j] == 'B' && k <= EAST; ++k )
					if ( vc(ni=i+dx[k],nj=j+dy[k]) && g[ni][nj] == 'W' )
						id[i|(j<<9)|(k<<18)] = V++;
		for ( E = 0, x = 0; x < V; last[S][P(x)]=last[T][P(x)]=last[S][N(x)]=last[T][N(x)]=-1, ++x );
		for ( ok = 1, i = 0; i < m && ok; ++i )
			for ( j = 0; j < n && ok; ++j )
				if ( g[i][j] == 'B' ) {
					x = (i|(j<<9)|(EAST<<18)), y = (i|(j<<9)|(WEST<<18));
					if ( id[x] >= 0 && id[y] >= 0 )
						add_clause(P(id[x]),P(id[y])), add_clause(N(id[x]),N(id[y]));
					if ( id[x] < 0 && id[y] >= 0 )
						add_clause(P(id[y]),P(id[y]));
					if ( id[x] >= 0 && id[y] < 0 )
						add_clause(P(id[x]),P(id[x]));
					if ( id[x] < 0 && id[y] < 0 ) ok = 0;
					x = (i|(j<<9)|(SOUTH<<18)), y = (i|(j<<9)|(NORTH<<18));
					if ( id[x] >= 0 && id[y] >= 0 )
						add_clause(P(id[x]),P(id[y])), add_clause(N(id[x]),N(id[y]));
					if ( id[x] < 0 && id[y] >= 0 )
						add_clause(P(id[y]),P(id[y]));
					if ( id[x] >= 0 && id[y] < 0 )
						add_clause(P(id[x]),P(id[x]));
					if ( id[x] < 0 && id[y] < 0 ) ok = 0;
				}
		if ( !ok ) { puts("NO"); continue ; }
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == 'W' ) {
					for ( ptr = e, k = NORTH; k <= EAST; ++k )
						if ( vc(ni=i+dx[k],nj=j+dy[k]) && g[ni][nj] == 'B' ) 
							assert ( (*ptr++ = id[(ni|(nj<<9)|(((k+2)&3)<<18))]) >= 0 );
					for ( k = 0; k < ptr-e; ++k )
						for ( x = e[k], l = k+1; l < ptr-e; y = e[l++], add_clause(N(x),N(y)) );
				}
		for ( ++yes, top = st, x = 0; x < V; ++x ) {
			if ( seen[P(x)] != yes ) dfs(P(x),T);
			if ( seen[N(x)] != yes ) dfs(N(x),T);
		}
		for ( mark = 0, ++yes; top > st; )
			if ( seen[x = *top--] != yes )
				++mark, dfs(x,S);
		for ( k = 1, x = 0; x < V; ++x )
			if ( scc[P(x)] == scc[N(x)] ) {
				k = 0;
				break ;
			}
		puts(k?"YES":"NO");
	}
	return 0;
};





