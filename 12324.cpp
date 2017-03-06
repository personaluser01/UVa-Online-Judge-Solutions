/*
 * 12324. Philip J. Fry Problem
 * TOPIC: bfs, dijkstra, dp, search space
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
#define N 0x80
#define M (N*N)
#define oo 0xfffffffful
#include <queue>
using namespace std;

int n;
vector<pair<int,int> > v;
unsigned int z[N][M],w;
queue<pair<int,int> > q;

int main() {
	int i,j,k,ni,nk,t,nt;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(;scanf("%d",&n)&&n>0;) {
		memset(z,0xffull,sizeof z);
		for(v.clear(),i=1;i<=n;++i)
			scanf("%d %d",&j,&k), v.push_back(make_pair(j,k));
		for(w=+oo,q.push(make_pair(0,0));!q.empty();){
			pair<int,int> r = q.front();
			q.pop(), i = r.first, k = r.second;
			if ( i == n ) { w = min(w,z[i][k]); continue ; }
			nk = k+v[i].second, nt = v[i].first;
			assert( !(nt&1) );
			if ( k && z[i+1][nk-1] > z[i][k]+(nt>>1) )
				z[i+1][nk-1] = z[i][k]+(nt>>1), q.push(make_pair(i+1,nk-1));
			if ( z[i+1][nk] > z[i][k]+nt )
				z[i+1][nk] = z[i][k]+nt, q.push(make_pair(i+1,nk));
		}
		printf("%u\n",w+1);
	}
    return 0;
}

