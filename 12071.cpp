/*
 * 12071. Understanding Recursion
 * TOPIC: very neat interview question
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;

int n;
map<int,long long> m;
vector<pair<int,long long> > vec;

int main() {
	int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		for ( m.clear(), i = 0; i < n; ++i ) {
			scanf("%d",&k);
			if ( m.find(k) == m.end() )
				m[k] = 1;
			else ++m[k];
		}
		vec.clear();
		for ( map<int,long long>::iterator it = m.begin(); it != m.end(); ++it )
			vec.push_back(make_pair(it->first,it->second));
		long long ans = 0, sq = 0;
		for ( map<int,long long> :: iterator it = m.begin(); it != m.end(); ++it )
			ans += it->second, sq += it->second*it->second;
		printf("Case %d: %lld\n",++cs,(ans*ans-sq)/2);
	}
	return 0;
}


