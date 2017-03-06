/*
 * 10410. Tree Reconstruction
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
enum { BFS, DFS };
int inside( int i, int j, int t ) { return i <= t && t <= j; }
int c[2][N],inv[2][N],adj[N][N],deg[N],n;

void recover( int L, int R ) {
	int i,j,k,t,r;
	if ( L >= R ) return ;
	r = c[DFS][L], j = c[DFS][L+1];
	i = inv[BFS][j];
	assert( c[BFS][i] == j );
	for ( k = i+1; k < n && inside(L,R,inv[DFS][c[BFS][k]]) && c[BFS][k-1]<c[BFS][k] && inv[DFS][c[BFS][k-1]]<inv[DFS][c[BFS][k]]; ++k );
	for ( t = i; t < k; adj[r][deg[r]++] = c[BFS][t++] );
	for ( --k, t = i; t <= k-1; ++t )
		recover(inv[DFS][c[BFS][t]],inv[DFS][c[BFS][t+1]]-1);
	recover(inv[DFS][c[BFS][t]],R);
}

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(1==scanf("%d",&n)){
		for(t=BFS;t<=DFS;++t)
			for(i=0;i<n;scanf("%d",c[t]+i),inv[t][--c[t][i]]=i,++i);
		memset(deg,0,sizeof(deg)), recover(0,n-1);
		for(i=0;i<n;++i,putchar('\n'))
			for(printf("%d:",1+i),j=0;j<deg[i];printf(" %d",1+adj[i][j++]));
	}
	return 0;
}

