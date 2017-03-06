/*
 * 11195.
 * TOPIC: backtracking, bitmasks
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15
#define L(i) ((i)&((~(i))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef long long i64;
typedef unsigned long long u64;

int n;
i64 ans;
char which[1 << N];
u64 d,e,r,v[N];

void f( int col, int m ) {
    unsigned int u,i;
    if ( m == n ) {
        ++ans;
        return ;
    }
    if ( col >= n || !r || n-m < n-col ) return ;
    assert( m <= n-1 && col <= n-1 );
    for ( u = (r&~v[col]); u; u -= L(u) ) {
        i = which[L(u)];
        if ( !((e>>(col+i))&1) && !((d>>(col-i+N))&1) ) {
            e |= BIT(col+i),  d |= BIT(col-i+N), r &= ~BIT(i);
            f(col+1,m+1);
            e &= ~BIT(col+i), d &= ~BIT(col-i+N), r |= BIT(i);
        }
    }
    /*f(col+1,m);*/
}

void read_case() {
    int i,j;
    char tmp[N+N];
    for ( j = 0; j < n; ++j ) v[j] = 0;
    for ( r = MASK(n), e = d = 0, i = 0; i < n; ++i )
        for ( scanf("%s",tmp), j = 0; j < n; ++j ) 
            if ( tmp[j] == '*' )
                v[j] |= BIT(i);
}

int main() {
    int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = 0; i < N; ++i ) which[1 << i] = i;
    for (;1 == scanf("%d",&n) && n > 0; ans = 0, read_case(), f(0,0), printf("Case %d: %lld\n",++cs,ans) );
    return 0;
}

