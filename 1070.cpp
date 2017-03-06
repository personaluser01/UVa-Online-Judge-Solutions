
/*
 * 1070. Conveyor Belt
 * TOPIC: geometry, graphs, rotations, vectors, trigonometry, maths, shortest path
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
#include <vector>
#define tol 1e-10
#define S(x) ((x)*(x))
#define DIM 3
#define N 21
#define Q (1<<10)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define DB 0
#define MAXE (N*N)
typedef unsigned long long u64;
using namespace std;
bool approx( double a, double b ) { return fabs(a-b) < tol; };
struct cell {
	double x,y,L;
	cell() { x=y=L=0; }
	cell( double xx, double yy ) { x = xx, y = yy, L = sqrt(x*x+y*y); };
};
cell operator - ( const cell &a, const cell &b ) {
	cell r(a.x-b.x,a.y-b.y);
	return r;
};

const double pi = 2*acos(0.00);
char which[BIT(N)];
int cs,to[MAXE],E,parent[N],n,V,*ptr,tt[Q],seen[Q],yes,edge_id[N][N],examined[Q][Q],indeed;
bool bah[Q][Q],gr[N][N],iscc[N];
pair<cell,cell> T[MAXE];
cell c[N],tangent[N][N],unit(1,0),h[N][N];
double r[N],D,best,_alpha[MAXE],beta[MAXE],cost[MAXE];
vector<int> path;
unsigned int adj[N];

int add_arcs( int x, int y, double a, double b, pair<cell,cell> e ) {
	int i = E++;
	assert( i < MAXE && i < Q );
	assert( !((adj[x]>>y)&1) );
	to[i] = y, _alpha[i] = a, beta[i] = b, T[i] = e, cost[i] = tangent[x][y].L;
	edge_id[x][y] = i, adj[x] |= BIT(y);
	gr[x][y] = true ;
	return i;
};

cell operator + ( const cell &a, const cell &b ) {
	cell r(a.x+b.x,a.y+b.y);
	return r;
};
double operator , ( const cell &a, const cell &b ) { return a.x*b.x+a.y*b.y; };
double operator * ( const cell &a, const cell &b ) { return a.x*b.y-a.y*b.x; };
cell operator * ( const cell &a, const double &t ) {
	cell r(a.x*t,a.y*t);
	return r;
};
cell operator / ( const cell &a, const double t ) {
	cell r(a.x/t,a.y/t);
	return r;
};
bool operator < ( const cell &a, const cell &b ) {
	if ( fabs(a.x-b.x) < tol ) return a.y<b.y;
	return a.x<b.x;
};

double operator ^ ( const cell &a, const cell &b ) {
	double co = (a,b)/a.L/b.L, si = (a*b)/a.L/b.L;
	if ( fabs(co-1.00) < tol )
		return 0;
	if ( fabs(co+1.00) < tol )
		return pi;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
};

cell operator % ( const cell &a, double t ) {
	double c = cos(t), s = sin(t);
	cell r(a.x*c-a.y*s,a.x*s+a.y*c);
	return r;
};

bool is_perp( const cell &a, const cell &b ) { return approx((a,b),0); };

double dist( const cell &p, const cell &x, const cell &y ) {
	cell m = y-x;
	double k,tau;
	tau = (k = (m,p-x))/(m,m);
	if ( 0 <= tau && tau <= 1 )
		return sqrt(S(tau)*(m,m) - 2*tau*k + (x-p,x-p));
	return sqrt(min(S(0)*(m,m)-2*0*k+(x-p,x-p),S(1)*(m,m)-2*1*k+(x-p,x-p)));
};

bool operator == ( const cell &a, const cell &b ) { return approx(a.x,b.x) && approx(a.y,b.y); };
bool on_segment( const cell &x, const pair<cell,cell> &t ) {
	if ( x == t.first || x == t.second ) return true ;
	return approx((x-t.first)*(x-t.second),0) && ((x-t.first),(x-t.second)) < 0; 
};
int ccw( const cell &a, const cell &b, const cell &c ) {
	cell u=b-a, v=c-a;
	double s=u*v;
	if ( approx(s,0) ) return 0;
	return s<0?-1:1;
};

bool intersection( const pair<cell,cell> &p, const pair<cell,cell> &q ) {
#define CH(i) {if(i==0) u|=1; else if (i==1) u|=2; else u |= 4;}
	if ( on_segment(p.first,q) || on_segment(p.second,q) || on_segment(q.first,p) || on_segment(q.second,p) )
		return false;
	cell a = p.first, b = p.second, c = q.first, d = q.second;
	int i = ccw(a,c,b), j = ccw(c,b,d), k = ccw(b,d,a), t = ccw(d,a,c), u = 0;
	CH(i); CH(j); CH(k); CH(t);
	return !(u&(u-1));
};

bool conflict( int edge_id ) {
	for ( int i = 0; i < ptr-tt; ++i ) {
		if ( examined[edge_id][tt[i]] == indeed ) {
			if ( bah[edge_id][tt[i]] )
				return true ;
			continue ;
		}
		examined[edge_id][tt[i]] = examined[tt[i]][edge_id] = indeed;
		if ( bah[edge_id][tt[i]] = bah[tt[i]][edge_id] = intersection(T[edge_id],T[tt[i]]) )
			return true ;
	}
	return false ;
};

double rot( double a, double b, bool f ) {
	if ( approx(pi,a) && approx(b,0) || approx(b,pi) && approx(a,0) ) return 0;
	if ( approx(a,b) ) return 0;
	if ( f ) {
		if ( b >= a )
			return b-a;
		return b+2*pi-a;
	}
	return rot(b,a,f^1);
};

void ssp( const int dst, int x, double weight, unsigned int used ) {
	unsigned int u,v,i,j,y;
	int k;
	double w;
	if ( weight > best || !gr[x][dst] ) return ;
	if ( x == dst ) {
		best = weight;
		return ;
	};
	for ( u = (~used)&adj[x]; u && (i=which[L(u)]) >= 0; u &= ~L(u) ) {
		k = edge_id[x][i], y = to[k];
		assert( i==y );
		if ( conflict(k) ) 
			continue ;
		*ptr++ = k;
		if ( parent[x] == -1 ) w = 0;
		else w = r[x]*rot(beta[parent[x]],_alpha[k],iscc[x]);
		parent[y] = k, ssp(dst,y,weight+w+cost[k],used|BIT(y));
		--ptr;
	}
};

bool on_circle( int i, cell p ) { return approx((c[i]-p,c[i]-p),S(r[i])); };
double nearest( double x ) { return (int)(100*(x+0.005))/100.00; };
bool inside( int i, int j ) { return h[i][j].L <= max(r[j],r[i]); }

void solve() {
	int i,j,k,src,dst,x,y;
	char tmp[0x10];
	double g[N][N],tau,o,leg;
	bool ok;
	cell shift,u,v,w,mid;
	for ( i = 0; i < n; ++i )
		adj[i] = 0, scanf("%lf %lf %lf %s",&c[i].x,&c[i].y,&r[i],tmp), iscc[i]=(1[tmp]=='C');
	assert( 3 == scanf("%d %d %lf",&src,&dst,&D) );
	for ( E = 0, i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			if ( i == j ) { gr[i][j] = true; continue ; }
			gr[i][j] = false ;
			h[i][j] = c[j]-c[i];
			if ( iscc[i] == iscc[j] ) {
				if ( S(h[i][j].L)-S(r[i]-r[j]) >= S(D)+tol ) continue ;
				g[i][j] = sqrt(S(h[i][j].L)-S(r[i]-r[j]));
				tau = atan((r[j]-r[i])/g[i][j]);
				tangent[i][j] = ((h[i][j]%(iscc[i]?-tau:tau))/h[i][j].L)*g[i][j];
				if ( tangent[i][j].L >= D+tol ) continue ;
				shift = ((tangent[i][j]%(iscc[i]?-pi/2:pi/2))/tangent[i][j].L)*r[i];
				u = c[i]+shift+tangent[i][j];
#if DB
				assert( on_circle(i,c[i]+shift) );
				assert( is_perp(u-c[j],tangent[i][j]) );
				assert( on_circle(j,u) );
				assert( approx((u-c[j]).L,r[j]) );
#endif
				for ( ok = true, k = 0; k < n && ok; ++k )
					if ( k != i && k != j ) {
						double dd = dist(c[k],c[i]+shift,u);
						if ( approx(dd,r[k]) || dd <= r[k] ) 
							ok = false;
					}
				if ( ok ) 
					add_arcs(i,j,unit^shift,unit^(u-c[j]),make_pair(c[i]+shift,u));
				continue ;
			}
			if ( S(h[i][j].L)-S(r[i]+r[j]) >= S(D)+tol ) continue ;
			g[i][j] = sqrt(S(h[i][j].L)-S(r[i]+r[j]));
			o = r[i]/(r[i]+r[j]);
			mid = c[i]+(c[j]-c[i])*o;
			tau = asin(r[i]/(o*h[i][j].L));
			u = c[i]-mid, leg = o*h[i][j].L*cos(tau);
			v = (u%(iscc[i]?tau:-tau))/u.L*leg;
			// v = (u%(iscc[i]?-tau:tau))/u.L*leg;
			u = c[j]-mid, leg = (1-o)*h[i][j].L*cos(tau);
			w = (u%(iscc[j]?-tau:tau))/u.L*leg;
			// w = (u%(iscc[j]?tau:-tau))/u.L*leg;
			tangent[i][j] = w-v;
#if DB
			assert( approx(w^v,pi) );
			assert( approx(tangent[i][j].L,g[i][j]) );
#endif
			if ( tangent[i][j].L >= D+tol ) continue ;
#if DB
			assert( on_circle(i,mid+v) );
			assert( on_circle(j,mid+w) );
			assert( is_perp(mid+v-c[i],v) );
			assert( is_perp(mid+w-c[j],w) );
#endif
			for ( ok = true, k = 0; k < n && ok; ++k )
				if ( k != i && k != j ) {
					double dd = dist(c[k],mid+v,mid+w);
					if ( approx(dd,r[k]) || dd <= r[k] ) 
						ok = false ;
				}
			if ( ok ) 
				add_arcs(i,j,unit^(mid+v-c[i]),unit^(mid+w-c[j]),make_pair(mid+v,mid+w));
		}
	for ( k = 0; k < n; ++k )
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( gr[i][k] && gr[k][j] )
					gr[i][j] = true;
	++indeed, ptr = tt, best = (1<<29), parent[src] = -1, ssp(dst,src,0,BIT(src));
	// printf("src = %c, dst = %c\n",src+'A',dst+'A');
	if ( src == dst || approx(best,(1<<29)) ) 
		puts("Cannot reach destination shaft");
	else {
		double ans = nearest(best);
		if ( fabs(ans-(int)ans) < tol )
			printf("length = %.lf\n",ans+(double)1e-12);
		else
			printf("length = %g\n",(double)ans);
		/*
		printf("[%c]\n",src+'A');
		for ( i = 0; i < path.size(); ++i ) {
			printf("[%c] %.2lf %.2lf\n",to[path[i]]+'A',_alpha[path[i]]*180/pi,beta[path[i]]*180/pi);
			printf("\\draw (%lf,%lf) -- (%lf,%lf);\n",T[path[i]].first.x/10.00,T[path[i]].first.y/10.00,T[path[i]].second.x/10.00,T[path[i]].second.y/10.00);
		}
		*/
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("1070.in","r",stdin);
#endif
	for ( cs = 0; cs < N; which[BIT(cs)] = cs, ++cs );
	for( cs = 0; 1==scanf("%d",&n)&&n>0;printf("Case %d: ",++cs), solve());
	return 0;
}

