/*
 * 11997. K-Smallest Sums
 * status: Accepted
 * TOPIC: backtracking, pruning
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 751
typedef long long i64;
using namespace std;

int n,m,t;
i64 c[N][N],a[N],best[N];
priority_queue<i64,vector<i64> > q;

void f( int row, i64 w ) {
	if ( row == n ) {
		if ( q.size() < n ) {
			q.push(w);
			return ;
		}
		if ( q.top() > w ) {
			q.pop(), q.push(w);
			return ;
		}
		return ;
	}
	if ( q.size() == n && q.top() <= w )
		return ;
	if ( q.size() == n && q.top() <= best[row]+w )
		return ;
	for ( int j = 0; j < n && !(q.size()==n&&q.top()<=w+c[row][j]); ++j )
		f(row+1,w+c[row][j]);
}

void dis() {
	if ( q.empty() )
		return ;
	i64 x = q.top();
	q.pop();
	dis();
	if ( t ) printf(" %lld",x);
	else printf("%lld",x);
	++t;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n); putchar('\n') ) {
		for ( i = 0; i < n; sort(c[i],c[i]+n), ++i )
			for ( j = 0; j < n; scanf("%lld",&c[i][j++]) );
		if ( n == 1 ) {
			printf("%lld\n",c[0][0]);
			continue ;
		}
		for ( i = 0; i < n; ++i )
			for ( best[i] = 0, k = i; k < n; ++k )
				best[i] += c[k][0];
		t = 0, f(0,0), dis();
	}
	return 0;
}

