/*
 * 10627. Infinite Race
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-11
typedef long long i64;

int main() {
     i64 L,u,v,t,T,tau,rem,tt,P,p;
     i64 ax,k,j,i,ii,jj;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    while ( 4 == scanf("%lld %lld %lld %lld",&L,&u,&v,&T) && L > 0 ) {
        if ( u < v ) tt = u, u = v, v = tt;
        assert( u >= v );
        if ( (T*(u+v)/L)&1 )
            k = (T*(u+v)/L)/2+1;
        else 
            k = (T*(u+v)/L)/2;
        if ( (T*(u-v)/L)&1 )
            j = (T*(u-v)/L)/2+1;
        else 
            j = (T*(u-v)/L)/2;
        printf("%lld\n",k+j);
    }
    return 0;
}

