/*
 * 12197. Trick or Treat
 * TOPIC: ternary search
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N (1<<16)
using namespace std;
#define S(x) ((x)*(x))
#define oo (1LL<<28)
#include <cmath>
#define tol 1e-12

pair<long double,long double> v[N];
int n;

long double f( long double t ) {
	long double w = -oo;
	for ( int i = 0; i < n; ++i )
		w = max(w,S(v[i].first-t)+S(v[i].second));
	return w;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("12197.in","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && n > 0; ) {
		for ( i = 0; i < n; scanf("%Lf %Lf",&v[i].first,&v[i].second), ++i );
		long double a,b,na,nb,t;
		for ( a = -oo, b = +oo; fabs(b-a) >= tol; ) {
			na = (2*a+b)/3.00, nb = (2*b+a)/3.00;
			if ( f(na) > f(nb) ) a = na;
			else b = nb;
		}
		t = (a+b)/2;
		printf("%.8Lf %.8Lf\n",t+1e-13,sqrt(f(t)));
	}
	return 0;
}

