/*
 * 1197. The Suspects
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
#define N 30100
#define M 512

int n,m,rank[N],p[N];

void link( int x, int y ) {
	if ( rank[x] > rank[y] )
		p[y] = x;
	else {
		if ( rank[x] == rank[p[x] = y] )
			++rank[y];
	}
}

int find( int x ) { return p[x] = (p[x]==x)?x:find(p[x]);  }

void merge( int x, int y ) { link(find(x),find(y)); }

void make_set( int x ) { rank[p[x]=x]=0; }

int main() {
	int i,j,k,l;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;2==scanf("%d %d",&n,&m)&&(n||m);printf("%d\n",k)){
		for ( i = 0; i < n; ++i ) make_set(i);
		for ( l = 0; l < m; ++l ) 
			for ( scanf("%d %d",&k,&i); --k; scanf("%d",&j), merge(i,j) );
		for ( i = find(0), k = 0, j = 0; j < n; ++j )
			if ( find(j) == i ) ++k;
	}
	return 0;
}
