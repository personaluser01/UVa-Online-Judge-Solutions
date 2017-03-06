/*
 * 393. The Doors
 * TOPIC: dijkstra, sssp
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#define oo (1L << 29)
#define S(x) ((x)*(x))
using namespace std;
#define N 32
#define tol 1e-9

int n,V;
map<pair<int,pair<long double,long double> >,int> m;
map<int,pair<int,pair<long double,long double> > > im;
set<pair<long double,int> > s;
map<int,long double> dist;
pair<long double,long double> d[2][N];
long double x[N];

long double f( long double k, long double b, long double x ) { return k*x+b; }

bool passes_through( pair<long double,long double> a, pair<long double,long double> b, int i, int j, bool direct ) {
	long double slope = (b.second-a.second)/(b.first-a.first),
		   intercept = -(b.second-a.second)/(b.first-a.first)*a.first+a.second, level;
	if ( direct ) {
		for ( int k = i+1; k <= j-1; ++k ) {
			level = f(slope,intercept,x[k]);
			if ( d[0][k].first <= level && level <= d[0][k].second )
				continue ;
			if ( d[1][k].first <= level && level <= d[1][k].second )
				continue ;
			return false;
		}
	}
	else {
		for ( int k = i-1; k >= j+1; --k ) {
			level = f(slope,intercept,x[k]);
			if ( d[0][k].first <= level && level <= d[0][k].second )
				continue ;
			if ( d[1][k].first <= level && level <= d[1][k].second )
				continue ;
			return false;
		}
	}
	return true;
}

int main() {
	int i,j,k,l,t,xx,yy;
	long double w,dw,level;
	pair<int,pair<long double,long double> > r;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n) && n >= 0;) {
		for ( i = 1; i <= n; ++i ) 
			scanf("%Lf %Lf %Lf %Lf %Lf",x+i,&d[0][i].first,&d[0][i].second,&d[1][i].first,&d[1][i].second);
		d[0][n+1] = d[1][n+1] = make_pair(5,5), x[n+1] = 10;
		d[0][0] = d[1][0] = make_pair(5,5), x[0] = 0;
		V = 0, dist.clear(), s.clear(), m.clear(), im.clear();
		im[m[r=make_pair(0,make_pair(0,5))]=V++] = r;
		s.insert(make_pair(dist[0]=0,0));
		for ( w = +oo; !s.empty(); ) {
			set<pair<long double,int> >::iterator it = s.begin();
			i = im[xx = it->second].first+1;
			pair<int,pair<long double,long double> > e = im[xx];
			s.erase(*it);
			if ( i == n+2 ) {
				w = min(w,dist[xx]);
				continue ;
			}
			for ( level = e.second.second, j = 0; j <= 1; ++j )
			for ( k = i; k <= n+1; ++k ) {
				if ( passes_through(make_pair(x[i-1],level),make_pair(x[k],d[j][k].first),i-1,k,true) ) {
					r = make_pair(k,make_pair(x[k],d[j][k].first));
					if ( m.find(r) == m.end() ) im[m[r] = V++] = r;
					dw = sqrt(S(x[k]-x[i-1])+S(d[j][k].first-level));
					if ( dist.find(yy = m[r]) == dist.end() || dist[yy] > dist[xx]+dw )
						s.insert(make_pair(dist[yy] = dist[xx]+dw,yy));
				}
				if ( passes_through(make_pair(x[i-1],level),make_pair(x[k],d[j][k].second),i-1,k,true) ) {
					r = make_pair(k,make_pair(x[k],d[j][k].second));
					dw = sqrt(S(x[k]-x[i-1])+S(d[j][k].second-level));
					if ( m.find(r) == m.end() ) im[m[r] = V++] = r;
					if ( dist.find(yy = m[r]) == dist.end() || dist[yy] > dist[xx]+dw )
						s.insert(make_pair(dist[yy] = dist[xx]+dw,yy));
				}
			}
		}
		printf("%.2Lf\n",w+tol);
	}
    return 0;
}


