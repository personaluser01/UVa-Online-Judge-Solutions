/**
 * 11649. Home, sweet home
 * TOPIC: STL, data structures, greedy
 * status: WIP
 */
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "../profile.h"
#endif
using namespace std;
using i64= int64_t;
#define N 100100

int m,n,idx[N<<3],home[N],pillar[N],height[N];
pair<int,int> house[N];

void build( int v, int i, int j ) {
    if ( i == j ) { idx[v]= i; return ; }
    auto k= (i+j)>>1;
    build(2*v+1,i,k), build(2*v+2,k+1,j);
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
    update((v<<1)+1,i,k,pos,nv), update((v<<1)+2,k+1,j,pos,nv);
    idx[v]= (house[idx[(v<<1)+1]].second<house[idx[(v<<1)+2]].second?idx[(v<<1)+1]:idx[(v<<1)+2]);
}

int query( int v, int i, int j, int qi, int qj ) {
    if ( qj < i or qi > j )
        return m;
    if ( qi <= i and j <= qj )
        return idx[v];
    auto k= (i+j)>>1;
    auto l= query((v<<1)+1,i,k,qi,qj), r= query((v<<1)+2,k+1,j,qi,qj);
    return house[l].second<=house[r].second?l:r;
}

#define oo (std::numeric_limits<int>::max())
#define xchg(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))

int pos[N],cnt,heap[N<<2];
#define bubble(i,j) (swap(pos[heap[i]],pos[heap[j]]), swap(heap[i],heap[j]))

int cmp( int x, int y ) {
    if ( house[x].second == std::numeric_limits<int>::min() )
        return -1;
    if ( house[y].second == std::numeric_limits<int>::min() )
        return 1;
    if ( house[x].second == +oo and house[y].second == +oo ) {
        return x-y;
    }
    if ( house[x].second == +oo )
        return 1;
    if ( house[y].second == +oo )
        return -1;
    if ( house[x].first+house[x].second < house[y].first+house[y].second )
        return -1;
    if ( house[x].first+house[x].second > house[y].first+house[y].second )
        return 1;
    return x-y;
}

inline void push( int x ) {
    int i,j;
    if ( pos[x] < 0 )
        pos[heap[cnt]= x]= cnt, ++cnt;
    for ( j= pos[x]; j>0 and cmp(heap[i= (j-1)>>1],heap[j]) > 0; bubble(i,j), j= i ) ;
}

int pop() {
    int x= *heap, i,j;
    if ( cnt+= (pos[x]= -1) )
        pos[heap[0]= heap[cnt]]= 0;
    for ( j= 0; i= j, j<<= 1, ++j < cnt; bubble(i,j) ) {
        if ( j < cnt-1 and cmp(heap[j+1],heap[j]) < 0 ) ++j;
        if ( cmp(heap[i],heap[j]) <= 0 ) break ;
    }
    return x;
}

void remove( int x ) {
    if ( pos[x] < 0 )
        return ;
    auto tmp= house[x].second;
    house[x].second= std::numeric_limits<int>::min();
    push(x);
    auto y= pop();
    assert( x == y );
    house[x].second= tmp;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int i,j,k,ts,cs= 0;
    const i64 HG= 10000, MR= 100000;
#ifndef ONLINE_JUDGE
    freopen("11649.in","r",stdin);
#endif
#ifndef ONLINE_JUDGE
    LOG_DURATION("total duration for all test cases");
#endif
    for ( cin >> ts; ts--; ) {
        {
            (cin >> n >> m);
            {
                i64 A, B, C;
                cin >> A >> B >> C;
                if (n >= 1)
                    height[0] = (C % HG) + 1;
                if (n >= 2)
                    height[1] = (A * height[0] + C) % HG + 1;
                for (i = 2; i < n; ++i)
                    height[i] = (A * height[i - 1] + B * height[i - 2] + C) % HG + 1;
            }
            {
                i64 E, F, G, H, I, J;
                cin >> E >> F >> G >> H >> I >> J;
                if (m >= 1) {
                    home[0] = (G % HG) + 1;
                    pillar[0] = (J % MR) + 1;
                }
                for (i = 1; i < m; ++i) {
                    home[i] = (E * home[i - 1] + F * pillar[i - 1] + G) % HG + 1;
                    pillar[i] = (H * pillar[i - 1] + I * home[i - 1] + J) % MR + 1;
                }
            }
        }

        sort(height,height+n);

        {
            for (k= 0, i = 0; i < m and n; ++i) {
                int it;
                if ( height[0] < home[i] ) {
                    if ( height[n-1] < home[i] )
                        continue ;
                    auto low= 0, high= n-1, mid= low;
                    for ( ;low+1<high; )
                        height[mid= (low+high)>>1]<home[i]?(low= mid):(high= mid);
                    it= high;
                }
                else it= 0;
                if (it+pillar[i]-1 >= n)
                    continue;
                house[k++]= {it,pillar[i]};
            }
        }

        m= k, sort(house,house+m); //sort them by left end
        house[m].second= +oo;

        cnt= 0, memset(pos,-1,sizeof pos);
        {
            for (i = 0; i < m; push(i++));
        }
        int ans= 0, T= -1, cur_pos= -1;
        {
            for (build(1, 0, m - 1);;) {
                if (house[i = query(1, 0, m - 1, 0, cur_pos)].second < +oo and cnt > 0) {
                    assert(i < m);
                    j = pop();
                    auto end_time_lft = T + house[i].second;
                    auto end_time_rgt = house[j].first + house[j].second - 1;
                    if (min(end_time_lft, end_time_rgt) >= n) break;
                    if (end_time_lft <= end_time_rgt) {
                        ++ans, update(1, 0, m - 1, i, +oo);
                        for (T = end_time_lft; cur_pos + 1 < m and house[cur_pos + 1].first <= T;)
                            remove(++cur_pos);
                    } else {
                        assert(j > cur_pos);
                        auto excess = house[j].first - T - 1;
                        assert(excess >= 0);
                        if (house[i].second < +oo) {
                            auto l = min(excess, house[i].second);
                            update(1, 0, m - 1, i, house[i].second - l);
                            excess -= l;
                            assert(not excess);
                        }
                        ++ans, remove(j), update(1, 0, m - 1, j, +oo);
                        for (T = end_time_rgt; cur_pos + 1 < m and house[cur_pos + 1].first <= T;)
                            remove(++cur_pos);
                    }
                } else if (house[i].second < +oo) {
                    assert(i < m);
                    auto end_time_lft = T + house[i].second;
                    if (end_time_lft >= n) break;
                    ++ans, update(1, 0, m - 1, i, +oo);
                    T = end_time_lft;
                } else if (cnt > 0) {
                    j = pop();
                    assert(j > cur_pos);
                    auto end_time_rgt = house[j].first + house[j].second - 1;
                    if (end_time_rgt >= n) break;
                    ++ans, remove(j), update(1, 0, m - 1, j, +oo);
                    for (T = end_time_rgt; cur_pos + 1 < m and house[cur_pos + 1].first <= T;)
                        remove(++cur_pos);
                } else break;
            }
        }
        cout << "Case " << ++cs << ": " << ans << endl;
    }
    return 0;
}
