//
// Created by sj on 20/09/19.
//
#include <bits/stdc++.h>
#define S (1000)
using namespace std;
using i64= long long;

set<i64> ans,x,y;

int main() {
    i64 a[2],b[2],i,j,k,t,signs[2]= {-1,1},s,r,MX= 0x400;
    freopen("input.txt","r",stdin);
    while ( cin >> a[0] >> b[0] >> a[1] >> b[1] >> s >> r ) {
        for ( x.clear(), y.clear(), ans.clear(), t= 0; t < 2; ++t ) {
            for ( i = -a[t^1]; i < a[t^1]; ++i )
                x.insert(i * a[t] + signs[t] * s);
            for ( j = -b[t^1]; j < b[t ^ 1]; ++j )
                y.insert((j * b[t] + signs[t] * r));
        }
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
