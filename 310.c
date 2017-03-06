/*
 * 310. L-System
 * TOPIC: bfs, bitmasks, grammar, production
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15
#define Q BIT(N+4)
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define CLR(a,k) (a[(k)>>3]&=~BIT((k)&7))
#define SET(a,k) (a[(k)>>3]|=BIT((k)&7))
#define TST(a,k) (a[(k)>>3]&BIT((k)&7))

int n,pi[N+4],m,failure[N+4][2],a[2][BIT(N)];
unsigned char seen[(BIT(N)>>3)+8];
unsigned int q[Q],*head,*tail,r[2],src,dst,L[2],*ptr,lst[BIT(N)];

unsigned int conv( char *s ) {
	unsigned int u = 0,i = 0;
	for (;s[i]; u |= (((unsigned int)(s[i]-'a'))<<i), ++i );
	return u;
}

int main() {
	int i,j,k,ok,t;
	unsigned int u,v;
	char target[N+4],source[N+4],prod[2][N+4];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(;4==scanf("%s %s %s %s",prod[0],prod[1],source+1,target+1);) {
		for ( i = 0; i <= 1; ++i ) r[i] = conv(prod[i]), L[i] = strlen(prod[i]);
		src = conv(source+1), dst = conv(target+1), m = strlen(source+1), n = strlen(target+1);
		for ( t = 0, i = 0; i < m; a[t][i] = ((src>>i)&1), ++i );
		for ( ;m < n; m = k ) 
			for ( t ^= 1, k = 0, i = 0; i < m; ++i )
				for ( j = 0; j < L[a[t^1][i]]; ++j )
					a[t][k++] = ((r[a[t^1][i]]>>j)&1);
		memset(seen,0,sizeof seen), head = tail = q;
		ptr = lst;
		for ( u = 0, i = 0; i < n; ++i )
			u |= (a[t][i]<<i);
		SET(seen,u), *tail++ = u, *ptr++ = u;
		for ( j = 1; (j+n-1) < m; ++j )  {
			u >>= 1, u |= (a[t][j+n-1]<<(n-1));
			if ( !TST(seen,u) ) SET(seen,u), *tail++ = u, *ptr++ = u;
		}
		memset(seen,0,sizeof seen), head = tail = q;
		for ( i = 0; i < ptr-lst; SET(seen,u = lst[i]), *tail++ = u, ++i );
		while ( head < tail && !TST(seen,dst) ) {
			for ( u = *head++, i = 0; i < n; ++i ) 
				a[0][i] = ((u>>i)&1);
			for ( v = 0, k = 0, i = 0; i < n; ++i )
				for ( j = 0; j < L[a[0][i]]; ++j )
					a[1][k++] = ((r[a[0][i]]>>j)&1);
			for ( i = 0; i < n; ++i ) v |= (a[1][i] << i);
			if ( !TST(seen,v) ) SET(seen,v), *tail++ = v;
			for ( j = 1; (j+n-1) < k; ++j ) {
				v >>= 1, v |= (a[1][j+n-1] << (n-1));
				if ( !TST(seen,v) ) SET(seen,v), *tail++ = v;
			}
		}
		puts(TST(seen,dst)?"YES":"NO");
	}
    return 0;
}



