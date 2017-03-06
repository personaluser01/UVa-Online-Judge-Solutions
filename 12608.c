/*
 * 12608. Garbage collection
 * TOPIC: simulation, excellent interview question, binary search
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#define MAXW 0x400
#define N 0x400

int W,n,x[N],w[N],pref[N];

int main() {
	int i,j,k,ts,good,bad,mid,covered;
#ifndef ONLINE_JUDGE
	freopen("12608.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&W,&n); printf("%d\n",covered) ) {
		for ( i = 1; i <= n; ++i )
			scanf("%d %d",x+i,w+i), pref[i] = pref[i-1]+w[i];
		for ( covered = 0, i = 1; i <= n; ) {
			if ( pref[n]-pref[i-1] <= W ) {
				covered += 2*x[n];
				i = n+1;
			}
			else {
				assert( pref[bad = n]-pref[i-1] > W );
				assert( pref[good=i]-pref[i-1] <= W );
				for(;good+1<bad;pref[mid=(good+bad)/2]-pref[i-1]<=W?(good=mid):(bad=mid));
				covered += (pref[good]-pref[i-1]==W?2*x[good]:2*x[good+1]), i = good+1;
			}
		}
	}
	return 0;
}

