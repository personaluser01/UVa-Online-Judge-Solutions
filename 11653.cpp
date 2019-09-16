//
// Created by sj on 16/09/19.
//
#include <bits/stdc++.h>
#define MOD (0xffffffffffffffffull)
#define Q (100100)
#define N (1<<21)
#define MAXP (3*Q)
using namespace std;
using i64= long long;
#define enlist(l) (unique_points[len++]= k)

int ans[Q],unique_points[MAXP],len,
    tp[Q],lft[Q],rgt[Q],n,
    qrp[Q],queries,
    rnk[N];

void rank_space_reduction( int *x, int n ) {
    for ( int i= 0; i < n; ++i )
        rnk[x[i]]= lower_bound(unique_points,unique_points+n,x[i])-unique_points, x[i]= rnk[x[i]];
}

int original_value( int r ) {
    assert( 0 <= r and r < n );
    return unique_points[r];
}

enum class event_type {
    Insertion,
    Query,
    Deletion
};

class general_event {
protected:
    const event_type type;
    int time;
public:
    general_event( const event_type &type ) : type(type) {};
    friend bool operator < ( const general_event &a, const general_event &b ) ;
};

class update_event : public general_event {
public:
    update_event( const event_type &type, int time ) : general_event(type) {
        this->time= time;
    }
};

class query_event : public general_event {
public:
    query_event( int time ) : general_event( event_type::Query ) {
        this->time= time;
    }
};

bool operator < ( const general_event &a, const general_event &b ) {
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

int main() {
    int i,j,k,ts,cs= 0,n,m,tp,qr;
    for ( scanf("%d",&ts); ts-- and 2 == scanf("%d %d",&n,&m); ) {
        for ( len= 0, i= 0; i < m; ++i ) {
            scanf("%d %d %d",&tp[i],&lft[i],&rgt[i]);
            enlist(lft[i]), enlist(rgt[i]);
            // push a new event, together with its removal one, into pq
        }
        for ( scanf("%d",&qr), queries= 0; qr-- and 1 == scanf("%d",&k); ++queries ) {
            qrp[queries]= k;
            enlist(k);
            // push a query event into pq
        }
        sort(unique_points,unique_points+len);
        n= unique(unique_points,unique_points+len)-unique_points;
        rank_space_reduction(lft,m);
        rank_space_reduction(rgt,m);
        rank_space_reduction(qrp,queries);
    }
    return 0;
}

