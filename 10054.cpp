/*
 * 10054. Necklace
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define N 64
#define M (1 << 16)
#define oo 0xfffffffful
using namespace std;

int cnt[N][N],v[N],u[N],nn,n,m,seen[N],yes,path[M],*ptr,*head,*tail,deg[N],T[N];
set<int> adj[N],lst;
set<pair<int,int> > D;
vector<int> cycle[N];

bool dfs( int x, int len, int dst ) {
	set<int>::iterator it;
	int y;
	if ( len && x == dst ) {
		for ( int i = 0; i < ptr-path; ++i )
			cycle[dst].push_back(path[i]);
		return true;
	}
	if ( seen[x] == yes )
		return false;
	seen[x] = yes;
	for ( it = adj[x].begin(); it != adj[x].end(); ++it ) {
		if ( (y = *it) != dst && seen[*it] == yes )
			continue ;
		if ( D.find(make_pair(min(x,y),max(x,y))) != D.end() )
			continue ;
		*ptr++ = (y = *it);
		if ( !--cnt[min(x,y)][max(x,y)] )
			D.insert(make_pair(min(x,y),max(x,y)));
		if ( dfs(y,len+1,dst) ) {
			if ( adj[y].size() )
				lst.insert(y);
			return true;
		}
		--ptr;
		if ( ++cnt[min(x,y)][max(x,y)] == 1 )
			D.erase(make_pair(min(x,y),max(x,y)));
	}
	return false;
}

void euler_tour() {
	set<int>::iterator it;
	if ( !adj[v[0]].size() )
		return ;
	D.clear();
	for ( lst.insert(v[0]); lst.size();) {
		ptr = path, it = lst.begin();
		++yes, dfs(*it,0,*it);
		for ( set<pair<int,int> >::iterator q = D.begin(); q != D.end(); ++q ) {
			pair<int,int> t = *q;
			int xx = q->first, yy = q->second;
			adj[xx].erase(yy), adj[yy].erase(xx);
			if ( !adj[xx].size() ) lst.erase(xx);
			if ( !adj[yy].size() ) lst.erase(yy);
		}
		D.clear();
	}
}

void dump( int x ) {
	if ( seen[x] == yes )
		return ;
	seen[*ptr++ = x] = yes;
	while ( (--T[x]) >= 0 ) *ptr++ = x;
	for ( int i = 0; i < (int)cycle[x].size(); ++i ) {
		int y = cycle[x][i];
		if ( seen[y] == yes )
			*ptr++ = y;
		else dump(y);
	}
}


int main() {
	int i,j,k,ts,cs = 0,x,y;
	set<int>::iterator it;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		if ( cs >= 1 ) putchar('\n');
		printf("Case #%d\n",++cs);
		for ( lst.clear(), x = 0; x < N; ++x )
			adj[x].clear(), cycle[x].clear(), deg[x] = 0, T[x] = 0;
		for ( i = 0; i < N; ++i )
			for ( j = i; j < N; ++j )
				cnt[i][j] = 0;
		for ( scanf("%d",&n), k = 0; k < n; ++k ) {
			scanf("%d %d",&i,&j), --i, --j;
			if ( i > j ) swap(i,j);
			if ( i == j ) { ++T[i]; continue ; }
			if ( !cnt[x = i][y = j]++ ) 
				adj[x].insert(y), adj[y].insert(x);
			++deg[x], ++deg[y];
		}
		for ( nn = 0, x = 0; x < N; ++x )
			if ( (!adj[x].size()) && T[x] )
				u[nn++] = x;
		for ( n = 0, x = 0; x < N; ++x )
			if ( adj[x].size() && (v[n++] = x) );
		for ( i = 0; i < n; ++i )
			if ( deg[v[i]] & 1 ) {
				epa: puts("some beads may be lost");
				goto next;
			}
		for ( k = 0, head = tail = path, seen[*tail++ = v[0]] = ++yes; head < tail;)
			for ( ++k, x = *head++, it = adj[x].begin(); it != adj[x].end(); ++it )
				if ( seen[*it] != yes )
					seen[*tail++ = *it] = yes;
		if ( k < n ) goto epa;
		if ( !n ) {
			assert( nn == 1 );
			++yes, ptr = path, dump(u[nn-1]);
		}
		else {
			euler_tour();
			ptr = path, ++yes, dump(v[0]);
		}
		/*
		for ( k = 0, i = 0; i < n; ++i )
			k += cycle[v[i]].size()-1;
		printf("%d\n",k);
		*/
		for ( i = 0; i+1 < ptr-path; ++i )
			printf("%d %d\n",path[i]+1,path[i+1]+1);
		next:;
	}
	return 0;
}

