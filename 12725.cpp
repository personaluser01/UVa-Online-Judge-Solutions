/*
 * 12725. Fat and Orial
 * TOPIC: ad hoc
 * status: Accepted
 */
#include <iostream>
#include <cstdio>
using namespace std;

double tol = 1e-9;
int main() {
		int i,j,k,ts,cs = 0,a,b;
		scanf("%d",&ts);
		double m,n,s;
		for(;ts-->0;) {
			printf("Case #%d: ",++cs);
			scanf("%lf %lf %d %d",&n,&m,&a,&b);
			s = (a*(m-n))/b+m;
			if ( s < 0 || s > 10 ) {
				puts("Impossible");
				continue ;
			}
			printf("%.2lf\n",s+tol);
		}
		return 0;
};

