/*
 * 202. Repeating Decimals
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 16)
typedef long long i64;

i64 m,n,len,L,p,q,pre_period,period;
char c[N];
int prev[4096];

int main() {
	int i,j,k,lim;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%lld %lld",&m,&n); putchar('\n') ) {
		printf("%lld/%lld = %lld.",m,n,m/n);
		memset(prev,-1,sizeof(prev));
		for ( m %= n, L = N, prev[m] = len = 1, c[len] = (10*m)/n, m = (10*m) % n; (++len) < L; ) {
			if ( prev[m] >= 0 ) {
				period = len-prev[m];
				pre_period = prev[m]-1;
				break ;
			}
			prev[m] = len;
			c[len] = (10*m)/n;
			m = (10*m) % n;
		}
		for ( i = 1; i <= pre_period; ++i ) 
			putchar(c[i]+'0');
		for ( putchar('('), i = pre_period+1, k = period+1, lim = 51; (--k) && (--lim); putchar(c[i++]+'0') );
		printf("%s)\n   %lld = number of digits in repeating cycle\n",k ? "...":"",period);
	}
	return 0;
}

