/*
 * 10901. Ferry Loading
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 10001
using namespace std;

int L,D,cars,tm[N],*p[2],*q[2],
	*ptr[2],bank[2][N],stamp,arrival[N];

int main() {
	int i,j,k,t,ts,odottavissa;
	char tmp[N];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d",&L,&D,&cars);
		for ( i = 0; i <= 1; ptr[i] = bank[i], ++i );
		for ( i = 0; i < cars; ++i ) {
			scanf("%d %s",&tm[i],tmp);
			*ptr[0[tmp]=='l'?0:1]++ = i;
		}
		for ( i = 0; i <= 1; ++i ) q[i] = (p[i] = bank[i])-1;
		for ( odottavissa = cars, t = 0, stamp = 0; odottavissa; ) {
			for ( i = 0; i <= 1; ++i ) 
				for (;q[i]+1 < ptr[i] && tm[*(q[i]+1)] <= stamp; ++q[i] );
			for ( k = 0; p[t] <= q[t] && k < L; arrival[*p[t]] = stamp+D, ++p[t], ++k );
			if ( k || (p[1-t] <= q[1-t] && q[1-t] < ptr[1-t]) ) t = 1-t, stamp += D;
			else {
				if ( q[0]+1 < ptr[0] && q[1]+1 < ptr[1] ) {
					assert( stamp < min(tm[*(q[0]+1)],tm[*(q[1]+1)]) );
					stamp = min(tm[*(q[0]+1)],tm[*(q[1]+1)]);
				}
				else if ( q[0]+1 < ptr[0] )
					stamp = tm[*(q[0]+1)];
				else if ( q[1]+1 < ptr[1] )
					stamp = tm[*(q[1]+1)];
			}
			odottavissa -= k;
			assert( odottavissa >= 0 );
		}
		for ( i = 0; i < cars; ++i )
			printf("%d\n",arrival[i]);
		if ( ts ) putchar('\n');
	}
	return 0;
}

