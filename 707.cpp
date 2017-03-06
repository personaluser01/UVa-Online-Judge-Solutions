/*
 * 707. Robbery
 */
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define Q (1UL<<21)
#define M(k) ((1UL<<(k))-1UL)
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
using namespace std;


unsigned int enc( unsigned int x, unsigned int y, unsigned int t ) {
	return x|(y<<7)|(t<<14);
}

int m,n,T,mess,xx[2][N],yy[2][N],tm[N],ts;
unsigned int q[Q],*head,*tail,parent[Q],*ptr,*qtr,*str,out[N];
unsigned char a[(Q>>3)+8],bastardo[(Q>>3)+8];
unsigned char b[(Q>>3)+8];
#define SET(a,k) (a[(k)>>3] |= (M((k)&7)+1))
#define CLR(a,k) (a[(k)>>3] &= ~(M((k)&7)+1))
#define TST(a,k) (a[(k)>>3] & (M((k)&7)+1))

int main() {
	int i,j,k,l,t,x,y,nx,ny;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;3 == scanf("%d %d %d",&m,&n,&T) && (m||n||T);) {
		assert( m <= 100 && n <= 100 && T <= 100 );
		printf("Robbery #%d:\n",++ts);
		for ( scanf("%d",&mess), k = 0; k < mess; ++k )  {
			for ( scanf("%d",tm+k), t = 0; t <= 1; ++t )
				scanf("%d %d",xx[t]+k,yy[t]+k), --xx[t][k], --yy[t][k];
			assert( xx[0][k] <= xx[1][k] );
			assert( yy[0][k] <= yy[1][k] );
			assert( xx[1][k] < m );
			assert( yy[1][k] < n );
			assert( xx[0][k] >= 0 );
			assert( yy[0][k] >= 0 );
			assert( 1 <= tm[k] );
			assert( tm[k] <= T );
		}
		memset(b,0,sizeof(b));
		for ( k = 0; k < mess; ++k )
			for ( x = xx[0][k]; x <= xx[1][k]; ++x )
				for ( y = yy[0][k]; y <= yy[1][k]; ++y )
					SET(b,enc(x,y,tm[k]));
		memset(a,0,sizeof(a));
		memset(bastardo,0,sizeof(bastardo));
		for ( head = tail = q, x = 0; x < m; ++x )
			for ( y = 0; y < n; ++y )
				if ( !TST(b,enc(x,y,1)) )
					SET(a,enc(x,y,1)), parent[*tail++ = enc(x,y,1)] = enc(0,0,0);
		for(;head < tail;)
			for ( u = *head++, x = (u&M(7)), y = ((u>>7)&M(7)), t = (u>>14), i = -1; t < T && i <= 1; ++i )
				for ( j = -1; j <= 1 && t < T; ++j )
					if ( abs(i)+abs(j) <= 1  ) {
						nx = x+i, ny = y+j;
						if ( !vc(nx,ny) )
							continue ;
						v = enc(nx,ny,t+1);
						if ( TST(b,v) ) continue ;
						if ( !TST(a,v) ) 
							SET(a,v), parent[*tail++ = v] = u;
						else SET(bastardo,v);
					}
		ptr = out, *ptr++ = enc(0,0,0);
		for ( t = 1; t <= T; ++t ) {
			for ( k = 0, x = 0; x < m && k <= 1; ++x )
				for ( y = 0; y < n && k <= 1; ++y )
					if ( TST(a,enc(x,y,t)) && ++k )
						v = enc(x,y,t);
			if ( !k ) { goto ESCAPE; }
			if ( k == 1 ) {
				for ( str = ptr-1, *ptr++ = v; !TST(bastardo,v) && (parent[v]>>14)>((*str)>>14); *ptr++ = v = parent[v] );
				for ( qtr = ptr-1, ++str; str < qtr; ++str, --qtr )
					swap(*qtr,*str);
			}
		}
		if ( ptr == out+1 ) {
			puts("Nothing known.\n");
			continue ;
		}
		for ( k = 1; k < ptr-out; ++k ) 
			printf("Time step %u: The robber has been at %lu,%lu.\n",(out[k]>>14),1+(out[k]&M(7)),1+((out[k]>>7)&M(7)));
		putchar('\n');
		continue ;
		ESCAPE: puts("The robber has escaped.\n");
	}
	return 0;
}

