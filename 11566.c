/*
 * 11566.Let's Yum Cha
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
#define N 0x80
#define SET(a,k) (a[(k)>>3] |= BIT((k)&7) )
#define TST(a,k) (a[(k)>>3] & BIT((k)&7) )
#define CLR(a,k) (a[(k)>>3] &= ~BIT((k)&7) )
#define BIT(k) (1UL << (k))
#define MASK(k) (BIT(k)-1)
#define oo 0xfffffffful

int m,n,T,PRICE,favour[N][N],price[N],F[N];
unsigned int z[2][23][11*100+8];

void update( unsigned int *z, unsigned int w ) {
	if ( w == +oo ) return ;
	if ( *z == +oo || *z < w )
		*z = w;
}

int main() {
	int i,j,k,l,t,how_many,cost,sum;
	unsigned int u,v,w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 4 == scanf("%d %d %d %d",&m,&PRICE,&T,&n) ) {
		if ( !n&&!m&&!T&&!PRICE ) break ;
		for ( ++m, j = 1; j <= n; ++j ) {
			scanf("%d",price+j), F[j] = 0;
			for ( i = 1; i <= m; ++i )
				scanf("%d",&favour[i][j]), F[j] += favour[i][j];
		}
		memset(z[1],0xfful,sizeof(z[1]));
		for ( z[t = 1][0][0] = 0, j = 1; j <= n; ++j ) 
			for ( t ^= 1, memset(z[t],0xfful,sizeof(z[t])), sum = 0; sum <= 2*m; ++sum )
				for ( cost = 0; cost <= m*PRICE; ++cost )
					for ( l = 0; l <= 2; ++l )
						if ( sum >= l && cost >= l*price[j] && z[t^1][sum-l][cost-l*price[j]] < +oo )
							update(z[t][sum]+cost,z[t^1][sum-l][cost-l*price[j]]+l*F[j]);
		for ( w = +oo, cost = 0; cost <= m*PRICE; ++cost )
			if ( (cost+m*T)+ceil((cost+m*T)/10.00) <= m*PRICE )
				for ( sum = 0; sum <= 2*m; ++sum )
					update(&w,z[t][sum][cost]);
		printf("%.2lf\n",w/(m+0.00));
	}
	return 0;
}
