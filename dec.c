#include <assert.h>
#include <stdio.h>
#define N 64

int c[N],n;

void rec( int n, int k, int limit ) {
	int i;
	if ( n ) 
		for (i=limit<n?limit:n;i>=1;rec(n-i,k+1,c[k]=i),--i);
	else if (k>1) {
		for ( i = 0; i < k-1; printf("%d+",c[i++]) );
		printf("%d\n",c[i]);
	}
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	for (;1 == scanf("%d",&n); rec(n,0,n) );
	return 0;
}
