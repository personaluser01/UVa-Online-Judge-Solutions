/*
 * 11919. Hybrid Silentia
 * TOPIC: dp, geometry, ternary search, bitmasks, point-segment distance
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N    0x11
#define DIM  2
#define tol  1e-12
#define oo   (1L<<29)
#define L(k) ((k)&((~(k))+1ULL))
using namespace std;

double S( double x ) { return x*x; }

int n;
double x[N],y[N],r[N],d[N][N];
char bts[BIT(N)],tp[N][2],which[BIT(N)];

struct cell {
	double x[DIM];
	cell() { for ( int i = 0; i < DIM; x[i++] = 0); };
};
cell c[N],u[N][4];

cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a.x[i]+b.x[i];
	return r;
}

cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a.x[i]-b.x[i];
	return r;
}

cell operator * ( const cell &a, const double t ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a.x[i]*t;
	return r;
}

double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; ++i )
		s += a.x[i]*b.x[i];
	return s;
}

cell h( double l ) {
	cell r;
	r.x[0] = l;
	return r;
}

cell v( double l ) {
	cell r;
	r.x[1] = l;
	return r;
}

double point2segment( cell &x, cell &p, cell &q ) {
	double a,b,na,nb;
	/*
	cell pp,qq,m = q-p;
	for ( a = 0, b = 1; fabs(b-a) > tol; ) {
		na = (2*a+b)/3, nb = (a+2*b)/3;
		pp = p+m*na, qq = p+m*nb;
		if ( (x-pp,x-pp) < (x-qq,x-qq) )
			b = nb;
		else a = na;
	}
	pp = p+m*((a+b)/2);
	return sqrt((x-pp,x-pp));
	*/
	cell m = q-p;
	double t = (x-p,m)/((m,m));
	if ( 0 <= t && t <= 1 )
		return sqrt((x-p-m*t,x-p-m*t));
	return sqrt(min((x-p,x-p),(x-q,x-q)));
}

double dist( int i, int j ) {
	double w = +oo;
	if ( 0[tp[i]] == 'C' ) {
		if ( 0[tp[j]] == 'C' ) 
			return sqrt(S(x[i]-x[j])+S(y[i]-y[j]))-r[i]-r[j];
		else {
			for ( int l,k = 0; k < 4 && (l=(k+1)&3)>=0; ++k ) 
				w = min(w,point2segment(c[i],u[j][k],u[j][l]));
			return w-r[i];
		}
	}
	else {
		if ( 0[tp[j]] == 'C' ) 
			return dist(j,i);
		else {
			for ( int t = 0; t < 4; ++t ) 
			for ( int l,k = 0; k < 4 && (l=(k+1)&3)>=0; ++k ) 
				w = min(w,point2segment(u[i][t],u[j][k],u[j][l]));
			for ( int t = 0; t < 4; ++t ) 
			for ( int l,k = 0; k < 4 && (l=(k+1)&3)>=0; ++k ) 
				w = min(w,point2segment(u[j][t],u[i][k],u[i][l]));
			return w;
		}
	}
}

double D[N+N];
int z[BIT(N)][N],yes;
#define Q (1 << 21)
#define enc(u,x) ((u)|((x)<<N))
unsigned int q[Q],*head,*tail;

bool can_accomplish( const double L ) {
	unsigned int e,o,t,i,j,k,U;
	double H;
	for ( head=tail=q, z[BIT(0)][0]=++yes, *tail++=enc(BIT(0),0); head<tail; )
		for ( U=*head++, e=(U&MASK(N)), H=L*D[bts[e]-1], i=(U>>N), t=(~e)&MASK(n); t && (j=which[L(t)])>=0; t&=~L(t) )
			if ( d[i][j]<=H && z[BIT(j)|e][j]!=yes )
				z[e|BIT(j)][j] = yes, *tail++ = enc(e|BIT(j),j);
	for ( i = 0; i < n; ++i )
		if ( z[MASK(n)][i] == yes )
			return true ;
	return false ;
}

double dp[BIT(N)][N];
vector<pair<int,unsigned int> > A;

int main() {
	int i,j,k,ts;
	unsigned int e,o,t;
	double good,bad,mid;
#ifndef ONLINE_JUDGE
	freopen("11919.in","r",stdin);
#endif
	for ( D[0] = 1, i = 1; i < N; D[i] = D[i-1]/.9, ++i );
	for ( k = 0; k < BIT(N); bts[k]=bts[k>>1]+(k&1), ++k );
	for ( k = 0; k < N; which[BIT(k)] = k, ++k );
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i ) {
			scanf("%s %lf %lf %lf",tp[i],x+i,y+i,r+i), c[i].x[0] = x[i], c[i].x[1] = y[i];
			if ( 0[tp[i]] != 'C' ) {
				u[i][0] = c[i];
				u[i][1] = c[i]+h(r[i]);
				u[i][2] = u[i][1]+v(r[i]);
				u[i][3] = u[i][2]+h(-r[i]);
			}
		}
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; d[i][j] = d[j][i] = dist(i,j), ++j );
		/*
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				printf("%.2lf%c",d[i][j],j==n-1?'\n':' ');
		*/
		for ( e = 0; e < BIT(n); ++e )
			for ( i = 0; i < n; ++i )
				dp[e][i] = +oo;
		for ( dp[BIT(0)][0] = 0, e = 0; e < BIT(n); ++e )
			for ( o = e; o && (i=which[L(o)]) >= 0; o &= ~L(o) )
				if ( dp[e][i] < +oo )
					for ( t = (~e)&MASK(n); t && (j=which[L(t)])>=0; t &= ~L(t) )
						dp[e|BIT(j)][j] = min(dp[e|BIT(j)][j],max(d[i][j]*D[bts[e]-1],dp[e][i]));
		double ans = +oo;
		for ( i = 0; i < n; ++i )
			ans = min(ans,dp[MASK(n)][i]);
		printf("%lf\n",ans);
	}
	return 0;
}


