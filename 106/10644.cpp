/**
 * TOPIC: spotting the pattern, trivial DP
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define N 0x400
using state= unsigned int;

state enc( unsigned int x, unsigned int y ) { return x|(y<<10); }

unordered_map<state,bool> mp;
queue<state> q;
bool ans[1 << 21];
vector<state> goods;
int dp[N][N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    /*
    state seed1= enc(2,3), seed2= enc(5,9);
    goods.push_back(seed1), goods.push_back(seed2);
    for ( q.push(seed1), q.push(seed2), mp[seed1]= mp[seed2]= true, ans[seed1]= ans[seed2]= true; not q.empty(); ) {
        vector<state> new_goods;
        auto u= q.front(); q.pop();
        auto p= (u&1023), r= (u>>10);
        cout << p << " " << r << endl;
        state v= enc(r,p);
        if ( not mp.count(v) )
            ans[v]= true, mp[v]= true, q.push(v), new_goods.push_back(v);
        for ( auto z: goods ) {
            auto m= (z&1023), n= (z>>10);
            assert( m and n );
            assert( p and r );
            auto g= __gcd(m,p);
            auto lcm= m*p/g;
            if ( lcm < N and n+r < N )
                if ( not mp.count(v= enc(lcm,n+r)) )
                    ans[v]= true, mp[v]= true, q.push(v), new_goods.push_back(v);
            g= __gcd(n,r), lcm= n*r/g;
            if ( lcm < N and m+p < N )
                if ( not mp.count(v= enc(m+p,lcm)) )
                    ans[v]= true, mp[v]= true, q.push(v), new_goods.push_back(v);
        }
        goods.insert(end(goods), begin(new_goods),end(new_goods));
    }
    cout << "done" << endl;
     */
    int i,j,k,t,ts;
    for ( j= 6; j < N; j+= 3 )
        for ( i= 4; i < N; ++i )
            dp[i][j]= dp[j][i]= 1;
    for ( j= 3; j < N; j += 3 )
        dp[2][j]= dp[j][2]= 1;
    for ( i= 2; i < N; i += 2 )
        dp[3][i]= dp[i][3]= 1;
    for ( i= 1; i < N; ++i )
        for ( j= 1; j < N; ++j )
            dp[i][j]= dp[i-1][j]+dp[i][j-1]+dp[i][j]-dp[i-1][j-1];
    for ( cin >> ts; ts--; ) {
        cin >> i >> j >> k >> t;
        if ( i > j ) swap(i,j);
        if ( k > t ) swap(k,t);
        cout << dp[j][t]-dp[i-1][t]-dp[j][k-1]+dp[i-1][k-1] << endl;
    }
    return 0;
}
