/*
 * 11329. Curious Fleas
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 4
#define Q (1 << (14+6+4))
#define MASK(k) (BIT(k)-1ULL)
#define BIT(k) (1ULL<<(k))
#define SET(u,k) ((u)|=BIT(k))
#define CLR(u,k) ((u)&=~BIT(k))
#define TST(u,k) ((u)&BIT(k))
#define enc(u,v,x,y) ((u)|((v)<<14)|((x)<<20)|((y)<<22))
#define vc(x,y) (0<=(x)&&(x)<N&&0<=(y)&&(y)<N)
typedef unsigned int state;
#define oo 0xfffffffful
enum { NOR, WES, SOU, EAS, TOP, DOWN };
#define conservation_of_fleas(u) (assert(bts[s[(u)&MASK(14)]]+bts[((u)>>14)&MASK(6)]==6))

char bts[1 << (N*N)],
	 dx[]={-1,0,1,0},
	 dy[]={0,-1,0,1},
	 perm[4][6] = {
			 		TOP,WES,DOWN,EAS,SOU,NOR,
					NOR,TOP,SOU,DOWN,EAS,WES,
					DOWN,WES,TOP,EAS,NOR,SOU,
					NOR,DOWN,SOU,TOP,WES,EAS
	 			  },
	 iperm[4][6];

state s[1<<14],*ptr = s,q[Q],*head,*tail,*marker;
unsigned char seen[(Q>>3)+8];
#define SET_SEEN(u) (SET(seen[(u)>>3],(u)&7))
#define VISITED(u) (TST(seen[(u)>>3],(u)&7))

unsigned int which( unsigned int u ) {
	unsigned int i,j,k;
	assert( bts[u] <= 6 );
	if ( s[0] == u ) return 0;
	for ( i = 0, j = ptr-s-1; i+1 != j; s[k=(i+j)/2]<u?(i=k):(j=k));
	assert( s[j] == u );
	return j;
}

state roll_over( state u, int dir ) {
	int x,y,nx,ny,
		i,j,k;
	unsigned int v = 0,
				 die = (u>>14)&MASK(6),
				 new_die = 0;

	conservation_of_fleas(u);
	x = (u>>20)&MASK(2), y = (u>>22);
	nx = x+dx[dir], ny = y+dy[dir];
	if ( !vc(nx,ny) )
		return +oo;
	for ( i = NOR; i <= DOWN; ++i )
		if ( TST(die,perm[dir][i]) && SET(new_die,i) );
	assert( bts[die]==bts[new_die] );
	v = s[u&MASK(14)];
	if ( ((die>>dir)&1)^(v>>(N*nx+ny)&1) ) {
		if ( TST(die,dir) ) {
			assert( TST(new_die,iperm[dir][dir]) );
			SET(v,N*nx+ny);
			CLR(new_die,iperm[dir][dir]);
		}
		else {
			assert( TST(v,N*nx+ny) );
			CLR(v,N*nx+ny);
			SET(new_die,iperm[dir][dir]);
		}
	}
	assert( bts[v]+bts[new_die]==6 );
	v = which(v), v = enc(v,new_die,nx,ny);
	conservation_of_fleas(v);
	return v;
}

unsigned int
bfs( state src ) {
	unsigned int u,v,dist,i;
	memset(seen,0,sizeof(seen));
	head = tail = q, dist = 0;
	conservation_of_fleas(src);
	for(SET_SEEN(src),*tail++=src,marker=tail;head<tail;) {
		u = *head++;
		conservation_of_fleas(u);
		if ( head == marker+1 ) 
			++dist, marker = tail;
		if ( (u&MASK(14)) == 0 ) 
			return dist;
		for ( i = NOR; i <= EAS; ++i )
			if ( (v = roll_over(u,i)) < +oo && !VISITED(v) )
				*tail++ = v, SET_SEEN(v);
	}
	return dist;
}

int main() {
	int i,j,k,l,t,ts;
	unsigned int u,v,sx,sy;
	char tmp[0x80];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < 4; ++i )
		for ( j = NOR; j <= DOWN; ++j )
			iperm[i][perm[i][j]] = j;
	for ( u = 0; u < (1 << (N*N)); ++u )
		if ( (bts[u] = bts[u>>1]+(u&1)) <= 6 )
			*ptr++ = u;
	for ( scanf("%d",&ts); ts--; ) {
		for ( u = 0, i = 0; i < N; ++i ) {
			scanf("%s",tmp);
			for ( j = 0; j < N; ++j )
				if (tmp[j]=='D')
					sx = i, sy = j;
				else if ( tmp[j]=='X' )
					SET(u,i*N+j);
		}
		printf("%u\n",bfs(enc(which(u),0,sx,sy)));
	}
	return 0;
}

