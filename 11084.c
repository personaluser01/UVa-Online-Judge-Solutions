/*
 * 11084. Anagram Division
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
#define N 10
typedef long long i64;
#define M 10008
#define L(u) ((u) & ((~(u))+1))

int ts,n,d,seen[10],yes;
char s[N+10],who[1 << N];
unsigned int z[1<<N][M];

int main() {
	int i,j,k;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		who[1 << i] = i;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%s %d",s,&d), n = strlen(s);
		memset(z,0,sizeof(z));
		for ( z[0][0] = 1, u = 1; u < (1 << n); ++u ) 
			for ( k = 0; k < d; ++k )
			for ( ++yes, v = u; v; v -= L(v) )
				if ( seen[s[i = who[L(v)]]-'0'] != yes ) 
					if ( z[u&~(1ul<<i)][k] ) {
						z[u][(((i64)(s[i]-'0'))+10*k)%d] += z[u&~(1ul<<i)][k];
						seen[s[i]-'0'] = yes;
					}
		printf("%u\n",z[(1<<n)-1][0]);
		memset(seen,0,sizeof(seen)), yes = 0;
	}
	return 0;
}

