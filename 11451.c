/*
 * 11451. Water Restrictions
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 11
#define MAXL 21
#define MAXF 11
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned long long u64;

int L,pos[N],C,n,cap[N],w,left[N],right[N];
u64 u;
char bts[BIT(21)];

int Bits( u64 u ) { return bts[u>>60]+bts[(u>>40)&MASK(20)]+bts[(u>>20)&MASK(20)]+bts[u&MASK(20)]; }

void f( int m, int k ) {
	u64 v;
	int i;
	if ( k == n ) {
		if ( Bits(u) > w ) 
			w = Bits(u);
		return ;
	}
	assert( k < n );
	if ( !cap[k] || !m ) { f(m,k+1); return ; }
	if ( k < n-1 ) {
		for ( i = 1; i <= cap[k] && i <= m; ++i ) 
			v=u,left[k]=pos[k]-i,right[k]=pos[k]+i,u|=(MASK(right[k]-left[k]+1)<<left[k]),f(m-i,k+1),u=v;
		f(m,k+1);
	}
	else {
		if ( cap[k] > m ) i = m; else i = cap[k];
		v=u,left[k]=pos[k]-i,right[k]=pos[k]+i,u|=(MASK(right[k]-left[k]+1)<<left[k]),f(m-i,k+1),u=v;
		f(m,k+1);
	}
}

int main() {
	int i,j,k,ts;
	for ( i = 0; i < BIT(21); ++i ) bts[i]=bts[i>>1]+(i&1);
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&L,&n), w = 0;
		for ( i = 0; i < n; scanf("%d",&pos[i++]) );
		for ( scanf("%d",&C), i = 0; i < n; scanf("%d",&cap[i++]) );
		u = 0, f(C,0), printf("%d\n",w);
	}
	return 0;
}

