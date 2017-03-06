/*
 * 1109. Mummy Madness
 * TOPIC: sweepline
 * status:
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <vector>
#define N (1<<21)
#define B 1000010
using namespace std;
typedef long long i64;

struct cell {
 	i64 x,y,h;
	bool is_opening;
	struct cell *sib;
	cell() {x=y=h=0,is_opening=false;};
	cell( i64 p, i64 q, i64 r, bool f ) { x=p,y=q,h=r,is_opening=f; };
};

bool is_less( const cell *a, const cell *b ) {
	if ( a->x < b->x ) return true ;
	if ( a->x > b->x ) return false ;
	if ( a->is_opening && !b->is_opening ) return false ;
	if ( !a->is_opening && b->is_opening ) return true ;
	return false ;
};

struct comp {
	bool operator() ( const cell *a, const cell *b ) {
		if ( a->x < b->x ) return false;
		if ( a->x > b->x ) return true ;
		if ( a->is_opening && !b->is_opening )
			return false;
		if ( !a->is_opening && b->is_opening )
			return true;
		return false;
	};
};

bool operator < ( const cell &a, const cell &b ) {
	if ( a.y == b.y ) {
		if ( a.h == b.h ) 
			return a.x < b.x;
		return a.h < b.h;
	}
	return a.y < b.y;
};

bool operator == ( const cell &a, const cell &b ) {
	return a.y==b.y && a.h==b.h && a.x==b.x;
};

cell *heap[N];
i64 cnt,mid;

void push( cell *c ) {
 	i64 i,j;
	for ( heap[j = cnt++] = c; j && is_less(heap[j],heap[i=(j-1)>>1]); ) {
		cell *t = heap[i];
		heap[i] = heap[j], heap[j] = t, j = i;
	};
};
cell *pop() {
	cell *x = *heap;
 	i64 i,j;
	for ( heap[0]=heap[--cnt], j=0; (i=j,j<<=1,++j)<cnt; ) {
		if ( j < cnt-1 && is_less(heap[j+1],heap[j]) ) ++j;
		if ( !is_less(heap[j],heap[i]) ) break ;
		cell *t = heap[i];
		heap[i] = heap[j], heap[j] = t;
	};
	return x;
};

i64 m,n,cx[N],cy[N];
cell c[N];
map<pair<i64,i64>,int> s;
bool needs_recalc;

struct pr {
 	i64 x,y;
	pr(){};
};

bool operator < ( const pr &a, const pr &b ) {
	if ( a.x == b.x )
		return a.y<b.y;
	return a.x<b.x;
};

pr w[N];

i64 segment_union( map<pair<i64,i64>,int> &s ) {
 	i64 left=-B-B,right = -B-B,len = 0,i,j,k;
	static i64 saved_len = 0;
	if ( !s.size() ) return 0;
	if ( !needs_recalc )
		return saved_len;
	m = 0;
	for ( map<pair<i64,i64>,int>::iterator it = s.begin(); it != s.end(); ++it )
		w[m].x = it->first.first, w[m++].y = it->first.second;
	for ( i = 0; i < m; ++i ) {
		if ( w[i].x > right ) {
			len += right-left;
			left = w[i].x, right = w[i].y;
			continue ;
		}
		if ( w[i].y > right ) {
			right = w[i].y;
		}
	}
	if ( left < right )
		len += right-left;
	return saved_len = len;
};

i64 area() {
 	i64 S = 0, prev = -B-B-B;
	cell *r;
	assert( s.empty() );
	for (;cnt;prev=r->x) {
		r = pop();
		if ( prev >= r->x ) 
		assert( prev <= r->x );
		if ( prev>-B-B-B && prev<r->x )
			S+=(r->x-prev)*segment_union(s);
		if ( r->is_opening ) {
			push(r->sib);
			pair<i64,i64> e = make_pair(r->y,r->y+r->h);
			if ( s.count(e) ) ++s[e];
			else s[e] = 1;
			continue ;
		}
		pair<i64,i64> e = make_pair(r->y,r->y+r->h);
		assert( s.count(e) );
		if ( !--s[e] )
			s.erase(e), needs_recalc = true ;
	};
	return S;
};

int main() {
 i64 i,j,k,cs = 0,good,bad,area0,area1;
#ifndef ONLINE_JUDGE
	freopen("1109.in","r",stdin);
#endif
	for (;1==scanf("%lld",&n)&&n>=0&&printf("Case %lld: ",++cs);) {
		for ( i = 0; i < n; ++i ) 
			scanf("%lld %lld",cx+i,cy+i);
		for ( good=0, bad=B+0x10; good+1!=bad; ) {
			mid=(good+bad)/2, needs_recalc = true ;
			for ( cnt = 0, j = 0, i = 0; i < n; ++i, j += 2 ) {
				c[j].x = cx[i]-mid, c[j].y = cy[i]-mid, c[j].h = 2*mid+1, c[j].is_opening = true ;
				c[j^1].x = cx[i]+mid+1, c[j^1].y = cy[i]-mid, c[j^1].h = 2*mid+1, c[j^1].is_opening = false ;
				c[j].sib = &c[j^1], c[j^1].sib = &c[j];
				push(c+j);
			};
			area0 = area();
			for ( cnt = 0, j = 0, i = 0; i < n; ++i, j += 2 ) {
				c[j].x = cx[i]-mid, c[j].y = cy[i]-mid, c[j].h = 2*mid+1, c[j].is_opening = true ;
				c[j^1].x = cx[i]+mid+1, c[j^1].y = cy[i]-mid, c[j^1].h = 2*mid+1, c[j^1].is_opening = false ;
				c[j].sib = &c[j^1], c[j^1].sib = &c[j];
				push(c+j);
			};
			c[j].x = -mid, c[j].y = -mid, c[j].h = 2*mid+1, c[j].is_opening = true ;
			c[j^1].x = mid+1, c[j^1].y = -mid, c[j^1].h = 2*mid+1, c[j^1].is_opening = false ;
			c[j].sib = &c[j^1], c[j^1].sib = &c[j];
			push(c+j);
			if ( area0 == (area1=area()) ) bad = mid;
			else good = mid;
		}
		if ( good >= B+2 ) puts("never");
		else printf("%lld\n",bad);
		/*
		for ( i = 0; i < n; ++i ) {
			printf("%lld %lld -- %lld %lld\n",cx[i]-bad,cy[i]-bad,cx[i]+bad+1,cy[i]+bad+1);
		}
		printf("Me: %lld %lld -- %lld %lld\n",-bad,-bad,bad+1,bad+1);
		*/
	};
	return 0;
};

