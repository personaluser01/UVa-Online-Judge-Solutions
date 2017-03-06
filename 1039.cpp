/*
 * 1039. Simplified GSM Network
 * TOPIC: dijkstra
 * status: Accepted
 */
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#define N BIT(13)
#include <cmath>
#define tol 1e-9
#define BIT(k)  (1ULL<<(k))
#include <cfloat>
#define MASK(k) (BIT(k)-1ULL)
#define INF 0xfffffffful
#include <vector>
#define oo (DBL_MAX-0x400)
#define Q BIT(12)
#define L(u) ((u)&((~(u))+1ULL))
#define A(x) ((x)*(x))
typedef unsigned long long u64;
using namespace std;

int n,towers,roads,cities,qr,V;
char which[BIT(21)];
u64 nearest[N];
pair<double,double> c[N],pt[N];
double dist[N];
vector<int> adj[N];
set<pair<unsigned int,pair<int,int> > > s;
unsigned int d[N][N];
set<double> lst[0x40][0x40];
map<pair<double,double>,int> m;

typedef struct { pair<double,double> r; int idx; } cell;

double operator,( const pair<double,double> &a, const pair<double,double> &b ) {
	return a.first*b.first+a.second*b.second;
}

pair<double,double> operator * ( const double t, const pair<double,double> &a ) {
	return make_pair(a.first*t,a.second*t);
}

pair<double,double> operator - ( const pair<double,double> &a, const pair<double,double> &b ) {
	return make_pair(a.first-b.first,a.second-b.second);
}

pair<double,double> operator + ( const pair<double,double> &a, const pair<double,double> &b ) {
	return make_pair(a.first+b.first,a.second+b.second);
}

double f( const pair<double,double> &p, const pair<double,double> &q, const pair<double,double> &r, double t ) {
	pair<double,double> u = p+t*(q-p)-r;
	return (u,u);
}

double find_t( const pair<double,double> &p, const pair<double,double> &q, const pair<double,double> &r ) {
	double a,b,na,nb;
	for ( a = 0.00, b = 1.00; fabs(b-a) >= tol; ) {
		na = (2*a+b)/3, nb = (a+2*b)/3;
		if ( f(p,q,r,na) > f(p,q,r,nb) )
			a = na;
		else b = nb;
	}
	return a;
}

int who( u64 u ) {
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

int main() {
	int i,j,k,x,y,T,cs = 0;;
	double w;
	unsigned int u,v,D;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < 21; which[BIT(k)] = k, ++k );
	for (;4==scanf("%d %d %d %d",&towers,&cities,&roads,&qr)&&(towers||cities||roads||qr);) {
		for ( i = 0; i < cities; ++i )
			for ( j = 0; j < cities; ++j )
				lst[i][j].clear();
		printf("Case %d:\n",++cs);
		for ( i = 0; i < N; adj[i].clear(), dist[i] = +oo, nearest[i] = 0, ++i );
		for ( i = 0; i < towers+cities; ++i ) 
			scanf("%lf %lf",&c[i].first,&c[i].second);
		for ( m.clear(), i = 0; i < cities; ++i ) pt[m[c[towers+i]] = i] = c[towers+i];
		assert( (V=m.size()) == cities );
		for ( i = 0; i < cities; ++i )
			for ( j = 0; j < towers; ++j )
				if ( dist[i]>(w=A(c[i+towers].first-c[j].first)+A(c[i+towers].second-c[j].second)) ) 
					dist[i] = w, nearest[i] = BIT(j);
				else if ( fabs(dist[i]-w) < tol )
						nearest[i] |= BIT(j);
		for(n=V,k=0;k<roads;++k){
			scanf("%d %d",&i,&j),--i,--j;
			// adj[i].push_back(j), adj[j].push_back(i);
			for ( int l = 0; l < towers; ++l ) {
				double t = find_t(c[i+towers],c[j+towers],c[l]);
				pair<double,double> r = c[i+towers]+t*(c[j+towers]-c[i+towers]);
				if ( m.find(r)==m.end() )
					pt[m[r]=V++] = r;
				lst[i][j].insert(t);
				// if ( m[r] < n ) continue ;
				if ( dist[m[r]]>(w=((c[l]-r,c[l]-r))) )
					dist[m[r]]=w,nearest[m[r]]=BIT(l);
				else if ( fabs(dist[m[r]]-w) < tol )
					nearest[m[r]]|=BIT(l);
			}
		}
		for ( i = 0; i < V; ++i )
			for ( int l = 0; l < towers; ++l )
				if ( dist[i] > (w=(pt[i]-c[l],pt[i]-c[l])) )
					dist[i] = w, nearest[i] = BIT(l);
				else if ( fabs(dist[i]-w) < tol )
					dist[i] = w, nearest[i] |= BIT(l);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) {
				if ( !lst[i][j].size() ) continue ;
				set<double>::iterator it = lst[i][j].begin();
				pair<double,double> p,q,r;
				p = c[i+towers];
				assert( m.find(p) != m.end() );
				for ( it = lst[i][j].begin(); it != lst[i][j].end(); ++it ) {
					q = c[i+towers]+(*it)*(c[j+towers]-c[i+towers]);
					assert( m.find(q) != m.end() );
					adj[m[p]].push_back(m[q]);
					adj[m[q]].push_back(m[p]);
					p = q;
				}
				adj[m[p]].push_back(m[c[j+towers]]);
				adj[m[c[j+towers]]].push_back(m[p]);
			}
		for(;qr--&&2==scanf("%d %d",&i,&j);){
			for ( --i, --j, x = 0; x < V; ++x )
				for ( v=nearest[x]; v; v&=~L(v) )
					d[x][who(L(v))]=INF;
			for ( s.clear(),x=i,v=nearest[x]; v; v&=~L(v) )
				i=who(L(v)),s.insert(make_pair(d[x][i]=0,make_pair(x,i)));
			for ( T = j, D = INF; !s.empty(); ) {
				set<pair<unsigned int,pair<int,int> > > :: iterator it = s.begin();
				x = it->second.first, i = it->second.second, s.erase(*it);
				if ( x == T && D > d[x][i] ) D = d[x][i];
				// printf("This %d\n",x);
				if ( d[x][i] >= D ) continue ;
				for ( int l = 0; l < (int)adj[x].size(); ++l )
					for ( v=nearest[y=adj[x][l]]; v; v &= ~L(v) )
						if ( y != x && d[y][j=who(L(v))]>d[x][i]+(i==(j=who(L(v)))?0:1) )
							d[y][j]=d[x][i]+(i==j?0:1),s.insert(make_pair(d[y][j],make_pair(y,j)));
			}
			if ( D == INF ) puts("Impossible");
			else printf("%u\n",D);
		}
	} 
	return 0;
}

