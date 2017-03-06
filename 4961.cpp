/*
 * 4961. Assembly Line
 * TOPIC: dp, livearchive, swerc2010
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 32
#define M 0x100
using namespace std;
typedef long long i64;
#define oo (1LL<<59)

int n,w[N][N],which[256],m;
char ch[N],g[N][N];
i64 z[M][M][N],weight;

int main() {
	int i,j,k,qr,l,t,cs = 0,x,y;
	char tmp[M];
	for ( ;1 == scanf("%d",&n) && n>0; ) {
		if ( ++cs > 1 ) putchar('\n');
		for ( i = 0; i < n; ++i ) 
			scanf("%s",tmp), which[ch[i] = 0[tmp]] = i;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				scanf("%d-%s",&k,tmp), g[i][j] = which[0[tmp]], w[i][j] = k;
		for ( scanf("%d",&qr); qr--; ) {
			scanf("%s",tmp+1), m = strlen(tmp+1);
			for ( i = 0; i <= m; ++i )
				for ( j = i; j <= m; ++j )
					for ( k = 0; k <= n; ++k )
						z[i][j][k] = +oo;
			for ( i = 1; i <= m; ++i )
				z[i][i][which[tmp[i]]] = 0;
			for ( l=2; l<=m; ++l )
				for ( i=1; (j=i+l-1)<=m; ++i )
					for ( t=i; t<=j-1; ++t )
						for ( x=0; x<n; ++x )
							if ( z[i][t][x] < +oo )
								for ( y=0; y<n; ++y )
									if ( z[t+1][j][y] < +oo ) 
										if ( z[i][j][k=g[x][y]]>z[i][t][x]+z[t+1][j][y]+w[x][y] )
											z[i][j][k]=z[i][t][x]+z[t+1][j][y]+w[x][y];
			for ( weight = z[1][m][y=0], x = 1; x < n; ++x )
				if ( weight > z[1][m][x] ) weight = z[1][m][y=x];
			printf("%lld-%c\n",weight,ch[y]);
		}
	}
	return 0;
}

