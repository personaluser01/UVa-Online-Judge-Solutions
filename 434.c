/*
 * 434. Matty's Block
 * TOPIC: dp, bitmask, greedy
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define oo 0xfffffffful
#define enc(j,u) ((j)|((u)<<4))
#define Q (1 << 21)
#define L(u) ((u)&((~(u))+1UL))
enum {MI,MA};

unsigned int max ( unsigned int x, unsigned int y ) {
    if ( x < y ) return y;
    return x;
}

unsigned int min( unsigned int x, unsigned int y ) {
    if ( x < y ) return x;
    return y;
}

int n,a[N],b[N],c[N][N],which[1 << N],s[1 << N],bts[1 << N];
unsigned int z[2][N+1][1<<N],q[Q],*head,*tail,dp[2][1 << N],T;

int main() {
    int i,j,k,l,t,ts,height,weight;
    unsigned int u,nu,v,w,nw,base,e,B,ee;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = 0; i < N; which[BIT(i)] = i, ++i );
    for ( u = 0; u < BIT(N); bts[u] = bts[u>>1]+(u&1), ++u );
    for(scanf("%d",&ts);ts-- && 1 == scanf("%d",&n); ) {
        for ( i = 0; i < n; scanf("%d",&a[i++]) ) ;
        for ( i = n-1; i >= 0; scanf("%d",&b[i--]) ) ;
        for ( dp[MI][0] = +oo, dp[MA][0] = s[0] = 0, u = 1; u < BIT(n); ++u ) {
            dp[MA][u] = max(dp[MA][u&~L(u)],b[which[L(u)]]), s[u] = s[u&~L(u)]+b[which[L(u)]];
            dp[MI][u] = min(dp[MI][u&~L(u)],b[which[L(u)]]);
        }
        for ( i = MI; i <= MA; ++i )
            for ( j = 0; j <= n; ++j )
                for ( u = 0; u < BIT(n); ++u )
                    if ( i == MI )
                        z[i][j][u] = +oo;
                    else z[i][j][u] = 0;
        z[MI][0][0] = 0;
        for ( j = 0; j < n; ++j )
        for ( u = 0; u < BIT(n); ++u ) {
            if ( z[MI][j][u] == +oo )
                continue ;
            for ( i = 0; i < n; ++i ) {
                if ( b[i] < a[j] ) continue ;
                assert( a[j] <= b[i] );
                if ( !(u&BIT(i)) && a[j] == b[i] ) nu = u|BIT(i); else nu = u;
                for ( v=base=(~(u|BIT(i)))&MASK(n); v; v=(v-1)&base ) {
                    if ( dp[MA][v] > a[j] ) continue ;
                    if ( z[MI][j+1][v|nu] > z[MI][j][u]+a[j]+s[v] ) {
                         z[MI][j+1][v|nu] = z[MI][j][u]+a[j]+s[v];
                        /*if ( z[MA][j+1][v|nu] < z[MI][j+1][v|nu] )
                            z[MA][j+1][v|nu] = z[MI][j+1][v|nu];*/
                    }
                    /*
                    for ( e = B = ~(BIT(i)|v)&MASK(n); e; e = ((e-1)&B) ) {
                        for ( weight = 0, ee = e; ee; ee -= L(ee) )
                            weight += min(a[j],b[which[L(ee)]]);
                        if ( z[MA][j+1][nu|v] < z[MA][j][u]+s[v]+a[j]+weight )
                             z[MA][j+1][nu|v] = z[MA][j][u]+s[v]+a[j]+weight;
                    }
                    */
                }
                if ( z[MI][j+1][v|nu] > z[MI][j][u]+a[j]+s[v] )
                     z[MI][j+1][v|nu] = z[MI][j][u]+a[j]+s[v];
                /*
                if ( z[MA][j+1][v|nu] < z[MI][j+1][v|nu] )
                     z[MA][j+1][v|nu] = z[MI][j+1][v|nu];
                for ( e = B = ~(BIT(i)|v)&MASK(n); e; e = ((e-1)&B) ) {
                    for ( weight = 0, ee = e; ee; ee -= L(ee) )
                        weight += min(a[j],b[which[L(ee)]]);
                    if ( z[MA][j+1][nu|v] < z[MA][j][u]+s[v]+a[j]+weight )
                         z[MA][j+1][nu|v] = z[MA][j][u]+s[v]+a[j]+weight;
                }
                */
            }
        }
        for ( T = 0, j = n-1; j >= 0; --j ) 
            for ( i = 0; i < n; ++i )
                T += min(a[j],b[i]);
        printf("Matty needs at least %u blocks, and can add at most %u extra blocks.\n",z[MI][n][MASK(n)],T-z[MI][n][MASK(n)]);
    }
    return 0;
}


