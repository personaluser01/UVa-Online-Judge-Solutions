//
// Created by sj on 16/09/19.
//
#include <bits/stdc++.h>
#define MOD (0xffffffffffffffffull)
#define Q (100100)
#define N (1000001)
using namespace std;
using u64= unsigned long long;

int tp[Q],lft[Q],rgt[Q],n,
    qrp[Q],queries;
u64 ans[Q];

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
    event( const event &other ) {
        this->type= other.type, this->idx= other.idx, this->time= other.time;
    }
    bool operator < ( const event &b ) {
        if ( time < b.time )
            return true ;
        if ( time > b.time )
            return false ;
        if ( type == b.type )
            return false ;
        if ( type == event_type::Insertion )
            return true ;
        return type == event_type::Query and b.type == event_type::Deletion;
    }
};

bool operator == ( const event &a, const event &b ) {
    return a.type == b.type and a.idx == b.idx and a.time == b.time;
}

bool operator < ( const event &a, const event &b ) {
    if ( a == b )
        return false ;
    if ( a.time < b.time )
        return false ;
    if ( a.time > b.time )
        return true;
    if ( a.type == b.type )
        return false;
    return a.type != event_type::Query;
    /*
    if ( a.type == event_type::Query )
        return true ;
    return not(a.type == event_type::Query and b.type == event_type::Deletion);
     */
}

bool operator > ( const event &a, const event &b ) {
    return b < a;
}

u64 prefix[3][N];

u64 operator / ( const event &a, const event &b ) {
    //assert( b.time >= a.time );
    return prefix[tp[a.idx]-1][b.time-a.time];
}

//priority_queue<event,vector<event>,greater<>> pq;
priority_queue<event,vector<event>> pq;
//set<event> status_line;
map<int,int> series[3];

u64 calculate( int t, int l, int r ) {
    return prefix[t][r-l];
}

int main() {
    int i,ts,cs= 0,m,qr;
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
        for ( i= 0; i < m; ++i )
            scanf("%d %d %d",tp+i,lft+i,rgt+i);
        for ( scanf("%d",&qr), queries= 0; qr-- and 1 == scanf("%d",&qrp[queries++]); ) ;
        for ( i= 0; i < m; ++i )
            pq.push(event(event_type::Insertion,i,lft[i]));
        for ( i= 0; i < queries; ++i )
            pq.push(event(event_type::Query,i,qrp[i]));
        //status_line.clear();
        for ( int tt= 0; tt < 3; series[tt++].clear() ) ;
        for ( u64 curr= 0; not pq.empty(); ) {
            const event &e= pq.top(); pq.pop();
            if ( e.type == event_type::Insertion ) {
                pq.push(event(event_type::Deletion,e.idx,rgt[e.idx]));
                //status_line.insert(e);
                auto &mp= series[tp[e.idx]-1];
                if ( mp.count(lft[e.idx]) )
                    ++mp[lft[e.idx]];
                else mp[lft[e.idx]]= 1;
                continue ;
            }
            if ( e.type == event_type::Deletion ) {
                //auto res= status_line.erase(event(event_type::Insertion,e.idx,lft[e.idx]));
                //assert( res > 0 );
                curr+= prefix[tp[e.idx]-1][rgt[e.idx]-lft[e.idx]], curr&= MOD;
                auto &mp= series[tp[e.idx]-1];
                if( not --mp[lft[e.idx]] )
                    mp.erase(lft[e.idx]);
                continue ;
            }
            //assert( e.type == event_type::Query );
            ans[e.idx]= curr;
            /*for ( const auto &entry: status_line ) {
                ans[e.idx] += entry / e, ans[e.idx] &= MOD;
            }
            */
            for ( int tt= 0; tt < 3; ++tt )
                for ( const auto &it: series[tt] ) {
                    assert( it.first <= qrp[e.idx] );
                    ans[e.idx]+= it.second*calculate(tt,it.first,qrp[e.idx]);
                    ans[e.idx]&= MOD;
                }
        }
        printf("Case %d:\n",++cs);
        for ( i= 0; i < queries; printf("%llu\n",ans[i++]) ) ;
    }
    return 0;
}

