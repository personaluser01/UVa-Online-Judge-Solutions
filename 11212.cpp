/*
 * 11212. Editing a Book
 * TOPIC: bfs
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#define N 10
using namespace std;
typedef unsigned long long u64;

int ord[N],n;
u64 BIT( int k )  { return (1ULL<<(k));  }
u64 MASK( int k ) { return BIT(k)-1ULL; }

		u64 Foo( int *c ) {
			u64 u = 0;
			for ( int i = 0; i < n; ++i ) 
				u |= (((u64)c[i])<<(4*i));
			return u;
		}

		u64 cutAndPaste( u64 u, int i, int j, int k ) {
			u64 w, m = MASK(4*(j-i+1)), mid = ((u>>(4*i))&m), left = (u&MASK(4*i)), right = (u>>(4*(j+1)));
			w = left|(right<<(4*i));
			left = (w&MASK(4*k)); right = (w>>(4*k));
			return left | (mid<<(4*k)) | (right<<(4*(k+(j-i+1))));
		}

		void display( u64 u ) {
			for ( int i = 0; i < n; ++i )
				printf("%llu ",(u>>(4*i))&0xfull);
			puts("");
		}

queue<u64> q;
map<u64,int> s,r;

int main() {
	int cs = 0,i,j,k,t,l,c[N],w;
	u64 u,v,x,y,src,dst,LIM = (1ULL<<16);
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i ) ord[i] = i;
	for(;1 == scanf("%d",&n) && n > 0; printf("Case %d: %d\n",++cs,w)) {
#ifndef ONLINE_JUDGE
		for ( i = 0; i < n; ++i ) scanf("%d",c+i);
#else
		for ( i = 0; i < n; ++i ) scanf("%d",c+i), --c[i];
#endif
		src = Foo(c); dst = Foo(ord);
		for(;!q.empty();q.pop()); w = 0;
		for ( s.clear(), s[src] = 0, q.push(src), w = max(w,t); !q.empty() && s.find(dst) == s.end() && s.size() < LIM; )
			for ( t=s[x=q.front()], q.pop(),i=0; i<n && t <= n+1; ++i )
				for ( j = i; j < n; ++j )
					for ( k = 0; k <= (n-(j-i+1)); ++k )
						if ( s.find(y=cutAndPaste(x,i,j,k))==s.end() || s[y] > t+1 ) 
							s[y] = t+1, q.push(y);
		if ( s.find(dst) != s.end() ) {
			w = s[dst];
			continue ;
		}
		for(;!q.empty();q.pop());
		w = (1<<29);
		for ( r.clear(), r[dst] = 0, q.push(dst); !q.empty() && q.size() < LIM; ) {
			t = r[x=q.front()], q.pop();
			if ( s.find(x) != s.end() ) {
				if ( w > s[x]+t ) w = s[x]+t;
				continue ;
			}
			for ( i=0; i<n && t <= n+2 && t < w; ++i )
				for ( j = i; j < n; ++j )
					for ( k = 0; k <= (n-(j-i+1)); ++k )
						if ( r.find(y=cutAndPaste(x,i,j,k))==r.end() || r[y] > t+1 ) 
							r[y] = t+1, q.push(y);
		}
	}
	return 0;
}


