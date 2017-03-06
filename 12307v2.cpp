/*
 * 12307. Smallest Enclosing Rectangle
 * TOPIC: rotating calipers, convex hull, graham scan, rotations, computational geometry, libraries
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
#define N (1<<21)
#define tol 1e-9
#define DIM 3
#include <cfloat>
#define eps 1e-4
#define oo (DBL_MAX-0x400)
using namespace std;

const long double pi = 2*acosl(0.00);

class cell {
public:
	long double x[DIM];
	cell() {memset(x,0,sizeof x);};
	cell( long double a, long double b ) { x[0] = a, x[1] = b, x[2] = 0; }
	long double operator [] ( const int i ) const { return x[i]; }
	void read() {
		scanf("%Lf %Lf",x,x+1), x[2] = 0;
	}
	cell operator -= ( const cell &a ) {
		for ( int i = 0; i < DIM; x[i] -= a[i], ++i );
		return *this;
	}
	cell operator += ( const cell &a ) {
		for ( int i = 0; i < DIM; x[i] += a[i], ++i );
		return *this;
	}
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabsl(a[i]-b[i]) >= tol )
			return a[i]<b[i];
	return false ;
}
cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]+b[i], ++i );
	return r;
}
cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]-b[i], ++i );
	return r;
}
cell operator ~( const cell &a ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = -a[i], ++i );
	return r;
}
cell operator ^( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i ) 
		k = (((j=(i+1)%DIM)+1)%DIM), r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
}
long double operator , ( const cell &a, const cell &b ) {
	long double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
}
cell operator * ( const cell &a, const long double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
}
cell operator * ( const long double t, const cell &a ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
}
cell operator / ( const cell &a, const long double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]/t, ++i );
	return r;
}
long double norm( const cell &a ) { return sqrtl((a,a)); }
long double operator | ( const cell &a, const cell &b ) {
	long double la = norm(a), lb = norm(b),
		   co = (a,b)/la/lb, si = (a^b)[DIM-1]/la/lb;
	assert( fabs(la) > tol && fabs(lb) > tol );
	if ( fabsl(co-1.00) < tol )
		return 0.00;
	if ( fabsl(co+1.00) < tol )
		return -pi;
	if ( co >= tol && si >= tol )
		return acosl(co);
	if ( co <= tol && si >= tol )
		return acosl(co);
	if ( co >= tol && si <= tol )
		return asinl(si);
	return -pi+acosl(-co);
}

cell operator ^ ( const cell &a, long double t ) {
	long double co = cosl(t), si = sinl(t);
	return cell(a[0]*co-a[1]*si,a[0]*si+a[1]*co);
}

bool is_perp( const cell &a, const cell &b ) { return fabsl((a/norm(a),b/norm(b))) < 1e-2; }
bool is_parallel( const cell &a, const cell &b ) { return 1||fabsl(a[0]*b[1]-a[1]*b[0]) < 1e-2; }

class pcell {
public:
	cell c;
	long double ang,dist;
	pcell() {};
};

bool operator < ( const pcell &a, const pcell &b ) {
	if ( fabsl(a.ang-b.ang) < tol )
		return a.dist > b.dist;
	return a.ang < b.ang;
}

bool is_left_turn( const cell &a, const cell &b, const cell &c ) {
	cell u = b-a, v = c-b;
	long double co = (u,v), si = (u^v)[DIM-1];
	if ( fabsl(si) < tol ) {
		if ( co < -tol ) { assert(0); }
		return false ;
	}
	return si >= tol;
}

cell c[N],pole,ex(1,0),v[N];
int n,m,st[N],*top;
pcell p[N];

class caliper {
public:
	int idx;
	cell vec;
	caliper() {};
	caliper( int ii, cell v ) {
		this->idx = ii, this->vec = v;
	}
};

caliper operator ^ ( const caliper &cc, long double t ) {
	cell u = cc.vec;
	long double ang = 0,delta;
	int i,j,k;
	//assert( t >= 0 );
	if ( t >= 2*pi ) 
		t = fmod(t,2*pi);
	if ( fabsl(t) < tol ) return cc;
	for ( i = ((j = cc.idx)+1)%n; ;j = i, ++i, i %= n ) {
		delta = u|v[i];
		//assert( delta >= 0 );
		if ( ang+delta <= t ) {
			ang += delta;
			u = v[i];
			if ( fabsl(ang-t) < tol )
				return caliper(i,u);
			continue ;
		}
		//assert( delta > t-ang );
		delta = t-ang;
		u = u^delta;
		return caliper(j,u);
	}
	// assert( 0 );
}

caliper operator ^ ( const caliper &cc, const caliper &nml ) {
	cell u = cc.vec;
	long double ang = nml.vec|cc.vec, delta;
	caliper res;
	int i,j,k;
	/* invariant: (u,nml) >= 0 */
	assert( (u,nml.vec) >= 0 );
	for ( i = ((j = cc.idx)+1)%n; ;j = i, ++i, i %= n ) {
		/*
		delta = u|v[i];
		assert( delta >= 0 );
		if ( ang+delta <= pi/2 ) {
			ang += delta;
			u = v[i];
			if ( fabsl(ang-pi/2) < tol ) {
				res = caliper(i,u);
				return res;
			}
			continue ;
		}
		assert( delta > pi/2-ang );
		delta = pi/2-ang;
		u = u^delta;
		res = caliper(j,u);
		return res;
		*/
		if ( (v[i],nml.vec) >= 0 ) {
			if ( fabs((v[i],nml.vec)) < tol && fabs((nml.vec|v[i])-pi/2) < tol ) 
				return caliper(i,v[i]);
			u = v[i];
			continue ;
		}
		delta = pi/2-(nml.vec|u);
		return caliper(j,u^delta);
	}
}


