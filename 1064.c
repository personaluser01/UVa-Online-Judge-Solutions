/*
 * 1064. Network
 * TOPIC: ad hoc, simulation
 * status: WA
 * NOTES: wrong I/O
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 8
#define M 0x400
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u) ((u)&((~(u))+1ULL))
#define enc(x,y) ((x)|((y)<<10))
#define oo (1<<29)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define S(u) (RIGHT(u)-LEFT(u)+1)
int max( int x, int y ) { return x<y?y:x; }
int min( int x, int y ) { return x<y?x:y; }
#define LEFT(k) ((k)&MASK(10))
#define RIGHT(k) ((k)>>10)

int m,n,which[BIT(N)],c[N],len[N],bufsize,ans,id[M],Left[M],Right[M],last[N],sz[N],idx,cs;
int who( unsigned int u ) { return which[L(u)]; }
unsigned int lst[N][M],mask;

void propagate() {
	int i,j,k,t;
	for ( t = 1; t && idx < n; (last[c[idx]]==sz[c[idx]]?++idx:1) ) 
		for ( t = 0, i = 0; i < len[c[idx]] && !t; ++i )
			if ( last[c[idx]]+1 == LEFT(lst[c[idx]][i]) ) {
				bufsize -= S(lst[c[idx]][i]), last[c[idx]] = RIGHT(lst[c[idx]][i]), ++t;
				for ( --len[c[idx]], j = i; j < len[c[idx]]; xchg(lst[c[idx]][j],lst[c[idx]][j+1]), ++j );
			}
}

void push_merge( int t, int Left, int Right ) {
	int i,j,k,l,o,e[2],ii,jj;
	unsigned int a[2][M],u;
	/*
	for ( i = 0; i < len[t]; ++i )
		assert( LEFT(lst[t][i]) > Right || RIGHT(lst[t][i]) < Left );
	for ( i = 0; i < len[t]; ++i )
		for ( j = i+1; j < len[t]; ++j ) 
			assert( RIGHT(lst[t][i]) < LEFT(lst[t][j]) || RIGHT(lst[t][j]) < LEFT(lst[t][i]) );
			*/
	for ( e[0]=e[1]=0, bufsize+=(Right-Left+1), k = 0, i = 0; i < len[t] && !k; ++i ) 
		if ( Right+1 == LEFT(lst[t][i]) ) 
			++k, lst[t][i] = enc(Left,RIGHT(lst[t][i]));
		else if ( (lst[t][i]>>10)+1 == Left )
			++k, lst[t][i] = enc(LEFT(lst[t][i]),Right);
	if ( !k ) { lst[t][len[t]++] = enc(Left,Right); return ; }
	for ( e[0] = len[t], i = 0; i < len[t]; a[0][i] = lst[t][i], ++i );
	for(l=0;k;) {
		for(k=0,i=0;i<e[l]&&!k;++i)
			for ( j = 0; j < e[l] && !k; ++j )
				if ( RIGHT(a[l][i])+1 == LEFT(a[l][j]) ) 
					++k, u = enc(LEFT(a[l][i]),RIGHT(a[l][j])), ii = i, jj = j;
		for ( i = 0, e[l^1] = e[l]-2, o = 0; k && o < e[l]; ++o )
			if ( o != ii && o != jj ) a[l^1][i++] = a[l][o];
		if ( k ) a[l^1][e[l^1]++] = u, l ^= 1;
	}
	for ( len[t] = i = 0; i < e[l]; lst[t][len[t]++] = a[l][i++] );
	/*
	for ( i = 0; i < len[t]; ++i )
		for ( j = i+1; j < len[t]; ++j ) 
			assert( RIGHT(lst[t][i]) < LEFT(lst[t][j]) || RIGHT(lst[t][j]) < LEFT(lst[t][i]) );
			*/
}

int f() {
	int i,w = -1;
	for ( i = 0; i < n; last[i] = 0, len[i++] = 0 );
	for ( idx = bufsize = i = 0; i < m; push_merge(id[i],Left[i],Right[i]), ++i, propagate(), w = max(w,bufsize) );
	if ( 1 && cs == 18 ) {
		for ( i = 0; i < n; printf("%d ",c[i++]) );
		printf(": %d\n",w);
	}
	return w;
}

void rec( int k ) {
	unsigned int i,u;
	if ( k == n ) ans = min(ans,f());
	for( u=((~mask)&MASK(n));u&&(c[k]=who(u))>=0;mask|=BIT(c[k]),rec(k+1),mask&=~BIT(c[k]),u&=~L(u));
}

int main() {
	int i,j,k;
	for ( i = 0; i < N; which[BIT(i)] = i, ++i );
	for ( ;2 == scanf("%d %d",&n,&m) && (n||m); ans=+oo,rec(0),printf("Case %d: %d\n\n",++cs,ans) ) {
		for ( i = 0; i < n; scanf("%d",&sz[i++]) );
		for ( i = 0; i < m; scanf("%d %d %d",&id[i],&Left[i],Right+i),(Left[i]>Right[i]?xchg(Left[i],Right[i]):1),--id[i++] );
		if ( 1 && cs == 18 ) {
			for ( i = 0; i < n; ++i )
				printf("%d ",sz[i]);
			puts("");
			for ( i = 0; i < m; ++i )
				printf("%d %d %d\n",id[i],Left[i],Right[i]);
		}
	}
	return 0;
}

