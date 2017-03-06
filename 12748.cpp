/*
 * 12748. WiFi Access
 * TOPIC: maths, geometry
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define N 0x80
#define S(x) ((x)*(x))

int ts,cs,n,qr;
double x[N],y[N],r[N],sx,sy;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&n,&qr);
		for ( i = 0; i < n; ++i ) 
			scanf("%lf %lf %lf",x+i,y+i,r+i);
		for ( printf("Case %d:\n",++cs); qr-- && 2 == scanf("%lf %lf",&sx,&sy); ) {
			for ( k = 0, i = 0; i < n && !k; ++i ) 
				if ( S(sx-x[i])+S(sy-y[i]) <= S(r[i]) ) ++k;
			puts(k?"Yes":"No");
		}
	}
    return 0;
}

