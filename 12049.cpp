/*
 * 12049. Prune the List
 * status: Accepted
 * TOPIC: sorting, two-pointer linear walk, greedy, good-basic
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
#define N (1 << 16)
using namespace std;
typedef long long i64;

int n[2];
i64 c[2][N];

int main() {
    int i,j,k,l,t,ts,ans;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",n,n+1); printf("%d\n",ans) ) {
        for ( t = 0; t < 2; sort(c[t],c[t]+n[t]), ++t )
            for ( i = 0; i < n[t]; ++i )
                scanf("%lld",&c[t][i]);
            i = 0; k = 0; ans = 0;
            for (;i < n[0] && k < n[1];) {
                for ( j = i+1; j < n[0] && c[0][j] == c[0][i]; ++j );
                for ( t = k+1; t < n[1] && c[1][t] == c[1][k]; ++t );
                if ( c[0][i] == c[1][k] ) {
                    ans += abs((t-k)-(j-i));
                    i = j; k = t;
                    continue ;
                }
                if ( c[0][i] < c[1][k] ) {
                    ans += (j-i);
                    i = j;
                    continue ;
                }
                assert (c[0][i] > c[1][k]);
                ans += (t-k);
                k = t;
            }
            ans += (n[0]-i)+(n[1]-k);
    }
    return 0;
}

