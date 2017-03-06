/*
 * 1070. Conveyor Belt
 * TOPIC: geometry, graphs, rotations, vectors, trigonometry
 * status: in progress
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
#define tol 1e-9
#define S(x) ((x)*(x))
#define DIM 3
#define N 21
#define Q (1<<10)
#define BIT(k) (1ULL<<(k))
#define L(k) ((k)&((~(k))+1ULL))
#define DB 0
using namespace std;

const double pi = 2*acos(0.00);
char which[1<<N];

struct cell {
	double x,y,L;
	cell() { x=y=L=0; }
	cell( double xx, double yy ) { x = xx, y = yy, L = sqrt(x*x+y*y); };
};
cell operator + ( const cell &a, const cell &b ) {
	cell r(a.x+b.x,a.y+b.y);
	return r;
};
cell operator - ( const cell &a, const cell &b ) {
	cell r(a.x-b.x,a.y-b.y);
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

struct node {
	int idx;
	double phi;
	node() {};
	node( int id, double t ) { idx = id, phi = t; };
};

node make_node( int id, double t ) {
	node r(id,t);
	return r;
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

bool operator < ( const node &a, const node &b ) {
	if ( a.idx == b.idx ) 
		return a.phi < b.phi;
	return a.idx < b.idx;
};

cell c[N],tangent[N][N],unit(1,0),h[N][N];
int n,V,*ptr,tt[Q],seen[Q],yes;
double r[N],D,best;
bool iscc[N];
map<node,int> m;
vector<pair<int,double> > adj[Q];
vector<int> lst[N],path;
node vertex[Q];
pair<cell,cell> T[Q][Q];

int ins( node p ) {
	if ( m.count(p) ) return m[p];
	adj[m[p] = V++].clear(), vertex[V-1] = p;
	lst[p.idx].push_back(V-1);
	return V-1;
};

bool approx( double a, double b ) { return fabs(a-b) < tol; };
bool is_perp( const cell &a, const cell &b ) { return approx((a,b),0); };

double dist( const cell &p, const cell &x, const cell &y ) {
	double a,b,na,nb,k;
	cell m = y-x;
#if 0
	for ( a = 0, b = 1; fabs(b-a) > tol; ) {
		na = (2*a+b)/3.00, nb = (2*b+a)/3.00;
		cell A = x+m*na, B = x+m*nb;
		if ( (A-p,A-p) < (B-p,B-p) )
			b = nb;
		else a = na;
	};
	return (p-x-m*((a+b)/2)).L;
#else
	double tau = (k = (m,p-x))/(m,m);
	if ( 0 <= tau && tau <= 1 )
		return sqrt(S(tau)*(m,m) - 2*tau*k + (x-p,x-p));
	return sqrt(min(S(-1)*(m,m)-2*0*k+(x-p,x-p),S(1)*(m,m)-2*1*k+(x-p,x-p)));
#endif
};

bool operator == ( const cell &a, const cell &b ) {
	return approx(a.x,b.x) && approx(a.y,b.y);
};

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

bool bah[N][N][N][N],gr[N][N];
int examined[N][N][N][N],indeed,cnt,id[N][N];
unsigned int used,aa[N];

bool intersection( const pair<cell,cell> &p, const pair<cell,cell> &q ) {
	pair<pair<cell,cell>,pair<cell,cell> > r = make_pair(p,q);
#define CH(i) {if(i==0) u|=1; else if (i==1) u|=2; else u |= 4;}
	if ( on_segment(p.first,q) || on_segment(p.second,q) || on_segment(q.first,p) || on_segment(q.second,p) )
		return true;
	cell a = p.first, b = p.second, c = q.first, d = q.second;
	int i = ccw(a,c,b), j = ccw(c,b,d), k = ccw(b,d,a), t = ccw(d,a,c), u = 0;
	CH(i); CH(j); CH(k); CH(t);
	return !(u&(u-1));
};

bool conflict( int x, int y ) {
	int px = x, py = y,nx,ny;
	x = vertex[x].idx, y = vertex[y].idx;
	for ( int i = 0; i < ptr-tt; ++i ) {
		nx = vertex[tt[i]&1023].idx, ny = vertex[tt[i]>>10].idx;
		if ( examined[x][y][nx][nx] == indeed ) {
			if ( bah[x][y][nx][ny] )
				return true ;
			continue ;
		}
		examined[x][y][nx][ny] = examined[nx][ny][x][y] = indeed;
		if ( bah[x][y][nx][ny] = bah[nx][nx][x][y] = intersection(T[px][py],T[tt[i]&1023][tt[i]>>10]) ) 
			return true ;
	}
	return false ;
};

double rot( double a, double b, bool f ) {
	if ( approx(a,b) ) return 0;
	if ( f ) {
		if ( b >= a ) return b-a;
		return b+2*pi-a;
	}
	return rot(b,a,f^1);
};

void ssp( const int dst, int t, int x, double cost ) {
	unsigned int v,ll;
	if ( cost >= best ) return ;
	if ( t == dst ) {
		best = cost;
#if DB
		path.clear();
		for ( int i = 0; i < ptr-tt; ++i )
			path.push_back(tt[i]);
#endif
		return ;
	};
	if ( !gr[t][dst] ) return ;
	int i,j,k,l,xx,y;
	for ( v = ~used & aa[t]; v && (ll=which[L(v)])>=0; v &= ~L(v) )
	//for ( i = 0; i < (int)lst[t].size(); ++i )
			for ( xx = (id[t][ll]&1023), l = 0; l < (int)adj[xx].size(); ++l ) {
				y = adj[xx][l].first;
				if ( seen[vertex[y].idx] == yes || conflict(xx,y) ) continue ;
				seen[vertex[y].idx] = yes, *ptr++ = xx|(y<<10);
				// assert( vertex[y].idx == ll );
				used |= BIT(vertex[y].idx);
				ssp(dst,vertex[y].idx,y,cost+r[t]*rot(vertex[x].phi,vertex[xx].phi,iscc[t])+adj[xx][l].second);
				used &= ~BIT(vertex[y].idx);
				--ptr, seen[vertex[y].idx] = 0;
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
		aa[i] = 0, lst[i].clear(), scanf("%lf %lf %lf %s",&c[i].x,&c[i].y,&r[i],tmp), iscc[i]=(1[tmp]=='C');
	assert( 3 == scanf("%d %d %lf",&src,&dst,&D) );
	for ( m.clear(), V = 0, i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			if ( i == j ) { gr[i][j] = true; continue ; }
			gr[i][j] = false ;
			h[i][j] = c[j]-c[i];
			if ( iscc[i] == iscc[j] ) {
				if ( S(h[i][j].L)-S(r[i]-r[j]) >= D*D ) continue ;
				g[i][j] = sqrt(S(h[i][j].L)-S(r[i]-r[j]));
				tau = atan((r[j]-r[i])/g[i][j]);
				tangent[i][j] = ((h[i][j]%(iscc[i]?-tau:tau))/h[i][j].L)*g[i][j];
				if ( tangent[i][j].L >= D ) continue ;
				shift = ((tangent[i][j]%(iscc[i]?-pi/2:pi/2))/tangent[i][j].L)*r[i];
				u = c[i]+shift+tangent[i][j];
				// assert( !inside(i,j) );
				// assert( !inside(j,i) );
				// assert( on_circle(i,c[i]+shift) );
				// assert( is_perp(u-c[j],tangent[i][j]) );
				// assert( on_circle(j,u) );
				// assert( approx((u-c[j]).L,r[j]) );
				for ( ok = true, k = 0; k < n && ok; ++k )
					if ( k != i && k != j && dist(c[k],c[i]+shift,u) < r[k] )
						ok = false ;
				if ( ok ) {
					x = ins(make_node(i,unit^shift));
					y = ins(make_node(j,unit^(u-c[j])));
					adj[x].push_back(make_pair(y,g[i][j])), T[x][y] = make_pair(c[i]+shift,u), gr[vertex[x].idx][vertex[y].idx] = true;
					aa[i] |= BIT(j), id[i][j] = x|(y<<10);
				}
				continue ;
			}
			if ( S(h[i][j].L)-S(r[i]+r[j]) >= D*D ) continue ;
			g[i][j] = sqrt(S(h[i][j].L)-S(r[i]+r[j]));
			o = r[i]/(r[i]+r[j]);
			mid = c[i]+(c[j]-c[i])*o;
			tau = asin(r[i]/(o*h[i][j].L));
			u = c[i]-mid, leg = o*h[i][j].L*cos(tau);
			v = (u%(iscc[i]?tau:-tau))/u.L*leg;
			u = c[j]-mid, leg = (1-o)*h[i][j].L*cos(tau);
			w = (u%(iscc[j]?-tau:tau))/u.L*leg;
			tangent[i][j] = w-v;
			// assert( approx(tangent[i][j].L,g[i][j]) );
			// assert( approx(w^v,pi) );
			if ( tangent[i][j].L >= D ) continue ;
			/*
			assert( on_circle(i,mid+v) );
			assert( on_circle(j,mid+w) );
			assert( is_perp(mid+v-c[i],v) );
			assert( is_perp(mid+w-c[j],w) );
			*/
			for ( ok = true, k = 0; k < n && ok; ++k )
				if ( k != i && k != j && dist(c[k],mid+v,mid+w) < r[k] )
					ok = false ;
			if ( ok ) {
				x = ins(make_node(i,unit^(mid+v-c[i])));
				y = ins(make_node(j,unit^(mid+w-c[j])));
				adj[x].push_back(make_pair(y,tangent[i][j].L)), T[x][y] = make_pair(mid+v,mid+w), gr[vertex[x].idx][vertex[y].idx] = true ;
				aa[i] |= BIT(j), id[i][j] = x|(y<<10);
			}
		}
