/*
 * 1357. Cells
 * TOPIC: dfs, nested intervals
 * status: Accepted
 */
#pragma comment(linker , "/STACK:102400000,102400000")
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
#define N (1<<22)
#define MAXTOT (20000007)
enum { WHITE, GREY, BLACK };

int n,c[N],in[MAXTOT],out[MAXTOT],tick,first_son[N];

void dfs( int x ) {
	in[x] = ++tick;
	for ( int i = 0; i < c[x]; ++i )
		if ( first_son[x]+i < n )
			dfs(first_son[x]+i);
		else in[first_son[x]+i] = ++tick, out[first_son[x]+i] = tick;
	out[x] = tick;
}

int main() {
	int i,j,k,qr,cs = 0,ts;
#ifndef ONLINE_JUDGE
	freopen("1357.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		memset(in,0,sizeof in);
		memset(out,0,sizeof in);
		tick = 0;
		for ( i = 0; i < n; scanf("%d",&c[i++]) );
		for ( k = first_son[0] = 1, i = 1; i < n; ++i )
			first_son[i] = first_son[i-1]+c[i-1];
	   	dfs(0), printf("Case %d:\n",++cs);
		for ( scanf("%d",&qr); qr-- && 2 == scanf("%d %d",&i,&j); puts(in[i]<in[j]&&out[j]<=out[i]?"Yes":"No") );
		if ( ts ) putchar('\n');
	}
	return 0;
}


