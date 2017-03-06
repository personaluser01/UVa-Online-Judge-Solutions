/*
 * 11432. Busy Programmer
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 36
#define oo 0xffffffffffffffffull
typedef unsigned long long u64;

int ts,n,m;
u64 z[67][2][2][34][34],P[67][2][2][34];
u64 calc_z( int k, int a, int b, int l, int s );

u64 calc_f( int k, int a, int b, int s ) {
	u64 *res = P[k][a][b]+s;
	int t;
	if ( *res < +oo )
		return *res;
	for ( *res = 0, t = 1; t <= k && t <= m; ++t )
		(*res) += calc_z(k,a,b,t,s);
	return *res;
}

u64 calc_z( int k, int a, int b, int l, int s ) {
	u64 *res = z[k][a][b][l]+s;
	if ( *res < +oo )
		return *res;
	if (l>m||l<=0||((b+a)&&!s) )
		return *res = 0;
	if ( k == 1 ) {
		if ( (a!=b)||(l!=1)||(s>0&&b==0)||(b==1&&s!=1) ) 
			return *res = 0;
		if ( (b==1&&s==1)||(b==0&&s==0) )
			return *res = 1;
		return *res = 0;
	}
	assert( k > 1 );
	return *res=((l==1)?calc_f(k-1,a,b^1,s-b):calc_z(k-1,a,b,l-1,s-b));
}



int main() {
	u64 w;
	int k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&n,&m)&&(n+1||m+1);) {
		memset(z,0xffull,sizeof(z)),memset(P,0xffull,sizeof(P));
		w = calc_f(2*n,0,1,n)+calc_f(2*n,1,0,n);
		for ( k = m+1; k <= n; ++k )
			w += calc_f(2*n-k,1,1,n)+calc_f(2*n-k,0,0,n-k<=0?0:n-k);
		if ( w ) printf("z[%d][%d]=%llu;\n",n,m,w);
	}
	/*
	for ( n = 0; n <= 33; ++n )
		for ( m = 0; m <= 33; ++m ) {
			memset(z,0xffull,sizeof(z)),memset(P,0xffull,sizeof(P));
		}
	*/
	return 0;
}

