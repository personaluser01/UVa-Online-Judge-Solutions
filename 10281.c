/*
 * 10281. Average Speed
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

int h,m,s,v,
	lh,lm,ls,lv;
double ax,w;
char buff[0x400];

double f( int v ) {
	return v/18.00/200;
}

double conv( int h, int m, int s ) {
	return 3600.00*h + 60*m + s;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( fgets(buff,sizeof(buff),stdin) ) {
		if ( 4 == sscanf(buff,"%d:%d:%d %d",&h,&m,&s,&v) ) {
			ax += (conv(h,m,s)-conv(lh,lm,ls))*f(lv);
			lh = h, lm = m, ls = s, lv = v;
		}
		else {
			assert( 3 == sscanf(buff,"%d:%d:%d %d",&h,&m,&s,&v) );
			w = ax+(conv(h,m,s)-conv(lh,lm,ls))*f(lv);
			printf("%02d:%02d:%02d %.2lf km\n",h,m,s,w);
		}
	}
	return 0;
}
