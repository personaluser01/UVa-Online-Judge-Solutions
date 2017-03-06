/*
 * 1518. Train Delays
 * TOPIC: bellman-ford, math expectation
 * status: Accepted
 * NOTES: didn't get why we need to start from the end; also, printf("%g") is needed rather than printf("%lf")
 */
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#define N 0x800
#define MAXT 60
#define tol 1e-7
#include <climits>
#include <cfloat>
#define oo (DBL_MAX-0x400)
using namespace std;

const double infty = 1e100;
const double eps = 1e-10;
map<string,int> m;
double d[N],best[N][MAXT],mean_delay[N];
int n,connections,delay[N],dep_time[N],duration[N],x[N],y[N],src,dst,p[N];

int round_up( double x ) {
	int ix = (int)(x+tol);
	if ( fabs(x-ix) < tol )
		return ix;
	return ix+1;
}

bool is_greater( double x, double y ) {
	if ( fabs(x-y) < tol )
		return false ;
	return x > y;
}

int main() {
	int i,j,k,l,t,ts,expected_arrival;
	char a[0x40],b[0x40];
	bool flag;
	double w;
#ifndef ONLINE_JUDGE
	freopen("1518.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%s %s",a,b), m.clear();
		assert( strcmp(a,b) != 0 );
		src = m[string(a)] = 0, dst = m[string(b)] = 1;
		for ( n = 2, scanf("%d",&connections), l = 0; l < connections; ++l ) {
			scanf("%s %s %d %d %d %d",a,b,dep_time+l,duration+l,p+l,delay+l);
			mean_delay[l] = p[l]*(delay[l]+1.00)/200.00;
			if ( m.find(string(a)) == m.end() )
				m[string(a)] = n++;
			if ( m.find(string(b)) == m.end() )
				m[string(b)] = n++;
			x[l] = m[string(a)], y[l] = m[string(b)];
		}
		for ( t = 0; t < MAXT; best[dst][t++] = 0 );
		for ( t = 0; t < MAXT; ++t )
			for ( i = 0; i < n; ++i )
				if ( i != dst ) 
					best[i][t] = infty;
		for ( flag = true; flag; )
			for ( flag = false, i = 0; i < connections; ++i ) {
				double tm = (1-p[i]/100.0)*(duration[i]+best[y[i]][(dep_time[i]+duration[i])%MAXT]);
				for ( j = 1; j <= delay[i]; ++j )
					tm += p[i]/100.0/delay[i]*(duration[i]+j+best[y[i]][(dep_time[i]+duration[i]+j)%MAXT]);
				if ( tm < eps*infty && tm < best[x[i]][dep_time[i]]-eps ) {
					best[x[i]][dep_time[i]] = tm, flag = true ;
					for ( j = 0; j < MAXT; ++j )
						if ( best[x[i]][dep_time[i]]+((MAXT+dep_time[i]-j)%MAXT) < best[x[i]][j]-eps )
							best[x[i]][j] = best[x[i]][dep_time[i]]+((MAXT+dep_time[i]-j)%MAXT);
				}
			}
		for ( w = infty, t = 0; t < MAXT; ++t )
			if ( best[src][t] < w )
				w = best[src][t];
		if ( w < infty )
			printf("%.10g\n",w);
		else puts("IMPOSSIBLE");
	}
	return 0;
}

