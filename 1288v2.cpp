
/*
 * 1288. Shortest Flight Plan
 * TOPIC: geometry,worldfinals,3d circle,ternary search,binary search,vector calculus,trigonometry,quadratic equations
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#define BIT(k) (1LL<<(k))
#define TST(u,k) (((u)>>(k))&1)
#define oo ((double)(1<<29))
#define eps ((double)(1e-4))
#define tol ((double)(1e-12))
#define MAXV 0x400
#define DBG 0
#define N 32
#define MAXQ (1<<21)
using namespace std;
#define DIM 3

bool equal( double a, double b ) { return fabsl(a-b)<tol; };
bool leq( double a, double b ) { return equal(a,b) || a<b; };
bool geq( double a, double b ) { return equal(a,b) || a>b; };

const double R = 6370.00, pi = 2*acos(0.00);
double g[MAXV][MAXV],D;
double S( double s ) { return s*s; };
struct cell {
	double x[DIM];
	cell() { for ( int i = 0; i < DIM; x[i++] = 0 ); };
	cell( double phi, double theta ) {
		x[0] = cos(theta)*cos(phi);
		x[1] = cos(theta)*sin(phi);
		x[2] = sin(theta);
	};
	cell( double a, double b, double c ) { x[0] = a, x[1] = b, x[2] = c; };
	double getlen() const {
		double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
	double operator [] ( int i ) const { return x[i]; };
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a.x[i]-b.x[i])>tol )
			return a.x[i]<b.x[i];
	return false ;
};

bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); };
double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
};
cell operator * ( const cell &a, const double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
};
cell operator * ( const double t, const cell &a ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
};
cell operator / ( const cell &a, const double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]/t, ++i );
	return r;
};
cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a[i]+b[i];
	return r;
};
cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a[i]-b[i];
	return r;
};
cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i ) 
		j = (i+1)%DIM, k = (j+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
};

void operator += ( cell &a, const cell &b ) { for ( int i = 0; i < DIM; a.x[i] += b.x[i], ++i ); };
void operator -= ( cell &a, const cell &b ) { for ( int i = 0; i < DIM; a.x[i] -= b.x[i], ++i ); };
void operator *= ( cell &a, const double t ) { for ( int i = 0; i < DIM; a.x[i++] *= t );   };
void operator /= ( cell &a, const double t ) { for ( int i = 0; i < DIM; a.x[i++] /= t );   };
bool is_perp( const cell &a, const cell &b ) { return fabs((a,b))<0.01; };

double operator ^ ( const cell &a, const cell &b ) {
	double A = a.getlen(), B = b.getlen(),
		 		co = (a,b)/A/B;
	return acos(min((double)1.00,max(co,(double)-1.00)));
};

cell h[N],c[N],ZERO;
int V,n,belongsto[MAXV],seen[MAXQ],yes;
double d[MAXQ];
map<cell,int> s;

bool find_intersection( int idxm, int idxn, const cell &x, const cell &y, cell *res, bool is_great_circle ) {
	double aa,bb,na,nb,t_v,mid,b[2],sw,_a,_b,_c,_d,discr;
	int biggest = 0;
	cell w,m[2];
	m[0] = x, m[1] = y, w = m[0]*m[1];
	for ( int i = 1; i < DIM; ++i )
		if ( fabs(w[i]) > fabs(w[biggest]) )
			biggest = i;
	for ( int i = 0; i < 2; b[i] = (m[i],m[i]), ++i );
	if ( is_great_circle ) b[0] = 0;
	DBG && printf("CHECKING %d %d\n",idxm,idxn);
	if ( w == ZERO )
		return false ;
	sw = (w,w);
#define X(t) (biggest==0?(t):(biggest==1?((b[1]*m[0][2]-b[0]*m[1][2])+w[0]*(t))/w[1]:((b[0]*m[1][1]-b[1]*m[0][1])+w[0]*(t))/w[2]))
#define Y(t) (biggest==0?((b[0]*m[1][2]-b[1]*m[0][2])+w[1]*(t))/w[0]:(biggest==1?(t):((b[1]*m[0][0]-b[0]*m[1][0])+w[1]*(t))/w[2]))
#define Z(t) (biggest==0?((b[1]*m[0][1]-b[0]*m[1][1])+w[2]*(t))/w[0]:(biggest==1?((b[0]*m[1][0]-b[1]*m[0][0])+w[2]*(t))/w[1]:(t)))
#define f(t) (S(X(t))+S(Y(t))+S(Z(t))-1)
#define DX(t) (w[0]!=0?1:(w[1]!=0?(w[0]/w[1]:w[0]/w[2])))
#define DY(t) (w[0]!=0?(w[1]/w[0]:(w[1]!=0?1:w[1]/w[2])))
#define DZ(t) (w[0]!=0?(w[2]/w[0]:(w[1]!=0?w[2]/w[1]:1)))
#define df(t) (2*(X(t)*DX(t)+Y(t)*DY(t)+Z(t)*DZ(t)))
	if ( biggest == 0 ) {
		t_v = -((b[0]*m[1][2]-b[1]*m[0][2])*w[1]+(b[1]*m[0][1]-b[0]*m[1][1])*w[2])/sw;
		_b = 2*((b[0]*m[1][2]-b[1]*m[0][2])*w[1]+(b[1]*m[0][1]-b[0]*m[1][1])*w[2]);
		_a = sw, _c = S(b[0]*m[1][2]-b[1]*m[0][2])+S(b[1]*m[0][1]-b[0]*m[1][1])-S(1)*S(w[0]);
	}
	else if ( biggest == 1 ) {
		t_v = -((b[1]*m[0][2]-b[0]*m[1][2])*w[0]+(b[0]*m[1][0]-m[0][0]*b[1])*w[2])/sw;
		_b = 2*((b[1]*m[0][2]-b[0]*m[1][2])*w[0]+(b[0]*m[1][0]-m[0][0]*b[1])*w[2]);
		_a = sw, _c = S(b[1]*m[0][2]-b[0]*m[1][2])+S(b[0]*m[1][0]-m[0][0]*b[1])-S(1)*S(w[1]);
	}
	else {
		assert( w[2] != 0 );
		t_v = -((b[0]*m[1][1]-b[1]*m[0][1])*w[0]+(b[1]*m[0][0]-b[0]*m[1][0])*w[1])/sw;
		_b = 2*((b[0]*m[1][1]-b[1]*m[0][1])*w[0]+(b[1]*m[0][0]-b[0]*m[1][0])*w[1]);
		_a = sw, _c = S(b[0]*m[1][1]-b[1]*m[0][1])+S(b[1]*m[0][0]-b[0]*m[1][0])-S(1)*S(w[2]);
	}
	_d = S(_b)-4*(_a*_c);
	if ( !equal(_d,0) && _d < 0 ) return false ;
	if ( !equal(f(t_v),0) && f(t_v) > 0 ) return false ;
	/*
	 * searching the parabola's vertex t_v
	 */
	/*
	for(aa=-oo,bb=+oo;bb-aa>=tol;na=(2*aa+bb)/3.00,nb=(2*bb+aa)/3.00,f(na)<f(nb)?(bb=nb):(aa=na));
	t_v = (aa+bb)/2;
	*/
	/*
	assert( f(t_v+0.5) > f(t_v) );
	assert( f(t_v-0.5) > f(t_v) );
	assert( f(t_v+1) > f(t_v) );
	assert( f(t_v-1) > f(t_v) );
	if ( f(t_v) > 0 ) 
		return false ;
	*/
	DBG && printf("SURVIVED %d %d\n",idxm,idxn);
	/*
	if ( fabs(f(t_v)) < tol ) {
		res[0] = res[1] = cell(X(t_v),Y(t_v),Z(t_v));
		return true ;
	}
	*/
	if ( equal(_d,0) ) {
		res[0] = res[1] = cell(X(t_v),Y(t_v),Z(t_v));
		return true ;
	}
	discr = sqrt(_d);
	/*
	assert( f(t_v) < 0 );
	assert( f(-oo) > 0 );
	for(aa=-oo,bb=t_v;bb-aa>=1e-15;f(mid=(aa+bb)/2)>0?(aa=mid):(bb=mid));
	mid = bb;
	printf("mid = %lf, %lf\n",mid,f(mid));
	res[0] = cell(X(mid),Y(mid),Z(mid));
	res[1] = 2*cell(X(t_v),Y(t_v),Z(t_v))-res[0];
	*/
	mid = t_v - discr/(2*_a);
	/*
	if ( fabs(f(mid)) > 1e-3 )
		printf("Violation %lf %lf %lf %lf %lf %lf\n",mid,t_v,f(t_v),_a,f(mid),_d);
		*/
	/*assert(fabs(f(mid))<1e-3);*/
	// if ( !equal(f(mid),0) )
	//	printf("Violation %.8lf\n",f(mid));
	// assert( equal(f(mid),0) );
	res[0] = cell(X(mid),Y(mid),Z(mid));
	mid = t_v + discr/(2*_a);
	res[1] = cell(X(mid),Y(mid),Z(mid));
	/*
	assert( fabs(f(mid)) < tol );
	assert( fabs(f(2*t_v-mid)) < tol );
	*/
	/*
	for ( int i = 0; i < 2; ++i ) 
		for ( int j = 0; j < 2; ++j ) {
			if ( fabs((res[i],m[j])-b[j]) >= tol )
				printf("[%d] Perpendicularity violated %lf vs %lf\n",i,(res[i],m[j]),b[j]);
		}
	*/
	return true ;
};

