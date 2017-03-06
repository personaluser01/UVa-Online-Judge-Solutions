/*
 * 1161. Objective: Berlin
 * TOPIC: maxflow
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define N 0x100
#define enc(x,idx) ((x)|((idx)<<8))
#define MAXN (1<<21)
#define MAXE (1<<21)

map<string,int> m;
int latest_time,n,city_a,city_b,last[MAXN],to[MAXE],cap[MAXE],flow[MAXE],d[MAXN],_next[MAXE],E,V,
	visited[MAXN],yes,q[MAXN],*head,*tail,seen[MAXN],indeed,src,sink;
string name[0x400];

void add_arcs( int u, int v, int c ) {
	int i = E++, j = E++;
	to[i] = v, _next[i] = last[u], last[u] = i, cap[i] = c;
	to[j] = u, _next[j] = last[v], last[v] = j, cap[j] = 0;
	flow[i] = flow[j] = 0;
}

class Flight {
public:
	int x,y,cap;
	int start,end;
	Flight() {}
	Flight( int xx, int yy, int c, int s, int e ) {
		this->x = xx, this->y = yy, this->cap = c, this->start = s-30, this->end = e;
	}
};

bool operator < ( const Flight &a, const Flight &b ) {
	return a.start < b.start;
}

vector<Flight> lst[N];

int f( int x, int t ) {
	int low,high,mid;
	if ( !lst[x].size() ) return -1;
	if ( t <= lst[x][0].start ) return 0;
	if ( t > lst[x][lst[x].size()-1].start ) return -1;
	assert( lst[x][lst[x].size()-1].start >= t );
	assert( lst[x][0].start < t );
	for ( low=0, high=lst[x].size()-1; low+1 < high; )
		lst[x][mid=(low+high)/2].start<t?(low=mid):(high=mid);
	assert( lst[x][high].start >= t );
	assert( lst[x][low].start < t );
	return high;
}

int conv( char *s ) {
	int h[] = {0[s]-'0',1[s]-'0'},
		m[] = {2[s]-'0',3[s]-'0'};
	return (0[h]*10+1[h])*60+(0[m]*10+1[m]);
}

int ins( map<string,int> &m, char *s ) {
	string t = string(s);
	int k = m.size();
	if ( m.find(t) == m.end() ) {
		lst[m[t] = k++].clear();
		name[k-1] = t;
	}
	n = m.size();
	return m[t];
}

int bfs() {
	int x,y,i;
	for ( head=tail=q, d[*tail++ = sink] = 0, visited[sink] = ++yes; head < tail; )
		for ( i = last[x = *head++]; i >= 0; i = _next[i] ) 
			if ( cap[i^1] > flow[i^1] && (visited[y=to[i]]!=yes || d[y] > d[x]+1) ) 
				d[y]=d[x]+1, visited[*tail++=y]=yes;
	return visited[src] == yes;
}

int dfs( int x, int df ) {
	int dt,i,y;
	if ( x == sink ) return df;
	if ( seen[x] == indeed ) return 0;
	for ( seen[x] = indeed, i = last[x]; i >= 0; i = _next[i] )
		if ( visited[y = to[i]] == yes && cap[i] > flow[i] && d[y]+1 == d[x] )
			if ( dt = dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

int maxflow() {
	int T = 0,t;
	src = enc(city_a,0), sink = enc(city_b,f(city_b,latest_time));
	for(;bfs();)
		for (;++indeed&&(t=dfs(src,INF));T+=t);
	return T;
}

int main() {
	int i,j,k,l,t;
	char a[0x10],b[0x10],tt[0x10],ss[0x10];
#ifndef ONLINE_JUDGE
	freopen("1161.in","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n); printf("%d\n",maxflow()) ) {
		m.clear(), scanf("%s %s %s",a,b,tt), latest_time = conv(tt);
		city_a = ins(m,a), city_b = ins(m,b);
		for ( E = 0, t = 0; t < MAXN; last[t++] = -1 );
		for ( scanf("%d",&l), t = 0; t < l; ++t ) {
			scanf("%s %s %d %s %s",a,b,&k,ss,tt);
			i = ins(m,a), j = ins(m,b);
			lst[i].push_back(Flight(i,j,k,conv(ss),conv(tt)));
		}
		lst[city_b].push_back(Flight(city_b,city_b,INF,latest_time+30,INF));
		for ( i = 0; i < n; ++i ) 
			sort(lst[i].begin(),lst[i].end());
		for ( i = 0; i < n; ++i ) 
			for ( l = 0; l < (int)lst[i].size(); ++l ) {
				if ( lst[i][l].cap == INF || (t=f(lst[i][l].y,lst[i][l].end)) == -1 )
					continue ;
				//printf("These between %s, %s:  %d %d\n",name[i].c_str(),name[lst[i][l].y].c_str(),lst[i][l].end,lst[lst[i][l].y][t].start);
				add_arcs(enc(i,l),enc(lst[i][l].y,t),lst[i][l].cap);
			}
		for ( i = 0; i < n; ++i )
			for ( l = 0; l+1 < (int)lst[i].size(); ++l ) 
				add_arcs(enc(i,l),enc(i,l+1),INF);
	}
	return 0;
}

