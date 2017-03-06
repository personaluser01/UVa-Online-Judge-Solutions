/*
 * 111523. Recycling
 * TOPIC: dp
 * status: Accepted
 */
#include <iostream>
#include <cstring>
#include <set>
#include <map>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define oo 0xfffffffful
using namespace std;

int ts,cs,n,c[N],V,idx[N],K;
map<string,int> m;
unsigned int z[N][N];

int f( int left, int right ) {
	int i,j,k,l;
	if ( left > right ) return 0;
	if ( left == right )
		return 1;
	assert( left < right );
	for ( i = left; i <= right; ++i )
		for ( j = left; j <= right; ++j )
			z[i][j] = (i<=j?+oo:0);
	for ( i = left; i <= right; ++i ) 
		for ( j = i; j <= right && c[j] == c[i]; ++j )
			z[i][j] = 1;
	for ( l = 2; l <= right-left+1; ++l )
		for ( i = left; (j=i+l-1) <= right; ++i )
			for ( z[i][j]=min(z[i][j],z[i+1][j]+1),k = i+1; k <= j; ++k )
				if ( c[i] == c[k] )
					z[i][j] = min(z[i][j],z[i+1][k]+z[k+1][j]);
	return z[left][right];
}

int main() {
	int i,j,k,cost;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( K=0,idx[K++]=-1,V=1,m.clear(),printf("Case %d: ",++cs),scanf("%d",&n), i=0; i<n; ++i ) {
			scanf("%s",tmp);
			string t(tmp);
			if ( isupper(0[tmp]) ) { c[idx[K++]=i]=0; continue; }
			if ( m.find(t) == m.end() ) m[t] = V++;
			c[i] = m[t];
		}
		for ( idx[K++]=n,cost=0, i=1; i<K; ++i ) 
			cost += f(idx[i-1]+1,idx[i]-1);
		printf("%d\n",cost);
	}
    return 0;
}

