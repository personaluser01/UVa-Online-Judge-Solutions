/*
 * 12862. Intrepid Climber
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<17)
#define M (N<<1)
#define oo 0xfffffffful
unsigned int max( unsigned int x, unsigned int y ) { return x<y?y:x; }

int last[N],next[M],cost[M],to[M],from[M],n,E,fr,is_landmark[N],yes,outdeg[N],
	*head,*tail,q[N];
unsigned int z[N],w[N];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	from[i]=x, to[i]= y, cost[i] = 0, next[i] = last[x], last[x] = i;
	from[y]=y, to[j]= x, cost[j] = c, next[j] = last[y], last[y] = j;
	++outdeg[x];
}

unsigned int f( int x ) {
	int i,y;
	if ( w[x] < +oo )
		return w[x];
	if ( z[x] == 0 )
		return w[x] = 0;
	for ( w[x] = 0, i = last[x]; i >= 0; i = next[i] )
		if ( cost[i] == 0 ) 
			if (z[y = to[i]] || is_landmark[y] )
				w[x] = max(w[x],cost[i^1]+f(y));
	return w[x];
}

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(;2==scanf("%d %d",&n,&fr); printf("%u\n",z[0]-f(0)) ) {
		for ( E = 0, i = 0; i < n; w[i] = +oo, is_landmark[i] = 0, outdeg[i]=0, z[i]=0, last[i++]=-1 );
		for ( l = 0; l < n-1; ++l, scanf("%d %d %d",&i,&j,&k), add_arcs(--i,--j,k) );
		for ( k = 0; (++k) <= fr; scanf("%d",&i), is_landmark[--i] = 1 );
		for ( head = tail = q, i = 0; i < n; ++i )
			if ( !outdeg[i] ) *tail++ = i;
		for (;head<tail;) 
			for ( l=last[i=*head++]; l>=0; l=next[l] ) {
				if ( !cost[l] ) continue ;
				if ( !--outdeg[j = to[l]] ) *tail++ = j;
				if ( z[i] == 0 ) {
					z[j] += is_landmark[i]*cost[l];
				}
				else {
					z[j] += cost[l]+z[i];
				}
			}
		/*
		for ( i = 0; i < n; ++i )
			printf("z[%d] = %u\n",i,z[i]);*/
	}
    return 0;
}


