/*
 * 11987. Almost Union Find
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
#define N 110100
typedef long long i64;

int n,m,isdig[256],id[N],
	rank[N+N],p[N+N];
i64 card[N+N],sum[N+N];

int getnum() {
	int ch,n = 0;
	for (;(ch = getchar()) != EOF && !isdig[ch];);
	if ( ch == EOF )
		return -1;
	for( n = ch-'0';(ch = getchar()) != EOF && isdig[ch];)
		n = (n<<1)+(n<<3)+(ch-'0');
	return n;
}

void make_set( int x ) { card[p[id[x]] = id[x]] = rank[id[x]] = 1, sum[id[x]] = x+1; }

int find( int x ) { return p[x] = (x==p[x]?x:find(p[x])); }
void link( int x, int y ) {
	if ( rank[x] > rank[y] ) 
		p[y] = x, card[x] += card[y], sum[x] += sum[y];
	else {
		p[x] = y, card[y] += card[x], sum[y] += sum[x];
		if ( rank[y] == rank[x] ) ++rank[y];
	}
}

void merge( int x, int y ) { 
	if ( find(x) != find(y) )
		link(find(x),find(y)); 
}

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(i='0';i<='9';isdig[i++]=1);
	while ( (n = getnum()) != -1 && (m = getnum()) >= 0 ) {
		for ( k = 0; k < n; make_set(id[k] = k), ++k );
		while ( m-- ) {
			k = getnum();
			switch ( k ) {
				case 1: i = id[getnum()-1], j = id[getnum()-1];
						if ( find(i) != find(j) )
							merge(i,j);
						break ;
				case 2: i = getnum()-1, j = getnum()-1;
						if ( find(id[i]) == find(id[j]) )
							continue ;
						--card[find(id[i])], sum[find(id[i])] -= (i+1);
						id[i] = n++, make_set(i), merge(id[i],id[j]);
						break ;
				case 3: i = id[getnum()-1];
						printf("%lld %lld\n",card[find(i)],sum[find(i)]);
						break ;
				default: assert( 0 );
			}
		}
	}
	return 0;
}

