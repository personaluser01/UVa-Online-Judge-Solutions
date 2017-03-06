/*
 * 10864. The Predator
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N    5
#define MAXR 10000
#define L(i) ((i)&((~(i))+1))
typedef long long i64;

char bts[1 << N];
i64 max( i64 x, i64 y ) { return x < y ? y : x; }
i64 min( i64 x, i64 y ) { return x < y ? x : y; }

i64 n,cs,who[1 << N],
	x[N],y[N],r[N],
	nx[1 << N],ny[1 << N],nw[1 << N],nh[1 << N];

int inside( int i, i64 a, i64 b, i64 k ) {
	return x[i] <= a && a+k <= x[i]+r[i] && y[i] <= b && b+k <= y[i]+r[i];
}

i64 Area( unsigned int u ) {
	return nh[u]*nw[u];
}

int main() {
	int i,j,k,l,t,q;
	unsigned int u,v,uu,B;
	i64 Union,ax;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(u=0;u<(1<<N);++u) bts[u] = bts[u>>1]+(u&1);
	for ( i = 0; i < N; ++i )
		who[1<<i]=i;
	for(;1 == scanf("%lld",&n) && printf("Case %lld:\n",++cs);) {
		for ( i = 0; i < n; ++i )
			scanf("%lld %lld %lld",x+i,y+i,r+i), --x[i], --y[i];
		nx[0] = ny[0] = 0, nw[0] = nh[0] = MAXR;
		for ( u = 1; u < (1UL << n); ++u ) {
			nw[u] = nh[u] = 0;
			i = who[L(u)], v = u-L(u);
			if ( !nw[v]||!nh[v] ) 
				continue ;
			/*
			if ( nx[v]+nw[v] <= x[i] )
				continue ;
			if ( x[i]+r[i] <= nx[v] )
				continue ;
			if ( ny[v]+nh[v] <= y[i] )
				continue ;
			if ( y[i]+r[i] <= ny[v] )
				continue ;
			if ( nw[v] <= 0||nh[v] <= 0 ) 
				continue ;
			*/
			nx[u]=max(x[i],nx[v]), nw[u]=min(x[i]+r[i],nx[v]+nw[v])-nx[u];
			ny[u]=max(y[i],ny[v]), nh[u]=min(y[i]+r[i],ny[v]+nh[v])-ny[u];
			nw[u]=max(0,nw[u]);
			nh[u]=max(0,nh[u]);
		}
		for ( scanf("%d",&q); q-- && 2 == scanf("%d %d",&i,&j); ) {
			--i, --j;
			for ( u = 0, t = 0; t < n; ++t )
				if ( inside(t,i,j,1) ) 
					u += (1UL<<t);
			/*
			for ( B = bts[uu = 0], u = 0; u < (1 << n); ++u )
				if ( nh[u] && nw[u] && nx[u] <= i && i+1 <= nx[u]+nw[u] )
					if ( ny[u] <= j && j+1 <= ny[u]+nh[u] ) 
						if ( B < bts[u] )
							B = bts[uu = u];
			u = uu;
			*/
			for ( ax = 0, v = 0; v < (1ul << n); ++v )
				if ( (u&v) == u ) {
					if ( !nh[v]||!nw[v] )
						continue ;
					k = bts[v]-bts[u];
					assert( k >= 0 );
					if ( k & 1 ) {
						printf("Subtracting %lld\n",nh[v]*nw[v]);
						ax -= nh[v]*nw[v];
					}
					else {
						printf("Adding %lld\n",nh[v]*nw[v]);
						ax += nh[v]*nw[v];
					}
				}
			if ( ax == 20 ) {
				printf("i = %d, j = %d, u = %u, n = %lld\n",i,j,u,n);
				printf("%lld %lld %lld %lld\n",nx[u],ny[u],nw[u],nh[u]);
			}
			printf("%lld\n",ax);
		}
	}
	return 0;
}
