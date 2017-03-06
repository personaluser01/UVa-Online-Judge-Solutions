/*
 * 1251. Repeated Substitution with SED
 * TOPIC: bfs, bitmasks
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <queue>
typedef unsigned long long u64;
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#include <map>
#include <set>
#define MAXR 11
#define oo (0xffffffffffffffffull)
using namespace std;

u64 from[MAXR],to[MAXR],src,sink;
int rules,limit,SH,L = 5,dest_len;

u64 convert( char *c, map<char,char> &id ) {
	u64 u = 0,i;
	for ( i = 0; c[i]; u |= (((u64)(id[c[i]]-'a'+1))<<(i*SH+L)), ++i );
	assert( i < (1<<L) );
	assert( L+i*SH < 63 );
	return u|i;
}

map<u64,unsigned int> mp;
queue<u64> q;

u64 apply( u64 u, int rule ) {
	assert( 0 <= rule && rule < rules );
	u64 v = 0,F = from[rule],T = to[rule];
	int i,j,k,t,len = (u&MASK(L)),new_len = len,l,
			pos[0x20],*top = pos,n,m;
	if ( F == T ) return u;
	n = (F&MASK(L)), m = (T&MASK(L));
	for ( i = 0; i < len && new_len < (1<<L); i = k+1 ) {
		for ( j = i; (k=j+n-1) < len && ((u>>(L+(j*SH)))&MASK(SH*n)) != (F>>L) ; ++j ) ;
		if ( k < len ) 
			if ( (*++top=j,new_len-=n,new_len+=m)*SH+L >= 63 && n < m || new_len >= (1<<L) || new_len > dest_len )
				return +oo;
	}
	if ( new_len > dest_len || L+SH*new_len >= 63 || new_len >= (1<<L) ) return +oo;
	if ( top == pos ) return +oo;
	for ( t = 0, l = 0, i = 1; i <= top-pos; ++i ) {
		j = pos[i], k = j+n-1;
		assert( k < len );
		assert( j >= t );
		v |= ((u>>(t*SH+L))&MASK((j-t)*SH)) << (SH*l+L);
		l += (j-t);
		v |= (T>>L) << (SH*l+L);
		l += m, t = pos[i]+n;
	}
	if ( l < new_len ) {
		j = len;
		v |= ((u>>(t*SH+L))&MASK((j-t)*SH)) << (SH*l+L);
		l += (j-t);
	}
	assert( l == new_len );
	return v|(new_len);
}

map<u64,u64> parent;
map<u64,int> _move;

void dump( u64 src, u64 u ) {
	if ( u == src ) return ;
	assert( parent.find(u) != parent.end() );
	dump(src,parent[u]);
	printf("Rules %d\n",_move[u]+1);
}

unsigned int bfs( map<u64,unsigned int> &s, unsigned int LS ) {
	u64 u,v;
	unsigned int d;
	for (;!q.empty(); q.pop());
	for ( s.clear(), q.push(src), s[src] = 0; !q.empty() && q.size() < LS; ) {
		u = q.front(), q.pop(), d = s[u];
		if ( u == sink ) {
			// dump(src,sink);
			return d;
		}
		//printf("d = %u\n",d);
		for ( int i = 0; i < rules; ++i ) 
			if ( (v = apply(u,i)) < +oo ) {
				if ( s.find(v) == s.end() )
					s[v] = d+1, q.push(v);//, parent[v] = u, _move[v] = i;
				else {
					assert( s[v] <= d+1 ) ;
				}
			}
	}
	return 0xfffffffful;
}

int main() {
	int i,j,k;
	char tmpa[0x40],tmpb[0x40],
		ff[0x40][0x40],tt[0x40][0x40];
	map<char,char> id;
	unsigned int ans,d;
	char next;
	u64 u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;1==scanf("%d",&rules) && rules; ) {
		for ( i = 0; i < rules; ++i ) 
			scanf("%s %s",ff[i],tt[i]);
		id.clear(), next = 'a';
		scanf("%s %s",tmpa,tmpb);
		for ( i = 0; tmpa[i]; ++i )
			if ( id.find(tmpa[i]) == id.end() )
				id[tmpa[i]] = next++;
		for ( i = 0; tmpb[i]; ++i )
			if ( id.find(tmpb[i]) == id.end() )
				id[tmpb[i]] = next++;
		for ( i = 0; i < rules; ++i ) {
			for ( j = 0; ff[i][j]; ++j )
				if ( id.find(ff[i][j]) == id.end() )
					id[ff[i][j]] = next++;
			for ( j = 0; tt[i][j]; ++j )
				if ( id.find(tt[i][j]) == id.end() )
					id[tt[i][j]] = next++;
		}
		for ( SH = 0; (1<<SH) < id.size(); ++SH );
		for ( ++SH, i = 0; i < rules; ++i ) 
			from[i] = convert(ff[i],id), to[i] = convert(tt[i],id);
		src = convert(tmpa,id), sink = convert(tmpb,id);
		dest_len = sink&MASK(L);
		ans = bfs(mp,(1<<21));
		if ( ans < 0xfffffffful ) {
			printf("%u\n",ans);
			continue ;
		}
		else printf("-1\n");
	}
	return 0;
}

