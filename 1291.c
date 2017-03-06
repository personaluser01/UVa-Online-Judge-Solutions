/*
 * 1291. Dance Dance Revolution
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<16)
#define S (1<<6)
#define enc(x,y) ((x)|((y)<<3))
#define oo 0xfffffffful

unsigned int min( unsigned int x, unsigned int y ) {
	if ( x < y ) return x;
	return y;
}

int n,c[N];
unsigned int z[N][S],w[8][8],ans;

int rinput() {
	for ( n = 1; 1 == scanf("%d",&c[n]) && c[n] != 0; ++n );
	return --n;
}

int main() {
	int i,j,k,t,l;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("a.txt","r",stdin);
#endif
	memset(w,0xff,sizeof w);
	w[0][1] = w[0][2] = w[0][3] = w[0][4] = 2;
	w[1][2] = w[1][4] = w[4][1] = w[2][1] = w[4][3] = w[3][4] = w[2][3] = w[3][2] = 3;
	w[1][3] = w[3][1] = w[2][4] = w[4][2] = 4;
	w[1][1] = w[2][2] = w[3][3] = w[4][4] = 1;
	for (;rinput();) {
		memset(z,0xff,sizeof z);
		for ( z[0][0] = 0, i = 0; i <= n-1; ++i )
			for ( j = 0; j <= 4; ++j )
				for ( k = 0; k <= 4; ++k )
					if ( z[i][u=enc(j,k)] < +oo ) {
						t = c[i+1];
						if ( w[j][t] < +oo && t != k )
							z[i+1][v=enc(t,k)] = min(z[i][u]+w[j][t],z[i+1][enc(t,k)]);
						if ( w[k][t] < +oo && t != j )
							z[i+1][v=enc(j,t)] = min(z[i][u]+w[k][t],z[i+1][enc(j,t)]);
					}
		for ( ans = +oo, j = 0; j <= 4; ++j )
			for ( k = 0; k <= 4; ++k )
				ans = min(ans,z[n][enc(j,k)]);
		printf("%u\n",ans);
	}
	return 0;
}

