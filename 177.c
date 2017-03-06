/*
 * 177. Paper Folding
 * status: Accepted
 * TOPIC: recursion, very nice
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define DBG 0

int sign( int x ) { if ( x < 0 ) return 1; return -1; }

int m,n,x[1 << 16],y[1<<16],skip[1<<16],yes,last[1<<16];
char g[N][N];

void f( int n ) {
	int i,k;
	for(k=0,i=m-2;i>=0&&n;x[m+k]=x[m-1]+y[i]-y[m-1],y[m+k]=y[m-1]-x[i]+x[m-1],--i,++k);
	n&&(m+=k,f(n-1),1);
}

int main() {
	int i,j,k,mix,miy,cx,cy,bot,top,left,right,mx;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n)&&n&&++yes;puts("^") ) {
        memset(g,'*',sizeof g);
        x[0]=y[0]=0,x[1]=1,y[1]=0,m=2,f(n);
        for ( mx=-(mix=miy=(1<<29)),i=0; i < m; ++i ) {
            if ( x[i] < mix ) mix = x[i];
            if ( y[i] < miy ) miy = y[i];
            if ( mx < y[i] ) mx = y[i];
        }
        for ( mx -= miy, i = 0; i < m; x[i] -= mix, y[i] -= miy, ++i );
        for ( i = 0; i < m; ++i )
            k=x[i],x[i]=y[i],y[i]=k,x[i]=mx-x[i];
		DBG && printf("g(%d) = %d\n",n,m);
		for ( i = 0; i < m && DBG; printf("%d %d\n",x[i],y[i]),++i );

        for ( i = 0; i < m; ++i ) {
            x[i] <<= 1, y[i] <<= 1;
            assert( x[i] >= 0 );
            assert( y[i] >= 0 );
        }
        for ( cx = x[0], cy = y[0], i = 1; i < m; ++i ) {
            if ( x[i] == x[i-1] ) {
                g[(x[i]+x[i-1])>>1][(y[i]+y[i-1])>>1]='_';
                cy = y[i];
            }
            else {
                assert(y[i]==y[i-1]);
                g[(x[i]+x[i-1])>>1][(y[i]+y[i-1])>>1]='|';
                cx = x[i];
            }
        }
        for ( top = 0, j = N; j == N && top < N; ++top )
            for ( j = 0; j < N && g[top][j]=='*'; ++j );
        for ( bot = N-1, j = N; j == N && bot >= 0; --bot )
            for ( j = 0; j < N && g[bot][j]=='*'; ++j );
        for ( right = N-1, i = N; i == N && right >= 0; --right )
            for ( i = 0; i < N && g[i][right]=='*'; ++i );
        for ( left = 0, i = N; i == N && left < N; ++left )
            for ( i = 0; i < N && g[i][left]=='*'; ++i );
        --left, --top, ++right, ++bot;
        for ( i = top; i <= bot;) {
            for ( k = 0, j = left; !k && j <= right; ++j )
                k |= (g[i][j]=='|');
            if ( !k ) { ++i; continue ; }
            for ( j = left; j <= right; ++j )
                if ( g[i][j] == '|' )
                    g[i+1][j] = g[i][j], g[i][j] = '*';
            skip[i] = yes, i += 2;
        }
        for ( i = top; i <= bot; last[i++] = j )
            for ( j = right; j >= 0 && g[i][j] == '*'; --j );
        for ( i = top; i <= bot; ++i ) {
            if ( skip[i] == yes ) continue ;
            for ( j = left; j <= right && j <= last[i]; ++j )
                if ( g[i][j] != '*' )
                    putchar(g[i][j]);
                else putchar(' ');
            puts("");
        }
	}
	return 0;
}

