/*
 * 12582. Wedding of a Sultan
 * TOPIC: recursion, tree traversal
 * status: Accepted
 */
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#define N 32
using namespace std;

int ts,cs,n,cn[N];
char buff[0x400];
vector<int> adj[N];

void recover( int i, int j ) {
	int x = buff[i]-'A',k,t,y;
	for ( k = i+1; k < j; k = 1+t ) {
		for ( t = k+1; t < j && buff[t] != buff[k]; ++t );
		assert( t < j );
		recover(k,t), adj[x].push_back(y = buff[k]-'A'), adj[y].push_back(x);
	}
}

int main() {
  int i,j,k;
#ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
#endif
  for ( scanf("%d",&ts); ts--; ) {
    scanf("%s",buff);
    printf("Case %d\n",++cs);
    n = strlen(buff);
	for ( i = 0; i < N; adj[i++].clear() );
	assert( buff[0] == buff[n-1] );
	recover(0,n-1);
	for ( i = 0; i < N; ++i )
		if ( adj[i].size() )
			printf("%c = %lu\n",i+'A',adj[i].size());
  }
  return 0;
}
