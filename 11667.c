/*
 * 11667. Income Tax Hazard II
 * TOPIC: expectation, deriving a formula, neat interview question, medium-hard, street-fighting-mathematics
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 L,H,M,Omega,up;

int main() {
	int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 3 == scanf("%lld %lld %lld",&M,&L,&H) && (L||H||M) ) {
		printf("Case %d: ",++cs);
		Omega = (H-L+1)+(H-L+1)*(H-L)/2;
		if ( M <= L ) {
			puts("0.00");
			continue ;
		}
		if ( L < M && M <= H ) {
			up = (M-L)*(M-L+1)*(H-L+2);
			printf("%.2Lf\n",((long double)up)/20/Omega);
			continue ;
		}
		up  = ((H-L)*(4*M-2*H-2*L+4)+8*(M-H))*(H-L+1);
		printf("%.2Lf\n",((long double)up)/40/Omega);
	}
	return 0;
}

