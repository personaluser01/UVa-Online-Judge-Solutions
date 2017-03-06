/*
 * KEYWORDS: Derangements
 * status: Accepted
 */
#include <stdio.h>
#define N 13
long long z[N],n,i,F[N],ts;
int main() {
	for(F[0]=1LL,n=1;n<N;++n) 
		for(F[n]=F[n-1]*n,i=0;i<=n;(z[n]+=(i&1)?-F[n]/F[i]:F[n]/F[i]),++i);
	for(scanf("%lld",&ts);ts--&&1==scanf("%lld",&n);printf("%lld/%lld\n",z[n],F[n]));
	return 0;
}



