/*
 * 11363. Cuckoo Hashing
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
#define N 10100
enum { S, T };

int mate[2][N],visited[N],yes,n[2],adj[N][2];

int alt_path( int x ) {
	int i,y;
	if ( visited[x]==yes )
		return 0;
	for ( visited[x]=yes, i = 0; i < 2; ++i ) {
		if ( mate[T][y=adj[x][i]]<0||alt_path(mate[T][y]) ) {
			mate[S][mate[T][y] = x] = y;
			return 1;
		}
	}
	return 0;
}

int solve() {
	int x;
	for ( x = 0; x < n[S]; ++x ) 
		if ( !(++yes && alt_path(x)) )
			return 0;
	return 1;
}

int main() {
	int i,j,k,t,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",n,n+T);
		for ( i = 0; i < n[S]; ++i )
			for ( j = 0; j < 2; ++j )
				scanf("%d",adj[i]+j);
		memset(mate,-1,sizeof(mate));
		puts(solve()?"successful hashing":"rehash necessary");
	}
	return 0;
}
