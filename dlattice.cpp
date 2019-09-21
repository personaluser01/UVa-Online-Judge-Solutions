//
// Created by sj on 20/09/19.
//
#include <bits/stdc++.h>
#define S (1000)
using namespace std;
using i64= long long;

set<i64> ans,x,y;

int main() {
    i64 a[2],b[2],i,j,s,r;
    freopen("input.txt","r",stdin);
    while ( cin >> a[0] >> b[0] >> a[1] >> b[1] >> s >> r ) {
        auto lcmx= a[0]*a[1]/__gcd(a[0],a[1]),
             lcmy= b[0]*b[1]/__gcd(b[0],b[1]);
        assert( s <= a[0] and r <= b[0] );
        for ( ans.clear(), x.clear(), y.clear(), i= 0; i < 2*lcmx/a[0]; ++i )
            x.insert(a[0]*i);
        for ( i= 0; i < 2*lcmx/a[1]; ++i )
            x.insert(s+a[1]*i);
        for ( j= 0; j < 2*lcmy/b[0]; ++j )
            y.insert(b[0]*j);
        for ( j= 0; j < 2*lcmy/b[1]; ++j )
            y.insert(r+b[1]*j);
        vector<i64> vx, vy;
        for ( const auto xx: x ) vx.push_back(xx);
        for ( const auto yy: y ) vy.push_back(yy);
        for ( i= 0; i+1 < vx.size(); ++i )
            for ( j= 0; j+1 < vy.size(); ++j )
                ans.insert( (vx[i+1]-vx[i])*(vy[j+1]-vy[j]) );
        cout << ans.size() << endl;
        for ( const auto &it: ans )
            cout << it << endl;
    }
    return 0;
}
