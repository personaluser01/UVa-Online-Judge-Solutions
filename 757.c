/*
 * 757. Gone Fishing
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 5)
#define MAXT (1 << 8)
#define oo 0xfffffffful
#define BIT(k) (1ULL << (k))
#define MASK(k) (BIT(k)-1ULL)
#define enc(x,y) ((x)|((y)<<5))
typedef long long i64;

i64 max( i64 x, i64 y ) { if ( x < y ) return y; return x; }

int n,H,ts,pr,seen[N][MAXT],yes;
unsigned int z[N][MAXT];
int p[N][MAXT];
i64 t[N],a[N],b[N],pref[N];

unsigned int calc_z( int i, int h ) {
	int j,k,s;
	unsigned int w;
	if ( seen[i][h] == yes )
		return z[i][h];
	if ( i == 0 ) {
		seen[i][h] = yes;
		if ( h == 0 ) {
			p[i][h] = -1;
			return z[i][h] = 0;
		}
		return z[i][h] = +oo;
	}
	assert( i >= 1 );
	for ( s = 0, k = 0; k+pref[i-1] <= h; ++k ) {
		if ( k > 0 ) s += max(0,a[i]-(k-1)*b[i]); else s = 0;
		if ( (w = calc_z(i-1,h-k-t[i-1])) < +oo )
			if ( z[i][h] == +oo || s+w > z[i][h] )
				z[i][h] = s+w, p[i][h] = enc(i-1,h-k-t[i-1]);
	}
	seen[i][h] = yes;
	return z[i][h];
}

void dump( int i, int h ) {
	if ( p[i][h] == -1 )
		return ;
	dump(p[i][h]&MASK(5),p[i][h]>>5);
	if ( pr++ ) printf(", %lld",(5*(h-(p[i][h]>>5)-t[i-1])));
	else printf("%lld",(5*(h-(p[i][h]>>5)-t[i-1])));
}

int main() {
	int i,j,k,m;
	unsigned int w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && n > 0 && ++yes; ) {
		if ( ++ts > 1 ) putchar('\n');
		assert( 1 == scanf("%d",&H) );
		for ( i = 1; i <= n; ++i )
			assert( 1 == scanf("%lld",a+i) );
		for ( i = 1; i <= n; ++i )
			assert( 1 == scanf("%lld",b+i) );
		for ( i = 1; i <= n-1; ++i ) {
			assert( 1 == scanf("%lld",t+i) );
			pref[i] = pref[i-1]+t[i];
		}
		memset(z,0xff,sizeof z), H *= 12;
		assert( H < MAXT );
		for ( w = 0, pr = 0, k = 1; k <= n; ++k )
			if ( calc_z(k,H) < +oo && calc_z(k,H) > w )
				w = calc_z(k,H), m = k;
		if ( !w ) {
			for ( i = 1; i <= n; ++i )
				if ( i == 1 )
					printf("%d",H*5);
				else printf(", 0");
			putchar('\n');
			printf("Number of fish expected: %u\n",0);
			continue; 
		}
		for ( dump(m,H); pr < n; ++pr )
			printf(", 0");
		putchar('\n');
		printf("Number of fish expected: %u\n",w);
	}
	return 0;
}

