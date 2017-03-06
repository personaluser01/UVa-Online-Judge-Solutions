/*
 * 1710. Asteroids
 * TOPIC: ternary search, convex polygons, geometry
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <vector>
#define oo (1LL<<29)
#define N 0x20
#define tol 1e-13
#define DIM 3
#define S(x) ((x)*(x))
using namespace std;

const long double pi = 2*acos(0.00);

struct cell {
	long double x[DIM];
	cell() { for ( int i = 0; i < DIM; x[i++] = 0 ); };
	cell( long double X, long double Y ) { x[0] = X, x[1] = Y, x[2] = 0; };
	long double getlen() const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
	long double dist_to( cell other ) { return S(x[0]-other.x[0])+S(x[1]-other.x[1]); };
};

bool operator == ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a.x[i]-b.x[i]) >= tol )
			return false ;
	return true ;
};

cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a.x[i]+b.x[i], ++i );
	return r;
};

cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a.x[i]-b.x[i], ++i );
	return r;
};

long double operator , ( const cell &a, const cell &b ) {
	long double s = 0;
	for ( int i = 0; i < DIM; s += (a.x[i])*(b.x[i]), ++i );
	return s;
};

cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i ) 
		j = ((i+1)%DIM), k = ((j+1)%DIM), r.x[i] = (a.x[j])*(b.x[k])-(a.x[k])*(b.x[j]);
	return r;
};

bool on_perp( cell &a, cell &b ) { return fabs((a,b))<tol; };

long double operator ^ ( const cell &a, const cell &b ) {
	long double A = a.getlen(), 
		   B = b.getlen(),
		   co = (a,b)/A/B, 
		   si = (a*b).x[DIM-1]/A/B;
	if ( fabs(co-1.00) < tol )
		return 0.00;
	if ( fabs(co+1.00) < tol )
		return -pi;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 ) 
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a.x[i]-b.x[i]) > tol )
			return a.x[i]<b.x[i];
	return false ;
};

cell operator / ( const cell &a, const long double &t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i]=a.x[i]/t, ++i );
	return r;
};

cell operator * ( const cell &a, const long double &t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i]=a.x[i]*t, ++i );
	return r;
};

cell operator * ( const long double &t, const cell &a ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i]=a.x[i]*t, ++i );
	return r;
};

int signum( long double x ) {
	if ( x < 0 ) return -1;
	if ( x > 0 ) return  1;
	return 0;
};

int ccw( cell &a, cell &b, cell &c ) {
	cell u = b-a,
		 v = c-a,
		 r = (u*v);
	return signum(r.x[DIM-1]);
};

bool on_segment( const cell &a, const cell &b, const cell &p ) {
	if ( a == p || b == p ) return true ;
	long double co = (p-a,p-b), si = ((p-a)*(p-b)).x[DIM-1];
	/*
	printf("Is (%.2Lf,%.2Lf) between (%.2Lf,%.2LF) and (%.2Lf,%.2Lf)?\n",p.x[0],p.x[1],a.x[0],a.x[1],b.x[0],b.x[1]);
	printf("%Lf %Lf\n",co,si);
	*/
	return co<0 && fabs(si)<tol;
};

bool get_intersection( cell &u, cell &v, cell &p, cell &q, cell &res ) {
	cell e,m=v-u,n=q-p,b=p-u;
	if ( on_segment(u,v,p) ) {
		res = p;
		return true ;
	}
	if ( on_segment(u,v,q) ) {
		res = q;
		return true ;
	}
	if ( on_segment(p,q,u) ) {
		res = u;
		return true ;
	}
	if ( on_segment(p,q,v) ) {
		res = v;
		return true ;
	}
	long double 
		 delta = -m.x[0]*n.x[1]+m.x[1]*n.x[0], 
		 dt = -b.x[0]*n.x[1]+b.x[1]*n.x[0], 
		 dtau = m.x[0]*b.x[1]-m.x[1]*b.x[0];
	if ( fabs(delta) < tol )
		return false ;
	long double t = dt/delta, tau = dtau/delta;
	if ( !(0<=t && t<=1 && 0<=tau && tau<=1) )
		return false ;
	res = p+tau*n;
	assert( on_segment(u,v,res) );
	assert( on_segment(p,q,res) );
	assert( res == u+t*m );
	return true ;
};

bool inside_polygon( cell *c, int n, cell &p ) {
	long double s = 0;
	for ( int i = 0; i < n; ++i )
		if ( c[i] == p ) return true ;
	for ( int i = 0; i < n; ++i )
		if ( on_segment(c[i],c[(i+1)%n],p) )
			return true ;
	for ( int i = 0; i < n; s += (c[i]-p)^(c[(i+1)%n]-p), ++i );
	//printf("Winding number for (%.2Lf,%.2Lf) is %.2Lf\n",p.x[0],p.x[1],s*180/pi);
	return fabs(fabs(s)-2*pi) < tol;
};

