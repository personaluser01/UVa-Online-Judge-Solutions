/*
 * 10086. Text the rods
 * TOPIC: DP
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#define  N 0x80
#define  MAXT 0x200
#define  oo 0xfffffffful
#define  enc(x,y) ((x)|((y)<<9))
#define  BIT(k)   (1UL << (k))
#define  MASK(k)  (BIT(k)-1UL)

unsigned int min( unsigned int x, unsigned int y ) { return x < y ? x:y; }

int T[2],n,m[N],c[2][N][N];
unsigned int z[N][MAXT][MAXT],way[N][MAXT][MAXT];

void dump( int i, int j, int k ) {
	if ( i == 1 ) { printf("%d",T[0]-j); return ; }
	dump(i-1,way[i][j][k]&MASK(9),way[i][j][k]>>9);
	printf(" %lu",(way[i][j][k]&MASK(9))-j);
}

int main() {
	int i,j,k,l,t;
	for(;2==scanf("%d %d",T,T+1)&&(T[0]||T[1]);puts("\n")) {
		for ( scanf("%d",&n), i = 1; i <= n; ++i ) 
			for ( scanf("%d",m+i), t = 0; t <= 1; ++t )
				for ( j = 1; j <= m[i]; scanf("%d",&c[t][i][j++]) );
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= T[0]; ++j )
				for ( k = 0; k <= T[1]; z[i][j][k++] = +oo );
		for ( j = 0; j <= T[0] && j <= m[1]; ++j )
			if ( m[1]-j <= T[1] )
				z[1][T[0]-j][T[1]-(m[1]-j)] = c[0][1][j]+c[1][1][m[1]-j], way[1][T[0]-j][T[1]-m[1]+j];
		for ( i = 2; i <= n; ++i )
			for ( j = 0; j <= T[0]; ++j )
				for ( k = 0; k <= T[1]; ++k )
					if ( z[i-1][j][k] < +oo ) 
						for ( l = 0; l <= j && l <= m[i]; ++l )
							if ( m[i]-l <= k )
								if ( (z[i][j-l][k-m[i]+l]=min(z[i][j-l][k-m[i]+l],z[i-1][j][k]+c[0][i][l]+c[1][i][m[i]-l]))==z[i-1][j][k]+c[0][i][l]+c[1][i][m[i]-l] )
									way[i][j-l][k-m[i]+l] = enc(j,k);
		printf("%u\n",z[n][0][0]), dump(n,0,0);
	}
	return 0;
}

