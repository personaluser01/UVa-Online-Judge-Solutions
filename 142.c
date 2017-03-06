/*
 * 142. Mouse Clicks
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
#define L 0x400
#define N 0x400
#define SQ(x) ((x)*(x))

int m,n,cx[N],cy[N],x,y,w,d,l,bad[N],ax[N],bx[N],ay[N],by[N],regs[N],*ptr,ch;

int inside( int i, int x, int y ) {
	return ax[i] <= x && x <= bx[i] && ay[i] <= y && y <= by[i] ? 1 : 0;
}

int main() {
	char inp[L];
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	for ( l = 0, m = n = 0; 1 == (ch = scanf("%s",inp)) && *inp != '#'; ) {
		if ( *inp == 'I' ) {
			assert( 2 == scanf("%d %d",cx+m,cy+m) ); ++m;
			assert( cx[m-1]<=499 );
			assert( cy[m-1]<=499 );
		}
		else if ( *inp == 'R' ) {
			assert( 4 == scanf("%d %d %d %d",ax+n,ay+n,bx+n,by+n) );
			++n;
			assert( ax[n-1] <= bx[n-1] );
			assert( ay[n-1] <= by[n-1] );
		}
		else {
			if ( (++l) == 1 ) 
				for ( j = 0; j < m; ++j )
					for ( i = 0; i < n; ++i )
						bad[j] |= inside(i,cx[j],cy[j]);
			assert( *inp == 'M' );
			assert( 2 == scanf("%d %d",&x,&y) );
			for ( k = -1, i = 0; i < n; ++i ) 
				if ( inside(i,x,y) ) k = i;
			if ( k >= 0 ) {
				printf("%c\n",k+'A');
				continue ;
			}
			for(d=(1<<30),ptr=regs,i=0;i<m;++i){
				if ( bad[i] ) continue ;
				if ( d>(w=SQ(cx[i]-x)+SQ(cy[i]-y)) )
					d = w, ptr = regs, *ptr++ = i;
				else if ( w == d ) 
					*ptr++ = i;
			}
			if ( ptr == regs ) {
				puts("");
				continue ;
			}
			for ( i = 0; i < ptr-regs; ++i )
				printf("%3d",regs[i]+1);
			putchar('\n');
		}
	} 
	return 0;
}
