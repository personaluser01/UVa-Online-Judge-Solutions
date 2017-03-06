/*
 * 11670. Physics Experiment
 * TOPIC: binary search
 * status: In Progress
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N (1<<14)
#define tol 1e-9
#include <set>
using namespace std;

int n,ts,idx[N],Left[N],Right[N],m;
double x[N],D,w,d[N],p[N];

int main() {
	int i,j,k,low,high,mid,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;scanf("%d",&n) && n >0; ) {
		for ( i = 0; i < n; scanf("%lf",&x[i++]) );
		scanf("%lf",&D), sort(x,x+n);
		for ( idx[n-1] = -1, i = 0; i < n-1; ++i ) {
			if ( x[n-1]-x[i] <= D ) { idx[i] = n-1; continue ; }
			if ( x[i+1]-x[i] > D )  { idx[i] = -1;	continue ; }
			assert( x[high = n-1]-x[i] > D );
			assert( x[low = i+1]-x[i] <= D );
			for (;low+1<high; x[mid=(low+high)/2]-x[i]<=D?(low=mid):(high=mid) );
			idx[i] = low;
		}
		for ( t = 0, i = 0; i < n; i = k+1 ) {
			for ( k = i, j = idx[i]; j != -1; k = j, j = idx[j] );
			Left[t] = i, Right[t++] = k;
		}
		for ( i = 0; i < t; ++i ) {
			for ( p[i] = 0, j = Left[i]; j < Right[i]; ++j )
				p[i] += (D-(x[j+1]-x[j]))/2.00;
		}
		for ( w = 0, m = t, i = 0; i < m-1; ++i )
			w += (x[Left[i+1]]-x[Right[i]]-D)/2.00;
		printf("Case %d: %.3lf\n",++ts,w);
	}
	return 0;
}