bool strictly_inside( cell *c, int n, cell &p ) {
	long double s = 0;
	for ( int i = 0; i < n; ++i )
		if ( c[i] == p ) return false ;
	for ( int i = 0; i < n; ++i )
		if ( on_segment(c[i],c[(i+1)%n],p) )
			return false ;
	for ( int i = 0; i < n; s += (c[i]-p)^(c[(i+1)%n]-p), ++i );
	//printf("Winding number for (%.2Lf,%.2Lf) is %.2Lf\n",p.x[0],p.x[1],s*180/pi);
	return fabs(fabs(s)-2*pi) < tol;
};

int n[2],m;
cell c[2][N],v[2],sc[2][N],poly[N],dir[2],unit,d[2][N];

void shift_by( const long double t ) {
	for ( int i = 0; i < n[1]; ++i )
		for ( int j = 0; j < DIM; sc[1][i].x[j] = c[1][i].x[j]+t*dir[0].x[j], ++j );
	/*
	for ( int k = 0; k <= 1; ++k )
		for ( int i = 0; i < n[k]; ++i )
			for ( int j = 0; j < DIM; sc[k][i].x[j] = (c[k][i].x[j])+t*(v[k].x[j]), ++j );
			*/
};

void chull( set<cell> &s, cell *poly, int &m ) {
	cell c[0x400];
	int i,j,k,n = 0,next[0x400],t;
	for ( set<cell>::iterator it = s.begin(); it != s.end(); c[n++] = *it++ );
	m = 0, k = 0;
	do {
		poly[m++] = c[k];
		for ( next[k] = k, i = 0; i < n; ++i ) {
			t = ccw(c[k],c[next[k]],c[i]);
			if ( t < 0 || t == 0 && c[k].dist_to(c[next[k]]) < c[k].dist_to(c[i]) )
				next[k] = i;
		}
		k = next[k];
	} while ( k != 0 );
	assert( m <= n );
	//puts("Done...");
	//printf("m = %d\n",m);
	//for ( i = 0; i < m; ++i )
	//	printf("%.2Lf %.2Lf\n",poly[i].x[0],poly[i].x[1]);
		/*
	for ( i = 0; i < m-1; ++i ) {
		j = (i+1)%m, k = (j+1)%m;
		t = ccw(poly[i],poly[j],poly[k]);
		assert( t >= 0 );
	}
	for ( i = 0; i < n; ++i ) 
		assert( inside_polygon(poly,m,c[i]) );
		*/
};

void construct_polygon() {
	int i,j,k,l,t;
	cell res,GC;
	set<cell> s;
	for ( s.clear(), t = 0; t <= 1; ++t )
		for ( i = 0; i < n[t]; ++i )
			if ( strictly_inside(sc[t^1],n[t^1],sc[t][i]) )
				s.insert(sc[t][i]);
	for ( i = 0; i < n[0]; ++i )
		for ( j = ((i+1)%n[0]), k = 0; k < n[1] && (l=(k+1)%n[1])>=0; ++k )
			if ( get_intersection(sc[0][i],sc[0][j],sc[1][k],sc[1][l],res) )
				s.insert(res);
	chull(s,poly,m);
};

long double area( const cell *c, const int n ) {
	long double s = 0;
	if ( n == 0 ) return -1;
	if ( n <= 2 ) return  0;
	assert( n >= 3 );
	/*
	for ( int j,i = 0; i < n; ++i ) 
		j = (i+1)%n, s += ((c[i].x[0])+(c[j].x[0]))*((c[i].x[1])-(c[j].x[1]));
	*/
	for ( int i = 1; i < n-1; ++i ) {
		s += ((c[i]-c[0])*(c[i+1]-c[0])).x[DIM-1];
	}
	return fabs(s)/2.00;
};

bool on_border( const cell &p, const cell *c, const int n ) {
	for ( int i = 0; i < n; ++i )
		if ( on_segment(c[i],c[(i+1)%n],p) )
			return true ;
	return false ;
};

