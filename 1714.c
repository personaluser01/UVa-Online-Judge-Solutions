/*
 * 1714. Keyboarding
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define MAXV (1<<12)
#define MAXE (1<<21)
#define Q (1<<26)
#define enc(x,pos) ((x)|((pos)<<12))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned int state;

unsigned char a[(Q>>3)+8];
#define SET(k) (a[(k)>>3] |= BIT((k)&7UL))
#define TST(k) (a[(k)>>3] & BIT((k)&7UL))
char g[64][64],txt[1<<14];
int m,n,nx[0x40][0x40][4],
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};
state q[Q],*head,*tail;

int bfs() {
	state u,v;
	int x,i,t,T=1,dist = 0;

	for ( memset(a,0,sizeof a),u=enc(0,0),SET(u),head=tail=q,*tail++=u; head<tail; ) {
		x=((u=*head++)&MASK(12)), t=(u>>12);
		if ( t == n ) return dist;
		if ( g[x&63][x>>6]==txt[t] ) {
			if ( !TST(v=enc(x,t+1)) )
				SET(v), *tail++ = v;
		}
		else {
			for ( i = 0; i < 4; ++i )
				if ( nx[x&63][x>>6][i] != -1 && !TST(v=enc(nx[x&63][x>>6][i],t)) )
					SET(v), *tail++ = v;
		}
		if ( !--T ) T = tail-head, ++dist;
	}
	assert(0);
}

int main() {
	int i,j,k,l,t,ni,nj;
#ifndef ONLINE_JUDGE
	freopen("1714.in","r",stdin);
#endif
	for ( ;2 == scanf("%d %d\n",&m,&n); printf("%d\n",bfs()) ) {
		for ( i = 0; i < m; scanf("%s\n",g[i++]) );
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < 4; ++k ) {
					for ( l = 1; vc(ni=i+dx[k]*l,nj=j+dy[k]*l) && g[ni][nj] == g[i][j];  ++l );
					if ( vc(ni,nj) ) nx[i][j][k] = (ni|(nj<<6));
					else nx[i][j][k] = -1;
				}
		for ( fgets(txt,sizeof txt,stdin), n = 0; txt[n] && txt[n] != '\n'; ++n ); txt[n++] = '*';
	}
	return 0;
};


