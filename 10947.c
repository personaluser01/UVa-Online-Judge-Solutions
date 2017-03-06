/*
 * 10947. 
 * TOPIC: floyd-warshall, geometry, circles
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
typedef long long i64;
#define YES (puts("Larry and Ryan will escape!"))
#define NO  (puts("Larry and Ryan will be eaten to death."))
#define S(x) ((x)*(x))

i64 x[N],y[N],r[N],n,K,m;
double d[N][N];
int g[N][N];

double f( int i, int j ) {
    double L = sqrt(S(x[i]-x[j]) + S(y[i]-y[j]));
    if ( L < r[i]+r[j] )
        return 0;
    return L-r[i]-r[j];
}

int main() {
    int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for(;2 == scanf("%lld %lld",&K,&m);) {
        scanf("%lld %lld %lld %lld %lld %lld",x,y,r,x+1,y+1,r+1);
        for ( scanf("%lld",&n), n += 2, i = 2; i < n; ++i )
            scanf("%lld %lld %lld",x+i,y+i,r+i);
        for ( i = 0; i < n; ++i )
            for ( j = 0; j < n; ++j )
                g[i][j] = (d[i][j]=f(i,j))<=m*K;
        for ( k = 0; k < n; ++k )
            for ( i = 0; i < n; ++i )
                for ( j = 0; j < n; ++j )
                    if ( g[i][k] && g[k][j] )
                        g[i][j] = 1;
        if ( g[0][1] )
            YES;
        else NO;
    }
    return 0;
}

