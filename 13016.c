/*
 * 13016. Black Vienna
 * TOPIC: 2-sat
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 32
#define A 26
#define MAXN 0x400
#define MAXE (1<<20)
#define enc(i,j,k) ((j)|((k)<<1)|((i)<<2))
enum { D, T };

int to[2][MAXE],next[2][MAXE],last[2][MAXN],E[2],
	inv,aa[MAXN],bb[MAXN],who[MAXN],val[MAXN],
	scc[MAXN],mark,st[MAXN],*top,visited[MAXN],yes;

void add_arcs( int x, int y ) {
	int i = E[D]++, j = E[T]++;
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

void add_or( int x, int y ) { add_arcs(x^1,y), add_arcs(y^1,x); }

void dfs( int x, int t ) {
	int i,y;
	assert( visited[x] != yes );
	for ( visited[x] = yes, i = last[t][x]; i >= 0; i = next[t][i] )
		if ( visited[y = to[t][i]] != yes )
			dfs(y,t);
	if ( t ) *++top = x;
	else scc[x] = mark;
}

int solvalble( int a, int b, int c ) {
	int i,j,k,x;

	for ( E[D]=E[T]=0, i=0; i<A; ++i )
		for ( j=0; j<2; ++j )
			for ( k=0; k<2; ++k )
				last[D][enc(i,j,k)]=last[T][enc(i,j,k)]=-1;
	for ( i = 0; i < inv; ++i )
		switch ( val[i] ) {
			case 0: add_or(enc(aa[i],1,who[i]),enc(aa[i],1,who[i]));
					add_or(enc(bb[i],1,who[i]),enc(bb[i],1,who[i]));
					break ;
			case 1: add_or(enc(aa[i],0,who[i]),enc(bb[i],0,who[i]));
					add_or(enc(aa[i],1,who[i]),enc(bb[i],1,who[i]));
					break ;
			case 2: add_or(enc(aa[i],0,who[i]),enc(aa[i],0,who[i]));
					add_or(enc(bb[i],0,who[i]),enc(bb[i],0,who[i]));
					break ;
			default: assert( 0 );
		}
	add_or(enc(a,1,0),enc(a,1,0)); add_or(enc(a,1,1),enc(a,1,1));
	add_or(enc(b,1,0),enc(b,1,0)); add_or(enc(b,1,1),enc(b,1,1));
	add_or(enc(c,1,0),enc(c,1,0)); add_or(enc(c,1,1),enc(c,1,1));
	for ( i = 0; i < A; ++i )
		if ( i != a && i != b && i != c ) 
			add_or(enc(i,0,0),enc(i,0,1)), add_or(enc(i,1,0),enc(i,1,1));
	for ( ++yes, top = st, i = 0; i < A; ++i )
		for ( j = 0; j < 2; ++j )
			for ( k = 0; k < 2; ++k )
				if ( visited[x = enc(i,j,k)] != yes )
					dfs(x,T);
	for ( ++yes, mark = 0; top > st; )
		if ( visited[x = *top--] != yes )
			++mark, dfs(x,D);
	for ( i = 0; i < A; ++i )
		for ( k = 0; k < 2; ++k )
			if ( scc[enc(i,0,k)] == scc[enc(i,0,k)^1] )
				return 0;
	return 1;
}

int main() {
	int i,j,k,ans;
	char tmp[0x20];
#ifndef ONLINE_JUDGE
	freopen("13016.in","r",stdin);
#endif
	for (;1==scanf("%d",&inv) && inv>=0; printf("%d\n",ans) ) {
		for ( i = 0; i < inv; ++i )
			scanf("%s %d %d",tmp,who+i,val+i), --who[i], aa[i] = 0[tmp]-'A', bb[i] = 1[tmp]-'A';
		for ( ans = 0, i = 0; i < A; ++i )
			for ( j = i+1; j < A; ++j )
				for ( k = j+1; k < A; ++k ) 
					ans += solvalble(i,j,k);
	}
	return 0;
}

