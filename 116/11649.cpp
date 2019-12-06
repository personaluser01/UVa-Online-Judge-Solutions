/**
 * 11649. Home, sweet home
 * TOPIC: STL, data structures, greedy
 * status: WIP
 */
#include <bits/stdc++.h>
using namespace std;
using i64= int64_t;
#define N 100100

int m,n;
i64 home[N],pillar[N];
vector<i64> height;
vector<pair<i64,i64>> house;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int i,j,k,ts,cs= 0;
#ifndef ONLINE_JUDGE
    freopen("11649.in","r",stdin);
#endif
    for ( cin >> ts; ts--; ) {
        (cin>>n>>m), height.resize(n);
        {
            i64 A, B, C;
            cin >> A >> B >> C;
            if ( n >= 0 )
                height[0]= (C%10000)+1;
            if ( n >= 2 )
                height[1]= ((A*height[0]+C)%10000)+1;
            for ( i= 2; i < n; ++i )
                height[i]= ((A*height[i-1]+B*height[i-2]+C)%10000)+1;
        }
        {
            i64 E,F,G,H,I,J;
            cin >> E >> F >> G >> H >> I >> J;
            if ( m >= 1 ) {
                home[0] = (G % 10000) + 1;
                pillar[0] = (J % 100000) + 1;
            }
            for ( i= 1; i < m; ++i ) {
                home[i]= ((E*home[i-1]+F*pillar[i-1]+G)%10000)+1;
                pillar[i]= ((H*pillar[i-1]+I*home[i-1]+J)%100000)+1;
            }
        }
        sort(begin(height),end(height)), house.clear();
        for ( i= 0; i < m; ++i ) {
            auto it= lower_bound(height.begin(),height.end(),home[i]);
            if ( it == height.end() )
                continue ;
            house.emplace_back(distance(begin(height),it),pillar[i]);
        }
        auto cmp_by_start= [&]( int i, int j ) {
            return house[i].first < house[j].first or (house[i].first == house[j].first and i < j);
        };
        auto cmp_by_end=   [&]( int i, int j ) {
            return house[i].first+house[i].second < house[j].first+house[j].second or
                    (house[i].first+house[i].second == house[j].first+house[j].second and i < j);
        };
        m= house.size();
        set<int, std::function<bool(int,int)>> by_left(cmp_by_start), by_right(cmp_by_end);
        // put all inside the sets
        for ( i= 0; i < m; ++i )
            by_left.insert(i), by_right.insert(i);
        int ans= 0;
        while ( not by_right.empty() ) {
            assert( by_left.size() == by_right.size() );
            auto it= by_right.begin();
            auto begin_time= house[*it].first, end_time= house[*it].first+house[*it].second-1;
            if ( end_time >= n ) break ;
            auto val= *it;
            ++ans, by_right.erase(*it), by_left.erase(*it);
            assert( by_left.size() == by_right.size() );
            auto jt= by_left.upper_bound(val);
            vector<int> to_update;
            for ( auto kt= begin(by_left); kt != jt; to_update.emplace_back(*kt++) ) ;
            for ( auto z: to_update )
                by_left.erase(z), by_right.erase(z);
            assert( by_left.size() == by_right.size() );
            for ( i= 0; i < to_update.size(); ++i ) {
                j= to_update[i];
                assert( house[j].first <= end_time );
                assert( end_time <= house[j].first+house[j].second-1 );
                house[j].first= end_time+1;
            }
            by_left.insert(begin(to_update),end(to_update));
            by_right.insert(begin(to_update),end(to_update));
            assert( by_left.size() == by_right.size() );
        }
        cout << "Case " << ++cs << ": " << ans << endl;
    };
    return 0;
}

