/*
 * 1223. Editor
 * TOPIC: kmr naming, suffix array, lcp array, dbf
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define N (1<<K)
#define K 15
#define MASK(k) (BIT(k)-1UL)
#define BIT(k) (1UL<<(k))
#include <set>
typedef long long i64;
using namespace std;

struct Foo {
	int i,j;
	i64 a,b;
	Foo ( int i, int j, i64 a, i64 b ) {
		this->i = i, this->j = j, this->a = a, this->b = b;
	}
};

	bool operator < ( const Foo &x, const Foo &y ) {
		if ( x.a == y.a ) {
			if ( x.b == y.b ) {
				if ( x.i == y.i )
					return x.j < y.j;
				return x.i < y.i;
			}
			return x.b < y.b;
		}
		return x.a < y.a;
	}


int h,n,L,H,len[K],SA[N],lcp[N];
i64 name[K][N];
char s[N],bts[BIT(21)];
queue<int> q[K][N];
set<Foo *> e;
vector<int> vec[N];

int Bts( unsigned int u ) { return bts[u&MASK(21)]+bts[u>>21]; }

int f( int i, int j ) {
	int low,high,mid;
	if ( i >= n || j >= n )
		return 0;
	assert ( i < n && j < n );
	if ( name[0][i] != name[0][j] )
		return 0;
	for ( high = L, low = 0; low+1<high; ) {
		mid=(low+high)/2;
		if ( name[mid][i] != -1 && name[mid][j] != -1 && name[mid][i] == name[mid][j] )
			low = mid;
		else high = mid;
	}
	return (1<<low)+f(i+(1<<low),j+(1<<low));
}

int main() {
	int i,j,k,ts,l,t,w;
	unsigned int uu;
	i64 prev,ky;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( uu = 0; uu < BIT(21); bts[uu] = bts[uu>>1]+(uu&1), ++uu );
	for ( scanf("%d\n",&ts); ts--; printf("%d\n",w) ) {
		fgets(s,sizeof s,stdin);
		for ( n = 0; s[n] && s[n] != '\n'; ++n );
		for ( uu = 0, s[n++] = 'z'+1, s[n] = '\0', i = 0; i < n; uu|=(1UL<<(s[i++]-'a')) );
		for ( L = 0; (1<<L) < n; ++L );
		for ( i = 0; i <= L; ++i )
			for ( j = 0; j <= n; name[i][j++] = -1 );
		for ( len[H=0]=Bts(uu), i = 0; i < n; ++i )
			q[H][name[H][i]=Bts(uu&MASK(s[i]-'a'))].push(i);
		for (;++H<=L;) {
			for ( i = 0; i < len[H-1]; vec[i++].clear() );
			for ( len[H] = 0, e.clear(), k = 0; k < len[H-1]; ++k ) 
				for (;!q[H-1][k].empty();) {
					j = q[H-1][k].front(), q[H-1][k].pop();
					// printf("Here %d %d\n",j,j-(1<<(H-1)));
					if ( (i=j-(1<<(H-1))) >= 0 )  
						vec[name[H-1][i]].push_back(j);
				}
			for ( i = 0; i < len[H-1]; ++i )
				for ( prev=-1, l = 0; l < (int)vec[i].size(); prev = name[H-1][vec[i][l++]] ) {
					if ( name[H-1][vec[i][l]] != prev ) ++len[H];
					j=vec[i][l]-(1<<(H-1));
					q[H][name[H][j]=len[H]-1].push(j);
				}
		}
		for ( w = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				w = max(w,k = f(i,j));
			}
	}
	return 0;
}

