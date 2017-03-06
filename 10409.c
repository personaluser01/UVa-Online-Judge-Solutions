/*
 * 10409. Die Game
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
enum { NORTH, WEST, SOUTH, EAST, TOP, BOTTOM };

int c[6],a[256],q,
	p[4][6] = {BOTTOM,WEST,TOP,EAST,NORTH,SOUTH,
			   NORTH,BOTTOM,SOUTH,TOP,WEST,EAST,
			   TOP,WEST,BOTTOM,EAST,SOUTH,NORTH,
			   NORTH,TOP,SOUTH,BOTTOM,EAST,WEST};
char s[0x400];

void rotate( int *c, int *p ) {
	int nc[6],i;
	for ( i = 0; i < 6; ++i )
		nc[p[i]] = c[i];
	for ( i = 0; i < 6; ++i ) c[i] = nc[i];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	a['n'] = NORTH, a['s'] = SOUTH, a['e'] = EAST, a['w'] = WEST;
	for (;1==scanf("%d",&q) && q; printf("%d\n",c[TOP]+1) ) {
		c[TOP] = 0, c[NORTH] = 1, c[SOUTH] = 4, c[WEST] = 2, c[EAST] = 3, c[BOTTOM] = 5;
		for (;q--&&scanf("%s",s)==1;rotate(c,p[a[*s]]));
	}
	return 0;
}
