/*
 * 10854. Number of Paths
 * TOPIC: dag, dp, number of paths, combinatorics
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define N 0x400
typedef long long i64;

char buff[0x400],c[N];
int n,V;
vector<int> adj[2][N];

void skip() { for ( ;fgets(buff,sizeof(buff),stdin) && 0 == strncmp(buff,"S",1); ); }

void recover( int x ) {
	int y;
	assert( 0 == strncmp(buff,"IF",2) );
	for ( skip(); 0==strncmp(buff,"IF",2); skip() ) 
		recover(y=V++),adj[0][x].push_back(y);
	assert( 0 == strncmp(buff,"ELSE",4) );
	for ( skip(); 0==strncmp(buff,"IF",2); skip() ) 
		recover(y=V++),adj[1][x].push_back(y);
	assert( 0 == strncmp(buff,"END_IF",6) );
}

i64 f( int x ) {
	i64 ax[2] = {1LL,1LL};
	for ( int t = 0; t <= 1; ++t ) 
		for ( int i = 0; i < (int)adj[t][x].size(); ++i ) 
			ax[t] *= (f(adj[t][x][i]));
	return ax[0]+ax[1];
}

int main() {
	int i,j,k,t,ts;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( t = 0; t <= 1; ++t )
			for ( i = 0; i < N; ++i )
				adj[t][i].clear();
		for ( V = 1, skip(); 0 != strncmp(buff,"ENDPROGRAM",10); skip() ) 
			if ( 0 == strncmp(buff,"IF",2) ) 
				recover(j = V++), adj[0][0].push_back(j);
		printf("%lld\n",f(0)-1);
	}
    return 0;
}

