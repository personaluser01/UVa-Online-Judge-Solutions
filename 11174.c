/*
 * 11174. Stand in a Line
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
#define MOD 1000000007LL
#define N 40100
typedef unsigned long long u64;
#define oo 0xffffffffffffffffull

typedef long long i64;
i64 iF[N],F[N],n,minv[N],cnt[N],m;
u64 z[N];
int head[N],bigMan[N],yes,card[N];

typedef struct { int u,v; } cell;
cell c[N];

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) { !y?(*a=1,*b=0,*d=x):(ext_euclid(y,x%y,b,a,d),*b-=(*a)*(x/y)); }

i64 inv( i64 p ) {
	i64 a,b,d;
	ext_euclid(p,MOD,&a,&b,&d);
	for( a %= MOD; a < 0; a += MOD );
	assert( (a*p) % MOD == 1LL );
	return a;
}

int cmp( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	if ( x->u == y->u )
		return 0;
	return x->u < y->u ? -1 : 1;
}

int gcard( int x ) {
	int i;
	if ( card[x] )
		return card[x];
	for ( i = 0; i < cnt[x]; ++i )
		card[x]+=gcard(c[i+head[x]].v);
	return ++card[x];
}

u64 calc_z( int x ) {
	int i,y;
	if ( z[x] < +oo )
		return z[x];
	z[x] = F[gcard(x)-1];
	for ( i = 0; i < cnt[x]; ++i ) {
		y = c[i+head[x]].v;
		z[x] *= iF[gcard(y)], z[x] %= MOD;
		z[x] *= calc_z(y), z[x] %= MOD;
	}
	return z[x];
}

int main() {
	i64 i,j,k,ts,ax;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( minv[n = 1] = 1; (++n) < N; minv[n] = inv(n) );
	for ( iF[0] = iF[1] = 1, F[0] = F[1] = 1, n = 2; n < N; ++n )
		iF[n] = (iF[n-1]*minv[n])%MOD, F[n] = (F[n-1]*n)%MOD;
	for ( scanf("%lld",&ts); ts-- && ++yes; ) {
		scanf("%lld %lld",&n,&m);
		for ( i = 0; i < n; cnt[i] = 0, bigMan[i] = yes, card[i++] = 0 );
		for ( k = 0; k < m; ++k ) {
			scanf("%lld %lld",&i,&j);
			bigMan[c[k].v = --i] = 0, ++cnt[c[k].u = --j];
		}
		qsort(c,m,sizeof *c,cmp);
		for ( k = -1, i = 0; i < m; ++i )
			if ( c[i].u != k ) 
				head[k = c[i].u] = i;
		for ( i = 0; i < n; ++i ) z[i] = +oo;
		for ( ax = F[n], i = 0; i < n; ++i )
			if ( bigMan[i] == yes ) {
				ax *= iF[gcard(i)], ax %= MOD;
				ax *= calc_z(i), ax %= MOD;
			}
		printf("%lld\n",ax);
	}
	return 0;
}
