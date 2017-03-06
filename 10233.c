/*
 * 10233. Dermuba Triangle
 * status: Accepted
 * TOPIC: Geometry
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-9
typedef long long i64;
#define S(x) ((x)*(x))
#define DBG 0

i64 m[2],n,row[2],up[2];
double x[2],y[2];

int main() {
    i64 i,j,k,rm[2],t;
    double h;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( h = sqrt(3.0)/2.0; 2 == scanf("%lld %lld",m,m+1); printf("%.3lf\n",sqrt(S(x[0]-x[1])+S(y[0]-y[1]))+tol) ) {
        for ( t = 0; t <= 1; ++t ) {
            rm[t] = (i64)(sqrt(++m[t])+tol);
            if ( rm[t]*rm[t] == m[t] )
                row[t] = rm[t];
            else row[t] = rm[t]+1;
            k = (row[t]-1)*(row[t]-1)+1;
            up[t] = (((m[t]-k)&1)^1);
            y[t] = -h*(row[t]-1);
            if ( up[t] )
                y[t] = y[t]-(2.0/3.0)*h;
            else y[t] = y[t]-(1.0/3.0)*h;
#if DBG
            printf("m[t] = %lld, row[t] = %lld, k = %lld, up[t] = %lld\n",m[t],row[t],k,up[t]);
#endif
            x[t] = (m[t]-k-row[t]+1)/2.0;
        }
#if DBG
        printf("THIS %.3lf\n",2*h+h/3);
        printf("Row[0] = %lld, Row[1] = %lld\n",row[0],row[1]);
        printf("(%.3lf,%.3lf) and (%.3lf,%.3lf)\n",x[0],y[0],x[1],y[1]);
#endif
    }
    return 0;
}

