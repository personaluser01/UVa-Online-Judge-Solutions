/*
 * 12063. Zeros and Ones
 * status: Accepted
 * TOPIC: bfs, states, remainders, modulo
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL << (k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned long long u64;
#define K (1<<7)
#define N (1<<7)
#define M (1<<6)
#define Q (K*M*N)
#define enc(rem,len,ones) (((rem)|((len)<<7)|((ones)<<14)))

unsigned int q[Q],*head,*tail;
u64 z[Q],c[N][N];
int seen[Q],yes,m,n;

int main() {
	int i,j,k,cs = 0,ts,ones,rem,len;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		c[i][0] = 1;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j]+c[i-1][j-1];
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m) && ++yes && printf("Case %d: ",++cs); ) {
		if ( n & 1 ) {
			puts("0");
			continue ;
		}
		if ( m == 0 ) {
			puts("0");
			continue ;
		}
		for (head=tail=q,z[*tail++=enc(1%m,1,1)]=1; head < tail; ) {
			u = *head++, rem = (u&MASK(7)), len = ((u>>7)&MASK(7)), ones = (u>>14);
			if ( len >= n || ones > n/2 ) continue ;
			for ( i = 0; i <= 1; ++i ) {
				k = ((i|(rem<<1))%m);
				if ( yes != seen[v = enc(k,len+1,ones+i)] )
					z[*tail++=v] = z[u], seen[v]=yes;
				else z[v] += z[u];
			}
		}
		if ( seen[u=enc(0,n,n/2)] != yes )
			z[u] = 0;
		printf("%llu\n",z[u]);
	}
	return 0;
}