long double line2line( const caliper &a, const caliper &b ) {
	cell m = a.vec, r = (c[a.idx]-c[b.idx]);
	long double A = (m,m), B = 2*(m,r), C = (r,r);
	//return sqrtl(A*tau*tau+B*tau+C);
	return sqrtl(C-B*B/4/A);
}

int main() {
	int i,j,k;
	cell orig;
	caliper cal[4];
	long double delta,perim,area;
#ifndef ONLINE_JUDGE
	freopen("critical12307.in","r",stdin);
#endif
	for(;1 == scanf("%d",&n) && n;) {
		for ( i = 0; i < n; c[i++].read() );
		for ( sort(c,c+n), i = 1; i < n; c[i++] -= c[0] );
		for ( orig = c[0], p[0].c = pole, k = 1, i = 1; i < n; ++i, ++k )
			p[k].c = c[i], p[k].dist = norm(c[i]), p[k].ang = (ex^c[i])[DIM-1]/p[k].dist;
		for ( m = 0, v[m++] = p[0].c, sort(p+1,p+n), i = 1; i < n; v[m++] = p[i].c, i = j ) 
			for ( j = i+1; j < n && fabsl(p[i].ang-p[j].ang) < tol; ++j );
		// assert( m >= 3 );
		/*
		printf("m = %d\n",m);
		for ( i = 0; i < m; ++i ) {
			cell tmp = v[i]+orig;
			printf("%.2Lf %.2Lf\n",tmp[0],tmp[1]);
		}
		*/
		for ( top = st, *++top = 0, *++top = 1, *++top = 2, i = 3; i < m; *++top = i++ ) 
			for (;top-st >= 2 && !is_left_turn(v[*(top-1)],v[*top],v[i]); 0&&printf("Removing %d\n",*top+1), --top );
		// printf("Left %d\n",top-st);
		for ( n = 0, i = 1; i <= top-st; c[n++] = v[st[i++]] );
		for ( i = 0; i < n; j = (i+1)%n, v[j] = c[j]-c[i], ++i );
		/*
		printf("Convex hull is %d\n",n);
		for ( i = 0; i < n; ++i ) {
			c[i] = c[i]+orig;
			printf("%.2Lf %.2Lf\n",c[i][0],c[i][1]);
		}
		*/
		for ( cal[0] = caliper(0,v[0]), i = 1; i < 4; ++i )
			cal[i] = cal[i-1]^cal[i-1];
		area = perim = +oo;
		for ( k = 0; k < n; ++k ) {
			long double height = line2line(cal[0],cal[2]), width = line2line(cal[1],cal[3]);
			area = min(area,height*width), perim = min(perim,2*height+2*width);
			/*
			assert( is_perp(cal[0].vec,cal[1].vec) );
			if ( !is_perp(cal[2].vec,cal[3].vec) )
				printf("[k = %d] This %Lf\n",k,(cal[2].vec|cal[3].vec)*180/pi);
			assert( is_perp(cal[2].vec,cal[3].vec) );
			if ( !is_perp(cal[0].vec,cal[3].vec) )
				printf("[k = %d] This %Lf\n",k,(cal[0].vec|cal[3].vec)*180/pi);
			assert( is_perp(cal[0].vec,cal[3].vec) );
			assert( is_parallel(cal[1].vec,cal[3].vec) );
			assert( is_parallel(cal[0].vec,cal[2].vec) );
			assert( is_parallel(cal[0].vec,v[cal[0].idx]) );
			*/
			//for ( i = 0; i < 4; ++i )
			//	printf("cal[%d].idx = %d\n",i,cal[i].idx);
			/*
			delta = cal[0].vec|v[(cal[0].idx+1)%n];
			cal[0] = cal[0]^delta;
			*/
			cal[0].vec = v[(cal[0].idx+1)%n], ++cal[0].idx, cal[0].idx %= n;
			for ( i = 1; i < 4; ++i )
				//cal[i].vec = v[(cal[i].idx+1)%n], ++cal[i].idx, cal[i].idx %= n, cal[i] = cal[i]^cal[i-1];
				cal[i] = cal[i]^cal[i-1];
				//cal[i] = cal[i-1]^cal[i-1];
		}
		printf("%.2Lf %.2Lf\n",area+1e-11,perim+1e-11);
	}
	return 0;
}




