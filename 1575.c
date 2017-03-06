/*
 * 1575. Factors
 * TOPIC: multinomial coefficient, number theory, brute force
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<21)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET(k) (a[(k)>>3] |= BIT((k)&7))
#define CLR(k) (a[(k)>>3] &= ~BIT((k)&7))
#define TST(k) (a[(k)>>3] & BIT((k)&7))
#define isprime(k) (TST(k))
#define L BIT(63)
typedef long long i64;
typedef unsigned long long u64;
#define DBG 0

u64 p[N],c[N],*ptr = c,C[63][63];
int e[N],m,d[N],len;
unsigned char a[(N>>3)+8];

u64 mpow( u64 x, int n ) {
	u64 ax = 1ULL;
	for(;n;n>>=1) {
		if ( n&1 ) {
			if ( (long double)ax >= ((long double)L)/x ) 
				return L;
			ax *= x;
		}
		if ( (long double)x >= (long double)L/x )
			return L;
		x *= x;
	}
	return ax;
};

void signature( u64 n, int *deg, int *k ) {
	int i;
	for ( i = 0; i < m && p[i] <= n; ++i ) 
		for ( deg[i] = 0; 0 == (n%p[i]); n /= p[i], ++deg[i] );
	if ( n > 1 )
		deg[i] = 1, *k = i+1;
	else *k = i;
};

u64 multinomial( int *e, int n ) {
	u64 w,ax,s,i;
	if ( n == 0 ) 
		return 1ULL;
	assert( n >= 1 );
	if ( (w=multinomial(e,n-1)) == L ) return L;
	for ( s = 0, i = 0; i < n; s += e[i++] );
	if ( (ax=C[s][e[n-1]]) == L || (long double)w >= ((long double)L)/ax )
		return L;
	return ax *= w;
};

void rec( int pos, u64 ax ) {
	int k;
	u64 t;
	if ( ax >= L ) return ;
	if ( e[pos] == 0 ) {
		if ( ax != 1 ) *ptr++ = ax;
		return ;
	}
	assert( e[pos] >= 1 );
	if ( pos >= m ) return ;
	for ( k = e[pos], t=mpow(p[pos+1],k); k >= 0 && (t == L || (long double)ax >= ((long double)L)/t); t=mpow(p[pos+1],--k) );
	for ( ;k >= 0; e[pos+1] = k--, rec(pos+1,ax*t), t /= p[pos+1] );
};

typedef struct { u64 x,y; } cell;

cell q[N],Q[N];
int K,s;

int cmp( const void *a, const void *b ) {
	cell *p = (cell *)a,
		 *q = (cell *)b;
	if ( p->x == q->x ) {
		if ( p->y == q->y ) 
			return 0;
		if ( p->y < q->y )
			return -1;
		return 1;
	}
	if ( p->x < q->x )
		return -1;
	return 1;
};

int main() {
	i64 i,j,k,n;
	u64 M;
#ifndef ONLINE_JUDGE
	freopen("1575.in","r",stdin);
#endif
	for ( i = 0; i < 63; C[i++][0] = 1 );
	for ( i = 1; i < 63; ++i )
		for ( j = 1; j <= i; ++j )
			if ( C[i-1][j-1] == L || C[i-1][j] == L ||\
					(long double)C[i-1][i]+(long double)C[i-1][j-1] >= (long double)L || (C[i][j] = C[i-1][j]+C[i-1][j-1]) >= L )
				C[i][j] = L;
	for ( SET(2), i = 3; i < N; SET(i), i += 2 );
	for ( i = 3; i < N; i += 2 )
		for ( j=i+i; j<N && isprime(i); CLR(j), j+=i );
	for ( m = 0, i = 0; i < N; ++i )
		if ( isprime(i) ) p[m++] = i;
	for ( e[0] = 62; e[0] >= 0; rec(0,BIT(e[0])), --e[0] );
#if DBG
	printf("%d\n",ptr-c);
#endif
	for ( i = 0; i < ptr-c; ++i ) {
		signature(c[i],d,&len);
		if ( (M = multinomial(d,len)) == L )
			continue ;
		/*printf("%lld --> %llu\n",c[i],M);*/
		q[K].x = M, q[K++].y = c[i];
	}
	qsort(q,K,sizeof *q,cmp);
	for ( i = 0; i < K; Q[s++] = q[i], i = j )
		for ( j = i+1; j < K && q[j].x == q[i].x; ++j );
#if DBG
	printf("%d\n",s);
#endif
	for (;1==scanf("%lld",&n);) {
		if ( n == 1 ) { puts("1 2"); continue ; };
		if ( Q[0].x == n ) { printf("%llu %llu\n",Q[0].x,Q[0].y); continue ; };
		for ( i = 0, j = s-1; i+1 < j; ) {
			k = (i+j)/2;
			if ( Q[k].x < n ) i = k;
			else j = k;
		}
		printf("%llu %llu\n",Q[j].x,Q[j].y);
	}
	return 0;
};

