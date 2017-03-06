/*
 * 11072. Points
 * TOPIC: computational geometry, convex hull, binary search, polar angle
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#define N (1<<17)
#define tol 1e-9
#define pi (2*acos(0.00))
typedef long long i64;
using namespace std;

inline i64 S( i64 x ) { return x*x; }

struct vec {
	i64 x,y;
	vec( i64 p=0, i64 q=0 ) { this->x = p, this->y = q; }
	long double Len() const { return sqrt(this->x*this->x+this->y*this->y); }
};

i64 operator , ( const vec &a, const vec &b ) { return a.x*b.x+a.y*b.y; }
vec operator + ( const vec &a, const vec &b ) { vec v(a.x+b.x,a.y+b.y); return v; }
vec operator - ( const vec &a, const vec &b ) { vec v(a.x-b.x,a.y-b.y); return v; }

i64 vector_product( const vec &a, const vec &b ) { return a.x*b.y-a.y*b.x; }

i64 vector_product( const vec &a, const vec &b, const vec &c ) { return vector_product(b-a,c-a); }

long double operator ^ ( const vec &a, const vec &b ) {
	long double si = vector_product(a,b), co = (a,b),
		   		A = a.Len(), B = b.Len();
	si = si/A/B, co = co/A/B;
	if ( fabs(co+1) < tol )
		return -pi;
	if ( fabs(co-1) < tol )
		return 0;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	return -pi+acos(-co);
}

bool operator < ( const vec &a, const vec &b ) {
	if ( a.x == b.x ) return a.y < b.y;
	return a.x < b.x;
}

i64 ccw( const vec &a, const vec &b, const vec &c ) {
	i64 w = vector_product(b-a,c-b);
	if ( w > 0 ) return  1;
	if ( w < 0 ) return -1;
	return 0;
}

struct foo { vec v; long double ang; i64 dist; };

bool operator < ( const foo &a, const foo &b ) {
	if ( fabs(a.ang-b.ang) < tol )
		return a.dist < b.dist;
	return a.ang < b.ang;
}

bool operator == ( const vec &a, const vec &b ) { return a.x == b.x && a.y == b.y; }

int m,n,top;
vec v[N],pole,one = vec(1,0),origin = vec(0,0);
foo a[N],b[N],st[N],e[N];
set<vec> s;

inline bool on_segment( const vec &p, const vec &a, const vec &b ) 
{ return p==a || p==b || (p-a,p-b)<0 && vector_product(p,a,b)==0; }

bool inside_triangle( const vec &p, const vec &a, const vec &b, const vec &c ) {
	if ( on_segment(p,a,b) || on_segment(p,b,c) || on_segment(p,c,a) )
		return true ;
	i64 aa = vector_product(p,b,c), bb = vector_product(p,c,a), cc = vector_product(p,a,b);
	/*long double alpha = (b-p)^(c-p), beta = (c-p)^(a-p), gamma = (a-p)^(b-p), w = alpha+beta+gamma;
	return fabs(fabs(w)-2*pi) < tol;*/
	return aa>0&&bb>0&&cc>0 || aa<0&&bb<0&&cc<0;
}

bool f( const vec &v ) {
	int i,j,k,low,high,mid;
	if ( v == origin )
		return  true ;
	if ( v == e[1].v ) return true ;
	if ( vector_product(v,e[1].v) == 0 ) {
label1:
		if ( (v,e[1].v) < 0 ) return false ;
		return (v,v) <= (e[1].v,e[1].v);
	}
	if ( v == e[m-1].v ) return true ;
	if ( vector_product(v,e[m-1].v) == 0 ) {
label2:
		if ( (v,e[m-1].v) < 0 ) return false ;
		return (v,v) <= (e[m-1].v,e[m-1].v);
	}
	long double ag = one^v;
	if ( fabs(ag-e[1].ang)<tol ) goto label1;
	if ( ag < e[1].ang )   return false ;
	assert( ag >= e[1].ang );
	if ( fabs(ag-e[m-1].ang) < tol ) goto label2;
	if ( ag > e[m-1].ang ) return false; 
	assert( ag <= e[m-1].ang );
	for(low=1,high=m-1;low+1<high;e[mid=(low+high)/2].ang<ag?(low=mid):(high=mid));
	assert( low+1 == high );
	assert( e[low].ang < ag );
	assert( e[high].ang >= ag );
	if ( vector_product(v,e[high].v) == 0 ) {
		if ( (v,e[high].v) < 0 )
			return false ;
		return (v,v) <= (e[high].v,e[high].v);
	}
	if ( vector_product(v,e[low].v) == 0 ) {
		if ( (v,e[low].v) < 0 )
			return false ;
		return (v,v) <= (e[low].v,e[low].v);
	}
	if ( fabs(e[high].ang-ag) < tol )
		return (v,v) <= (e[high].v,e[high].v);
	return inside_triangle(v,e[0].v,e[low].v,e[high].v);
}


int main() {
	int i,j,k;
	vec u;
	set<vec> :: iterator it;
	for (;1==scanf("%d",&n) && n > 0;) {
		for ( s.clear(), i = 0; i < n; scanf("%lld %lld",&v[i].x,&v[i].y), s.insert(v[i]), ++i );
		for ( n = 0, it = s.begin(); it != s.end(); v[n++] = *it++ );
		for ( sort(v,v+n), a[0].v=origin, pole=v[0], i = 1; i < n; ++i ) 
			a[i].ang = (one^(a[i].v=v[i]-pole)), a[i].dist = (a[i].v,a[i].v);
		for ( k = 0, b[k++] = a[0], sort(a+1,a+n), i = 1; i < n; b[k++] = a[j-1], i = j ) 
			for ( j = i+1; j < n && 0 == vector_product(a[i].v,a[j].v); ++j );
		for ( i = 0; i < k; a[i] = b[i], ++i );
		/*
		for ( i = 0; i < k; ++i )
			printf("%lld %lld %.3Lf\n",a[i].v.x+pole.x,a[i].v.y+pole.y,a[i].ang);
			*/
		assert( k >= 3 );
		top = 0, st[++top] = a[0], st[++top] = a[1], st[++top] = a[2];
		for ( n = k, i = 3; i < n; st[++top] = a[i++] ) 
			for(;top >= 2 && ccw(st[top-1].v,st[top].v,a[i].v) <= 0; --top );
		/*
		for(a[n]=a[0],sort(a+1,a+n),top=0,st[++top]=a[i=0],st[++top]=a[++i];++i<=n;) {
			// for (;top>=2 && !ccw(st[top-1].v,st[top].v,a[i].v);--top);
			for (;top>=2 && !ccw(st[top-1].v,st[top].v,a[i].v);--top);
			if ( top >= 2 && vector_product(st[top-1].v,st[top].v,a[i].v) == 0 )
				if ( st[top].v.distTo(st[top-1].v) >= a[i].v.distTo(st[top-1].v) ) 
					continue ;
			st[++top] = a[i];
		}
		*/
		for ( m = 0, i = 1; i <= top; e[m++] = st[i++] );
		assert( m >= 3 );
#ifndef ONLINE_JUDGE
		for ( i = 0; i < m && 0; ++i )
			printf("%lld %lld\n",e[i].v.x+pole.x,e[i].v.y+pole.y);
#endif
		for ( scanf("%d",&k); k-- && 2 == scanf("%lld %lld",&u.x,&u.y); puts(f(u-pole)?"inside":"outside") );
	}
	return 0;
}

