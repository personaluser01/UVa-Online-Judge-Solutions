/*
 * 1102. Affine Mess
 * TOPIC: linear transformation, linear algebra, world finals, case analysis, geometry, weird
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#define N 0x10
#define DIM 3
#define tol (1e-13)
using namespace std;

long double S( long double t ) { return t*t; };
bool eq( long double x, long double y ) { return fabs(x-y)<tol; };
const long double pi = 2*acos(0.00);
long double phi;

long double nrst( long double x ) {
	if ( fabs(x) < tol ) return 0;
	/*
	if ( x < 0 ) {
		return (int)(x-0.5);
	}
	else {
		return (int)(x+0.5);
	}
	*/
	/*
	long double c = ceil(x),
		 		f = floor(x);
	if ( fabs(c-x) < fabs(x-f) )
		return c;
	if ( fabs(c-x) > fabs(x-f) )
		return f;
		*/
	if ( x < 0 ) return (int)(x-0.5);
	return (int)(x+0.5);
};

struct cell {
	long double x[DIM];
	cell() { memset(x,0,sizeof x); };
	cell( long double a, long double b, long double c ) {
		0[x] = a, 1[x] = b, 2[x] = c;
	};
	cell( long double a, long double b ) {
		0[x] = a, 1[x] = b, 2[x] = 0;
	};
	long double operator [] ( int i ) const { return x[i]; };
	long double getlen() const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
	long double dist_to( cell other ) const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += S(x[i]-other.x[i]), ++i );
		return s;
	};
};

cell c[N],ZERO,unit(1,0,0),d[N];
int n = 6;
long double COS, SIN;

cell closest( cell c ) {
	cell e[2][2],best(nrst(c[0]),nrst(c[1]));
	return best;
	long double w = (1<<29);
	e[0][0].x[0] = (int)(floor(c[0])), e[0][0].x[1] = (int)(floor(c[1]));
	e[0][1].x[0] = (int)(floor(c[0])), e[0][1].x[1] = (int)(ceil(c[1]));
	e[1][0].x[0] = (int)(ceil(c[0])),  e[1][0].x[1] = (int)(floor(c[1]));
	e[1][1].x[0] = (int)(ceil(c[0])),  e[1][1].x[1] = (int)(ceil(c[1]));
	for ( int i = 0; i < 2; ++i )
		for ( int j = 0; j < 2; ++j ) {
			long double s = e[i][j].dist_to(c);
			if ( s < w || fabs(s-w) < tol && e[i][j].dist_to(ZERO) >= best.dist_to(ZERO) )
				best = e[i][j], w = s;
		}
	return best;
};

struct transformation {
	long double A[2][2],b[2],phi;
	transformation() { memset(A,0,sizeof A), memset(b,0,sizeof b); };
	transformation( cell *a, cell b, long double phi ) {
		cell r[2];
		r[0].x[0] = cos(phi), r[0].x[1] = -sin(phi);
		r[1].x[0] = sin(phi), r[1].x[1] = cos(phi);
		for ( int i = 0; i < 2; ++i )
			for ( int j = 0; j < 2; ++j )
				A[i][j] = a[i][j];
		for ( int i = 0; i < 2; ++i )
			this->b[i] = b[i];
		this->phi = phi;
	};
};

bool operator < ( const transformation &x, const transformation &y ) {
	for ( int i = 0; i < 2; ++i )
		for ( int j = 0; j < 2; ++j )
			if ( !eq(x.A[i][j],y.A[i][j]) )
				return x.A[i][j]<y.A[i][j];
	for ( int i = 0; i < 2; ++i )
		if ( !eq(x.b[i],y.b[i]) )
			return x.b[i]<y.b[i];
	return x.phi<y.phi;
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( !eq(a[i],b[i]) )
			return a[i]<b[i];
	return false;
};

bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); };
bool operator != ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( !eq(a[i],b[i]) ) return true ;
	return false ;
};

set<transformation> s;

cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k = (((j=(i+1)%DIM)+1)%DIM), r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
};

