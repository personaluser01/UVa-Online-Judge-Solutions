/*
 * 13018. Dice Cup
 * TOPIC: dp, trivial, probability
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 21
using namespace std;

int m,n,c[N*N];

int main() {
	int i,j,k,cs = 0;
	while ( 2 == scanf("%d %d",&n,&m) ) {
		if ( ++cs > 1 ) putchar('\n');
		memset(c,0,sizeof c);
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				++c[i+j];
		vector<int> vec;
		for ( k = -1, i = 1; i <= m+n; ++i )
			if ( c[i] > k ) 
				vec.clear(), vec.push_back(i), k = c[i];
			else if ( c[i] == k )
				vec.push_back(i);
		for ( i = 0; i < (int)vec.size(); ++i )
			printf("%d\n",vec[i]);
	}
	return 0;
}

