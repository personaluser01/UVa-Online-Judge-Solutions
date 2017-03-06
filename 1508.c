/*
 * 1508. Equipment
 * TOPIC: sorting, dp, bitmasks, greedy
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 5
#define N (1<<16)
typedef unsigned long long u64;

typedef struct { int c[M],w; } cell;

int cmp( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	return x->w==y->w?0:(x->w>y->w?-1:1);
}

int cmp00( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	return x->c[0]==y->c[0]?cmp(a,b):(x->c[0]>y->c[0]?-1:1);
}

int cmp01( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	return x->c[1]==y->c[1]?cmp(a,b):(x->c[1]>y->c[1]?-1:1);
}

int cmp02( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	return x->c[2]==y->c[2]?cmp(a,b):(x->c[2]>y->c[2]?-1:1);
}

int cmp03( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	return x->c[3]==y->c[3]?cmp(a,b):(x->c[3]>y->c[3]?-1:1);
}

int cmp04( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	return x->c[4]==y->c[4]?cmp(a,b):(x->c[4]>y->c[4]?-1:1);
}

cell c[M+1][N],e[N];
int m,n,K,z[M+1][32];
char bts[1<<8];

int f( unsigned int u ) {
	int i,j,k,l,t,w[M+1] = {0};
	for ( i = 0; i <= M; ++i )
		if ( (u>>i)&1 ) 
			for ( k = 0; k < M; ++k )
				if ( c[i][0].c[k] > w[k] )
					w[k] = c[i][0].c[k];
	for ( t = 0, k = 0; k < M; t += w[k++] );
	return t;
}


typedef int (*func) (const void*,const void*);
func CMP[] = {cmp00,cmp01,cmp02,cmp03,cmp04};

int main() {
	int i,j,k,t,l,ts,weight;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( u = 0; u < (1<<8); ++u )
		bts[u] = bts[u>>1]+(u&1);
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d %d",&n,&m), i = 0; i < n; ++i )
			for ( j = 0; j < M; scanf("%d",&c[M][i].c[j++]) );
		for ( i = 0; i < M; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < M; ++k )
					c[i][j].c[k] = c[M][j].c[k];
		for ( i = 0; i < M+1; ++i )
			for ( j = 0; j < n; ++j )
				for ( c[i][j].w = 0, k = 0; k < M; c[i][j].w += c[i][j].c[k++] );
		qsort(c[M],n,sizeof *c[M],cmp);
		for ( i = 0; i < M; ++i )
			qsort(c[i],n,sizeof *c[i],CMP[i]);
		if ( m == 1 ) {
			printf("%d\n",c[M][0].w);
			continue ;
		}
		if ( m >= M ) {
			for ( weight = 0, i = 0; i < M; ++i )
				weight += c[i][0].c[i];
			printf("%d\n",weight);
			continue ;
		}
		assert( 2 <= m && m <= M-1 );
		memset(z,0,sizeof z);
		for ( i = 0; i < n; ++i ) 
			for ( u = 0; u < (1<<M); ++u ) {
				for ( t = 0, k = 0; k < M; ++k )
					t += ((u>>k)&1)*c[M][i].c[k];
				if ( z[0][u] < t )
					z[0][u] = t;
			}
		for ( l = 1; l <= m; ++l ) 
			for ( u = 0; u < (1<<M); ++u )
				for ( v = 0; v < (1<<M); ++v )
					if ( !(u&v) ) 
						if ( z[l][u|v] < z[l-1][u]+z[0][v] )
							z[l][u|v] = z[l-1][u]+z[0][v];
		printf("%d\n",z[m-1][(1<<M)-1]);
	}
    return 0;
}

