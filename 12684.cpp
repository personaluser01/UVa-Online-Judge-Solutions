/*
 * 12684. VivoParc
 * TOPIC: graph coloring
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define N 0x80
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define W 64
#define C 4
typedef unsigned long long u64;
using namespace std;

char *ptr,buff[0x400],who[1<<21];
int which ( u64 u ) {
	if ( u >= BIT(60) )
		return 60+who[u>>60];
	if ( u >= BIT(40) )
		return 40+who[u>>40];
	if ( u >= BIT(20) )
		return 20+who[u>>20];
	return who[u];
};
u64 adj[N][N/W],color_forbidden[C][N/W];
int n,e[N];

int f( int x ) {
	int c,i,j;
	u64 u[N/W] = {0};
	if ( x == n ) {
		for ( i = 0; i < n; ++i )
			printf("%d %d\n",i+1,e[i]+1);
		return 1;
	}
	for ( c = 0; c < C; ++c )
		if ( !(color_forbidden[c][x>>6]&BIT(x&63)) ) {
			e[x] = c;
			for ( j = 0; j <= n/W; ++j )
				u[j] = color_forbidden[c][j], color_forbidden[c][j] |= adj[x][j];
			if ( f(x+1) ) return 1;
			for ( j = 0; j <= n/W; ++j )
				color_forbidden[c][j] = u[j];
		}
	return 0;
}

int main() {
	int i,j,k,cs = 0;
	for ( k = 0; k < 21; who[BIT(k)] = k, ++k );
	for(;FG && *ptr != '\0' && *ptr != '\n'; f(0) ) {
		if ( ++cs > 1 ) putchar('\n');
		for ( sscanf(ptr,"%d",&n), i = 0; i < n; ++i )
			for ( j = 0; j <= n/W; adj[i][j++] = 0 );
		for (;FG&&2==sscanf(ptr,"%d-%d",&i,&j);--i,--j,adj[i][j>>6]|=BIT(j&63),adj[j][i>>6]|=BIT(i&63));
		for ( i = 0; i < C; ++i )
			for ( j = 0; j <= n/W; color_forbidden[i][j++] = 0 );
	}
	return 0;
}

