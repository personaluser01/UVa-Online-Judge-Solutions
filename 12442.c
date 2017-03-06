/*
 * 12442. Forwarding Email
 * status: Accepted
 * TOPIC: scc, strongly-connected components
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 16)
#define oo 0xfffffffful
#define MAXE (2*N)
enum { D, T, R, S };

int V,E,n,m,to[4][MAXE],next[4][MAXE],last[4][N],*top,st[N],scc[N],mark,seen[N],yes,card[N],smallest[N];
unsigned int z[N];

void add_arcs( int x, int y ) {
	int i = E++;
   	int j = i;
	assert( x != y );
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

void dfs( int x, const int t ) {
	int i,y;
	if ( seen[x] == yes ) return ;
	for ( seen[x] = yes, i = last[t][x]; i >= 0; i = next[t][i] )
		if ( seen[y = to[t][i]] != yes )
			dfs(y,t);
	if ( t == T ) *++top = x;
	else scc[x] = mark;
}

void floodfill( int x ) {
	int i,j,y;
	assert( seen[x] != yes );
	for ( seen[x] = yes, i = last[D][x]; i >= 0; i = next[D][i] ) {
		if ( seen[y = to[D][i]] != yes ) floodfill(y);
		if ( scc[x] != scc[y] ) {
			j = E++, to[R][j] = scc[y], next[R][j] = last[R][scc[x]], last[R][scc[x]] = j;
			to[S][j] = scc[x], next[S][j] = last[S][scc[y]], last[S][scc[y]] = j;
		}
	}
}

unsigned int calc_z( int x ) {
	int i,y,k;
	if ( z[x] < +oo )
		return z[x];
	for ( k = 0, z[x] = card[x], i = last[R][x]; i >= 0; i = next[R][i], ++k ) {
		z[x]+=calc_z(y=to[R][i]);
		assert( x != y );
	}
	return z[x];
}

int main() {
	int i,j,k,cs = 0,ts,t,l;
	unsigned int w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n) && printf("Case %d: ",++cs); printf("%d\n",++j) ) {
		for ( i = 0; i < n; ++i )
			for ( t = D; t <= S; ++t )
				last[t][i] = -1;
		for ( E = 0, i = 0; i < n; ++i ) 
			scanf("%d %d",&j,&k), add_arcs(--j, --k);
		for ( top = st, ++yes, i = 0; i < n; ++i ) 
			if ( seen[i] != yes ) 
				dfs(i,T);
		for ( mark = 0, ++yes; top > st;)
			if ( seen[i = *top--] != yes ) 
				card[++mark] = 0, dfs(i,D);
		for ( i = 0; i < n; ++card[scc[i++]] );
		for ( i = 1; i <= mark; ++i )
			smallest[i] = n+1;
		for ( i = 0; i < n; ++i )
			if ( smallest[scc[i]] > i )
				smallest[scc[i]] = i;
		for ( E = 0, ++yes, i = 0; i < n; ++i ) 
			if ( seen[i] != yes ) 
				floodfill(i);
		memset(z,0xff,sizeof z);
		for ( i = 1; i <= mark; calc_z(i++) );
		/*
		for ( i = 1; i <= mark; ++i ) {
			printf("z[%d] = %u,  ",i,z[i]);
			for ( j = 0; j < n; ++j )
				if ( scc[j] == i )
					printf(" %d",j+1);
			puts("");
		}
		*/
		for ( w = 0, i = 1; i <= mark; ++i ) 
			if ( z[i] > w || z[i] == w && smallest[i] < j )
				w = z[i], j = smallest[i];
	}
	return 0;
}

