/*
 * 1558. Number Guessing Game
 * TOPIC: dp, game theory, bitmasks
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 21
#define oo 0xfffffffful
#define L(u) ((u)&(~(u)+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)

int m,n,c[N],*ptr,e[N];
char which[BIT(N)],idx[N];
unsigned int z[1<<N];

int is_winning(const unsigned int u,const unsigned int forbidden) {
	unsigned int nu,v,w,i,j,k,l,t,nf;
	if ( z[u] < +oo ) return z[u];
	for(v=u;v&&(i=which[L(v)])>=0;v&=~L(v)) {
		if ( c[i] < 2 ) continue ;
		for(nu=u,nf=forbidden,w=(~(u&~BIT(i)))&MASK(n);w&&(l=which[L(w)])>=0;w&=~L(w))
			for(j=0;(k=j*c[l])<N;++j)
				for(;(k+=c[i])<N;nf|=BIT(k))
					if(idx[k]!=-1)
						nu&=~BIT(idx[k]);
		for(w=forbidden;w&&(l=which[L(w)])>=0;w&=~L(w))
			for ( j=0; (k=j*l)<N; ++j )
				for (;(k+=c[i])<N; nf|=BIT(k) )
					if ( idx[k] != -1 )
						nu&=~BIT(idx[k]);
		if(!is_winning(nu,nf)) {
			if(u==MASK(n))
				*ptr++=c[i],z[u]=1;
			else return z[u]=1;
		}
	}
	if ( z[u] < +oo )
		return z[u];
	return z[u] = 0;
};

int main() {
	int i,j,k,cs = 0,ts;
	unsigned int fr;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < N; which[BIT(i)] = i, ++i );
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < N; idx[i++] = -1 );
		for ( i = 0; i < n; scanf("%d",&c[i++]), idx[c[i-1]] = i-1 );
		for ( fr = 0, i = 2; i < N; ++i )
			if ( idx[i] == -1 )
				fr |= BIT(i);
		memset(z,0xff,sizeof z), ptr = e;
		printf("Scenario #%d:\n",++cs);
		if ( !is_winning(MASK(n),fr) )
			puts("There is no winning move.");
		else {
			printf("The winning moves are:");
			for ( m = ptr-e, j = 1; j; )
				for ( i = j = 0; i < m-1; ++i )
					if ( e[i] > e[i+1] )
						k = e[i], e[i] = e[i+1], e[i+1] = k, ++j;
			for ( i = 0; i < m-1; printf(" %d",e[i++]) );
			printf(" %d.\n",e[m-1]);
		}
		putchar('\n');
	}
	return 0;
}

