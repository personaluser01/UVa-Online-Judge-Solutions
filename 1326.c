/*
 * 1326. Jurassic Remains
 * TOPIC: brute force
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define L(k) ((k)&((~(k))+1ULL))
#define MASK(k) (BIT(k)-1ULL)
#define A 26
#define N 24

char bts[BIT(21)],s[0x400],which[BIT(21)];
int m,n,w[N],id[N];
int cnt( unsigned int u ) { return bts[u&MASK(20)]+bts[u>>20]; }
int who( unsigned int u ) {
	assert( !(u&(u-1)) );
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}
unsigned int u[N],v[N],E[N];

int main() {
	int i,j,k,maxweight,weight;
	unsigned int mask,xor,o,e;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 21; bts[i]=bts[i>>1]+(i&1), ++i );
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i ) 
			for ( id[i]=i, scanf("%s",s), u[i]=j=0; s[j]; u[i]^=BIT(s[j++]-'A') );
		for ( j = 1; j; )
			for ( i = j = 0; i < n-1; ++i )
				if ( u[i] > u[i+1] ) {
					k = u[i], u[i] = u[i+1], u[i+1] = k, ++j;
					k = id[i], id[i] = id[i+1], id[i+1] = k;
				}
		/*
		for ( m = 0, i = 0; i < n; w[m]=j-i, v[m++] = u[i], i = j ) {
			for ( j = i+1; j < n && u[i] == u[j]; ++j );
			for ( E[m] = 0, k = i; k < j; E[m] |= BIT(id[k++]) );
		}
		*/
		for ( m = 0, i = 0; i < n; v[m] = u[i], w[m] = 1, E[m] = BIT(id[i]), ++i, ++m );
		for ( mask=0, maxweight=0, e=0; e<(1<<m); ++e ) {
			for ( weight=0, xor=0, o=e; o; i=who(L(o)), xor=(w[i]&1)?xor^v[i]:xor^0, weight+=w[i], o &= ~L(o) );
			if ( !xor && weight > maxweight )
				maxweight = weight, mask = e;
		}
		printf("%d\n",maxweight);
		for ( e = 0, o = mask; o; e |= E[who(L(o))], o &= ~L(o) );
		for ( i = 0; e; printf("%d",who(L(e))+1), e &= ~L(e) )
			if ( ++i > 1 ) putchar(' ');
		putchar('\n');
	}
	return 0;
};


