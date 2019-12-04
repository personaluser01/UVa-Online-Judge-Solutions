/**
 * 11270. Tiling Dominoes
 * TOPIC: combinatorics, bitmasks, DP, precalc
 * status:
 */
#include <bits/stdc++.h>
using namespace std;
#define N 101
#define BIT(k) (1ull<<(k))
#define MASK(k) (BIT(k)-1ull)
using u64= uint64_t;

u64 z[N][1<<11][11],full[N][N];

u64 calc( int m, int n ) {
    assert( m <= n );
    if ( (m*n)&1 ) return 0ull;
    unsigned int u,v,w,base;
    int i,j,k;
    z[0][0][0]= 1;
    for ( j= 1; j <= n; ++j ) {
        for ( u= 0; u < BIT(m); ++u )
            for ( i= 1; i <= m; ++i ) {
                z[j][u][i]= 0;
                if ( i >= 2 )
                    z[j][u][i]+= z[j][u][i-2];
                if ( u & BIT(i) )
                    z[j][u][i]+= z[j][u^BIT(i)][i-1];
            }
    }
}

u64 s[N][N];

int main() {
    int i,j,k;
    int m,n;
#ifndef ONLINE_JUDGE
    freopen("11270.in","r",stdin);
#endif
    for ( k= 0, m= 1; m < N; ++m )
        for ( n= m; m*n < N; ++n, ++k ) {
            if ( (m*n) & 1 ) continue ;
            cout << "s[" << m << "][" << n << "]= " << calc(m,n) << "llu;\n";
        }
        /*
    while ( cin >> m >> n ) {
        if ( m > n ) swap(m,n);
        if ( m == 0 ) {
            cout << 0 << endl;
            continue ;
        }
        cout << s[m][n] << endl;
    }
         */
    return 0;
}