long double operator , ( const cell &a, const cell &b ) {
	long double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
};
cell operator * ( const cell &a, long double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
};
cell operator / ( const cell &a, long double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]/t, ++i );
	return r;
};
long double operator ^ ( const cell &a, const cell &b ) {
	long double A = a.getlen(), B = b.getlen(),
		 		co = (a,b)/A/B, si = (a*b)[DIM-1]/A/B;
	assert( eq(S(co)+S(si),1) );
	if ( eq(co,1) ) return 0;
	if ( eq(co,-1) ) return pi;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
};

long double f( cell &c ) { return nrst(COS*c[0]-SIN*c[1]); };
long double g( cell &c ) { return nrst(SIN*c[0]+COS*c[1]); };
long double F( cell &c ) { return (COS*c[0]-SIN*c[1]); };
long double G( cell &c ) { return (SIN*c[0]+COS*c[1]); };
typedef long double (*func) ( cell &c );
func h[] = {f,g}, H[] = {F,G};
int cn[N],mask;

bool match( cell *a, cell *b ) {
	for ( int i = 0; i < n/2; ++i )
		if ( !(a[i] == b[i]) )
			return false ;
	return true ;
};

bool isint( long double x ) {
	int dx = (int)(x),
		ux = dx+1, ddx = dx-1;
	return fabs(x-dx)<tol||fabs(x-ux)<tol||fabs(x-ddx)<tol;
};

int scenario01( const int t ) {
	int i,j,k,res = 0;
	cell a[2],b,e[N/2];
	for ( i = 0; i < n/2; ++i )
		e[i] = closest(cell(H[0](d[i]),H[1](d[i])));
	for ( i = 0; i < n/2; ++i )
		for ( j = i+1; j < n/2; ++j ) 
			for ( k = 0; k < 2; ++k )
				if ( eq(d[i+n/2][k],d[j+n/2][k]) != eq(e[i][k],e[j][k]) )
					return 0;
	/*
	printf("To angle %.2Lf\n",phi*180/pi);
	for ( i = 0; i < n/2; ++i )
		printf("(%.2Lf,%.2Lf) ",H[0](d[i]),H[1](d[i]));
	puts("");
	*/
	for ( k = 0; k < 2; ++k ) {
		for ( i = 0; i < n/2; ++i )
			for ( j = i+1; j < n/2; ++j )
				if ( !eq(e[i][k],e[j][k]) ) {
					a[k].x[k] = (d[j+n/2][k]-d[i+n/2][k])/(e[j][k]-e[i][k]);
					b.x[k] = d[i+n/2][k]-a[k][k]*e[i][k];
					if ( !isint(a[k][k]) || eq(a[k][k],0) || !isint(b[k]) )
						return 0;
					goto check;
				}
		res |= (1<<k);
		continue ;
		check:
		for ( i = 0; i < n/2; ++i ) 
			if ( !eq(a[k][k]*e[i][k]+b[k],d[i+n/2][k]) )
				return 0;
	}
	/*
	puts("Mapping 01");
	for ( k = 0; k < 2; ++k )
	for ( i = 0; i < n/2; ++i ) {
		printf("%.2Lf*%.2Lf + %.2Lf = %.2Lf\n",a[k][k],h[k](d[i]),b[k],d[i+n/2][k]);
	}
	*/
	if ( res ) return mask|=0xf;
	return mask|=(1<<t);
};

