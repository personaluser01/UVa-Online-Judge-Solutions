/*
 * 1281. Bus Tour
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k)    ((k)&((~(k))+1ULL))
#define N 21
#define oo (0xfffffffful)
#define TST(u,i) (((u)>>(i))&1ULL)
enum { HEAD = 0, ATTR = 1 };

unsigned int w[N][N],z[2][BIT(N)][N],adj[N],
			 d[2][BIT(N)],ans;
char which[BIT(N)],bts[BIT(N)];
int m,n,h;

int main() {
	int i,j,k,cs=0,l,t;
	unsigned int u,v,e,cu;
#ifndef ONLINE_JUDGE
	freopen("1281.in","r",stdin);
#endif 
	for ( i = 0; i < N; which[BIT(i)] = i, ++i );
	for ( u = 0; u < BIT(N); bts[u] = bts[u>>1]+(u&1), ++u );
	for(;2 == scanf("%d %d",&n,&m); ) {
		for ( i = 0; i < n; ++i )
			for ( adj[i] = 0, j = i+1; j < n; w[j][i] = w[i][j] = +oo, ++j );
		for( l = 0; l < m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), w[i][j]=w[j][i]=k, adj[j]|=BIT(i), adj[i]|=BIT(j);
		for ( printf("Case %d: ",++cs), h = n-2, t = HEAD; t <= ATTR; ++t )
			for ( u = 0; u < BIT(n); ++u )
				for ( d[t][u] = +oo, i = 0; i < n; z[t][u][i] = +oo, ++i );
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( w[i][k] < +oo && w[k][j] < +oo )
						if ( w[i][k] + w[k][j] < w[i][j] )
							w[i][j] = w[i][k]+w[k][j];
		for ( i = 0; i < n; adj[i++] = MASK(n) );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				assert( w[i][j] == w[j][i] );

		for ( t = HEAD; t <= ATTR; ++t )
			for ( i = 1; i <= n-2; ++i )
				if ( w[t*(n-1)][i] < +oo )
					z[t][BIT(i)][i] = w[t*(n-1)][i];

		for ( t = HEAD; t <= ATTR; ++t )
			for ( u = 0; u < BIT(n); u += 2 )
				if ( !TST(u,n-1) )
					for ( v = u; v && (i=which[L(v)]) >= 0; v &= ~L(v) )
						for ( e = (u&~L(v))&adj[i]; e && (j=which[L(e)]) >= 0; e &= ~L(e) )
							if ( z[t][u&~L(v)][j]<+oo && w[j][i]<+oo && z[t][u&~L(v)][j]+w[j][i]<z[t][u][i] )
								z[t][u][i]=z[t][u&~L(v)][j]+w[j][i];
		if ( h == 1 ) {
			printf("%u\n",2*(z[HEAD][BIT(1)][1]+z[ATTR][BIT(1)][1]));
			continue ;
		}
		/*
		for ( i = 1; i <= n-2; ++ i) 
			printf("%u\n",z[HEAD][MASK(h)<<1][i]);
			*/

		for ( t = HEAD; t <= ATTR; ++t )
			for ( d[t][0] = 0, u = 2; u < BIT(n); u += 2 )
				if ( !TST(u,n-1) && bts[u]==h-(h>>1) )
					for ( v = u; v && (i=which[L(v)]) >= 0; v&=~L(v) )
						if ( z[t][u][i]<+oo )
							for ( e=(MASK(n)&~u); e && (j=which[L(e)]) >= 0; e&=~L(e) )
								if ( z[t^1][cu = MASK(n)&~u&~BIT(0)&~BIT(n-1)][j] < +oo && w[i][j] < +oo )
									if ( z[t][u][i]+z[t^1][cu][j]+w[i][j]<d[t][u] ) 
										d[t][u]=z[t][u][i]+z[t^1][cu][j]+w[i][j];

		for ( ans = +oo, u = 0; u < BIT(n); u += 2 )
			if ( !TST(u,n-1) && bts[u]==h-(h>>1) )
				if ( d[HEAD][u]<+oo && d[ATTR][u]<+oo )
					if ( d[HEAD][u]+d[ATTR][u]<ans )
						ans=d[HEAD][u]+d[ATTR][u];
		printf("%u\n",ans);
	}
	return 0;
}