#if DB
	puts("");
	for ( i = 0; i < V; ++i ) {
		printf("vertex[%d] = (%c,%.2lf): ",i,vertex[i].idx+'A',vertex[i].phi*180/pi);
		for ( j = 0; j < adj[i].size(); ++j ) {
			k = adj[i][j].first;
			double dd = adj[i][j].second;
			printf("vertex[%d] = (%c,%.2lf), dist %.2lf, ",k,vertex[k].idx+'A',vertex[k].phi*180/pi,dd);
		}
		puts("");
	}
#endif
	for ( k = 0; k < n; ++k )
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( gr[i][k] && gr[k][j] ) gr[i][j] = true;
	if ( !gr[src][dst] ) goto nx;
	ptr = tt, best = (1<<29), seen[src] = ++yes, ++indeed;
	for ( cnt = 0, i = 0; i < (int)lst[src].size(); ++i )
		used |= BIT(src), ssp(dst,src,lst[src][i],0), used &= ~BIT(src);
   	seen[src] = 0;
	if ( src == dst || best == (1<<29) )
		nx:
		puts("Cannot reach destination shaft");
	else {
		double ans = nearest(best);
		if ( fabs(ans-(int)ans) < tol )
			printf("length = %.lf\n",ans+(double)1e-12);
		else
			printf("length = %g\n",(double)ans);
#if DB
		for ( i = 0; i < path.size(); ++i ) {
			x = path[i]&1023; y = path[i]>>10;
			if ( i && vertex[x].idx == vertex[path[i-1]>>10].idx )
				printf("rotation to %.2lf %s\n",rot(vertex[path[i-1]>>10].phi,vertex[x].phi,iscc[vertex[x].idx])*180/pi,iscc[vertex[x].idx]?"counter":"wise");
			printf("(%c,%.2lf) --> (%c,%.2lf)\n",vertex[x].idx+'A',vertex[x].phi*180/pi,vertex[y].idx+'A',vertex[y].phi*180/pi);
		}
#endif
	}
};

int main() {
	int cs = 0;
#ifndef ONLINE_JUDGE
	freopen("1070.in","r",stdin);
#endif
	for ( cs = 0; cs < N; which[BIT(cs)] = cs, ++cs );
	for( cs = 0; 1==scanf("%d",&n)&&n>0;printf("Case %d: ",++cs), solve());
	return 0;
}

