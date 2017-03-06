/*
 * 1229. Sub-Dictionary
 * status: Accepted
 * TOPIC: Graphs, SCC, Topological Sort, DAG
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define N 0x80
#define FG (qtr=fgets(s,sizeof s,stdin))
#define FILL(s) (memset(s,0,sizeof s))
using namespace std;
enum { WHITE, GRAY, BLACK };
enum { D, T };

map<string,int> m;
int n,V,scc[N],mark,st[N],*top,g[N][N],yes,in[N],card[N],*ptr,q[N],z[N];
char color[N];
vector<int> adj[2][N],v[N];
char s[1<<21],*qtr;
string word[N];
set<string> e;

int ins( char *a ) {
	string t = string(a);
	if ( m.find(t) == m.end() ) 
		return m[t] = V++;
	return m[t];
}

void dfs( int x, const int t ) {
	int i,y;
	assert( color[x] == WHITE );
	for ( color[x] = GRAY, i = 0; i < (int)adj[t][x].size(); ++i )
		if ( color[y = adj[t][x][i]] == WHITE )
			dfs(y,t);
	if ( t == T )
		*++top = x;
	else scc[x] = mark;
    color[x] = BLACK;
}

void topo( int x, const int t ) {
    int i,y;
    assert( color[x] == WHITE );
    z[x] = (card[x]>=2);
    for ( *ptr++ = x, color[x] = GRAY, i = 0; i < (int)adj[D][x].size(); ++i ) {
        if ( color[y = adj[D][x][i]] == WHITE ) 
            topo(y,t);
        z[x] |= z[y];
    }
    if ( t == T ) *++top = x;
    color[x] = BLACK;
}

int main() {
	int i,j,k,l,t;
	char w[0x40];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;sscanf(FG,"%d",&n) && n > 0 && ++yes;) {
		for ( t = D; t <= T; ++t )
			for ( i = 0; i < n; adj[t][i++].clear() );
		for ( V = 0, m.clear(), k = 0; k < n; ++k ) 
			for ( sscanf(FG,"%s%n",w,&l), i = ins(w);(qtr += l) && 1==sscanf(qtr,"%s%n",w,&l);) {
				 j=ins(w), adj[T][i].push_back(j), adj[D][j].push_back(i);
				 assert( i != j );
			}
		assert( V <= n );
		for ( map<string,int>::iterator it = m.begin(); it != m.end(); ++it )
			word[it->second] = it->first;
		for ( top = st, FILL(color), i = 0; i < V; ++i )
			if ( color[i] == WHITE )
				dfs(i,T);
		for ( FILL(color), mark = 0; top > st; )
			if ( color[i = *top--] == WHITE )
				++mark, dfs(i,D);
		for ( i = 1; i <= mark; v[i++].clear() );
		for ( i = 0; i < V; ++i )
			v[scc[i]].push_back(i);
		for ( i = 1; i <= mark; ++i )
			card[i] = v[i].size();
		for ( k = 1; k <= mark; ++k )
			for ( l = 0; l < (int)v[k].size(); ++l )
				for ( i = v[k][l], t = 0; t < (int)adj[D][i].size(); g[k][scc[adj[D][i][t++]]] = yes );
		for ( t = D; t <= T; ++t )
			for ( i = 1; i <= mark; adj[t][i++].clear() );
		for ( FILL(in), i = 1; i <= mark; ++i )
			for ( j = 1; j <= mark; ++j )
				if ( i != j && g[i][j] == yes )
					adj[D][i].push_back(j), adj[T][j].push_back(i), ++in[j];
        for ( ptr = q, top = st, i = 1, FILL(color); i <= mark; ++i )
            if ( color[i] == WHITE )
                topo(i,T);
        for ( FILL(color), ptr = q; top > st; )
            if ( color[i = *top--] == WHITE )
                topo(i,D);
        for ( e.clear(), i = 1; i <= mark; ++i )
            for ( l = 0; (!in[i] || z[i]) && l < (int)v[i].size(); ++l )
                e.insert(word[v[i][l]]);
        printf("%lu\n",e.size()), k = 0;
        for ( set<string>::iterator it = e.begin(); it != e.end(); ++it )
            if ( ++k > 1 ) printf(" %s",(*it).c_str());
            else printf("%s",(*it).c_str());
        putchar('\n');
	}
	return 0;
}

