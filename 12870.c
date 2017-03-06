/*
 * 12870. Fishing
 * TOPIC: DP
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SH 		 7
#define BIT(k)   (1LL<<(k))
#define MASK(k)  (BIT(k)-1ULL)
#define N 		 BIT(SH)
#define Q 		 BIT(SH+SH)
#define enc(x,y) ((x)|((y)<<SH))
typedef long long i64;
#define oo BIT(45)
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

i64 a[Q][N],b[Q][N],c[Q],w;
int m,n,K;

int main() {
	int i,j,k,t,ts;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n); printf("%lld\n",w) ) {
		for ( K=(m<n?n:m), i=0; i<m; ++i )
			for ( j=0; j<n; ++j )
				scanf("%lld",&c[enc(i,j)]);
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k <= K; ++k ) {
					a[enc(i,j)][k] = -oo;
					b[enc(i,j)][k] = +oo;
				}
		/*
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				a[enc(i,j)][0] = b[enc(i,j)][0] = 0;
				*/
		for ( k = 1; k <= K; ++k )
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j ) {
					u = enc(i,j);
					if ( vc(i-1,j-1) && a[v = enc(i-1,j-1)][k-1] > -oo )
						if ( a[v][k-1]+c[u] > a[u][k] )
							a[u][k] = a[v][k-1]+c[u];
					if ( vc(i-1,j-1) && a[v=enc(i-1,j-1)][k] > -oo )
						if ( a[v][k] > a[u][k] ) a[u][k] = a[v][k];
					if ( k == 1 && a[u][k] < c[u] )
						a[u][k] = c[u];
					if ( vc(i-1,j) && a[v=enc(i-1,j)][k] > -oo )
						if ( a[v][k] > a[u][k] ) a[u][k] = a[v][k];
					if ( vc(i,j-1) && a[v=enc(i,j-1)][k] > -oo )
						if ( a[v][k] > a[u][k] ) a[u][k] = a[v][k];
					if ( vc(i-1,j-1) && b[v = enc(i-1,j-1)][k-1] < +oo )
						if ( b[v][k-1]+c[u] < b[u][k] )
							b[u][k] = b[v][k-1]+c[u];
					if ( vc(i-1,j-1) && b[v = enc(i-1,j-1)][k] < +oo )
						if ( b[v][k] < b[u][k] ) b[u][k] = b[v][k];
					if ( k == 1 && b[u][k] > c[u] )
						b[u][k] = c[u];
					if ( vc(i-1,j) && b[v=enc(i-1,j)][k] < +oo )
						if ( b[v][k] < b[u][k] ) b[u][k] = b[v][k];
					if ( vc(i,j-1) && b[v=enc(i,j-1)][k] < +oo )
						if ( b[v][k] < b[u][k] ) b[u][k] = b[v][k];
				}
		for ( w = 0, i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				for ( u = enc(i,j), k = 1; k <= K; ++k )
					for ( t = k+k; a[u][k] > -oo && t <= K; ++t )
						if ( b[u][t] < +oo )
							if ( w < a[u][k]-b[u][t] ) 
								w = a[u][k]-b[u][t];
	}
	return 0;
}

