/*
 * 12160. 
 * status: Accepted
 * TOPIC: easy bfs
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define R 0x10
#define N (10000)
#define oo 0xfffffffful
#include <queue>
#include <iostream>

int m,n;
unsigned int d[N],e[R];
queue<unsigned int> q;

bool bfs( const unsigned int src, const unsigned int dest ) {
	unsigned int u,v,i;
	memset(d,0xfful,sizeof d);
	for ( d[src] = 0, q.push(src); !q.empty(); ) 
		for ( u = q.front(), q.pop(), i = 0; i < m; ++i ) 
			if ( d[v = (u+e[i])%N] > d[u]+1 )
				d[v] = d[u]+1, q.push(v);
	return d[dest]<+oo;
}

int main() {
	int i,j,k,cs = 0,ts,src,dest;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;3 == scanf("%d %d %d",&src,&dest,&m) && (src||dest||m) && printf("Case %d: ",++cs); ) {
		for ( i = 0; i < m; ++i )
			scanf("%u",e+i);
		if ( bfs(src,dest) )
			printf("%u\n",d[dest]);
		else puts("Permanently Locked");
	}
	return 0;
}

