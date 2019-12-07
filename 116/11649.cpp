/**
 * 11649. Home, sweet home
 * TOPIC: STL, data structures, greedy
 * status: WIP
 */
#include <bits/stdc++.h>
using namespace std;
using i64= int64_t;
#define N 100100

int m,n,idx[N<<4];
i64 home[N],pillar[N];
vector<i64> height;
vector<pair<i64,i64>> house;

void build( int v, int i, int j ) {
    if ( i == j ) {
        idx[v]= i; //store the durations as values
        return ;
    }
    auto k= (i+j)>>1;
    build(2*v+1,i,k), build(2*k+2,k+1,j);
    idx[v]= (house[idx[2*v+1]].second<house[idx[2*v+2]].second?idx[2*v+1]:idx[2*v+2]);
}

void update( int v, int i, int j, int pos, i64 nv ) {
    if ( i > pos or pos > j )
        return ;
    if ( i == j ) {
        assert( i == pos );
        house[i].second= nv;
        return ;
    }
    auto k= (i+j)>>1;
    update(2*v+1,i,k,pos,nv), update(2*v+2,k+1,j,pos,nv);
    idx[v]= (house[idx[2*v+1]].second<house[idx[2*v+2]].second?idx[2*v+1]:idx[2*v+2]);
}

int query( int v, int i, int j, int qi, int qj ) {
    if ( qj < i or qi > j )
        return m;
    if ( qi <= i and j <= qj )
        return idx[v];
    auto k= (i+j)>>1;
    auto l= query(2*v+1,i,k,qi,qj), r= query(2*v+2,k+1,j,qi,qj);
    return house[l].second<house[r].second?l:r;
}

#define oo (std::numeric_limits<i64>::max())

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
            if ( n >= 1 )
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
            // @see docs: Returns an iterator pointing to the _first_ element in the range [first,last)
            // which does not compare less than val.
            auto it= lower_bound(height.begin(),height.end(),home[i]);
            if ( it == height.end() )
                continue ;
            house.emplace_back(distance(begin(height),it),pillar[i]);
        }

        m= house.size(), sort(begin(house),end(house)); //sort them by left end
        house.resize(m+1), house[m].second= +oo;

        auto cmp_by_end= [&]( int i, int j ) {
            return house[i].first+house[i].second < house[j].first+house[j].second or
                    (house[i].first+house[i].second == house[j].first+house[j].second and i < j);
        };
        set<int, std::function<bool(int,int)>> by_right(cmp_by_end);
        for ( i= 0; i < m; by_right.insert(i++) ) ;
        int ans= 0, T= -1, lft= 0, cur_pos= -1, rgt= by_right.size();
        for ( build(1,0,m-1); T+1 < n; ) {
            if ( lft > 0 and rgt > 0 ) {
                i= query(1,0,m-1,0,cur_pos);
                assert( i < m );
                auto jt= by_right.begin();
                auto end_time_lft= T+house[i].second;
                auto end_time_rgt= house[*jt].first+house[*jt].second-1;
                if ( min(end_time_lft,end_time_rgt) >= n ) break ;
                if ( end_time_lft <= end_time_rgt ) {
                    ++ans, --lft, update(1,0,m-1,i,+oo);
                    for ( T= end_time_lft; cur_pos+1 < m and house[cur_pos+1].first <= T; )
                        if ( by_right.erase(++cur_pos) ) ++lft;
                }
                else {
                    i= *jt;
                    ++ans, --rgt, by_right.erase(jt), update(1,0,m-1,i,+oo);
                    for ( T= end_time_rgt; cur_pos+1 < m and house[cur_pos+1].first <= T; )
                        if ( by_right.erase(++cur_pos) ) ++lft;
                }
            }
            else if ( lft > 0 ) {
                assert( rgt == 0 );
                i= query(1,0,m-1,0,cur_pos);
                assert( i < m );
                auto end_time_lft= T+house[i].second;
                if ( end_time_lft >= n ) break ;
                ++ans, --lft, update(1,0,m-1,i,+oo);
                T= end_time_lft;
            }
            else if ( rgt > 0 ) {
                assert( lft == 0 );
                auto jt= by_right.begin();
                i= *jt;
                auto end_time_rgt= house[*jt].first+house[*jt].second-1;
                if ( end_time_rgt >= n ) break ;
                ++ans, --rgt, by_right.erase(jt), update(1,0,m-1,i,+oo);
                for ( T= end_time_rgt; cur_pos+1 < m and house[cur_pos+1].first <= T; )
                    if ( by_right.erase(++cur_pos) ) ++lft;
            }
            else break ;
        }
        cout << "Case " << ++cs << ": " << ans << endl;
    }
    return 0;
}
