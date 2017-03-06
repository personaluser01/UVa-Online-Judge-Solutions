/*
 * 175. Expanding Fractions
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 15)
typedef long long i64;

i64 m,n,L = 1 << 29;
int prev[N];
char buff[1 << 16],*ptr,c[1 << 16];

int main() {
	int i,j,k,period,pre_period,l,ok;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;2 == scanf("%lld %lld",&m,&n) && (m||n); putchar('\n') ) {
		memset(prev,-1,sizeof(prev));
		for ( m %= n, c[prev[m] = k = 0] = (10*m)/n+'0', m = (10*m) % n; (++k) < L; ) {
			if ( prev[m] >= 0 ) {
				pre_period = prev[m];
				period = k-prev[m];
				break ;
			}
			c[prev[m] = k] = (10*m)/n+'0', m = (10*m) % n;
		}
		ptr = buff, *ptr++ = '.';
		for ( i = 0; i < pre_period; )
			*ptr++ = c[i++];
		for ( ok = 0, i = pre_period, k = period+1; (--k); )
			if ( c[i++] != '0' ) {
				ok = 1;
			}
		if ( ok ) {
			for ( k = period+1, i = pre_period; (--k); *ptr++ = c[i++]);
		}
		*ptr = '\0';
		for ( i = 0; i < ptr-buff; ) {
			for ( j = 0; j < 50 && i < ptr-buff; ++i, ++j )
				putchar(buff[i]);
			if ( i < ptr-buff )
				putchar('\n');
		}
		if ( m ) {
			printf("\nThe last %d digits repeat forever.\n",period);
		}
		else {
			puts("\nThis expansion terminates.");
		}
	}
	return 0;
}
