/*
 * 11095. Tabriz City
 * TOPIC: min vertex cover
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(u) ((u)&((~(u))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N 31
#define M (N*N)
#define TST(u,x) (((u)>>(x))&1ULL)
typedef unsigned long long u64;

int which[BIT(21)],bts[BIT(21)],n,m,x[M],y[M],g[N][N],yes,ans;
u64 u[N],best;
int Bits( const u64 u ) { return bts[(u>>20)&MASK(20)]+bts[u&MASK(20)]; }
int who( const u64 u )  { return u>=BIT(20)?20+who(u>>20):which[u];	    }

void f( int k, u64 mp ) {
	if ( k == m && Bits(mp) < ans )
		ans = Bits(mp), best = mp;
	if ( Bits(mp) >= ans ) return ;
	assert( k < m );
	if ( TST(mp,x[k])|TST(mp,y[k]) )
		f(k+1,mp);
	else {
	f(k+1,mp|BIT(x[k]));
	f(k+1,mp|BIT(y[k]));
	f(k+1,mp|BIT(x[k])|BIT(y[k]));
	assert( TST(u[x[k]],y[k]) );
	assert( TST(u[y[k]],x[k]) );
	f(k+1,mp|u[x[k]]);
	f(k+1,mp|u[y[k]]);
	f(k+1,mp|u[x[k]]|u[y[k]]);
	}
}

int main() {
	int i,j,k,ts,cs = 0;
	u64 v;
	for ( k = 0; k < BIT(21); ++k ) bts[k] = bts[k>>1]+(k&1);
	for ( k = 0; k < 21; ++k ) which[BIT(k)] = k;
	for ( scanf("%d",&ts); ts-- && ++yes && printf("Case #%d: ",++cs);) {
		for ( scanf("%d %d",&n,&m); m-- && 2 == scanf("%d %d",&i,&j); g[i][j]=g[j][i]=yes );
		for ( ++m,  i = 0; i < n; u[i++] = 0 );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				if ( g[i][j] == yes )
					x[m] = i, y[m++] = j, u[i]|=BIT(j),u[j]|=BIT(i);
		ans = (0x400), f(0,0);
		if ( ans == (0x400) ) {
			puts("\n\n");
			continue ;
		}
		printf("%d\n",ans);
		for ( k = 0, v = best; v; v &= ~L(v) ) {
			if ( ++k > 1 ) putchar(' ');
			printf("%d",who(L(v)));
		}
		putchar('\n');
	}
	return 0;
}

