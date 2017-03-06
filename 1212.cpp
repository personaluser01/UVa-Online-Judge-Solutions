/*
 * 1212. Duopoly
 * TOPIC: bipartite graphs, maxflow, mincut
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#define N (3001+3001+8)
enum { S=0, T=1 };
#define M (1<<21)
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define INF (1<<29)
#define oo (0xfffffffful)
using namespace std;

map<int,int> m;
set<int> s[2][N];
vector<int> v[2][N];
char buff[0x400],*ptr;
int n[2],V,pr[2][N],Total,src,sink,last[N],next[M],to[M],cap[M],flow[M],cost[M],
	visited[N],yes,seen[N],indeed,*tail,*head,q[N+N],E,channel[300005];
unsigned int d[N];
bool g[N/2][N/2];

bool f( const vector<int> &a, const set<int> &b ) {
	for ( int i = 0; i < (int)a.size(); ++i )
		if ( b.find(a[i]) != b.end() )
			return true;
	return false;
}

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

int dfs( int x, int df ) {
	int i,y,dt;
	if ( x == sink ) return df;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] ) {
			if ( d[y=to[i]] < +oo && visited[y] == indeed && d[x] == d[y]+1 ) {
				if ( (dt = dfs(y,min(df,cap[i]-flow[i]))) ) {
					flow[i] += dt, flow[i^1] -= dt;
					return dt;
				}
			}
		}
	return 0;
}

bool bfs() {
	int x,y,i;
	for ( visited[sink] = ++indeed, head=tail=q, d[*tail++=sink]=0; head<tail; )
		for ( i=last[x=*head++]; i>=0; i=next[i] )
			if ( flow[i^1]<cap[i^1] && (visited[y=to[i]]!=indeed || d[y]>d[x]+1) )
				d[*tail++=y]=d[x]+1, visited[y] = indeed;
	return visited[src]==indeed;
}

int fl( int cur, int cc ) {
	int i,y;
	if ( cur == sink ) return cc;
	if ( visited[cur] == indeed ) return 0;
	for ( visited[cur] = indeed, i = last[cur]; i >= 0; i = next[i] ) {
		if ( cap[i] <= flow[i] ) continue ;
		int t1 = fl(to[i],min(cc,cap[i]-flow[i]));
		if ( t1 == 0 ) continue ;
		flow[i] += t1, flow[i^1] -= t1;
		return t1;
	}
	return 0;
}

int mincut() {
	int i,cut = 0,k;
	for(;bfs();)for(;++yes&&(k=dfs(src,INF));cut+=k);
	//for(;++indeed && (k=fl(src,INF)); cut += k );
	return cut;
}

void CL( set<int> s[], int n ) { for ( int i = 0; i < n; ++i ) s[i].clear(); }
void VCL( vector<int> s[], int n ) { for ( int i = 0; i < n; ++i ) s[i].clear(); }
bool e[2][N/2];

int main() {
	int i,j,k,ts,cs = 0,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts); ts-- && FG; ) {
		printf("Case %d:\n",++cs);
		memset(channel,0,sizeof channel);
		for ( E = i = 0; i < N; ++i ) last[i] = -1;
		for ( Total = 0, t = S; t <= T; ++t ) {
			for(sscanf(FG,"%d",n+t),i=0;i<n[t];++i) {
				set<int> ch; ch.clear();
				for ( e[t][i] = false, FG, j = 0, sscanf(ptr,"%d%n",&pr[t][i],&j), Total += pr[t][i], ptr += j; 1 == sscanf(ptr,"%d%n",&k,&j); ptr += j ) {
					if ( !t ) channel[k] = i+1;
					else if ( channel[k] ) ch.insert(channel[k]-1);
					//if ( t ) s[t][i].insert(k);
					//else v[t][i].push_back(k);
				}
				if ( t )
					for ( set<int>::iterator it = ch.begin(); it != ch.end(); ++it )
						add_arcs(*it,i+n[S],INF);
			}
		}
		/*
		for ( i = 0; i < n[S]; ++i )
			for ( j = 0; j < n[T]; ++j )
				if ( g[i][j]=f(v[S][i],s[T][j]) )
					e[S][i] = e[T][j] = true;
			*/
		last[src = n[S]+n[T]] = -1, last[sink = src+1] = -1, V = sink+1;
		/*
		for ( i = 0; i < n[S]; ++i )
			for ( j = 0; j < n[T]; ++j )
				if ( g[i][j] )
					add_arcs(i,j+n[S],INF);
					*/
		for ( i = 0; i < n[S]; ++i )
		//	if ( e[S][i] )
				add_arcs(src,i,pr[S][i]);
		for ( j = 0; j < n[T]; ++j )
		//	if ( e[T][j] )
				add_arcs(j+n[S],sink,pr[T][j]);
		printf("%d\n",Total-mincut());
		if ( ts ) putchar('\n');
	}
	return 0;
}

