/*
 * 11464. Even Parity
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 16
#define enc(x,y) ((x)|((y)<<4))
#define MAXE (1 << 21)
#define valid_cell(x,y) (1<=(x)&&(x)<=n&&1<=(y)&&(y)<=n)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

int n,c[N][N],p[N][N],next[MAXE],to[MAXE],last[1<<10],
	dx[]={-1,0,1, 0},v[1<<10],m,E,
	dy[]={ 0,1,0,-1},best_cost,
	varname[N*N+N],id[N*N+N],
	A[N*N][N*N],B[N*N];

unsigned long long a[(1ULL << 9)];
#define SET(k) (a[(k)>>6] |= (1ULL<<((k)&63ULL)))
#define XOR(k) (a[(k)>>6] ^= (1ULL<<((k)&63ULL)))
#define CLR(k) (a[(k)>>6] &= ~(1ULL<<((k)&63ULL)))
#define TST(k) (a[(k)>>6] &  (1ULL<<((k)&63ULL)))

int is_solution() { return !a[0]&&!a[1]&&!a[2]&&!a[3]&&!a[4]&&!a[5]&&!a[6]; }

void rec( int cur, int cost ) {
	unsigned long long old_a[7];
	int i,j;
	if ( cost >= best_cost )
		return ;
	if ( cur == m )
		return ;
	if ( is_solution() ) {
		best_cost = cost;
		return ;
	}
	for ( j = cur; j < m; ++j ) {
		for ( i = 0; i < 7; ++i ) old_a[i] = a[i];
		for ( i = last[v[j]]; i >= 0; i = next[i] ) 
			XOR(to[i]);
		rec(j+1,cost+1);
		for ( i = 0; i < 7; ++i ) a[i] = old_a[i];
	}
}

int find_pivot( int k, int *row, int *col ) {
	int i,j;
	for ( i = k; i < m; ++i )
		for ( j = k; j < n; ++j )
			if ( A[i][j] ) {
				*row = i, *col = j;
				return 1;
			}
	return 0;
}

void swap_rows( int i1, int i2 ) {
	int j;
	for ( j = 0; j < n; ++j )
		xchg(A[i1][j],A[i2][j]);
	xchg(B[i1],B[i2]);
}

void swap_cols( int j1, int j2 ) {
	int i;
	for ( i = 0; i < m; ++i )
		xchg(A[i][j1],A[i][j2]);
	xchg(id[j1],id[j2]);
}

int main() {
	int i,j,k,ts,cs = 0,row,col,s,x[N*N+N],
		ni,nj,l,t,u,flag;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(scanf("%d",&ts);ts--&&printf("Case %d: ",++cs)&&scanf("%d",&n)==1;){
		memset(c,0,sizeof(c));
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%d",&c[i][j]), last[enc(i,j)] = -1;
		memset(p,0,sizeof(p));
		memset(a,0,sizeof(a)), E = 0;
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j ) 
				for ( k = 0; k < 4; ++k ) {
					ni = i+dx[k], nj = j+dy[k];
					p[i][j] += c[ni][nj], p[i][j] &= 1;
					if ( valid_cell(ni,nj) && c[ni][nj] == 0 ) {
						to[t = E++] = enc(i,j);
						u = enc(ni,nj);
						next[t] = last[u], last[u] = t;
					}
					if ( p[i][j] )
						SET(enc(i,j));
				}
		for ( m = 0, i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				if ( c[i][j] == 0 )
					(varname[v[m] = enc(i,j)] = m), ++m;
		for ( l = 0, i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j ) {
				for ( flag = B[l] = 0, t = 0; t < m; ++t ) A[l][t] = 0;
				for ( k = 0; k < 4; ++k ) {
					ni = i+dx[k], nj = j+dy[k];
					if ( !valid_cell(ni,nj) ) continue ;
					if ( c[ni][nj] ) ++B[l], B[l] &= 1;
					else ++flag, ++A[l][t = varname[enc(ni,nj)]], A[l][t] &= 1;
				}
				if ( B[l] && !flag ) {
					puts("-1");
					goto NX;
				}
				if ( flag ) ++l;
			}
		for ( k = 0; k < l; ++k ) 
			if ( B[k] ) {
				for ( j = 0; j < m; ++j )
					if ( A[k][j] ) goto nx;
				puts("-1");
				goto NX;
				nx: continue ;
			}
		n = m, m = l;
		best_cost = 0;
		for ( i = 0; i < n; ++i ) id[i] = i;
		for ( k = 0; k < m && k < n; ++k ) {
			if ( !find_pivot(k,&row,&col) ) {
				for ( i = k; i < m; ++i )
					if ( B[i] ) {
						puts("-1");
						goto NX;
					}
				break ;
			}
			swap_rows(k,row);
			swap_cols(col,k);
			assert(A[k][k]==1);
			for ( i = k+1; i < m; ++i ) 
				if ( A[i][k] ) {
					for ( j = k; j < n; ++j )
						A[i][j]-=A[k][j], A[i][j]+=2, A[i][j]&=1;
					B[i]-=B[k], B[i]+=2, B[i]&=1;
				}
		}
		for ( i = k; i < m; ++i )
			if ( B[i] ) {
				puts("-1");
				goto NX;
			}
		for ( j = k; j < n; ++j ) x[id[j]] = 0;
		for ( j = k-1; j >= 0;  --j ) {
			for ( s = 0, l = j+1; l < n; ++l ) s += A[j][l]*x[id[l]], s &= 1;
			B[j]-=s, B[j]+=2, B[j]&=1;
			x[id[j]] = B[j];
			if ( x[id[j]] ) ++best_cost;
		}
		rec(0,0);
		/*if ( best_cost <= n*n ) */
			printf("%d\n",best_cost);
		NX: continue ;
	}
	return 0;
}