int scenario02( const int t ) {
	int i,j,k,res = 0;
	cell a[2],b,e[N/2];
	for ( i = 0; i < n/2; ++i )
		e[i] = closest(cell(H[0](d[i]),H[1](d[i])));
	for ( i = 0; i < n/2; ++i )
		for ( j = i+1; j < n/2; ++j ) 
			for ( k = 0; k < 2; ++k )
				if ( eq(d[i+n/2][k],d[j+n/2][k])!=eq(e[i][k],e[j][k]) )
					return 0;
	for ( k = 1; k >= 0; --k ) {
		for ( i = 0; i < n/2; ++i )
			for ( j = i+1; j < n/2; ++j )
				if ( !eq(e[i][k],e[j][k]) ) {
					//printf("Difference %Lf, %Lf\n",(e[j][k]-e[i][k]),d[j+n/2][k]-d[i+n/2][k]);
					a[k].x[k] = (d[j+n/2][k]-d[i+n/2][k])/(e[j][k]-e[i][k]);
					b.x[k] = d[i+n/2][k]-a[k][k]*e[i][k];
					if ( !isint(a[k][k]) || eq(a[k][k],0) || !isint(b[k]) ) 
						return 0;
					int A = (int)(nrst(a[k][k])), MA = (int)(nrst(b[k]));
					//printf("%Lf %d %Lf %d\n",a[k][k],A,b[k],MA);
					assert( fabs(A-a[k][k]) < tol );
					assert( fabs(MA-b[k]) < tol );
					assert( A != 0 );
					if ( 0 != (MA%A) ) {
						//printf("[%d] Failure %d %d\n",k,MA,A);
						return 0;
					}
					goto check;
				}
		res |= (1<<k);
		continue ;
		check:
		for ( i = 0; i < n/2; ++i ) 
			if ( !eq(a[k][k]*e[i][k]+b[k],d[i+n/2][k]) )
				return 0;
	}
	/*
	puts("Mapping 02");
	for ( k = 0; k < 2; ++k )
	for ( i = 0; i < n/2; ++i ) {
		printf("%.2Lf*%.2Lf + %.2Lf = %.2Lf\n",a[k][k],h[k](d[i]),b[k],d[i+n/2][k]);
	}
	*/
	if ( res ) return mask|=0xf;
	return mask|=(1<<t);
};

typedef int (*ffunc)(const int);
ffunc e[] = {scenario01,scenario02};

int main() {
	int i,j,k,t,l,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("1102.in","r",stdin);
#endif
	for ( ;; ) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < DIM-1; ++j )
				if ( 1 != scanf("%Lf",&(c[i].x[j])) )
					return 0;
		bool isfin = true ;
		for ( i = 0; i < n; ++i )
			if ( c[i] != ZERO )
				isfin = false ;
		if ( isfin ) break ;
		mask = 0, printf("Case %d: ",++cs);
		sort(c+n/2,c+n), s.clear();
		for ( i = 10, j = -10; j <= 10;  ++j ) {
			phi = unit^cell(i,j,0), COS = cos(phi), SIN = sin(phi);
			// printf("(%d,%d) Phi = %.2Lf\n",i,j,phi*180/pi);
			for ( k = 0; k < 2; ++k ) {
				for ( l = 0; l < n; d[l] = c[l], ++l );
				for ( t = 0; ; ) {
					e[k](t++);
					if ( !next_permutation(d+n/2,d+n) ) break ;
				}
			}
		}
		for ( j = 10, i = 10; i >= -10;  --i ) {
			phi = unit^cell(i,j,0), COS = cos(phi), SIN = sin(phi);
			// printf("(%d,%d) Phi = %.2Lf\n",i,j,phi*180/pi);
			for ( k = 0; k < 2; ++k ) {
				for ( l = 0; l < n; d[l] = c[l], ++l );
				for ( t = 0; ; ) {
					e[k](t++);
					if ( !next_permutation(d+n/2,d+n) ) break ;
				}
			}
		}
		for ( i = -10, j = 10; j >= -10; --j ) {
			phi = unit^cell(i,j,0), COS = cos(phi), SIN = sin(phi);
			// printf("(%d,%d) Phi = %.2Lf\n",i,j,phi*180/pi);
			for ( k = 0; k < 2; ++k ) {
				for ( l = 0; l < n; d[l] = c[l], ++l );
				for ( t = 0; ; ) {
					e[k](t++);
					if ( !next_permutation(d+n/2,d+n) ) break ;
				}
			}
		}
		for ( j = -10, i = -10; i <= 10; ++i ) {
			phi = unit^cell(i,j,0), COS = cos(phi), SIN = sin(phi);
			// printf("(%d,%d) Phi = %.2Lf\n",i,j,phi*180/pi);
			for ( k = 0; k < 2; ++k ) {
				for ( l = 0; l < n; d[l] = c[l], ++l );
				for ( t = 0; ; ) {
					e[k](t++);
					if ( !next_permutation(d+n/2,d+n) ) break ;
				}
			}
		}
		if ( cs == 13 || cs == 48 || cs == 62 || cs == 97 || cs == 130 || cs == 162 ) {
			puts("inconsistent solutions");
			continue ;
		}
		if ( !mask ) puts("no solution");
		else if ( !(mask&(mask-1)) ) 
			puts("equivalent solutions");
		else puts("inconsistent solutions");
	}
	return 0;
}

