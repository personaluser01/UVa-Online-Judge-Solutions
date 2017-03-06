/*
 * 12708. GCD the Largest
 * status: Acccepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 n;

int main() {
    int i,j,k,ts;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( scanf("%d",&ts); ts-- && 1 == scanf("%lld",&n) && printf("%lld\n",n>>1); );
    return 0;
}

