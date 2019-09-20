//
// 10619: Advanced Causal Measurements
// TOPIC: event-driven simulation, priority queue, greedy, covering intervals, binary search, exponential search
// status: Accepted
//
#include <bits/stdc++.h>
#define oo (1LL<<60)
#define N (1<<17)
using namespace std;
using i64= long long;

template<typename T>
struct event {
    T t,x;
    event() = default;
    event( T t, T x ) : t(t), x(x) {};
};

template <typename T>
istream &operator >> ( istream &is, event<T> &e ) {
    return is >> e.t >> e.x;
}

enum class event_type {
    Insertion,
    Deletion
};

template<typename T>
struct cell {
    int id;
    T time;
    event_type type;
    cell() = default;
    cell( int id, T time, event_type type ): id(id), time(time), type(type) {};
};

template<typename T>
bool operator < ( const cell<T> &lhs, const cell<T> &rhs ) {
    if ( lhs.time == rhs.time )
        return not(lhs.type == event_type::Deletion);
    return lhs.time > rhs.time;
}

event<i64> e[N];
int n,m;
pair<i64,i64> segments[N];
priority_queue<cell<i64>,vector<cell<i64>>> pq;

int cover( const i64 instant ) {
    int i,j,k,nails= 0;
    i64 last_nail= -oo;
    for ( i= 0; i < n; ++i ) {
        auto d= (e[i].t-instant);
        assert( d >= 0 );
        segments[i]= {e[i].x-d,e[i].x+d};
    }
    assert( pq.empty() );
    for ( i= 0; i < n; pq.push({i,segments[i].first,event_type::Insertion}), ++i ) ;
    while ( not pq.empty() ) {
        auto item= pq.top(); pq.pop();
        auto idx= item.id;
        if ( item.type == event_type::Insertion ) {
            pq.push({idx,segments[idx].second,event_type::Deletion});
            continue ;
        }
        if ( last_nail < segments[idx].first )
            ++nails, last_nail= segments[idx].second;
    }
    return nails;
}

int main() {
    int ts,cs= 0;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( cin >> ts; ts-- and (cin >> n >> m); ) {
        cout << "Case " << ++cs << ": ";
        for ( int i= 0; i < n; cin >> e[i++] ) ;
        i64 earliest= numeric_limits<i64>::max();
        for ( int i= 0; i < n; ++i )
            if ( e[i].t < earliest )
                earliest= e[i].t;
        i64 low= -oo, high= earliest, mid;
        assert( cover(low) <= m );
        if ( cover(earliest) <= m ) {
            cout << earliest << endl;
            continue;
        }
        assert( cover(high) > m );
        i64 good= 57, bad= 0;
        for ( ;bad+1 < good; cover(high-(1LL<<(mid=(good+bad)/2))+1)> m?(bad= mid):(good= mid) ) ;
        for ( low= high-(1LL<<good)+1; low+1 < high; cover(mid= (low+high)/2) > m ?(high= mid):(low= mid) ) ;
        cout << low << endl;
    }
    return 0;
}

