/*
 * 10683. Decadary Watch
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
#define N 0x400
#define tol 1e-9
typedef long long i64;

char s[N];
i64 hh,mm,ss,cc,w;
long double T,D,W;

i64 conv(char *s) {return (0[s]-'0')*10+(1[s]-'0');}

int main() {

#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	hh = 9, mm = 99, ss = 99, cc = 99;
	T = 100*(100*100*hh + 100*mm + ss) + cc;
	W = 100*(3600*23+60*59)+59+99;
	for(;1==scanf("%s",s);){
		hh = conv(s), mm = conv(s+2), ss = conv(s+4), cc = conv(s+6);
		/*printf("%02lld%02lld%02lld%02lld\n",hh,mm,ss,cc);*/
		D = 100*(hh*60*60+mm*60+ss)+cc;
		w = (i64)(D*125/108.0+tol);
		cc = w % 100, w /= 100, ss = w % 100, w /= 100, mm = w % 100, w /= 100, hh = w;
		printf("%1lld%02lld%02lld%02lld\n",hh,mm,ss,cc);
	}
	return 0;
}

