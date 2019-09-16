//
// Created by sj on 16/09/19.
//
#include <bits/stdc++.h>
#define MOD (0xffffffffffffffffull)
#define Q (100100)
#define N (1<<21)
#define MAXP (3*Q)
using namespace std;
using u64= unsigned long long;
#define enlist(l) (unique_points[len++]= k)

int unique_points[MAXP],len,
    tp[Q],lft[Q],rgt[Q],n,
    qrp[Q],queries,
    rnk[N];
u64 ans[Q];

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

struct event {
    event_type type;
    int idx, time;
    event( const event_type &type, int idx, int time ) : type(type), idx(idx), time(time) {};
    event& operator = ( event &&other ) {
        this->type= other.type, this->idx= other.idx, this->time= other.time;
        return *this;
    }
    event& operator = ( const event &other ) {
        this->type= other.type, this->idx= other.idx, this->time= other.time;
        return *this;
    }
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
    return a.type == b.type and a.idx == b.idx and a.time == b.time;
}

u64 prefix[3][N];

u64 operator / ( const event &a, const event &b ) {
    assert( b.time >= a.time );
    return prefix[tp[a.idx]-1][b.time-a.time];
}

priority_queue<event,vector<event>,greater<>> pq;
set<event> status_line;

int main() {
    int i,k,ts,cs= 0,m,qr;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( u64 u= 1; u < N; ++u ) {
        prefix[0][u] = prefix[0][u - 1] + u;
        prefix[1][u] = prefix[1][u - 1] + ((u*u)&MOD);
        prefix[2][u] = prefix[2][u - 1] + ((((u*u) & MOD)*u)&MOD);
        for ( i= 0; i < 3; ++i )
            prefix[i][u] &= MOD;
    }
    for ( scanf("%d",&ts); ts-- and 2 == scanf("%d %d",&n,&m); ) {
        for ( len= 0, i= 0; i < m; ++i ) {
            scanf("%d %d %d",tp+i,lft+i,rgt+i);
            enlist(lft[i]), enlist(rgt[i]);
            // push a new event, together with its removal one, into pq
        }
        for ( scanf("%d",&qr), queries= 0; qr-- and 1 == scanf("%d",&k); ++queries ) {
            qrp[queries]= k;
            enlist(k);
            // push a query event into pq
        }
#if 0
        sort(unique_points,unique_points+len);
        n= unique(unique_points,unique_points+len)-unique_points;
        rank_space_reduction(lft,m);
        rank_space_reduction(rgt,m);
        rank_space_reduction(qrp,queries);
#endif
        for ( i= 0; i < m; ++i )
            pq.push(event(event_type::Insertion,i,lft[i]));
        for ( i= 0; i < queries; ++i )
            pq.push({event_type::Query,i,qrp[i]});
        for ( u64 curr= 0; not pq.empty(); ) {
            const event &e= pq.top(); pq.pop();
            if ( e.type == event_type::Insertion ) {
                pq.push(event(event_type::Deletion,e.idx,rgt[e.idx]));
                status_line.insert(e);
                continue ;
            }
            if ( e.type == event_type::Deletion ) {
                status_line.erase(event(event_type::Insertion,e.idx,lft[e.idx]));
                curr+= prefix[tp[e.idx]-1][rgt[e.idx]-lft[e.idx]], curr&= MOD;
                continue ;
            }
            auto &_ans= ans[e.idx]; _ans= curr;
            for ( const auto &entry: status_line )
                _ans+= entry / e, _ans&= MOD;
        }
        assert( status_line.empty() );
        printf("Case %d:\n",++cs);
        for ( i= 0; i < queries; printf("%llu\n",ans[i++]) ) ;
    }
    return 0;
}

