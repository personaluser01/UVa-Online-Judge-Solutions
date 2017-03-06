/*
 * 11838. Come and Go
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 2048
#define M (1 << 21)
enum { D, T };

int n,m,E[2],next[2][M],last[2][N];
short to[2][M],st[N],*top,seen[N],yes;

int add_arcs( int x, int y ) {
	int i = E[D]++, j = E[T]++;
	assert( E[D] < M );
	assert( E[T] < M );
	next[D][i] = last[D][x], to[D][i] = y, last[D][x] = i;
	next[T][j] = last[T][y], to[T][j] = x, last[T][y] = j;
	return 1;
}

void dfs( int x, int t ) {
	int i,y;
	for ( seen[x] = yes, i = last[t][x]; i >= 0; i = next[t][i] ) 
		if ( seen[y = to[t][i]] != yes ) 
			dfs(y,t);
	if ( t == D ) *++top = x;
}

int main() {
	int i,j,k,cc;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2==scanf("%d %d",&n,&m) && (n||m);){
		for ( k = D; k <= T; ++k )
			for ( i = 0; i < n; ++i )
				last[k][i] = -1;
		for( E[D]=E[T]=0; m-- && 3 == scanf("%d %d %d",&i,&j,&k);)
			--i,--j,add_arcs(i,j),(k==2)&&add_arcs(j,i);
		for ( ++yes, cc = 0, top = st, i = 0; i < n && cc <= 1; ++i )
			if ( seen[i] != yes && (++cc) <= 1 ) 
				dfs(i,D);
		if ( cc >= 2 ) {
			puts("0");
			continue ;
		}
		for( cc = 0, ++yes; top > st && cc <= 1; )
			if ( seen[i = *top--] != yes && (++cc) <= 1 )
				dfs(i,T);
		puts(cc<=1?"1":"0");
	}
	return 0;
}
