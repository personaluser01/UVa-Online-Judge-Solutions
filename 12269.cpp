/*
 * 12269. Lawn Mower
 * TOPIC: union of intervals, sorting
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
#include <cfloat>
#define tol 1e-9
#define oo (DBL_MAX-0x400)
typedef long long i64;
using namespace std;

i64 m,n;
double w,t;
vector<pair<double,double> > a,b;

bool contains_gap( const vector<pair<double,double> > &v, const double x, const double y ) {
	double left,right;
	int i,j,k;
	if ( !v.size() ) return false;
	left = v[0].first, right = v[0].second;
	for ( i = 1; i < (int)v.size(); ++i ) {
		if ( v[i].first > right )  {
			return !(left <= x && y <= right);
		}
		assert( v[i].first >= left );
		assert( v[i].first <= right );
		if ( v[i].second > right ) right = v[i].second;
	}
	return !(left <= x && y <= right);
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	while ( 3 == scanf("%lld %lld %lf",&m,&n,&w) && (m||n||w>tol) ) {
		for ( a.clear(), b.clear(), i = 0; i < m; ++i )
			scanf("%lf",&t), a.push_back(make_pair(t-w/2,t+w/2));
		for ( i = 0; i < n; ++i )
			scanf("%lf",&t), b.push_back(make_pair(t-w/2,t+w/2));
		sort(a.begin(),a.end()), sort(b.begin(),b.end());
		printf("%s\n",contains_gap(a,0,75)||contains_gap(b,0,100)?"NO":"YES");
	}
    return 0;
}

