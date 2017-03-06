/*
 * 10554. Calories From Fat
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
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
enum{ FAT, PRO, SUGAR, STARCH, ALCO };
#define N (1 << 18)
#define eps 1e-9

int n,c[5][N],nrg[5],tot[N],p[N];
char units[5][N][0x10],buff[0x400],*ptr;
long double a[5][N];

int rinp() {
	int i,j,k,cnt;
	for ( n = 0; FG && *ptr != '-'; ++n ) 
		for(cnt=0,i=0;i<5;sscanf(buff+cnt,"%d%[g%C]%n",c[i]+n,units[i][n],&k),++i,cnt+=k);
	return n;
}

int F( long double x ) {
	int up,down;
	up = ceil(x+eps), down = floor(x+eps);
	return (fabs(up-x) <= fabs(x-down) ? up : down);
}

int main() {
	int i,j,k;
	long double ax,T;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	nrg[FAT] = 9, nrg[PRO] = nrg[SUGAR] = nrg[STARCH] = 4, nrg[ALCO] = 7;
	for (;rinp();) {
		for ( i = 0; i < n; ++i ) 
			for ( tot[i] = 0, j = 0; j < 5; ++j )
				if ( units[j][i][0] == 'g' )
					units[j][i][0] = 'C', c[j][i] = nrg[j]*c[j][i];
		for ( i = 0; i < n; ++i )
			for ( p[i] = 100, j = 0; j < 5; ++j )
				if ( units[j][i][0] == 'C' )
					tot[i] += c[j][i];
				else p[i] -= c[j][i];
		for ( T = 0, ax = 0, i = 0; i < n; ax += a[0][i], ++i )
			for ( j = 0; j < 5; T += a[j++][i] )
				if ( units[j][i][0] == 'C' ) {
					a[j][i] = c[j][i];
				}
				else {
					a[j][i] = (c[j][i]*tot[i])/(p[i]+.0);
				}
		printf("%d%%\n",F(ax*100/T));
	}
	return 0;
}
