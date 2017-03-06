/*
 * 1720. Weather Report
 * TOPIC: huffman, preobability, expectation, greedy, priority_queue, multionomial distribution
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
typedef double ld;
using namespace std;
#define tol 1e-9
#define N 21

struct Entry {
	map<int,ld> h;
	ld weight;
	long long cnt;
	Entry( ld w, long long c ) {
		weight = w;
		cnt = c;
		h.clear();
	};
	Entry() {};
};

Entry merge( Entry &x, Entry &y ) {
	// Entry z(log(exp(x.weight)+exp(y.weight)),0LL);
	Entry z(x.weight+y.weight,0LL);
	for ( map<int,ld>::iterator it = x.h.begin(); it != x.h.end(); ++it )
		if ( y.h.find(it->first) != y.h.end() )
			z.h[it->first+1] = it->second+y.h[it->first];
		else z.h[it->first+1] = it->second;
	for ( map<int,ld>::iterator it = y.h.begin(); it != y.h.end(); ++it )
		if ( x.h.find(it->first) == x.h.end() )
			z.h[it->first+1] = it->second;
	return z;
}

struct comp {
	bool operator() ( const Entry &x, const Entry &y ) {
		return x.weight > y.weight;
	}
};

priority_queue<Entry,vector<Entry>,comp> pq;
int n;
ld p[4];
long long f[N];

int main() {
	int i,j,k,t;
	ld pi,pj,pk,pt,ans,sum,l[4];
	for ( f[0] = 1LL, i = 1; i < N; ++i )
		f[i] = f[i-1]*((long long)i);
	long long cnt;
	ld prob;
	Entry e1,e2,entry1,entry2;
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		for ( i = 0; i < 4; ++i )
			scanf("%lf",&p[i]), l[i] = log(p[i]);
		assert( pq.empty() );
		for ( pi = 1.00, i = 0; i <= n; ++i, pi *= p[0] )
			for ( pj = 1.00, j = 0; i+j <= n; ++j, pj *= p[1] )
				for ( pk = 1.00, k = 0; i+j+k <= n; ++k, pk *= p[2] ) {
					t = n-i-j-k, pt = pow(p[3],t);
					//prob = i*l[0]+j*l[1]+k*l[2]+t*l[3];
					prob = pi*pj*pk*pt;
					cnt = f[n]/f[i]/f[j]/f[k]/f[t];
					e1 = Entry(prob,cnt);
					e1.h[0] = pi*pj*pk*pt;
					pq.push(e1);
				}
		while ( pq.size() >= 2 ) {
			entry1 = pq.top(), pq.pop();
			if ( entry1.cnt >= 2 ) {
				e1 = merge(entry1,entry1);
				e1.cnt = entry1.cnt>>1;
				cnt = 1;
			}
			else cnt = 0;
			if ( entry1.cnt&1 ) {
				entry2 = pq.top(), pq.pop();
				e2 = merge(entry1,entry2);
				e2.cnt = 1;
				if ( --entry2.cnt ) pq.push(entry2);
				pq.push(e2);
			}
			if ( cnt ) pq.push(e1);
		}
		e1 = pq.top(), pq.pop(), ans = 0, sum = 0;
		assert( e1.cnt == 1 );
		for ( map<int,ld>::iterator it = e1.h.begin(); it != e1.h.end(); ++it )
			ans += it->first*it->second, sum += it->second;
		printf("%.9lf\n",ans);
	}
	return 0;
}

