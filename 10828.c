/*
 * 10828. Back to Kernighan-Ritchie
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define tol 1.0e-11
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

void swp( long double *a, long double *b ) {
	long double tmp = *a;
	*a = *b, *b = tmp;
}

int n,adj[N][N],cs,g[N][N],id[N],G[N][N],v[N],m,newname[N],
	indeg[N],outdeg[N],deg[N],
	fater[N][N],inf[N],yes,preset[N],ldeg[N];
long double A[N][N],x[N];
int queue[N],*head,*tail,is_reachable_at_all[N];

int find_pivot( int k, int *row, int *col ) {
	int i,j;
	long double max_so_far = 0;
	for ( *row = -1, i = k; i < m; ++i )
		for ( j = k; j < m; ++j )
			if ( fabs(A[i][j]) > tol ) 
				if ( fabs(A[i][j]) > max_so_far )
					max_so_far = fabs(A[*row = i][*col = j]);
	return *row != -1;
}

void dfs( int z ) {
	int i,nz;
	for ( i = 0; i < ldeg[z]; ++i ) 
		if ( inf[nz = adj[z][i]] != yes )
			inf[nz] = yes, dfs(nz);
}


void gaussian() {
	int i,j,k,l,row,col;
	long double cf;

	for ( i = 0; i < m; ++i ) id[i] = i;
	for ( k = 0; k < m; ++k ) {
		if ( !find_pivot(k,&row,&col) ) {
			for ( i = k; i < m; ++i )
				if ( is_reachable_at_all[i] == yes ) {
					if ( fabs(A[i][m]) > tol )
						if ( inf[id[i]] != yes )
							inf[id[i]] = yes, dfs(id[i]);
				}
			for ( i = k-1; i >= 0; --i )
				if ( preset[id[i]] != yes && inf[id[i]] != yes ) {
					for ( cf = 0, j = i+1; j < m; ++j )
						if ( inf[id[j]] != yes )
							cf += A[i][j]*x[id[j]];
					x[id[i]] = A[i][m]-cf;
				}
			return ;
		}
		for ( i = 0; i < m; ++i )
			swp(A[i]+k,A[i]+col);
		xchg(id[k],id[col]);
		for ( j = 0; j <= m; ++j )
			swp(A[k]+j,A[row]+j);
		assert( fabs(A[k][k]) > tol );
		for ( cf = A[k][k], j = 0; j <= m; ++j )
			A[k][j] /= cf;
		assert( fabs(A[k][k]-1)<tol );
		A[k][k] = 1.00;
		for ( i = k+1; i < m; ++i ) {
			for ( cf = A[i][k], j = k; j <= m; ++j )
				A[i][j] -= A[k][j]*cf;
			assert( fabs(A[i][k]) < tol );
		}
	}
	assert( fabs(A[m-1][m-1]-1) < tol );
	for ( x[id[m-1]] = A[m-1][m], i = m-2; i >= 0; --i ) {
		for ( cf = 0, j = i+1; j < m; ++j )
			if ( preset[id[j]] != yes )
				cf += x[id[j]]*A[i][j];
		x[id[i]] = (A[i][m]-cf); /* should be /A[i][], but A[i][i] == 1, so... */
	}
}

int main() {
	int i,j,k,l,qr,ii,jj;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		printf("Case #%d:\n",++cs);
		memset(g,0,sizeof(g));
		memset(indeg,0,sizeof(indeg));
		memset(outdeg,0,sizeof(outdeg));
		memset(ldeg,0,sizeof(ldeg));
		memset(deg,0,sizeof(deg));
		for (;2 == scanf("%d %d",&i,&j) && i > 0; ++g[--i][--j] );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j <= n; ++j )
				A[i][j] = 0;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) 
				if ( g[i][j] )
					indeg[j] += g[i][j], outdeg[i] += g[i][j], fater[j][deg[j]++] = i, adj[i][ldeg[i]++] = j;
		for ( head = tail = queue, is_reachable_at_all[*tail++ = 0] = ++yes; head < tail; )
			for ( i = *head++, l = 0; l < ldeg[i]; ++l )
				if ( is_reachable_at_all[j = adj[i][l]] != yes )
					is_reachable_at_all[*tail++ = j] = yes;
		for ( m = 0, i = 0; i < n; ++i )
			if ( is_reachable_at_all[i] == yes )
				newname[v[m] = i] = m, ++m;
		memset(indeg,0,sizeof(indeg));
		memset(outdeg,0,sizeof(outdeg));
		memset(ldeg,0,sizeof(ldeg));
		memset(deg,0,sizeof(deg));
		memset(G,0,sizeof(G));
		for ( i = 0; i < n; ++i )
			if ( is_reachable_at_all[i] == yes ) {
				ii = newname[i];
				for ( j = 0; j < n; ++j ) {
					if ( !g[i][j] )
						continue ;
					jj = newname[j];
					G[ii][jj] = g[i][j];
					outdeg[ii] += G[ii][jj];
					indeg[jj] += G[ii][jj];
					fater[jj][deg[jj]++] = ii;
					adj[ii][ldeg[ii]++] = jj;
				}
			}
		for ( A[0][m] = -1.00, i = 0; i < m; ++i )
			for ( A[i][i] = -1.00, l = 0; l < deg[i]; ++l ) {
				j = fater[i][l];
				A[i][j] += ((long double)(G[j][i]))/outdeg[j];
			}
		for ( gaussian(), scanf("%d",&qr); qr--; ) {
			scanf("%d",&i);
			if ( is_reachable_at_all[--i] != yes ) {
				puts("0.000");
				continue ;
			}
			if ( inf[newname[i]] == yes ) {
				puts("infinity");
				continue ;
			}
			printf("%.3Lf\n",x[newname[i]]+1e-9);
		}
	}
	return 0;
}
