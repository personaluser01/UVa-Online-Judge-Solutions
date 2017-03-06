/*
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 17)

int left[N],right[N],n,m;

int main() {
    int i,j,k,x,y;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    while ( 2 == scanf("%d %d",&n,&m) && (n||m) ) {
        for ( i = 0; i < n; ++i )
            left[i] = i-1, right[i] = i+1;
        while ( m-- && 2 == scanf("%d %d",&i,&j) ) {
            x = left[--i], y = right[--j];
            if ( y < n )
                left[y] = x;
            if ( x >= 0 )
                right[x] = y;
            if ( x < 0 && y >= n )
                puts("* *");
            else if ( y >= n )
                printf("%d *\n",x+1);
            else if ( x < 0 )
                printf ("* %d\n",y+1);
            else printf("%d %d\n",x+1,y+1);
        }
        puts("-");
    }
    return 0;
}

