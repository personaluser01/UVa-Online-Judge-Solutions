/*
 * 12393. Non-negative Partial Sums
 * TOPIC: dp, very neat, partial sums
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N (1000100)
#define oo (1LL<<43)
typedef long long i64;
using namespace std;

int n,ans;
i64 a[N],A[N],B[N],C[N],D[N];

int main() {
	int i,j,k;
	for ( ;1==scanf("%d",&n) && n>0; printf("%d\n",ans) ) {
		for ( i = 1; i <= n; scanf("%lld",&a[i++]) );
		for ( i = 1; i <= n; A[i] = A[i-1]+a[i], ++i );
		for ( B[n+1] = 0, i = n; i >= 1; B[i] = B[i+1]+a[i], --i );
		for ( C[0] = +oo, k = 1; k <= n; C[k] = min(C[k-1],A[k]), ++k );
		for ( D[n+1] = +oo, k = n; k >= 1; --k )
			D[k] = min(a[k],a[k]+D[k+1]);
		for ( ans = 0, k = 1; k <= n; ++k ) 
			if ( D[k] >= 0 && B[k]+C[k-1] >= 0 ) ++ans;
	}
	return 0;
};

