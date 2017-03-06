/*
 * 11378. Bey Battle
 * TOPIC: event-driven simulation, priority queue, sweepline, geometry, binary search
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
#include <queue>
typedef long long i64;
#define N (1 << 19)
#define x first
#define y second
#define L -1
#define R  1
#include <cmath>
#define tol 1e-9
#define oo (1 << 29)
#define TYPE_OF_EVENT first
#define IDX second
#define TIME first
#define T(r) (c[(r).IDX].TIME+d*(r).TYPE_OF_EVENT)

typedef pair<double,double> tp;
set<tp> s;
tp c[N],e[N];
int n;
double width,d;

struct event_comparator {
	bool operator () ( const pair<int,int> &a, const pair<int,int> &b ) {
		if ( T(a) == T(b) ) {
			if ( a.TYPE_OF_EVENT == b.TYPE_OF_EVENT )
				return false;
			return a.TYPE_OF_EVENT == L;
		}
		return T(a) >= T(b);
	}
};

priority_queue<pair<int,int>,vector<pair<int,int> >,event_comparator> q;

double length_of_union( const set<tp> &s ) {
	set<tp> :: iterator it;
	double len = 0,left,right;
	if ( !s.size() ) return len;
	it = s.begin(), left = it->x, right = it->y;
	for ( ;(++it) != s.end(); ) 
		if ( it->x > right ) len += (right-left), left = it->x, right = it->y;
		else if ( it->y > right ) right = it->y;
	return len+(right-left);
}

int main() {
	int i,j,k;
	double low,high,mid,prev_t,h;
	bool ok;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i ) scanf("%lf %lf",&c[i].x,&c[i].y);
		for ( low = 0, high = +oo; low+1 < high; ) {
			d = (width = mid = (low+high)/2)/2;
			for(s.clear();!q.empty();q.pop());
			for ( i = 0; i < n; ++i ) {
				e[i] = make_pair(c[i].y-d,c[i].y+d);
				q.push(make_pair(L,i));
			}
			for ( ok = true; !q.empty() && ok;) {
				pair<int,int> r = q.top();
				q.pop();
				if ( r.TYPE_OF_EVENT == L ) {
					s.insert(e[r.IDX]), q.push(make_pair(R,r.IDX));
					prev_t = T(r);
					continue ;
				}
				h = T(r)-prev_t;
				if ( h >= tol && length_of_union(s) < mid*s.size() ) 
					ok = false;
				else 
					s.erase(e[r.IDX]);
				prev_t = T(r);
			}
			if ( ok ) low = mid; else high = mid;
		}
		printf("%.lf\n",low+tol);
	}
	return 0;
}

