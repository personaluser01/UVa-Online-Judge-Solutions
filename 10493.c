/*
 * 10493. Cats, with or withoutt hats
 * status: Accepted
 */
#include <stdio.h>

int n,m;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while(2==scanf("%d %d",&n,&m)&&n&&printf("%d %d ",n,m)) {
		if ( m == 1 && n == 1 ) {
			puts("Multiple");
			continue ;
		}
		if ( n == 1 ) puts("Impossible");
		else if ( (m-1)%(n-1) )
			puts("Impossible");
		else printf("%d\n",(m-1)/(n-1)+m);
	}
	return 0;
}
