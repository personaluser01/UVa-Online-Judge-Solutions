/*
 * 10415. Eb Alto Saxophone Player
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
#define N 0x80

int len[] = {7,6,5,4,3,2,1,1,7,6,5,4,3,2},
		finger[] = {2,3,4,7,8,9,10,
					2,3,4,7,8,9,
					2,3,4,7,8,
					2,3,4,7,
					2,3,4,
					2,3,
					2,
					3,
					1,2,3,4,7,8,9,
					1,2,3,4,7,8,
					1,2,3,4,7,
					1,2,3,4,
					1,2,3,
					1,2};
char s[0x400];
int cnt[0x10],adj[N][N],deg[N],cd[N],used[2][N];
unsigned int u[N];

int f( char ch ) {
	if ( isupper(ch) ) 
		return 7+cd[tolower(ch)-'a'];
	return cd[ch-'a'];
}
#define BIT(k) ((1UL << ((k))))

int main() {
	int i,j,k,ts,t,n;
	unsigned int w[2];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	cd['c'-'a']=0,cd['d'-'a']=1,cd['e'-'a']=2,cd['f'-'a']=3,cd['g'-'a']=4,cd['a'-'a']=5,cd['b'-'a']=6;
	for ( k = 0, i = 0; i < 14; ++i )
		for ( j = 0; j < len[i]; ++j )
			adj[i][deg[i]++] = finger[k++];
	for ( i = 0; i < 14; ++i )
		for ( j = 0; j < deg[i]; ++j )
			u[i] |= (1UL << (adj[i][j]-1));
	for ( scanf("%d",&ts),getchar(); ts-- && fgets(s,sizeof(s),stdin);) {
		for ( n = 0; s[n] && s[n] != '\n'; ++n );
		memset(cnt,0,sizeof(cnt));
		if ( !n ) {
			puts("0 0 0 0 0 0 0 0 0 0");
			continue ;
		}
		memset(used,0,sizeof(used));
		w[0] = w[1] = 0;
		for ( t = 0, k = f(s[0]), j = 0; j < deg[k]; ++j )
			w[t] |= BIT(adj[k][j]-1), ++cnt[adj[k][j]];
		for ( i = 1; i < n; ++i ) {
			k = f(s[i]), t ^= 1, w[t] = w[t^1];
			w[t] = w[t]&~(w[t]&~u[k]);
			for ( j = 0; j < deg[k]; ++j )
				if ( !(w[t] & BIT(adj[k][j]-1)) ) {
					assert( !(w[t^1] & BIT(adj[k][j]-1)) );
					++cnt[adj[k][j]], w[t] |= BIT(adj[k][j]-1);
				}
		}
		for ( i = 1; i <= 9; ++i )
			printf("%d ",cnt[i]);
		printf("%d\n",cnt[10]);
	}
	return 0;
}

