/*
 * 1560. Extended Lights Out
 * TOPIC: systems of linear equations
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define enc(x,y) ((x)*n+(y))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

int c[N][N],m,n,b[N],A[N][N],V,id[N],x[N],
	di[] = {-1,0,1,0,0},
	dj[] = {0,1,0,-1,0};

int pivot( int k, int *r, int *c ) {
	int i,j;
	for ( i = k; i < V; ++i )
		for ( j = k; j < V; ++j )
			if ( A[i][j] ) {
				*r = i, *c = j;
				return 1;
			}
	assert( 0 );
	return 0;
}

void swap_cols( int j1, int j2 ) {
	int i;
	for ( i = 0; i < V; ++i )
		xchg(A[i][j1],A[i][j2]);
	xchg(id[j1],id[j2]);
}

void swap_rows( int i1, int i2 ) {
	int j;
	for ( j = 0; j < V; ++j )
		xchg(A[i1][j],A[i2][j]);
	xchg(b[i1],b[i2]);
}


int main() {
	int i,j,k,l,t,ni,nj,cs=0,ts,u,v,row,col,s;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( m=5,n=6,V=enc(m-1,n-1)+1,scanf("%d",&ts); ts-- && printf("PUZZLE #%d\n",++cs); ) {
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; scanf("%d",&c[i][j++]) );
		memset(A,0,sizeof A), memset(b,0,sizeof b);
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; b[enc(i,j)] = c[i][j],  ++j )
				for ( k = 0; k < 5; ++k ) 
					if ( vc(ni=i+di[k],nj=j+dj[k]) )
						u = enc(ni,nj), v = enc(i,j), A[u][v] = 1;
		for ( i = 0; i < V; id[i] = i, ++i );
		for ( k = 0; k < V-1; ++k ) 
			for ( pivot(k,&row,&col), swap_cols(col,k), swap_rows(row,k), i = k+1; i < V; ++i )
				if ( A[i][k] ) {
					for ( j = k; j < V; A[i][j++] &= 1 )
						for ( A[i][j] -= A[k][j]; A[i][j] < 0; A[i][j] += 2 );
					for ( b[i] -= b[k]; b[i] < 0; b[i] += 2 );
					b[i] &= 1;
				}
		for ( x[id[V-1]] = b[V-1], i = V-2; i >= 0; x[id[i]] = ((b[i]-s+2)&1), --i )
			for ( s = 0, j = i+1; j < V; ++j )
				s += A[i][j]*x[id[j]], s &= 1;
		for ( i = 0; i < m; ++i ) 
			for ( j = 0; j < n; ++j )
				printf("%d%c",x[enc(i,j)],j==n-1?'\n':' ');
	}
    return 0;
}

