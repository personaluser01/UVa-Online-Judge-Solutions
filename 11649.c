/*
 * 11649. Home! Sweet Home!
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define M 100100

int ts,cs,n,m,isdig[256];
i64 h[N],d[N],c[N];

i64 getnum() {
	i64 n = 0,ch;
	for(;(ch = getchar()) != EOF && !isdig[ch]; );
	for ( n = ch-'0'; (ch = getchar()) != EOF && isdig[ch]; n = (n<<1)+(n<<3)+(ch-'0') );
	return n;
}

int main() {
	int i,j,k,l,t;
	i64 A,B,C,E,F,G,H,I,J;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; isdig[i++] = 1 );
	for ( ts = getnum(); ts--; ) {
		m = getnum(), n = getnum(), A = getnum(), B = getnum(), C = getnum();
		for ( h[0] = (C % 10000)+1, h[1] = ((A*h[0]+C)%10000)+1, i = 2; i < m; ++i )
			h[i] = ((A*h[i-1]+B*h[i-2]+C)%10000)+1;
		E = getnum(), F = getnum(), G = getnum(), H = getnum(), I = getnum(), J = getnum();
		d[0] = (G%10000)+1, c[0] = (J%100000)+1;
		for ( i = 1; i < n; ++i ) {
			d[i] = ((E*d[i-1]+F*c[i-1]+G)%10000)  +1;
			c[i] = ((H*c[i-1]+I*d[i-1]+J)%100000) +1;
		}
		printf("Case %d: ",++cs);
	}
	return 0;
}

