/*
 * 11815. Ideas
 * TOPIC: bfs, greedy, necessary condition, nasty cases with self-loops
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define N 0x400
#define FG (ptr = fgets(buff,sizeof buff,stdin))
using namespace std;

int ts,n,m,I,cn[N],u[N],v[N],father[N][N];
char buff[1 << 21],*ptr;
bool needs[N][N],creates[N][N],seen[N],b[N][N],reachable[N],g[N][N],processed[N][N];
int edge_id[N][N];
vector<int> adj[N],a[N];
set<int> s[N][N];
queue<int> q;

void bfs( const int idea ) {
	int i,j,k,l;
	memset(seen,0,sizeof seen);
	for ( i = 0; i < n; ++i )
		if ( needs[i][idea] )
			q.push(i), seen[i] = true;
	while ( !q.empty() ) {
		for ( i = q.front(), q.pop(), l = 0; !creates[i][idea] && l < (int)adj[i].size(); ++l ) {
			j = adj[i][l];
			if ( reachable[j] )
				b[idea][edge_id[j][i]] = true;
			if ( !seen[j] && reachable[j] )
				seen[j] = true, q.push(j);
		}
	}
}

int main() {
	int i,j,k,l;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts); ts--; ) {
		sscanf(FG,"%d %d %d",&n,&m,&I);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				s[i][j].clear();
		memset(needs,0,sizeof needs), memset(creates,0,sizeof creates);
		memset(reachable,0,sizeof reachable);
		memset(g,0,sizeof g);
		memset(cn,0,sizeof cn);
		for ( l = 0; l < n; ++l ) {
			adj[l].clear(), a[l].clear();
			for ( FG; 1 == sscanf(ptr,"%d%n",&k,&j); ptr += j, needs[l][k]   = true, ++cn[l] );
			for ( FG; 1 == sscanf(ptr,"%d%n",&k,&j); ptr += j, creates[l][k] = true );
		}
		for ( k = 0; k < m; ++k ) {
			sscanf(FG,"%d %d",&i,&j), edge_id[i][j] = k;
			g[i][j] = true;
			s[i][j].insert(k);
			u[k] = i, v[k] = j;
		}
		memset(processed,0,sizeof processed);
		for ( k = 0; k < m; ++k ) {
			i = u[k], j = v[k];
			if ( processed[i][j] )
				continue ;
			adj[j].push_back(i), a[i].push_back(j);
			processed[i][j] = true;
			edge_id[i][j] = father[i][j] = k;
		}
		for ( q.push(0), memset(seen,0,sizeof seen), seen[0] = true; !q.empty(); )
			for ( i = q.front(), q.pop(), l = 0; l < (int)a[i].size(); ++l )
				if ( !seen[j=a[i][l]] )
					seen[j]=true,q.push(j);
		for ( i = 0; i < n; ++i )
			reachable[i] = seen[i];
		memset(b,0,sizeof b);
		for ( i = 0; i < I; ++i ) bfs(i);
		for ( k = 0; k < m; ++k, putchar('\n') ) {
			for ( j = 0, i = 0; i < I; ++i )
				if ( b[i][father[u[k]][v[k]]] ) {
					if ( ++j > 1 ) putchar(' ');
					printf("%d",i);
				}
		}
	}
	return 0;
}

