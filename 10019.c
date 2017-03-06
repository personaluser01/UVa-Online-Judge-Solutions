/*
 * 10019. Funny Encription Method 
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 0x400

int cs;
i64 ax[2],B[2] = {10,16};
char s[N];

int f( i64 n ) { return !n ? 0 : (n&1)+f(n>>1); }

int main() {
	int i,j,k;
	for ( scanf("%d",&cs); cs--; ) {
		for ( scanf("%s",s), i = 0; i < 2; ++i ) 
			for ( ax[i] = 0, j = 0; s[j]; ax[i] = B[i]*ax[i]+s[j++]-'0' );
		printf("%d %d\n",f(ax[0]),f(ax[1]));
	}
	return 0;
}
