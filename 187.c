/*
 * 10205. Stack Them Up
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
#define N 1000
#define tol 1e-9

char acname[N][0x30];
int balance[N],p[0x400],q[0x400],*ptr = p,*qtr = q;

int conv( char *s ) {
	int x = s[0]-'0',
		y = s[1]-'0',
		z = s[2]-'0';
	return 100*x+10*y+z;
}

void f( int prev ) {
	int i;
	if ( prev == -1||balance[prev]==0 ) {
		ptr = p, qtr = q;
		return ;
	}
	printf("*** Transaction %03d is out of balance ***\n",prev);
	for ( i = 0; i < ptr-p; ++i ) 
		printf("%03d %-30s %10.2lf\n",p[i],acname[p[i]],q[i]/100.00+tol);
	printf("999 %-30s %10.2lf\n\n","Out of Balance",-balance[prev]/100.00+tol);
	balance[prev] = 0;
	ptr = p, qtr = q;
}

int main() {
	int i,j,k,seq,cents,prev;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%[^\n]\n",tmp) &&(k = conv(tmp)); acname[k][j] = (char)0 ) 
		for ( j = 0, i = 3; tmp[i]; acname[k][j++] = tmp[i++] );
	for( prev = -1; 1 == scanf("%[^\n]\n",tmp) && (seq = conv(tmp)); prev = seq ) {
		if ( seq != prev && prev != -1 ) f(prev);
		k = conv(tmp+3), sscanf(tmp+6,"%d",&cents);
		*ptr++ = k, *qtr++ = cents;
		balance[seq] += cents;
	}
	f(prev);
	return 0;
}

