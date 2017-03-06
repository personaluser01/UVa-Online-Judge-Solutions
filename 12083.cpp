/*
 * 12083. Guardian of Decency
 * status: Accepted
 * TOPIC: bipartite matching
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <iostream>
#define N 0x200
enum { L, R };
using namespace std;
#define NX(t) ((t)=(((t)+1)&(N-1)))

char sex[N][2];
int n,music[N],sport[N],M,S,h[N],adj[2][N][N],deg[2][N],v[2][N],m[2],
	seen[N],yes,mate[2][N],g[N][N],head,tail,q[N],cnt;
map<string,int> ms,sp;

int alt_path( int x ) {
	int y,j;
	if ( seen[x] == yes )
		return 0;
	for ( seen[x] = yes, j = 0; j < deg[L][x]; ++j )
		if ( (mate[R][y=adj[L][x][j]]==-1||alt_path(mate[R][y])) ) {
			mate[R][mate[L][x]=y]=x;
			return 1;
		}
	return 0;
}

int bpm() {
	int i,j,k,x,y;
	bool flag;

	for ( cnt = 0, head = tail = 0, i = 0; i < m[L]; ++i )
		q[tail] = i, ++cnt, NX(tail);
	do {
		for ( ++yes, flag = false, k = cnt; k--; ) {
			x = q[head], head = NX(head), --cnt;
			if ( alt_path(x) ) flag = true;
			else q[tail] = x, NX(tail), ++cnt;
		}
	} while ( flag );
	return m[L]-cnt;
}

int main() {
	int i,j,k,ts,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( t = L; t <= R; ++t )
			for ( m[t] = 0, i = 0; i < n; deg[t][i++] = 0 );
		for ( M = S = 0, ms.clear(), sp.clear(), i = 0; i < n; ++i ) {
			char tmp0[N],tmp1[N];
			scanf("%d %s %s %s",h+i,sex[i],tmp0,tmp1);
			if ( ms.find(string(tmp0)) == ms.end() )
				ms[string(tmp0)] = M++;
			if ( sp.find(string(tmp1)) == sp.end() )
				sp[string(tmp1)] = S++;
			music[i] = ms[string(tmp0)];
			sport[i] = sp[string(tmp1)];
			if ( sex[i][0] == 'M' )
				v[L][m[L]++] = i;
			else v[R][m[R]++] = i;
		}
		for ( i = 0; i < m[L]; ++i )
			for ( mate[L][i] = -1, j = 0; j < m[R]; ++j ) {
				mate[R][j] = -1;
				if (music[v[L][i]]==music[v[R][j]]&&sport[v[L][i]]!=sport[v[R][j]]&&abs(h[v[L][i]]-h[v[R][j]])<=40)
					adj[L][i][deg[L][i]++] = j;
			}
		printf("%d\n",m[L]+m[R]-bpm());
	}
	return 0;
}

