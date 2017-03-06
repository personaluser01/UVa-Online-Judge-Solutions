/*
 * 10447. Sum-up the Primes (II)
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 301
#define MAXW 801
#define MAXK 13
#define MAXP 63
#define NO (puts("No Solution."))
#define BIT(k) (1ULL<<(k))
#define TST(a,k) (a[(k)>>6] & BIT((k)&63ULL))
#define SET(a,k) (a[(k)>>6] |= BIT((k)&63ULL))
#define E(u) ((u)&((~(u))+1ULL))
typedef unsigned long long u64;

int isprime[N],p[N],n,m,L[N],K,q[N],id[N],mi[N],yes,
	can_make[2][MAXP][MAXW][MAXK],c[MAXW],which[BIT(21)],
	nn[0x80],KK[0x80],LL[0x80],maxk,maxn;
u64 aha[2][MAXK][(MAXW>>6)+8];

int who( u64 u ) { 
	u = E(u);
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

int cmp( const void *a, const void *b ) {
	char A[5],B[5];
	sprintf(A,"%d",*((int *)a)), sprintf(B,"%d",*((int *)b));
	return strcmp(A,B);
}

int f( int n, int t, int pos ) {
	int i,l,ll;
	if ( t == K ) 
		return n==0;
	assert( t < K );
	if ( n <= 0 || pos >= m || can_make[L[0]][pos][n][K-t] != yes )
		return 0;
	if ( K-t==1 && (n>=N || n<N && !isprime[n]) ) return 0;
	for ( l = L[id[pos]]; l >= 0; --l ) {
		if ( t+l > K || n < l*p[pos] ) continue ;
		if ( f(n-l*p[pos],t+l,pos+1) ) {
			for ( ll = 0; ll < l; ++ll ) c[t+ll] = p[pos];
			return 1;
		}
	}
	return 0;
}

void fill_table( const int pos ) {
	int l,ll,i,j,k,idx,SH;
	static int t = 0;
	u64 w;
	if ( pos == m-1 ) {
		memset(aha,0,sizeof aha);
		for ( t = 0, SET(aha[t][0],0), t ^= 1, l = 0; l <= maxk; ++l )
			for ( SH = 0, idx = 0; idx <= ((maxn+8)>>6); ++idx, SH += 64 )
				for ( w = aha[t^1][l][idx]; w; w &= ~E(w) )
					for ( k = SH+who(w), ll = 0; ll <= L[id[m-1]] && ll+l <= maxk && ll*p[m-1]+k <= maxn; ++ll )
						SET(aha[t][l+ll],ll*p[m-1]+k);
		goto next;
	}
	for ( j = pos; j <= pos; ++j ) 
		for ( t ^= 1, l = 0; l <= maxk; ++l )
			for ( SH = 0, idx = 0; idx <= ((maxn+8)>>6); ++idx, SH += 64 )
				for ( w = aha[t^1][l][idx]; w; w &= ~E(w) ) 
					for ( k = SH+who(w), ll = 0; ll <= L[id[j]] && ll+l <= maxk && ll*p[j]+k <= maxn; ++ll )
						SET(aha[t][l+ll],ll*p[j]+k);
next:
	for ( l = 0; l <= maxk; ++l )
		for ( SH = 0, idx = 0; idx <= ((maxn+8)>>6); ++idx, SH += 64 )
			for ( w = aha[t][l][idx]; w; w &= ~E(w) )
				k = SH+who(w), can_make[L[0]][pos][k][l] = yes;
}

int main() {
	int i,j,k,ts,cs = 0,t,l,qr,tt;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < 21; ++k ) which[BIT(k)] = k;
	for ( i = 3; i < N; isprime[i] = 1, i += 2 );
	for ( i = 3; i < N; i += 2 )
		for ( j = i+i; j < N && isprime[i]; isprime[j] = 0, j += i );
	for ( m = 0, isprime[2] = 1, i = 0; i < N; ++i ) if ( isprime[i] ) q[m] = p[m] = i, ++m;
	qsort(p,m,sizeof *p,cmp);
	for ( i = 0; i < m; ++i ) id[i] = -1;
	for ( i = 0; i < m; ++i )
		for ( j = 0; j < m && id[i] == -1; ++j )
			if ( p[i] == q[j] ) id[i] = j;
	for ( i = 0; i < m; ++i ) 
		for ( mi[i] = p[i], j = i+1; j < m; ++j )
			if ( mi[i] > p[j] ) mi[i] = p[j];
	for ( scanf("%d",&ts); ts-- && printf("Block %d:\n",++cs); putchar('\n') ) {
		for ( ++yes, i = 1; i <= 61; scanf("%d",&L[i++]) );
		/*for ( t = 0; t <= 1; ++t ) 
			for ( L[0] = t, i = 0; i < m; fill_table(i++) );*/
		for ( maxn=maxk=0,scanf("%d",&qr), l = 0; l < qr && 3 == scanf("%d %d %d",&n,&K,L); ++l ) {
			nn[l] = n, KK[l] = K, LL[l] = L[0];
			if ( maxn < n ) maxn = n;
			if ( maxk < K ) maxk = K;
			/*printf("Query %d:\n",++l);
			if ( !f(n,0,0) ) { NO; continue ; }
			for ( i = 0; i < K-1; printf("%d+",c[i++]) );
			printf("%d\n",c[i]);*/
		}
		for ( t = 0; t <= 1; ++t )
			for ( L[0] = t, i = m-1; i >= 0; fill_table(i--) );
		for ( l = 0; l < qr; ++l ) {
			n = nn[l], K = KK[l], L[0] = LL[l];
			printf("Query %d:\n",l+1);
			if ( (0==(n&1) && 1==(K&1) && 0==L[0]) || !f(n,0,0) ) { NO; continue ; }
			for ( i = 0; i < K-1; printf("%d+",c[i++]) );
			printf("%d\n",c[i]);
		}
	}
	return 0;
}

