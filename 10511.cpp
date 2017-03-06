/*
 * 10511. Councilling
 * status: Accepted
 */
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <queue>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
using namespace std;
#define N 0x400
#define Q (10*N)
#define oo 0xfffffffful

queue<int> q;

int empty( char *ptr ) {
	for ( ;*ptr && *ptr != '\n' && isspace(*ptr); ++ptr );
	return *ptr == '\0'||*ptr == '\n';
}

typedef struct edge { struct edge *back_edge; int x,y,capacity,flow; } edge;
char buff[0x400],*ptr,
	 nm[N][0x100],
	 club[N][0x100],
	 party[N][0x100];
int m,n,E,V,src,sink,p[Q],P,u[Q],vin[Q],vout[Q],aid[Q];
map<string,int> mp,mc;
vector<int> adj[Q],lst[N];
edge e[Q],*ee[Q];
unsigned int d[Q];

void add_arcs( int x, int y, int c ) {
	int i,j;
	e[i = E].x = x, e[E].y = y, e[E].capacity = c, e[E].flow = 0, ++E;
	e[j = E].y = x, e[E].x = y, e[E].capacity = 0, e[E].flow = 0, ++E;
	e[i].back_edge = e+j, e[j].back_edge = e+i;
}

int retrace( int x, int df ) {
	if ( x != src )
		return retrace(p[x],min(df,ee[x]->capacity-ee[x]->flow));
	return df;
}

void update( int x, int df ) {
	if ( x != src )
		ee[x]->flow += df, ee[x]->back_edge->flow -= df, update(p[x],df);
}

int bfs() {
	int i,j,k,x,y;
	for ( x = 0; x < V; ++x ) d[x] = +oo;
	for(d[src]=0,q.push(src);!q.empty()&&d[sink]==+oo;)
		for ( x = q.front(), q.pop(), i = 0; i < (int)adj[x].size(); ++i )
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( d[y = e[j].y] > d[x]+1 )
					d[y]=d[x]+1,q.push(y),p[y]=x,ee[y]=e+j;
	while ( !q.empty() ) q.pop();
	return d[sink] < +oo;
}

int main() {
	int i,j,k,ts,l,t;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts), FG; ts--; ) {
		mp.clear(), mc.clear(), V = E = 0;
		for ( P = m = n = 0; FG && !empty(ptr); ++n ) {
			lst[n].clear(), k = 0, sscanf(ptr+k,"%s%n",nm[n],&l), k += l;
			sscanf(ptr+k,"%s%n",party[n],&l), k += l;
			string t = string(party[n]);
			if ( mp.find(t) == mp.end() )
				mp[t]=P++;
			for ( j = 0; 1 == sscanf(ptr+k,"%s%n",tmp,&l); k += l, ++j ) {
				string s = string(tmp);
				if ( mc.find(s) == mc.end() )
					mc[s] = m++, strcpy(club[mc[s]],tmp);
				lst[n].push_back(mc[s]);
			}
		}
		l = m/2-1+(m&1), src = 0, V = P+1;
		for ( j = 0; j < n; ++j ) aid[u[j] = V++] = j;
		for ( i = 0; i < P; ++i ) {
			add_arcs(src,i+1,l);
			for ( j = 0; j < n; ++j ) {
				string s(party[j]);
				if ( mp[s] == i )
					add_arcs(i+1,u[j],1);
			}
		}
		for ( i = 0; i < m; ++i ) {
			vin[i] = V++, vout[i] = V++;
			add_arcs(vin[i],vout[i],1);
		}
		for ( i = 0; i < n; ++i )
			for ( l = 0; l < (int)lst[i].size(); ++l )
				add_arcs(u[i],vin[lst[i][l]],1);
		sink = V++;
		for ( i = 0; i < m; ++i )
			add_arcs(vout[i],sink,1);
		for ( i = 0; i < V; adj[i++].clear() );
		for ( i = 0; i < E; ++i )
			adj[e[i].x].push_back(i);
		for(;bfs();update(sink,retrace(sink,(1<<29))) );
		for ( k = 0, i = 0; i < E; ++i )
			if ( e[i].y == sink )
				k += e[i].flow;
		if ( k != m||!k ) {
			puts("Impossible.");
			goto st;
			continue ;
		}
		for ( i = 0; i < m; ++i ) {
			for ( j = 0; j < E; ++j )
				if ( e[j].flow > 0 && e[j].y == vin[i] ) {
					printf("%s %s\n",nm[aid[e[j].x]],club[i]);
					goto nx;
				}
			assert( 0 );
			nx: continue ;
		}
		st: if ( ts ) putchar('\n');
	}
	return 0;
}
