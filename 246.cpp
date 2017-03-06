/*
 * 246. 10-20-30
 * TOPIC: ad hoc, simulation, deque
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <set>
#define M 7
#define Q 0x400
#define NX(k) ((k)=((k)+1)&(Q-1))
#define PR(k) ((k)=((k)+Q-1)&(Q-1))
using namespace std;

int q[M][Q],has_disappeared[M],yes,que[Q],head[M],tail[M],H,T,CNT,cnt[M];
set<string> s;

void pb( int x ) { que[T] = x, NX(T), NX(CNT); };
void init( int i ) { head[i] = tail[i] = 0, cnt[i] = 0; };

string snapshot( int cur ) {
	char tmp[0x400],*ptr = tmp;
	int i,j,k,l;
	for ( i = 0; i < M; ++i, ptr += sprintf(ptr,"|") )
		for ( l = cnt[i], k = head[i]; l--; ptr += sprintf(ptr,"%d ",q[i][k]), NX(k) );
	for ( l = CNT, k = H; l--; ptr += sprintf(ptr,"%d ",que[k]), NX(k) );
	ptr += sprintf(ptr,"| %d",cur);
	string t(tmp);
	return t;
};

int main() {
	int i,j,k,l,t,score,cur,x,y,z;
	bool changed_happening,flag;
#ifndef ONLINE_JUDGE
	freopen("246.in","r",stdin);
#endif
	for ( ;1 == scanf("%d",&k) && k > 0; ) {
		for ( CNT = 0, T=H=0, pb(k), i = 1; i < 52; ++i, scanf("%d",&k), pb(k) );
		for ( s.clear(), i = 0; i < M; init(i++) );
		for ( ++yes, score = 0, cur = -1; CNT; ++score ) {
			for ( l = 0; has_disappeared[cur=(cur+1)%M] == yes && l < M; ++l );
			if ( l == M ) { printf("Win : %d\n",score); goto next; }
			string tt = snapshot(cur);
			if ( s.count(tt) ) {
				printf("Draw: %d\n",score);
				goto next;
			}
			s.insert(tt);
			k = que[H], NX(H), PR(CNT), q[cur][tail[cur]] = k, NX(tail[cur]), NX(cnt[cur]);
			for ( flag = true; flag && cnt[cur] >= 3; ) {
				flag = false, x = q[cur][head[cur]], y = q[cur][(head[cur]+1)&(Q-1)], z = q[cur][(tail[cur]+Q-1)&(Q-1)];
				if ( x+y+z == 10 || x+y+z == 20 || x+y+z == 30 ) {
					NX(head[cur]), NX(head[cur]), PR(tail[cur]), PR(cnt[cur]), PR(cnt[cur]), PR(cnt[cur]);
					pb(x), pb(y), pb(z), flag = true ;
					goto nx;
				}
				x = q[cur][head[cur]], y = q[cur][(tail[cur]+Q-2)&(Q-1)], z = q[cur][(tail[cur]+Q-1)&(Q-1)];
				if ( x+y+z == 10 || x+y+z == 20 || x+y+z == 30 ) {
					NX(head[cur]), PR(tail[cur]), PR(tail[cur]), PR(cnt[cur]), PR(cnt[cur]), PR(cnt[cur]);
					pb(x), pb(y), pb(z), flag = true ;
					goto nx;
				}
				x = q[cur][(tail[cur]+Q-3)&(Q-1)], y = q[cur][(tail[cur]+Q-2)&(Q-1)], z = q[cur][(tail[cur]+Q-1)&(Q-1)];
				if ( x+y+z == 10 || x+y+z == 20 || x+y+z == 30 ) {
					PR(tail[cur]), PR(tail[cur]), PR(tail[cur]), PR(cnt[cur]), PR(cnt[cur]), PR(cnt[cur]);
					pb(x), pb(y), pb(z), flag = true ;
					goto nx;
				}
				nx: continue ;
			}
			if ( cnt[cur] == 0 ) has_disappeared[cur] = yes;
		}
		printf("Loss: %d\n",score);
next:;
	}
	return 0;
}

