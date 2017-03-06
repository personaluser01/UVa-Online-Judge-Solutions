/*
 * 1100. Paperweight
 * TOPIC: convex hull, arbitrary plane, geometry, world finals
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>
// #define NDEBUG
#define BIT(k) (1ULL<<(k))
#define TST(x,i) (((x)>>(i))&1)
#define eps 1e-8
#define tol 1e-13
#define DIM 3
#define N 0x40
#define oo (1<<29)
using namespace std;

long double S(long double x) { return x*x; };
bool eq( long double x, long double y ) { return fabs(x-y) < tol; };
const long double pi = (2*acos(0.00));

struct cell {
	long double x[DIM];
	cell() { memset(x,0,sizeof x); };
	cell( long double a, long double b, long double c ) { 0[x] = a, 1[x] = b, 2[x] = c; };
	long double operator [] ( const int i ) const { return x[i]; };
	long double getlen() const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
	bool read() { return 3 == scanf("%Lf %Lf %Lf",x,x+1,x+2); };
	void print( const char *a ) const {	puts(a), printf("(%.4Lf,%.4LF,%.4Lf)\n",0[x],1[x],2[x]); };
};
cell c[N],GC,ZERO;
bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( !eq(a[i],b[i]) )
			return a[i]<b[i];
	return false ;
};
bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); };
cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1],a[2]+b[2]); }
cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1],a[2]-b[2]); }
cell operator * ( const cell &a, long double t ) { return cell(a[0]*t,a[1]*t,a[2]*t); };
cell operator * ( long double t, const cell &a ) { return cell(a[0]*t,a[1]*t,a[2]*t); };
cell operator / ( const cell &a, long double t ) { return cell(a[0]/t,a[1]/t,a[2]/t); };
void operator /= ( cell &a, long double t ) { a.x[0]/=t,a.x[1]/=t,a.x[2]/=t; };
void operator *= ( cell &a, long double t ) { a.x[0]*=t,a.x[1]*=t,a.x[2]*=t; };
cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k = ((j=(i+1)%DIM)+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
};
long double operator , ( const cell &a, const cell &b ) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; };
long double operator ^ ( const cell &a, const cell &b ) { 
	long double A = a.getlen(), B = b.getlen(), co = (a,b)/A/B;
	if ( co > 1 ) co = 1; if ( co < -1 ) co = -1;
	return acos(co);
};
int sig( long double x ) { return fabs(x)<tol?0:(x<0?-1:1); };
bool is_perp( cell &a, cell &b ) { 
	long double s = (a,b);
	return fabs((a,b)) < eps;
};

cell _projection( cell p, cell a, cell b, long double &tau ) {
	cell m = b-a,n;
	long double t = (p-a,m)/(m,m);
	tau = t;
	n = p-(a+(t*m));
	assert( is_perp(n,m) );
	return (a+(t*m));
};

int n = 6;

cell projection( cell p, cell *c ) {
	cell a = (c[1]-c[0]), b = (c[2]-c[0]), h, normale, q = p-c[0];
	//assert( !(ZERO == (a*b)) );
	long double pa = (q,a), pb = (q,b), ab = (a,b), 
		 		A = (a,a), B = (b,b),
		 		delta = A*B-S(ab);
	if ( eq(delta,0) ) return p;
	long double alpha = (B*pa-ab*pb)/delta, 
				beta  = (A*pb-ab*pa)/delta;
	//assert( !((a*b) == ZERO) );
	h=(alpha*a)+(beta*b); normale=(q-h);
	//assert( is_perp(normale,a) );
	//assert( is_perp(normale,b) ); 
	return (h+c[0]);
};

long double volume( cell &a, cell &b, cell &c, cell &d ) {
	cell e[] = {a,b,c}, h = projection(d,e);
	return fabs((((b-a)*(c-a)).getlen())*((d-h).getlen()))/6.00;
};

bool on_segment( const cell &a, const cell &b, const cell &p ) {
	return ((p-a)*(p-b)) == ZERO && (p-a,p-b) <= 0;
};

bool on_triangle( const cell &a, const cell &b, const cell &c, const cell &p ) {
	if ( p == a || p == b || p == c ) return true ;
	if ( on_segment(a,b,p) || on_segment(b,c,p) || on_segment(c,a,p) ) return true ;
	cell normale = (b-a)*(c-a);
	normale/=normale.getlen();
	int i = sig(((p-a)*(p-b),normale)),
		j = sig(((p-b)*(p-c),normale)),
		k = sig(((p-c)*(p-a),normale));
	return i > 0 && j > 0 && k > 0 || i < 0 && j < 0 && k < 0;
};

bool inside_hull( const cell *c, const int n, cell p ) {
	for ( int i = 0; i < n; ++i )
		for ( int j = i+1; j < n; ++j )
			for ( int k = j+1; k < n; ++k )
				if ( on_triangle(c[i],c[j],c[k],p) )
					return true ;
	return false ;
};

void convex_hull( const cell *c, const int n, cell *p, int &m, cell &normale ) {
	cell d[N],u,v;
	int i,j,k,t,next[N];
	long double prod;
	normale = (c[1]-c[0])*(c[2]-c[0]);
	normale /= normale.getlen();
	for ( i = 0; i < n; d[i] = c[i], next[i++] = -1 );
	for ( sort(d,d+n), next[i=0]=-1;; i=next[i] ) {
		for ( next[i]=(i+1)%n, k = 0, j = (i+2)%n; k < n; ++k, ++j, j %= n ) {
			if ( j == next[i] ) continue ;
			u = d[j]-d[i]; v = d[next[i]]-d[i];
			prod = (u*v,normale);
			if ( sig(prod) > 0 || (u*v) == ZERO && (u,v) > 0 && (u,u) > (v,v) )
				next[i] = j;
		}
		if ( next[i] == 0 ) break ;
	}
	for ( m = 0, i = 0, p[m++] = d[i], i = next[i]; i != 0; p[m++] = d[i], i = next[i] );
	assert( m >= 3 );
	for ( i = 0; i < m; ++i ) {
		j = (i+1)%m, k = (i-1+m)%m;
		assert( ((p[i]-p[k])*(p[j]-p[k]),normale) > 0 );
	}
};

bool sufficiently_stable( const cell p, const cell *c, const int n, const cell &normale ) {
	int i,j,k;
	long double t,s = 0;
	for ( i = 0; i < n; s += t, ++i ) {
		j = (i+1)%n;
		if ( p == c[i] || p == c[j] ) return false ;
		if ( (p-_projection(p,c[i],c[j],t)).getlen() <= 0.2-tol ) {
			0 && puts("Failure 1");
			return false ;
		}
		/*
		t = (c[i]-p)^(c[j]-p);
		k = sig(((c[i]-p)*(c[j]-p),normale));
		assert( k == -1 || k == 1 );
		if ( k < 0 ) t = 2*pi-t;
		*/
	}
	//return eq(fabs(s),2*pi);
	return true ;
};

