//
// Created by sj on 16/09/19.
// TOPIC: lazy propagation, segment tree, sweep-line
//
#include <bits/stdc++.h>
#define MOD (0xffffffffffffffffull)
#define Q (100100)
using namespace std;

enum class event_type {
    Insertion,
    Query,
    Deletion
};

class event {
public:
    event_type type;
    event &parent;
    int time;
};

bool operator < ( const event &a, const event &b ) {
    if ( a.time < b.time )
        return true ;
    if ( a.time > b.time )
        return false ;
    if ( a.type == b.type )
        return false ;
    if ( a.type == event_type::Insertion )
        return true ;
    return a.type == event_type::Query and b.type == event_type::Deletion;
}

bool operator == ( const event &a, const event &b ) {
    //TODO
    return a.time == b.time and a.type == b.type;
}

int ans[Q];
priority_queue<vector<event>,greater<event>> pq;

int main() {
    int i,j,k,ts,cs= 0,n,m,tp,qr;
    for ( scanf("%d",&ts); ts-- and 2 == scanf("%d %d",&n,&m); ) {
        for ( i= 0; i < m; ++i ) {
            scanf("%d %d %d",&tp,&j,&k);
            // push a new event, together with its removal one, into pq
        }
        for ( scanf("%d",&qr); qr-- and 1 == scanf("%d",&k); ) {
            // push a query event into pq
        }
        // process the pq
        while ( not pq.empty() ) {
            auto e= pq.front(); pq.pop();
            if ( e.type == event_type::Query ) {
            }
        }
    }
    return 0;
}

