#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long i64;
#define M(k) ((1UL << (k))-1UL)

vector<pair<unsigned int, i64> > q;
char bts[1024];
i64 F[8];

int main() {
	unsigned int u,v,i,j,k,l;
	i64 A,B,total = 0;
	for ( F[i = 0] = 1; (++i) < 8; F[i] = F[i-1]*i );
	for ( u = 1; u < M(7); ++u ) 
		k=bts[u]=bts[u>>1]+(u&1),q.push_back(make_pair(u,F[k]*F[7-k])), total+=F[k]*F[7-k];
	// printf("%lld\n",total);
	for ( A = 0, i = 0; i < q.size(); ++i ) 
		for ( j = 0; j < q.size(); ++j )
			if ( (q[i].first&q[j].first) == 0 )
				A+=q[i].second*q[j].second;
	printf("%lf\n",(A+0.0)/total/total);
	printf("%lf\n",pow(0.75,7));
	return 0;
}

