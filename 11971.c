/*
 * 11971. Polygon
 * TOPIC: probability, integrals
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXK 0x40
#define MAXN (1<<17)
typedef long long i64;

int m,n;

int main() {
	int i,j,k,ts,cs = 0;
	i64 x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		printf("Case #%d: ",++cs);
		if ( m == 1 ) puts("0/1");
		else {
			x = (1LL<<(m))-m-1, y = (1LL<<(m));
			while ( !(x&1) ) x >>= 1, y >>= 1;
			printf("%lld/%lld\n",x,y);
		}
	}
	return 0;
}

