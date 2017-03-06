/*
 * 1202. Finding Nemo
 * TOPIC: dijkstra, coordinate compression
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>
#include <map>
#define N (1<<21)
#include <vector>
#define vc(x,y) (0<=(x)&&(x)<MX+10&&0<=(y)&&(y)<MY+10)
#include <queue>
using namespace std;
#define empty_interval(x,y) ((y)<=(x))
#define enc(x,y) ((x)|((y)<<10))
#define oo (1<<29)
#define tol 1e-9

int m,n,doors,walls,yes,d[N],MX,MY;
set<int> closed[N],opened[N];
vector<int> adj[N];
set<pair<int,int> > s;
queue<int> q;

int main() {
	int i,j,k,sx,sy,dir,len,u,v,dw,
		dx[] = {-1,0,1,0},
		dy[] = {0,1,0,-1},nx,ny,x,y;
	double lx,ly;
	while ( 2 == scanf("%d %d",&walls,&doors)&&(walls!=-1||doors!=-1) && ++yes ) {
		for( i = 0; i < N; ++i )
			opened[i].clear(), closed[i].clear(), adj[i].clear();
		MX = MY = -oo;
		while ( walls-- > 0 && 4 == scanf("%d %d %d %d",&sx,&sy,&dir,&len) ) {
			if ( dir == 1 ) {
				MY = max(MY,sy+len);
				for ( j = sy+1; j <= sy+len && j <= 1023; ++j ) {
					u=enc(sx,j), v=enc(sx+1,j);
					closed[u].insert(v);
					closed[v].insert(u);
				}
			}
			else {
				MX = max(MX,sx+len);
				for ( i = sx+1; i <= sx+len && i <= 1023; ++i ) {
					u=enc(i,sy), v=enc(i,sy+1);
					closed[u].insert(v);
					closed[v].insert(u);
				}
			}
		}
		MX = min(MX,1023);
		MY = min(MY,1023);
		while ( doors-- > 0 && scanf("%d %d %d",&sx,&sy,&dir) == 3 ) {
			if ( dir == 1 ) {
				for ( j = sy+1; j <= sy+1; ++j ) {
					u=enc(sx,j),v=enc(sx+1,j);
					opened[u].insert(v);
					opened[v].insert(u);
				}
			}
			else {
				for ( i = sx+1; i <= sx+1; ++i ) {
					u=enc(i,sy),v=enc(i,sy+1);
					opened[u].insert(v);
					opened[v].insert(u);
				}
			}
		}
		for ( u = 0; u < N; ++u ) {
			x = (u&1023), y = (u>>10), d[u] = +oo;
			for ( i = 0; i < 4; ++i ) {
				nx = x+dx[i], ny = y+dy[i], v = enc(nx,ny);
				if ( !vc(nx,ny) ) continue ;
				if ( !opened[u].size() && !closed[u].size() ) {
					adj[u].push_back(v);
					continue ;
				}
				if ( (opened[u].size()>0&&opened[u].find(v)!=opened[u].end()) || !closed[u].size() || closed[u].find(v)==closed[u].end() )
					adj[u].push_back(v);
			}
		}
		scanf("%lf %lf",&lx,&ly), sx = (int)ceil(lx+tol), sy = (int)ceil(ly+tol);
		if ( sx >= MX+10 || sy >= MY+10 ) { puts("0"); continue ; }
		/*
		for ( d[0] = 0, q.push(0); !q.empty(); ) {
			u = q.front(), q.pop(), x = (u&1023), y = u>>10;
			for ( i = 0; i < (int)adj[u].size(); ++i ) {
				v = adj[u][i];
				if ( opened[u].size() > 0 && opened[u].find(v) != opened[u].end() ) 
					dw = 1;
				else dw = 0;
				if ( d[v]>d[u]+dw )
					d[v]=d[u]+dw,q.push(v);
			}
		}
		*/
		for ( s.clear(), s.insert(make_pair(d[enc(0,0)]=0,enc(0,0))); !s.empty() && d[enc(sx,sy)] == +oo; ) {
			set<pair<int,int> >::iterator it = s.begin();
			u = it->second, x = (u&1023), y = u>>10;
			s.erase(*it);
			// printf("%d %d\n",x,y);
			for ( i = 0; i < (int)adj[u].size(); ++i ) {
				v = adj[u][i];
				if ( opened[u].size() > 0 && opened[u].find(v) != opened[u].end() ) 
					dw = 1;
				else dw = 0;
				if ( d[v]>d[u]+dw )
					s.insert(make_pair(d[v]=d[u]+dw,v));
			}
		}
		printf("%d\n",d[u=enc(sx,sy)]<+oo?d[u]:-1);
	}
	return 0;
}

