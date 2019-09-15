//
// Created by sj on 15/09/19.
// 11158. Elegant Permuted Sum
// TOPIC: greedy, constructive, sorting
// status: Accepted
//
#include <bits/stdc++.h>
using namespace std;
#define N (51)
using i64= long long;
#define oo (1<<61)

int a[N],b[N];

void f( int *x, int n, int &mx, int &mi, i64 &res ) {
    if ( n == 2 ) {
        mx= x[n-1], mi= x[0], res= mx-mi;
        return ;
    }
    if ( n == 3 ) {
        mx= x[n-1], mi= x[0], res= mx-mi + x[1]-mi;
        if ( mx-x[1]+ mx-mi > res ) {
            res= mx-x[1]+mx-mi;
        }
        return ;
    }
    assert( n >= 4 );
    mx= x[n-1], mi= x[0];
    f(x+1,n-2,mx,mi,res);
    res-= mx-mi, res+= (mx-x[0])+(x[n-1]-x[0])+(x[n-1]-mi);
    mi= x[0], mx= x[n-1];
}

int main() {
    int i,j,k,n,ts,mx,mi,cs= 0;
    i64 res;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( cin >> ts; ts--; ) {
        cin >> n;
        for ( i= 0; i < n; ++i )
            cin >> a[i];
        sort(a,a+n);
        f(a,n,mx,mi,res);
        cout << "Case " << ++cs << ": " << res << endl;
    }
    return 0;
}

