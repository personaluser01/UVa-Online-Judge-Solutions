/*
 * 1717. Ship Traffix
 * TOPIC: worl finals, ad hoc, segments, intervals, union of intervals
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
#define N (1<<17)
#define oo (1<<29)
using namespace std;

set<pair<double,double> > s,t;
pair<double,double> p[N];
double st,nd,u,v,width;
int m,n;

pair<double,double> intersection( pair<double,double> &a, pair<double,double> &b ) {
	if ( a.first <= b.first && b.second <= a.second )
		return b;
	if ( b.first <= a.first && a.second <= b.second )
		return a;
	if ( a.first <= b.first && b.first <= a.second && a.second <= b.second )
		return make_pair(b.first,a.second);
	if ( b.first <= a.first && a.first <= b.second && b.second <= a.second )
		return make_pair(a.first,b.second);
	return make_pair(+oo,-oo);
}

int main() {
	int i,j,k;
	char tmp[0x10];
	double len,pos,left,right,cur;
	pair<double,double> best,phi,tau;
#ifndef ONLINE_JUDGE
	freopen("1717.txt","r",stdin);
#endif
	while ( 6 == scanf("%d %lf %lf %lf %lf %lf",&n,&width,&u,&v,&st,&nd) ) {
		for ( s.clear(), i = 0; i < n; ++i ) {
			for ( scanf("%s %d",tmp,&m), j = 0; j < m; ++j ) 
				scanf("%lf %lf",&len,&pos), p[j].first = pos, p[j].second = pos+(0[tmp]=='W'?1:-1)*len;
			if ( 0[tmp] == 'W' ) {
				for ( j = m-1; j >= 0; --j ) {
					if ( p[j].second < 0 ) break ;
					if ( p[j].first <= 0 && p[j].second >= 0 ) 
						s.insert(make_pair(0.00-(i+1)*width/v,p[j].second/u-i*width/v));
					else if ( p[j].first >= 0 ) {
						assert( p[j].second >= 0 );
						s.insert(make_pair(p[j].first/u-(i+1)*width/v,p[j].second/u-i*width/v));
					}
				}
			}
			else {
				for ( j = 0; j < m; ++j ) {
					if ( p[j].second > 0 ) break ;
					if ( p[j].second <= 0 && 0 <= p[j].first )
						s.insert(make_pair(0.00-(i+1)*width/v,-p[j].second/u-i*width/v));
					else if ( p[j].first <= 0 ) {
						assert( p[j].second <= p[j].first );
						s.insert(make_pair(-p[j].first/u-(i+1)*width/v,-p[j].second/u-i*width/v));
					}
				}
			}
		}
		t.clear(), left = +oo, right = -oo;
		for ( set<pair<double,double> > :: iterator it = s.begin(); it != s.end(); ++it ) {
			if ( right < it->first ) {
				if ( left < right )
					t.insert(make_pair(left,right));
				left = it->first, right = it->second;
				continue ;
			}
			if ( it->second > right ) right = it->second;
		}
		if ( left < right ) t.insert(make_pair(left,right));
		/*
		for ( set<pair<double,double> >::iterator jt = t.begin(); jt != t.end(); ++jt )
			printf("%.2lf %.2lf\n",jt->first,jt->second);
		*/
		m = 0;
		if ( t.empty() ) p[m++] = make_pair(-oo,+oo);
		else {
			set<pair<double,double> > :: iterator it = t.begin();
			p[m++] = make_pair(-oo,it->first), cur = it->second;
			for ( ;++it != t.end(); )
				p[m++] = make_pair(cur,it->first), cur = it->second;
			p[m++] = make_pair(cur,+oo);
		}
		for ( best = make_pair(+oo,-oo), tau = make_pair(st,nd), i = 0; i < m; ++i )
			if ( !(p[i].first > tau.second || tau.first > p[i].second) ) {
				phi = intersection(p[i],tau);
				if ( best.first == +oo || best.second-best.first < phi.second-phi.first )
					best = phi;
			}
		printf("%.10lf\n",-best.first+best.second);
	}
	return 0;
}

