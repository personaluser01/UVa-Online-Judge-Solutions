/*
 * 11464. Even Parity
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
#define N 16
#define valid_cell(x,y) (1<=(x)&&(x)<=n&&1<=(y)&&(y)<=n)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define is_assignment(v,t) ((v)==0 && (t)==1)

int n,c[N+10][N+10],a[N+10][N+10],p[N+10][N+10],
	dx[]={-1,0,1, 0},m,col[N+10],
	dy[]={ 0,1,0,-1},best_cost;

int main() {
	int i,j,k,ts,cs = 0,
		ni,nj,l,t,ass,e;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(scanf("%d",&ts);ts--&&printf("Case %d: ",++cs)&&scanf("%d",&n)==1;){
		memset(c,0,sizeof(c));
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%d",&c[i][j]);
		for ( k = 0, j = 1; j <= n; ++j )
			if ( !c[2][j] ) col[k++] = j;
		best_cost = n*n*n+4*n;
		memset(a,0,sizeof(a));
		for ( u = 0; u < (1 << k); ++u ) 
			for ( t = c[1][1]; t <= 1; ++t ) {
				for ( i = 1; i <= n; ++i )
					for ( j = 1; j <= n; ++j )
						a[i][j] = c[i][j];
				for ( ass = 0, l = 0; l < k; ++l ) {
					/*assert( a[2][col[l]] == 0 );*/
					if ( is_assignment(a[2][col[l]],(u>>l)&1) ) ++ass;
					a[2][col[l]] = (u>>l)&1;
				}
				if ( a[1][1] && !t ) goto next;
				if ( is_assignment(a[1][1],t) ) ++ass;
				a[1][1] = t;
				for ( j = 2; j <= n; ++j ) {
					e = (4-a[1][j-2]-a[2][j-1])&1;
					if ( a[1][j] && !e )
						goto next;
					if ( is_assignment(a[1][j],e) ) ++ass;
					a[1][j] = e;
				}
				for ( i = 3; i <= n; ++i ) 
					for ( j = 1; j <= n; ++j ) {
						e = (4-a[i-2][j]-a[i-1][j+1]-a[i-1][j-1])&1;
						if ( a[i][j] && !e )
							goto next;
						if ( is_assignment(a[i][j],e) ) ++ass;
						a[i][j] = e;
					}
				for ( i = 1; i <= n; ++i )
				for ( j = 1; j <= n; ++j ) {
					e = (4-a[i-1][j]-a[i][j-1]-a[i][j+1]-a[i+1][j])&1;
					if ( e ) goto next;
				}
				if ( ass < best_cost ) best_cost = ass;
				next: continue ;
			}
		printf("%d\n",best_cost<=n*n?best_cost:-1);
	}
	return 0;
}

