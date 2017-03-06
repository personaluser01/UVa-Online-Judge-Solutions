#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long i64;
#define N 8
#define L(i) ((i) & ((~(i))+1))
#define oo 0xfffffffful
#define M(k) ((1UL << (k))-1UL)
i64 z[N][1 << N];
vector<unsigned int> adj[N];
int power_of_two( unsigned int u ) { return !(u - L(u)); }

i64 calc_z( unsigned int x, unsigned int u ) {
	unsigned int i,y;
	if ( z[x][u] < +oo )
		return z[x][u];
	for ( z[x][u] = 0, i = 0; i < adj[x].size(); ++i )
		if ( !((u>>(y=adj[x][i]))&1) ) 
			z[x][u] += calc_z(y,u|(1UL<<y));
	return z[x][u];
}

int main() {
	unsigned int i,j,k;
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < N; ++j )
			if ( i != j )
				if ( power_of_two(i ^ j) )
					adj[i].push_back(j);
	memset(z,0xfful,sizeof(z));
	for ( i = 1; i < N; ++i )
		z[i][M(N)] = 1UL;
	printf("%lu\n",calc_z(0,1));
	return 0;
}

