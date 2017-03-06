/*
 * 10273. Eat or Not To Eat?
 * status: Accepted
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define N 0x400
#define MAXT 11
typedef long long i64;
#define   Q 		   (N*2)
#define   xchg(x,y)    (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define   bubble       (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))

i64 gcd( i64 x, i64 y ) { return !y?x:gcd(y,x%y); }
i64 lcm( i64 x, i64 y ) { return x*(y/gcd(x,y));  }

int n,T[N],m[N][MAXT],d[Q],pos[N],heap[Q],cnt;
unsigned int mask;

void push( int x ) {
	int i,j;
	pos[x]<0?(pos[heap[cnt]=x]=cnt,++cnt):1;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	pos[*heap] = -1;
	(--cnt)?(pos[heap[0]=heap[cnt]]=0):1;
	for ( j = 0; (i = j, j <<= 1, ++j) <= cnt-1; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

void update( int t ) {
	int i;
	for ( mask = 0, i = 0; i < cnt; ++i ) {
		d[heap[i]] = m[heap[i]][t%T[heap[i]]], push(heap[i]);
		mask |= (1UL << T[heap[i]]);
	}
}

i64 LCM( int *x, int n ) {
	if ( n == 1 )
		return 0[x];
	if ( n == 2 )
		return lcm(0[x],1[x]);
	return lcm(0[x],LCM(x+1,n-1));
}

int precalc[1 << 15];

int main() {
	int i,j,k,l,t,ts,x,y,D,L,run,c[N];
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( u = 2; u < (1UL << 12); u += 2 ) {
		for ( n = 0, i = 1; i < 12; ++i )
			if ( (u>>i)&1 )
				c[n++] = i;
		precalc[u] = LCM(c,n);
	}
	for ( scanf("%d",&ts); ts-- && scanf("%d",&n) == 1;) {
		for ( i = 0; i < n; ++i ) for ( scanf("%d",T+i), j = 0; j < T[i]; scanf("%d",&m[i][j++]) );
		for ( i = 0; i < n; ++i ) pos[i] = -1;
		for ( mask = 0, cnt = 0, t = 0, i = 0; i < n; ++i )
			d[i] = m[i][t%T[i]], push(i), mask |= (1UL << T[i]);
		for ( run = 0, D = 0, t = 1; cnt && run <= precalc[mask] && run <= 500; update(t++), ++run ) {
			if ((cnt>=2&&d[heap[0]]==d[heap[1]])||(cnt>=3&&d[heap[0]]==d[heap[2]])) 
				continue ;
			pop(), D = t, run = 0;
		}
		printf("%d %d\n",cnt,D);
	}
	return 0;
}

