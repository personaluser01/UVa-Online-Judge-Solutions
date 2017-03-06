/*
 * 10159. Star
 * TOPIC: dp, elegant dp
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define M 16
#define N 64
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define oo 0xfffffffful
using namespace std;

queue<pair<unsigned int,int> > q;
unsigned int u[M],mi,z[1 << 12][49];
int seen[1 << 12][49],yes;

int g[M][N],a[M],m = 12, n = 48,limit[N],c[N],
    A[] = {4,5,6,7,8,9,10,11,12,13,14},
    B[] = {15,16,17,18,19,20,21,22,23},
    C[] = {24,25,26,27,28,29,30,31,32},
    D[] = {33,34,35,36,37,38,39,40,41,42,43},
    E[] = {33,34,24,25,16,17,7,8,1,2,0},
    F[] = {35,36,26,27,18,19,9,10,3},
    G[] = {44,37,38,28,29,20,21,11,12},
    H[] = {47,45,46,39,40,30,31,22,23,13,14},
    I[] = {47,45,44,37,36,25,26,15,16,4,5},
    J[] = {46,38,39,27,28,17,18,6,7},
    K[] = {40,41,29,30,19,20,8,9,1},
    L[] = {42,43,31,32,21,22,10,11,2,3,0};

void go( int *a, int len, int row ) {
    // printf("len = %d\n",len);
    for ( int j = 0; j < len; ++j )
        g[row][a[j]] = 1;
}

bool constraints_met() {
    for ( int i = 0; i < m; ++i )
        if ( !(BIT(a[i])&u[i]) )
            return false;
    return true;
}

unsigned int
calc_z( unsigned int u, int idx ) {
    unsigned int w,v,i,k;

    if ( idx == n ) {
        if ( u == MASK(m) ) 
            return z[u][n] = 0;
        return +oo;
    }

    assert( idx < n );
    assert( u <= MASK(m) );

    if ( seen[u][idx] == yes ) 
        return z[u][idx];

    for ( seen[u][idx] = yes, k = 0; k <= limit[idx]; ++k ) {
        for ( v = u, i = 0; i < m; ++i )
            if ( g[i][idx] && a[i] == k )
                v |= BIT(i);
        w = calc_z(v,idx+1);
        if ( w < +oo && k+w < z[u][idx] )
            z[u][idx] = k+w;
    }

    return z[u][idx];

}

int main() {
    int i,j,k,l,t,T;
    unsigned int v,w;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    go(A,(sizeof A)/sizeof (*A),0), go(B,(sizeof B)/sizeof (*B),1), go(C,(sizeof C)/sizeof (*C),2), go(D,(sizeof D)/sizeof (*D),3), go(E,(sizeof E)/sizeof (*E),4), go(F,(sizeof F)/sizeof (*F),5), go(G,(sizeof G)/sizeof (*G),6), go(H,(sizeof H)/sizeof (*H),7), go(I,(sizeof I)/sizeof (*I),8), go(J,(sizeof J)/sizeof (*J),9), go(K,(sizeof K)/sizeof (*K),10), go(L,(sizeof L)/sizeof (*L),11);
    for ( ;1 == scanf("%d",a); ) {
        for ( i = 1; i < m; scanf("%d",&a[i++]) );
        for ( j = 0; j < n; ++j )
            for ( limit[j] = 10, i = 0; i < m; ++i )
                if ( g[i][j] )
                    limit[j] = min(limit[j],a[i]);
        for ( i = 0; i < m; ++i ) u[i] = 0;
        for ( T = 0, j = 0; j < n; ++j ) 
            for ( T += (c[j] = limit[j]), i = 0; i < m; ++i )
                if ( g[i][j] )
                    u[i] |= BIT(c[j]);
        if ( !constraints_met() ) {
bad:
            puts("NO SOLUTION");
            continue ;
        }
        for ( j = 0; j < n; ++j )
            assert( limit[j] <= 9 );
        memset(z,0xff,sizeof z);
        ++yes, mi = calc_z(0,0);
        if ( mi == +oo ) goto bad;
        printf("%u %d\n",mi,T);
    }
    return 0;
}

