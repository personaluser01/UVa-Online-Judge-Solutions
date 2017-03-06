/*
 * 145. Gondwanaland Telecom
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

int max( int x, int y ) { return x < y ? y : x; }
int min( int x, int y ) { return x < y ? x : y; }

long double m[5][4] = {0.10,0.06,0.02,0.02,
					   0.25,0.15,0.05,0.05,
					   0.53,0.33,0.13,0.13,
					   0.87,0.47,0.17,0.17,
					   1.44,0.80,0.30,0.30};

int conv( char *s ) {
	return 10*(s[0]-'0')+(s[1]-'0');
}

int f( int s, int e ) {
	int a = 8*60, b = 18*60;
	if ( e < s ) return ;
	if (a>e||b<s) return 0;
	return min(e,b)-max(s,a);
}

int g( int s, int e ) {
	int a = 18*60, b = 22*60;	
	if ( e < s ) return ;
	if (a>e||b<s) return 0;
	return min(e,b)-max(s,a);
}

int h( int s, int e ) {
	int a = 22*60, b = 24*60;
	if ( e < s ) return ;
	if (a>e||b<s) return 0;
	return min(e,b)-max(s,a);
}

int n( int s, int e ) {
	int a = 0, b = 8*60;
	if ( e < s ) return ;
	if (a>e||b<s) return 0;
	return min(e,b)-max(s,a);
}


int main() {
	char sth[8],stm[8],eh[8],em[8],step[0x400],num[0x400];
	int st,en,c[3],aa,bb,cc,dd;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 6 == scanf("%s %s %s %s %s %s",step,num,sth,stm,eh,em) ) {
		st = 60*conv(sth)+conv(stm), en = 60*conv(eh)+conv(em);
		if ( st == en ) {
			c[0] = 10*60, c[1] = 4*60, c[2] = 2*60+8*60;
		}
		else if ( en < st ) {
			aa = 0, bb = en, cc = st, dd = 24*60;
			c[0] = f(aa,bb)+f(cc,dd);
			c[1] = g(aa,bb)+g(cc,dd);
			c[2] = h(aa,bb)+h(cc,dd)+n(aa,bb)+n(cc,dd);
		}
		else {
			c[0] = f(st,en);
			c[1] = g(st,en);
			c[2] = h(st,en)+n(st,en);
		}
		printf("%10s%6d%6d%6d%3s%8.2Lf\n",num,c[0],c[1],c[2],step,m[*step-'A'][0]*c[0]+m[*step-'A'][1]*c[1]+m[*step-'A'][2]*c[2]);
	}
	return 0;
}