bool first_encounter( long double &t ) {
	long double a[2][2],b[2],delta,dt,dtau;
	t = +oo;
	for ( int k = 0; k <= 1; ++k )
	for ( int i = 0; i < n[k^1]; ++i ) 
		for ( int j = 0; j < n[k]; ++j ) {
			a[0][0] = d[k][j].x[0], a[0][1] = -dir[k].x[0];
			a[1][0] = d[k][j].x[1], a[1][1] = -dir[k].x[1];
			b[0] = c[k^1][i].x[0]-c[k][j].x[0];
			b[1] = c[k^1][i].x[1]-c[k][j].x[1];
			delta = a[0][0]*a[1][1]-a[0][1]*a[1][0];
			if ( fabs(delta) < tol ) continue ;
			dtau = b[0]*a[1][1]-b[1]*a[0][1];
			dtau /= delta;
			if ( !(0<=dtau && dtau<=1) )
				continue ;
			dt = a[0][0]*b[1]-a[1][0]*b[0];
			dt /= delta;
			if ( dt < 0 ) continue ;
			assert( on_segment(c[k][j],c[k][(j+1)%n[k]],c[k^1][i]+dt*dir[k]) );
			assert( c[k^1][i]+dt*dir[k] == c[k][j]+dtau*d[k][j] );
			for ( int l = 0; l < n[k^1]; ++l ) {
				cell advance = c[k^1][l]+dt*dir[k];
				if ( !on_border(advance,c[k],n[k]) && inside_polygon(c[k],n[k],advance) )
					goto nx;
			}
			if ( 0 < dt && dt < t ) t = dt;
			nx: continue ;
		}
	return t<+oo;
};

bool last_encounter( long double &t ) {
	long double a[2][2],b[2],delta,dt,dtau;
	t = 0;
	for ( int k=0; k<=1; ++k )
	for ( int i=0; i<n[k^1]; ++i ) {
		for ( int j = 0; j < n[k]; ++j ) {
			a[0][0] = d[k][j].x[0];
			a[0][1] = -dir[k].x[0];
			b[0] = c[k^1][i].x[0]-c[k][j].x[0];
			a[1][0] = d[k][j].x[1];
			a[1][1] = -dir[k].x[1];
			b[1] = c[k^1][i].x[1]-c[k][j].x[1];
			delta = a[0][0]*a[1][1]-a[0][1]*a[1][0];
			if ( fabs(delta) < tol ) continue ;
			dtau = b[0]*a[1][1]-b[1]*a[0][1];
			dtau /= delta;
			if ( !(0<=dtau && dtau<=1) )
				continue ;
			dt = a[0][0]*b[1]-a[1][0]*b[0];
			dt /= delta;
			if ( dt < 0 ) continue ;
			assert( on_segment(c[k][j],c[k][(j+1)%n[k]],c[k^1][i]+dt*dir[k]) );
			assert( c[k^1][i]+dt*dir[k] == c[k][j]+dtau*d[k][j] );
			for ( int l = 0; l < n[k^1]; ++l ) {
				cell advance = c[k^1][l]+dt*dir[k];
				if ( !on_border(advance,c[k],n[k]) && inside_polygon(c[k],n[k],advance) )
					goto nx;
			}
			if ( dt > t ) t = dt;
			nx: continue ;
		}
	}
	return t > 0;
};

int main() {
	int i,j,k;
	long double na,nb,a,b,va,vb,frst,lst,maxw;
#ifndef ONLINE_JUDGE
	freopen("1710.in","r",stdin);
#endif
	/*
	char *it = "1 0 2 1 -1 0 0 3 -1 -2 0 -1 0 -3 -1 2 2 -1 -3 0 3 0";
	char *ptr;
	set<cell> ss;
	for ( ptr = it; 2 == sscanf(ptr,"%d %d%n",&i,&j,&k); ptr += k )
		ss.insert(cell(i,j));
	chull(ss,poly,m);
	return 0;
	*/
	for(unit.x[0]=1;1==scanf("%d",n) && 0[n];) {
		for ( i = 0; i < n[0]; ++i ) 
			scanf("%Lf %Lf",c[0][i].x,c[0][i].x+1), sc[0][i] = c[0][i];
		scanf("%Lf %Lf",v[0].x,v[0].x+1);
		for ( scanf("%d",n+1), i = 0; i < n[1]; ++i ) 
			scanf("%Lf %Lf",c[1][i].x,c[1][i].x+1);
		scanf("%Lf %Lf",v[1].x,v[1].x+1);
		for ( k = 0; k <= 1; ++k )
			for ( i = 0; i < n[k]; d[k][i] = c[k][(i+1)%n[k]]-c[k][i], ++i );
		for ( i = 0; i <= 1; ++i )
			dir[i] = v[i^1]-v[i];
		if ( !first_encounter(a) ) {
			puts("never");
			continue ;
		}
		for ( last_encounter(b), frst = a, lst = b; b-a >= 1e-12; ) {
			na = (2*a+b)/3.00, nb = (2*b+a)/3.00;
			shift_by(na), construct_polygon(), va = area(poly,m);
			shift_by(nb), construct_polygon(), vb = area(poly,m);
			if ( va < vb-tol ) 
				a = na;
			else b = nb;
		}
		assert( lst >= frst );
		shift_by((a+b)/2.00), construct_polygon(), va = area(poly,m);
		printf("%Lf\n",(a+b)/2);
	}
	return 0;
};

