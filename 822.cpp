/*
 * 822. Queue and A
 * TOPIC: simulation, priority queue
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#define MAXT 21
#define MAXN 5
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define GET_TYPE(e) ((e)&1)
#define GET_ID(e) (((e)>>1)&MASK(5))
#define GET_TIME(e) ((e)>>6)
#define enc(tp,id,time) ((tp)|((id)<<1)|((time)<<6))
#define oo (1LL<<60)
typedef unsigned long long u64;
typedef long long i64;
typedef u64 Event;
enum { E1=0, E2=1 };
using namespace std;

map<int,int> tmap;
int timeNeeded[MAXT],t0[MAXT],dt[MAXT],reqs[MAXT],m,n,cs,
	total, completed;

struct StaffMember {
	int id,rank[MAXT],k,pos;
	i64 last, freeAt;
	bool operator < ( const StaffMember &other ) const {
		if ( last == other.last )
			return pos<other.pos;
		return last<other.last;
	}
	void execute( int jobId, i64 curTime ) {
		assert( jobId < m );
		last = curTime, freeAt = last + timeNeeded[jobId], ++completed;
	}
};

StaffMember s[MAXN];

struct cmpStaffMember {
	bool operator() ( const int &a, const int &b ) const {
		return s[a]<s[b];
	}
};

struct cmpEvents {
	bool operator() ( const Event &a, const Event &b ) const {
		u64 i = GET_TIME(a), j = GET_TIME(b);
		return i > j;
	}
};

priority_queue<Event,vector<Event>,cmpEvents> pq;
set<Event> lst;
set<int> pool;

void simulate() {
	int i,j,k,l;
	i64 curTime = -oo;
	Event e;
	bool flag,f;

	assert( pq.empty() );
	total = completed = 0;
	for ( i = 0; i < m; ++i ) 
		for ( total += reqs[i], j = 0; j < reqs[i]; ++j ) 
			pq.push(enc(E1,i,t0[i]+j*dt[i]));

	for (;completed < total;) {
		for ( lst.clear(); !pq.empty() && (i64)GET_TIME(pq.top()) <= curTime; lst.insert(pq.top()), pq.pop() );
		assert( !pq.empty() );
		assert( curTime < (i64)GET_TIME(pq.top()) );
		for ( curTime = (i64)GET_TIME(pq.top()); !pq.empty() && (i64)GET_TIME(e = pq.top()) == curTime; pq.pop() )
			if ( GET_TYPE(e) == E1 ) 
				lst.insert(e);
			else {
				assert( pool.find(GET_ID(e)) == pool.end() );
				pool.insert(GET_ID(e));
			}
		//printf("%lld\n",curTime);
		do {
			map<Event,int> whoIsAssigned;
			whoIsAssigned.clear();
			flag = false ;
			for ( set<int,cmpStaffMember>::iterator it = pool.begin(); it != pool.end(); ++it ) {
				j = *it, f = false, e = +oo;
				for ( set<Event>::iterator jt = lst.begin(); jt != lst.end(); ++jt )
					if ( s[j].rank[GET_ID(*jt)] != -1 )
						if ( !f || s[j].rank[GET_ID(e)] < s[j].rank[GET_ID(*jt)] )
							e = *jt, f = true ;
				if ( f )
					if ( whoIsAssigned.find(e) == whoIsAssigned.end() || s[j] < s[whoIsAssigned[e]] )
						whoIsAssigned[e] = j;
			}
			for ( map<Event,int>::iterator it = whoIsAssigned.begin(); it != whoIsAssigned.end(); ++it ) {
				e = it->first, j = it->second;
				if ( pool.find(j) == pool.end() || lst.find(e) == lst.end() ) continue ;
				s[j].execute(GET_ID(e),curTime>GET_TIME(e)?curTime:GET_TIME(e));
				pq.push(enc(E2,j,s[j].freeAt));
				flag = true ;
				pool.erase(j); lst.erase(e);
			}
		} while ( flag );
		for ( set<Event>::iterator it = lst.begin(); it != lst.end(); pq.push(*it++) );
	}
	for (;!pq.empty(); curTime = max(curTime,(i64)GET_TIME(pq.top())), pq.pop() );
	printf("Scenario %d: All requests are serviced within %lld minutes.\n",++cs,curTime);
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&m) && m ) {
		for ( tmap.clear(), i = 0; i < m; ++i ) {
			scanf("%d",&k);
			assert ( tmap.find(k) == tmap.end() );
			tmap[k] = i;
			scanf("%d %d %d %d",reqs+i,t0+i,timeNeeded+i,dt+i);
		}
		for ( pool.clear(), scanf("%d",&n), j = 0; j < n; ++j ) {
			scanf("%d %d",&s[j].id,&s[j].k), s[j].pos = j;
			for ( i = 0; i <= m; ++i ) s[j].rank[i] = -1;
			for ( i = 0; i < s[j].k; ++i ) {
				scanf("%d",&k);
				assert( tmap.find(k) != tmap.end() );
				s[j].rank[tmap[k]] = s[j].k-i;
			}
			s[j].last = s[j].freeAt = -1, pool.insert(j);
		}
		assert( pool.size() == n );
		simulate();
	}
	return 0;
}

