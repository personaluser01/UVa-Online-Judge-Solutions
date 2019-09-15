//
// Created by sj on 15/09/19.
// 11497: Set
// TOPIC: convexity, ad hoc, inequalities, modelling
// status:
//
#include <bits/stdc++.h>
#define N 4
using namespace std;
using i64= long long;

int fst[256],sec[256];
i64 a[N][N];

int main() {
    int i,j,k,n;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    fst['u']= 1, fst['d']= 2, fst['t']= 3;
    sec['c']= 1, sec['q']= 2, sec['t']= 3;
    for ( ;(cin >> n) and n > 0; ) {
        memset(a,0,sizeof a);
        for ( i= 0; i < n; ++i ) {
            string aa,bb;
            cin >> aa >> bb;
            j= fst[aa[0]], k= sec[bb[0]];
            assert( 1 <= min(j,k) and max(j,k) <= 3 );
            ++a[j][k];
        }
        i64 ans= numeric_limits<i64>::min();
        for ( i64 d1= 0; d1 <= min(a[3][1],a[1][3]); ++d1 )
            for ( i64 d2= 0; d2 <= a[2][2]-d1 and d2 <= min(a[1][1],a[3][3]); ++d2 ) {
                i64 uc1= min(a[2][1],min(a[1][1]-d2,a[3][1]-d1)),c1,c2,c3;
                i64 uc2= min(a[1][2],min(a[2][2]-d1-d2,a[3][2]));
                i64 uc3= min(a[1][3],min(a[2][3],a[3][3]-d2));
                assert( uc1 >= 0 and uc2 >= 0 and uc3 >= 0 );
                for ( unsigned int u= 0; u < 8; ++u ) {
                    c1= (u&1)?0:uc1;
                    c2= (u&2)?0:uc2;
                    c3= (u&4)?0:uc3;
                    i64 r1= min(a[1][1]-c1-d2,min(a[1][2]-c2,a[1][3]-c3-d1));
                    i64 r2= min(a[2][1]-c1,min(a[2][2]-c2-d1-d2,a[2][3]-c3));
                    i64 r3= min(a[3][1]-c1-d1,min(a[3][2]-c2,a[3][3]-c3-d2));
                    assert( r1 >= 0 and r2 >= 0 and r3 >= 0 );
                    ans= max(ans,r1+r2+r3+c1+c2+c3+d1+d2);
                }
            }
        cout << ans << endl;
    }
    return 0;
}
