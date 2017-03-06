/*
 * 11733. Airports
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
#define N 10100
#define M 200100
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))

typedef long long i64;

int ts,cs,isdig[256],n,m,A,pos[N],heap[2*N],cnt,d[N],to[M],next[M],last[N],cost[M],E,
	seen[N],yes,z,p[N],mm;
i64 weight;

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cost[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cost[j] = c;
}

void putint( i64 n ) { n<10?(putchar(n+'0')):(putint(n/10),putchar((n%10)+'0')); }

i64 gint() {
	i64 ch,n = 0;
	for (;(ch = getchar()) != EOF && !isdig[ch];);
	assert( ch != EOF );
	for ( n = ch-'0';(ch = getchar()) != EOF && isdig[ch];)
		n = (n<<1)+(n<<3)+(ch-'0');
	return n;
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,r = *heap;
	pos[*heap] = -1;
	if ( --cnt )
		pos[heap[0] = heap[cnt]] = 0;
	for(j=0;(i=j,j<<=1,++j)<cnt;bubble){
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return r;
}

void upd( int x ) {
	if ( seen[x] == yes )
		return ;
	seen[x] = yes, ++mm;
	if ( !p[x] ) ++z;
	weight += d[x];
}

int main() {
	i64 i,j,k,l,t,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( x = 0; x <= 9; ++x )
		isdig[x+'0'] = 1;
	for ( ts = gint(); ts--; ) {
		n = gint(), m = gint(), A = gint();
		for ( x = 1; x <= n; ++x ) last[x] = pos[x] = -1;
		for ( weight = 0, E = 0, l = 0; l < m; ++l ) {
			x = gint(), y = gint(), k = gint();
			add_arcs(x,y,k);
		}
		for ( mm = 0, z = 0, cnt = 0, x = 1; x <= n; ++x ) 
			p[x] = 0, d[x] = A, push(x);
		for( mm = 0, ++yes;cnt && mm < n;) {
			for ( i = last[x = pop()], upd(x); i >= 0; i = next[i] ) 
				if ( d[y = to[i]] > cost[i] ) 
					p[y] = x, d[y] = cost[i], push(y);
		}
		putchar('C'), putchar('a'), putchar('s'), putchar('e'), putchar(' ');
		putchar('#'), putint(++cs), putchar(':'), putchar(' '), putint(weight), putchar(' '), putint(z);
		putchar('\n');
	}
	return 0;
}

