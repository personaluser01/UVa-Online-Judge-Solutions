//
// Created by sj on 13/09/19.
// 10570: Meeting with Aliens
// TOPIC: simulation, greedy, sorting by swaps
// status: Accepted
//
#include <bits/stdc++.h>
#define N (501)
using namespace std;

int a[N],c[2][N][N];

int f( int *x, int *z, int n ) {
    int address[N],i,j,k,res= 0,y[N];
    for ( i= 0; i < n; ++i )
        address[y[i]= z[i]]= i;
    for ( i= 0; i < n; ++i )
        if ( y[i] != x[i] and ++res ) {
            assert( address[x[i]] > i );
            int intruder= y[i];
            swap(y[i],y[address[x[i]]]);
            swap(address[intruder],address[x[i]]);
            assert( y[i] == x[i] );
        }
    for ( i= 0; i < n; ++i )
        assert( x[i] == y[i] );
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    int i,j,k,l,t,n,ans;
    for ( ;1 == scanf("%d",&n) and n > 0; printf("%d\n",ans) ) {
        for ( i= 0; i < n; scanf("%d",&a[i++]), --a[i-1] ) ;
        for ( t= 0; t <= 1; ++t ) {
            for ( i = 0, j = 0; j < n; ++j) c[t][i][j] = t==0?j:n-1-j;
            for (;++i < n;)
                for ( j= 0; j < n; ++j )
                    c[t][i][j] = c[t][i-1][(j + 1) % n];
        }
        for ( ans= (n*n), t= 0; t < 2; ++t )
            for ( i= 0; i < n; ++i )
                ans= min(ans,f(c[t][i],a,n));
    }
    return 0;
}

