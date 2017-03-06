/*
 * 12394. Peer Review
 * TOPIC: graphs
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#define N 0x400
using namespace std;

int m,n,V,tag[N];
map<string,int> s;
vector<int> adj[N];

int main() {
	int i,j,k,l,problema;
	char tmp[0x400];
	for (;2==scanf("%d %d",&m,&n) && (m||n);) {
		for ( i = 0; i < n; adj[i++].clear() );
		for ( V = 0, s.clear(), i = 0; i < n; ++i ) {
			scanf("%s",tmp);
			string t(tmp);
			if ( s.find(t) != s.end() ) k = s[t];
			else k = s[t] = V++;
			tag[i] = k;
			for ( j = 0; j < m; ++j ) {
				scanf("%d",&l), --l;
				adj[l].push_back(i);
			}
		}
		bool ok;
		for ( problema = 0, i = 0; i < n; ++i ) {
			set<int> e;
			for ( ok = true, e.clear(), l = 0; l < (int)adj[i].size(); ++l ) {
				e.insert(adj[i][l]);
				if ( tag[adj[i][l]] == tag[i] ) 
					if ( ok ) ++problema, ok = false;
			}
			if ( (adj[i].size() != m || e.size() != m) && ok ) ++problema, ok = false;
		}
		if ( problema == 1 ) puts("1 PROBLEM FOUND");
		else if ( problema >= 2 )
			printf("%d PROBLEMS FOUND\n",problema);
		else puts("NO PROBLEMS FOUND");
	}
	return 0;
}

