/*
 * 13024. Saint John Festival
 * TOPIC: convex hull, ccw, graham scan, binary search
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#define tol 1e-13
#define N (1<<16)
#define DIM 3
#define S(x) ((x)*(x))
typedef long long i64;
using namespace std;

const double pi = 2*acos(0.00);

struct cell {
	i64 x[DIM];
	cell() { 0[x]=1[x]=2[x]=0; };
	cell( i64 a, i64 b ) { 0[x]=a,1[x]=b,2[x]=0; };
	cell( i64 a, i64 b, i64 c ) { 0[x]=a,1[x]=b,2[x]=c; };
	i64 operator [] ( int i ) const { return x[i]; };
	void read() { 
		2[x] = 0;
		assert( 2 == scanf("%lld %lld",x,x+1) );
	};
	i64 dist_to( cell &b ) { return S(0[x]-b[0])+S(1[x]-b[1]); };
	double getlen() const {
		double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( a[i]!=b[i] )
			return a[i]<b[i];
	return false;
};

bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); }

cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1],a[2]+b[2]); }
cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1],a[2]-b[2]); }
i64 operator , ( const cell &a, const cell &b ) {
	i64 s = 0;
	for (int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
};

cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k=((j=(i+1)%DIM)+1)%DIM, r.x[i]=a[j]*b[k]-a[k]*b[j];
	return r;
}

cell operator * ( const cell &a, const i64 &t ) { return cell(a[0]*t,a[1]*t,a[2]*t); }
i64 cross( const cell &a, const cell &b ) { return a[0]*b[1]-a[1]*b[0]; };

bool ccw( cell &a, cell &b, cell &c ) {
	if ( a == b || b == c || c == a )
		return false ;
	cell p = b-a, q = c-a;
	i64 si = cross(p,q), co = (p,q);
	return si>0 || si==0 && co>=0 && (p,p)>(q,q);
};

cell c[N],a[N],pole,ZERO,unit(1,0),h[N];
int m,n,next[N],len,q[N],*head,*tail,st[N],*top;

bool on_segment( cell &a, cell &b, cell &p ) {
	if ( a == p || b == p )
		return true ;
	cell pa = p-a, pb = p-b;
	return cross(pa,pb) == 0 && (pa,pb) < 0;
};

bool inside_triangle( cell &a, cell &b, cell &c, cell &p ) {
	if ( on_segment(a,b,p) || on_segment(b,c,p) || on_segment(c,a,p) )
		return true ;
	cell pa = p-a, pb = p-b, pc = p-c, ba = b-a, ca = c-a;
	i64 sab = cross(pa,pb), sbc = cross(pb,pc), sca = cross(pc,pa), s = cross(ba,ca);
	return (sab > 0 && sbc > 0 && sca > 0 || sab < 0 && sbc < 0 && sca < 0) && labs(sab+sbc+sca) == labs(s);
};

bool inside( cell &a ) {
	int low,high,mid;
	if ( cross(a,h[1]) > 0 ) return false ;
	if ( cross(h[len-1],a) > 0 ) return false ;
	if ( cross(a,h[1]) == 0 )
		return on_segment(h[0],h[1],a);
	if ( cross(h[len-1],a) == 0 )
		return on_segment(h[0],h[len-1],a);
	assert( cross(a,h[1]) <= 0 );
	assert( cross(a,h[len-1]) > 0 );
	for ( low = 1, high = len-1; low+1 < high; ) {
		mid = (low+high)/2;
		if ( cross(a,h[mid]) <= 0 ) low = mid;
		else high = mid;
	}
	return inside_triangle(h[0],h[low],h[low+1],a);
};

double operator ^ ( const cell &a, const cell &b ) {
	double A = a.getlen(), B = b.getlen(),
		   si = cross(a,b)/A/B, co = (a,b)/A/B;
	if ( fabs(co-1.00) < tol )
		return 0.00;
	if ( fabs(co+1.00) < tol )
		return -pi;
	if ( co >= 0 & si >= 0 )
		return acos(co);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	return -pi+acos(-co);
};

struct foo {
	cell c;
	double phi;
	foo( cell C, double t ) { c = C, phi = t; };
	foo() {};
};

bool operator < ( const foo &a, const foo &b ) {
	if ( fabs(a.phi-b.phi) < tol )
		return (a.c,a.c) > (b.c,b.c);
	return a.phi < b.phi;
};

foo e[N];
cell u[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("13024.in","r",stdin);
#endif
	for (;1==scanf("%d",&n)&&n>0; printf("%d\n",k) ) {
		for ( i = 0; i < n; c[i++].read() );
		for ( scanf("%d",&m), j = 0; j < m; a[j++].read() );
		sort(c,c+n), pole = c[0];
		for ( i = 0; i < n; c[i] = c[i]-pole, ++i );
		for ( j = 0; j < m; a[j] = a[j]-pole, ++j );
		assert( c[0] == ZERO );
		for ( e[0].c = c[0], j = 1, i = 1; i < n; ++i,++j ) 
			e[j].phi = (unit^(e[j].c=c[i]));
		for ( k = 0, u[k++] = e[0].c, sort(e+1,e+n), i = 1; i < n; u[k++] = e[i].c, i = j ) 
			for ( j = i+1; j < n && fabs(e[i].phi-e[j].phi) < tol; ++j );
		for ( top = st, *++top = 0, *++top = 1, i = 2; i < k; *++top = i++ ) 
			for (;top-st >= 2 && !ccw(u[*(top-1)],u[*top],u[i]); --top );
		for ( len = 0, i = 1; i <= top-st; h[len++] = u[st[i++]] );
		/*
		for ( head = tail = q, len = 0, *tail++ = 0; ; ) {
			h[len++] = *head++, next[len-1] = (h[len-1]+1)%n;
			for ( k = 0, i = (next[len-1]+1)%n; k < n; ++k, ++i, i %= n )
				if ( ccw(c[h[len-1]],c[i],c[next[len-1]]) )
					next[len-1] = i;
			if ( (*tail++ = next[len-1]) == 0 ) break ;
		}
		*/
		/*
		printf("len = %d\n",len);
		for ( i = 0; i < len; ++i )
			printf("%lld %lld\n",c[h[i]][0],c[h[i]][1]);
		*/
		for ( k = 0, j = 0; j < m; )
			if ( inside(a[j++]) ) ++k; /*, printf("Inside: (%lld,%lld)\n",a[j-1][0],a[j-1][1]);*/
	}
	return 0;
}

