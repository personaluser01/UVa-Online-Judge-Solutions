/*
 * Sky code
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 10008
using namespace std;

int n,c[N];
bool is_prime[N];
vector<int> p;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( is_prime[2] = true, i = 1; i < N; is_prime[i+=2] = true );
	for ( i = 3; i < N; i += 2 )
		for (j=i+i;is_prime[i] && j<N;is_prime[j] = false, j+=i);
	for ( p.clear(), i = 3, p.push_back(2); i < N; i += 2 )
		if ( is_prime[i] )
			p.push_back(i);
	while ( 1 == scanf("%d",&n) ) {
		for ( i = 0; i < n; scanf("%d",c+i), ++i );
	}
	return 0;
}

