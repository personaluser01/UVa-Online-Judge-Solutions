/*
 * 1216. The Bug Sensor Problem
 * TOPIC: graphs, binary search
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cmath>
#define N  0x800
#define tol 1e-9
typedef long long i64;

double max( double x, double y ) { return x<y?y:x; }

int ts,m,n,yes;
bool g[N][N],seen[N];
double d[N][N],x[N],y[N];
double S( double x ) { return x*x; }
	void dfs( int x ) {
		int y;
		for ( seen[x] = true, y = 0; y < n; ++y )
			if ( g[x][y] && !seen[y] ) dfs(y);
	}
	int f( double lim ) {
		int i,j,k,cc;
		for ( ++yes, i = 0; i < n; ++i )
			for ( seen[i] = false, g[i][i] = true, j = i+1; j < n; ++j )
				g[i][j] = g[j][i] = (d[i][j]<=lim);
		for ( cc = 0, k = 0; k < n; ++k )
			if ( !seen[k] ) {
				dfs(k); ++cc;
			}
		return cc;
	}
	void go() {
		int i,j,k;
		double good,bad,mid;
		for ( scanf("%d",&ts); ts-->0; ) {
			for ( scanf("%d",&m), n = 0; scanf("%lf",x+n) && x[n] != -1; scanf("%lf",&y[n]), ++n );
			if ( f(0) >= m ) {
				puts("0");
				continue ;
			}
			for ( bad = good = 0, i = 0; i < n; ++i )
				for ( j = i+1; j < n; ++j )
					good = max(good,d[i][j]=d[j][i]=sqrt(S(x[i]-x[j])+S(y[i]-y[j])));
			for(;fabs(good-bad)>=tol;)
				if ( f(mid=(good+bad)/2)<=m )
					good=mid;
				else bad=mid;
			printf("%.lf\n",(ceil(bad))+tol);
		}
	}

int main() {
	go();
	return 0;
}