vector<pair<int,double> > adj[MAXV];

bool covered( double left, double right, const vector<pair<double, double> > &e ) {
	for ( int i = 0; i < (int)e.size(); ++i )
		if ( leq(e[i].first,left) && leq(right,e[i].second) )
			return true ;
	return false ;
};

int parent[MAXV];
void dump( int x ) {
	if ( parent[x] != -1 )
		dump(parent[x]);
	printf("->%d",x+1);
};

int main() {
	int i,j,k,qr,cs = 0,x,y,dst;
	double hlen,full_tank,ll,rr,left,right,dw,fuel_left,nfuel,ans,ANG;
	cell tt[2];
#ifndef ONLINE_JUDGE
	//freopen("critical1288.in","r",stdin);
	freopen("1288.in","r",stdin);
#endif
	for (;2==scanf("%d %lf",&n,&D)&&n>0;) {
		printf("Case %d:\n",++cs);
		for ( ANG = D/R, i = 0; i < MAXV; ++i )
			for ( adj[i].clear(), j = i+1; j < MAXV; g[i][j] = g[j][i] = +oo, ++j );
		assert( ANG <= pi/2 );
		for ( s.clear(), V = 0, hlen = cos(ANG), i = 0; i < n; ++i ) {
			double phi,theta,t;
			scanf("%lf %lf",&phi,&theta);
			c[i] = cell(phi*pi/180.00,theta*pi/180.00), t = c[i].getlen();
			h[i] = c[i], h[i] /= t, h[i] *= hlen;
			if ( !s.count(c[i]) )
				s[c[i]] = V++;
		}
		assert( V == n );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) 
				if ( find_intersection(i+1,j+1,h[i],h[j],tt,false) ) {
					/*printf("Intersection found between %d and %d\n",i+1,j+1);*/
					g[i][j] = g[j][i] = min(c[i]^c[j],c[j]^c[i]);
					adj[i].push_back(make_pair(j,g[i][j]));
					adj[j].push_back(make_pair(i,g[i][j]));
					for ( k = 0; k <= 1; ++k )
						if ( !s.count(tt[k]) ) {
							belongsto[s[tt[k]] = V++] = BIT(i)|BIT(j);
							/*printf("[%d] Inserted (%.2lf,%.2lf,%.2lf)\n",V,tt[k][0],tt[k][1],tt[k][2]);*/
							g[i][V-1] = g[V-1][i] = g[j][V-1] = g[V-1][j] = ANG;
							adj[i].push_back(make_pair(V-1,ANG));
							adj[j].push_back(make_pair(V-1,ANG));
							adj[V-1].push_back(make_pair(i,ANG));
							adj[V-1].push_back(make_pair(j,ANG));
						}
				}
		for ( map<cell,int>::iterator it = s.begin(); it != s.end(); ++it )
			if ( 1 || it->second >= n )
				for ( map<cell,int>::iterator jt = s.begin(); jt != s.end(); ++jt )
					if ( (1 || jt->second >= n) && it->second != jt->second ) {
						if ( it->second >= n && jt->second >= n && belongsto[it->second] == belongsto[jt->second] ) {
							double aang = it->first^jt->first;
							adj[it->second].push_back(make_pair(jt->second,aang));
							continue ;
						}
						if ( it->second<n && jt->second>=n && ((belongsto[jt->second]>>it->second)&1) ) 
							continue ;
						if ( jt->second<n && it->second>=n && ((belongsto[it->second]>>jt->second)&1) ) 
							continue ;
#if DBG
						printf("On circle defined by (%.2lf,%.2lf,%.2lf)--(%.2lf,%.2lf,%.2lf) these points found:\n",\
							it->first.x[0],it->first.x[1],it->first.x[2],jt->first.x[0],jt->first.x[1],jt->first.x[2]);
#endif
						set<pair<double,double> > q;
						cell normale = jt->first*it->first;
						for ( q.clear(), i = 0; i < n; ++i )
							if ( find_intersection(it->second+1,jt->second+1,it->first*jt->first,h[i],tt,true) ) {
								if ( tt[0] == tt[1] ) continue ;
								ll = tt[0]^it->first, rr = tt[1]^it->first;
								if ( ((tt[0]*it->first),normale) < 0 )
									ll = 2*pi-ll;
								if ( ((tt[1]*it->first),normale) < 0 )
									rr = 2*pi-rr;
								/*
								assert( 0 <= ll && ll < 2*pi );
								assert( 0 <= rr && rr < 2*pi );
								*/
								if ( ll > rr ) swap(ll,rr);
								if ( leq(rr-ll,pi) )
									q.insert(make_pair(ll,rr));
								else
									q.insert(make_pair(-tol,ll)), q.insert(make_pair(rr,2*pi+tol));
							}
						DBG && puts("\n-------------------------------------\n");
						vector<pair<double,double> > e; e.clear();
						left = +oo, right = -oo;
						for ( set<pair<double,double> > :: iterator kt = q.begin(); kt != q.end(); ++kt ) {
							if ( kt->first > right ) {
								if ( left < +oo )
									e.push_back(make_pair(left,right));
								left = kt->first, right = kt->second;
							}
							else if ( kt->second > right )
								right = kt->second;
							else {
								assert( left <= kt->first && kt->second <= right );
							}
						}
						if ( left < +oo )
							e.push_back(make_pair(left,right));
						left = 0, right = (jt->first^it->first);
						if ( covered(left,right,e) ) {
							adj[it->second].push_back(make_pair(jt->second,(right-left)));
						}
						left = right, right = 2*pi-tol;
						if ( covered(left,right,e) )
							adj[it->second].push_back(make_pair(jt->second,(right-left)));
					}
		for ( x = 0; x < V; ++x )
			for ( i = 0; i < (int)adj[x].size(); ++i ) {
				y = adj[x][i].first;
				g[x][y] = min(g[x][y],adj[x][i].second);
			}
		/*
		for ( y = 0; y < V; ++y )
			if ( g[4][y] < +oo ) 
				printf("Distance to %d is %.2lf\n",y+1,g[4][y]*180/pi);
				*/
		for ( i = 0; i < V; ++i )
			for ( j = i+1; j < V; ++j )
				if ( g[i][j] != g[j][i] ) 
					hlen = min(g[i][j],g[j][i]), g[i][j] = g[j][i] = hlen;
		for ( k = 0; k < V; ++k )
			for ( x = 0; x < V; ++x )
				for ( y = 0; y < V; ++y ) 
					if ( g[x][k] < +oo && g[k][y] < +oo && g[x][k]+g[k][y]<g[x][y] ) 
						g[x][y] = g[x][k]+g[k][y];
		/*
		for ( i = 0; i < V; ++i )
			for ( j = i+1; j < V; ++j ) {
				if ( g[i][j] < +oo )
					printf("g[%d][%d] = %lf\n",i+1,j+1,g[i][j]);
				assert( g[x][y] == g[y][x] );
			}
			*/

		for ( scanf("%d",&qr); qr--; ) {
			scanf("%d %d %lf",&i,&j,&full_tank), --i, dst = --j, full_tank /= R;
			set<pair<double,int> > que;
			set<pair<double,int> >::iterator it;
			for ( k = 0; k < n; ++k ) d[k] = +oo;
			for ( que.clear(), parent[i] = -1, que.insert(make_pair(d[i]=0,i)); !que.empty(); )
				for ( it = que.begin(), x = it->second, que.erase(*it), y = 0; y < n && x != dst; ++y )
					if ( g[x][y] < +oo && leq(g[x][y],full_tank) )
						if ( d[y] > d[x]+g[x][y] )
							que.insert(make_pair(d[y]=d[x]+g[x][y],y)), parent[y] = x;
			if ( d[dst] < +oo ) {
				printf("%.3lf\n",d[dst]*R);
				// dump(dst);puts("");
			}
			else puts("impossible");
		}
	}
	return 0;
}

