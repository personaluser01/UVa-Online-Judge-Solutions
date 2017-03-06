/*
 * 13046. Bus Collisions
 * TOPIC: diophantine equations
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define tol (long double)(1e-13)
#define N 0x400
using namespace std;

struct cell {
	long double x[2];
	cell( long double a, long double b ) { 0[x] = a, 1[x] = b; };
	cell() { 0[x]=1[x]=0; };
	long double operator [] ( int i ) const { return x[i]; };
};

bool operator < ( const cell &a, const cell &b ) {
	return a[0]<b[0]||a[0]==b[0]&&a[1]<b[1];
}
bool operator == ( const cell &a, const cell &b ) {
	return !(a<b||b<a);
}

cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1]); }
cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1]); }
cell operator * ( const cell &a, const long double &t ) { return cell(a[0]*t,a[1]*t); }
cell operator / ( const cell &a, const long double &t ) { return cell(a[0]/t,a[1]/t); }

int m,n;
long double A[N],B[N];
cell a[N],b[N];

bool intersect( cell &a, cell &b, cell &p, cell &q, cell &res ) {
	if ( a == p || a == q ) { res = a; return true; }
	if ( b == p || b == q ) { res = b; return true; }
	cell m = b-a, n = q-p, k = p-a;
	long double det = -m[0]*n[1]+m[1]*n[0];
	if ( fabs(det) < tol ) {
		return false ;
	}
	long double dt = -k[0]*n[1]+k[1]*n[0], dtau = m[0]*k[1]-m[1]*k[0];
	dt /= det; dtau /= det;
	if ( 0 <= dt && dt <= 1 && 0 <= dtau && dtau <= 1 ) {
		res = a+m*dt;
		return true ;
	}
	return false ;
}

int gcd( int x, int y ) { return !y?x:gcd(y,x%y); };

int to_int( long double x ) {
	int dx = (int)x,
		ux = dx+1;
	return fabs(x-dx)<fabs(ux-x)?dx:ux;
}

bool is_int( long double x ) { return fabs(to_int(x)-x)<tol; };

void ext_euclid( int a, int b, int c, int *x0, int *y0 ) { !b?(*x0=c/a,*y0=0):(ext_euclid(b,a%b,c,y0,x0),*y0-=(*x0)*(a/b)); }

void solve( int a, int b, int c, int *x, int *y ) {
	/* ax+by = c */
	ext_euclid(a,b,c,x,y);
}

vector<cell> u,v;

int main() {
	int i,j,k,cs = 0,ts,l,t,P,pa,pb,d,z,PA,PB,tau,len;
	long double ta,tb,T,w,x,y;
	cell ans,res,dv;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d: ",++cs);
		u.clear(), v.clear();
		for ( scanf("%d",&m), i = 0; i < m; ++i ) 
			scanf("%Lf %Lf",a[i].x,a[i].x+1);
		for ( scanf("%d",&n), i = 0; i < n; ++i )
			scanf("%Lf %Lf",b[i].x,b[i].x+1);
		a[m] = a[0], b[n] = b[0];
		for ( u.push_back(a[0]), i = 1; i <= m; ++i ) {
			dv = a[i]-a[i-1];
			len = fabs(dv[0])+fabs(dv[1]);
			dv = dv/len;
			for ( k = 0; k < len; ++k ) 
				u.push_back(a[i-1]+dv*k);
		}
		for ( v.push_back(b[0]), i = 1; i <= n; ++i ) {
			dv = b[i]-b[i-1];
			len = fabs(dv[0])+fabs(dv[1]);
			dv = dv/len;
			for ( k = 0; k < len; ++k )
				v.push_back(b[i-1]+dv*k);
		}
		for ( m = 0, i = 0; i < (int)u.size(); a[m++] = u[i++] );
		a[m] = a[0];
		for ( n = 0, j = 0; j < (int)v.size(); b[n++] = v[j++] );
		b[n] = b[0];
		for ( A[0] = 0, i = 1; i <= m; ++i )
			A[i] = A[i-1]+fabs(a[i][0]-a[i-1][0])+fabs(a[i][1]-a[i-1][1]);
		for ( B[0] = 0, i = 1; i <= n; ++i )
			B[i] = B[i-1]+fabs(b[i][0]-b[i-1][0])+fabs(b[i][1]-b[i-1][1]);
		d = gcd(pa=A[m],pb=B[n]);
		PA = pa/d, PB = pb/d;
		for ( T = (1<<29), i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j ) {
				if ( intersect(a[i],a[i+1],b[j],b[j+1],res) ) {
					// printf("%Lf %Lf\n",res[0],res[1]);
					x = A[i]+fabs(res[0]-a[i][0])+fabs(res[1]-a[i][1]);
					y = B[j]+fabs(res[0]-b[j][0])+fabs(res[1]-b[j][1]);
					if ( !is_int(y-x) ) continue ;
					z = to_int(y-x);
					if ( z%d ) continue ;
					z /= d;
					solve(PA,-PB,z,&k,&l);
					assert( PA*k - PB*l == z );
					for(tau=(int)(max(-k/PB,-l/PA)+1e-13);tau*PB+k<0||tau*PA+l<0;++tau);
					ta = x/d+(tau*PB+k)*PA;
					tb = y/d+(tau*PA+l)*PB;
					// printf("%Lf, %Lf diff = %.8Lf\n",ta,tb,ta-tb);
					assert( fabs(ta-tb) < 1e-9 );
					if ( ta < T ) T = ta, ans = res;
				}
			}
		if ( T == (1<<29) ) 
			puts("No Collision");
		else 
			printf("%d %d\n",(int)(ans[0]+1e-13),(int)(ans[1]+1e-13));
	}
	return 0;
}

