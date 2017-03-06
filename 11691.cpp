/*
   11691. Allergy Test
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
using namespace std;
#define M(k) ((1UL << (k))-1UL)
#define Q (1UL << 21)
#define oo 0xfffffffful

int bts( unsigned int k ) {
	int i;
	for ( i = 0; (1UL << i) < k; ++i );
	return i;
}

map<int,int> cnt;
int b[32],n,len[32];
unsigned int z[Q];
queue<unsigned int> q;
map<int,int> :: iterator it;

void bfs() {
	unsigned int u,v,dw,w = +oo;
	int i,j,k;
	memset(z,0xff,sizeof(z));
	for ( i = 1, it = cnt.begin(); it != cnt.end(); ++it, ++i ) {
		u = (1<<b[i])|((it->first-1)<<b[n+1]);
		q.push(u), z[u] = it->first;
	}
	while ( !q.empty() ) {
		u = q.front(), q.pop();
		if ( (u & M(b[n+1])) == T ) {
			w = min(w,z[u]);
			continue ;
		}
		for ( i = 1; i <= n; ++i ) {
			k = (u >> b[i]) & M(b[i+1]-b[i]);
			assert( cnt[len[i]] >= k );
			if ( cnt[len[i]] > k ) {
				v = u;
				if ( z[v] > z[u] + dw ) 
					z[v] = z[u] + dw, q.push(v);
			}
		}
	}
	printf("%u\n",w);
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( cin >> ts; ts--; ) {
		for ( scanf("%d",&n), cnt.clear(), i = 0; i < n; ++i, ++cnt[k] )
			if ( scanf("%d",&k) &&  cnt.find(k) == cnt.end() ) cnt[k] = 0;
		for ( i = 1, it = cnt.begin(); it != cnt.end(); ++it )
			len[i] = it->first, b[++i] = bts(it->first);
		n = cnt.size();
	}
	return 0;
}