bool valid_input() {
	cell e[3] = {c[0],c[1],c[2]};
	cell hd = projection(c[3],e),
		 he = projection(c[4],e);
	return ((c[3]-hd),(c[4]-he))<0;
};

int main() {
	int i,j,k,cs = 0,m,mask,l,len,idx[N];
	char bts[1<<10] = {0};
	cell e[N],taban,p[N],normale;
	long double mn,mx,w,v0,v1;
#ifndef ONLINE_JUDGE
	freopen("1100.in","r",stdin);
#endif
	for ( k = 1; k < 0x400; ++k )
		bts[k] = bts[k>>1]+(k&1);
	for (;c[0].read();) {
		for ( i=1; i<n; ++i )
			if ( !c[i].read() )
				return 0;
		v0 = volume(c[0],c[1],c[2],c[3]), v1 = volume(c[0],c[1],c[2],c[4]);
		GC = (((c[0]+c[1])+(c[2]+c[3]))*(v0/4)+((c[0]+c[1])+(c[2]+c[4]))*(v1/4))/(v0+v1);
		printf("Case %d: ",++cs), mn=+oo,mx=-oo;
		for ( k=0; k<(1<<(n-1)); ++k )
			if ( bts[k]==3 ) {
				for ( m = 0, i = 0; i < n-1; ++i )
					if ( TST(k,i) ) e[m++] = c[i], idx[m-1] = i;
				normale = (e[1]-e[0])*(e[2]-e[0]);
				if ( normale == ZERO ) continue ;
				for ( mask=0, i=0; i<n && (mask&6)!=6; ++i )
					if ( i==n-1 || !TST(k,i) ) {
						taban=projection(c[i],e);
						if ( c[i]==taban ) {
							if ( i<n-1 )
								e[m++]=c[i],idx[m-1]=i;
							continue ;
						}
						j=sig(((c[i]-taban),normale));
						//assert( ZERO == ((c[i]-taban)*normale) );
						assert( j==-1 || j==1 );
						mask|=(1<<(j==0?0:(j<0?1:2)));
					}
				assert(m<=5);
				if ( (mask&6) == 6 ) { 0&&printf("m = %d, %c %c %c w = %Lf\n",m,idx[0]+'A',idx[1]+'A',idx[2]+'A',w); continue ; }
				w = (c[n-1]-projection(c[n-1],e)).getlen();
				if ( mn <= w && w <= mx ) continue ;
				taban = projection(GC,e);
				convex_hull(e,m,p,len,normale);
				if ( inside_hull(p,len,taban) && sufficiently_stable(taban,p,len,normale) )
				// if ( inside_hull(e,m,taban) && sufficiently_stable(taban,e,m,normale) )
					mn = min(mn,w), mx = max(mx,w);
			}
		printf("%.5Lf %.5Lf\n",mn+tol,mx+tol);
	}
	return 0;
}

