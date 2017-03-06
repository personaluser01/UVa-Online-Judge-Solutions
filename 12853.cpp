/*
 * 12853. The Pony Cart Problem
 * TOPIC: maths, instant centres of velocity, geometry, similarity
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
#define pi (2*acos(0.00))
using namespace std;

int ts,cs;
double d,n;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%lf %lf",&d,&n); ) {
		printf("Case %d: ",++cs);
		printf("%.3lf\n",(d*n/(n-1)*2*pi));
	}
    return 0;
}

