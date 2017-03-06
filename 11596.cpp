/*
 * 11596. Convex Orthogonal Polyons
 * TOPIC: maths
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <set>
#define tol 1e-9
typedef long long i64;
using namespace std;
#define N 0x400

long double an,n,SQ,p0,d,sd;
int len;
i64 k,m,b0,cs,dv[N],a0;
set<i64> s;

bool plausible( i64 b0, i64 alpha, i64 beta, i64 a0 ) {
	i64 x,y;
	/*
	if ( alpha*beta == a0 )
		return true;
	for ( int i = 0; i < len; ++i )
		if ( dv[i] < alpha && (b0-a0)/dv[i] < beta || dv[i] < beta && (b0-a0)/dv[i] < alpha )
			return true;
	return false;
	*/
	return alpha*beta == a0 || a0/alpha+((a0%alpha)?1:0) <= beta || a0/beta+((a0%beta)?1:0) <= alpha;
}

int main() {
	while ( 3 == scanf("%lld %Lf %lld",&a0,&an,&b0) ) {
		if ( !a0 && fabs(an) < tol && !b0 ) break ;
		// printf("Case %lld: ",++cs);
		if ( an<=0||b0<=0||a0<=0 || an<a0 || b0<a0 ) { puts("-1\n"); continue;}
		for ( len = 0, k = 1; k*k <= (b0-a0); ++k )
			if ( (b0-a0)%k == 0 )
				dv[len++] = k;
		for ( s.clear(), k = 1; k*k <= b0; ++k ) {
			if ( b0%k ) continue ;
			m = b0/k;
			// if ( !plausible(b0,k,m,a0) ) continue ;
			if ( k+m-1 > a0 ) continue ;
			p0 = 2*(k+m);
			d = ((long double)k*k)+((long double)m*m)+((long double)2*b0)+4*(an-a0);
			sd = sqrt(d);
			if ( fabs(sd-((i64)(sd))) >= tol )
				continue ;
			if ( fabs(sd*sd-d) >= tol ) continue ;
			if ( (((i64)(sd-(k+m)))%4) ) continue ;
			// printf("k = %lld, m = %lld, sd = %Lf, d = %Lf, diff = %Lf\n",k,m,sd,d,d-sd*sd);
			s.insert(((i64)(sd-(k+m)))/4);
		}
		if ( !s.size() ) {
			puts("-1\n");
			continue ;
		}
		k = 0;
		// printf("%lld %.Lf %lld, ",a0,an+tol,b0);
		for ( set<i64> :: iterator it = s.begin(); it != s.end(); ++it ) 
			  // if ( ++k > 1 ) printf(" %lld",*it);
			 // else printf("%lld",*it);
			 printf("%lld\n",*it);
		 //puts("\n");
		puts("");
	}
	return 0;
}

