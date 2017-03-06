/*
 * 12321. Gas stations
 * TOPIC: greedy, interval coverage, classical greedy, similar to 10020
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define N (1<<16)
using namespace std;
typedef long long i64;

int L,n;

struct cell {
	int x,y;
	cell() {};
	cell( int xx, int yy ) {
		x = xx, y = yy;
	}
};

struct comp {
	bool operator() ( const cell &a, const cell &b ) {
		if ( a.x == b.x ) 
			return a.y > b.y;
		return a.x < b.x;
	}
};

cell p[N];

int main() {
	int i,j,k,left,right,m,best_right;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&L,&n) && (L||n) ) {
		for ( i = 0; i < n; ++i ) {
			scanf("%d %d",&j,&k);
			p[i] = cell(max(0,j-k),min(j+k,L));
		}
		sort(p,p+n,comp());
		if ( p[0].x > 0 ) {
			puts("-1");
			continue ;
		}
		for ( m = 0, right = p[0].y, ++m, i = 1; right < L && i < n; ) {
			for ( best_right = -1; i < n && p[i].x <= right; ++i )
				if ( p[i].y > best_right ) 
					best_right = p[j = i].y;
			if ( best_right == -1 ) break ;
			else 
				i = j+1, right = best_right, ++m;
		}
		if ( right < L ) puts("-1");
		else printf("%d\n",n-m);
	}
	return 0;
}

