/*
 * 1541. To Bet or Not to Bet
 * TOPIC: probability, dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXT 0x40
#define MAXN 0x40
#define N MAXN
#define oo (1<<29)
#define onboard(x) (ST <= (x) && (x) <= END2 )
enum { IDLE=0, ACTIVE=1 };

int n,T,b[MAXN],ST,END1,END2,adj[N][N],deg[N];
double p[2][MAXN][MAXT];

double calc_z( int s, int i, int k ) {
	int l,j,t;
	if ( i < ST || k < 0 ) return 0.00;

	if ( p[s][i][k] < +oo ) return p[s][i][k];

	if ( s == IDLE && b[i] != -oo )
		return p[s][i][k] = 0.00;

	if ( s == ACTIVE && b[i] == -oo ) {
		p[s][i][k] = calc_z(IDLE,i,k-1);
		for ( l = 0; l < deg[i]; ++l ) 
			for ( t = 1; t <= 2 && (j=adj[i][l]) != i; ++t )
				if ( j-t >= ST && j-t != END1 && j-t != END2 )
					p[s][i][k] += calc_z(ACTIVE,j-t,k-1)/2;
		return p[s][i][k];
	}

	if ( b[i] == -oo ) {
		for ( p[s][i][k] = 0, t = 1; t <= 2; ++t )
			if ( i-t >= ST && i-t != END1 && t-i != END2 )
				p[s][i][k] += calc_z(ACTIVE,i-t,k-1);
		return p[s][i][k]/=2;
	}

	for ( p[s][i][k] = 0.00, l = 0; l < deg[i]; ++l )  {
		j = adj[i][l];
		assert( -oo < b[j] && b[j] < +oo );
		assert( i == j+b[j] );
		for ( t = 1; t <= 2; ++t ) 
			if ( j-t >= ST && j-t != END1 && j-t != END2 )
				p[s][i][k] += calc_z(ACTIVE,j-t,k-1);
	}
	for ( t = 1; t <= 2 && !(-oo < b[i] && b[i] < +oo); ++t ) 
		if ( i-t >= ST && i-t != END1 && i-t != END2 )
			p[s][i][k] += calc_z(ACTIVE,i-t,k-1);
	return p[s][i][k]/=2.00;
}

int main() {
	int i,j,k,l,t,ts;
	char tmp[0x40];
	double w;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&T); ) {
		ST = 0, END1 = n+1, END2 = n+2;
		for ( i = ST; i <= END2; deg[i] = 0, b[i++] = +oo );
		for ( i = 1; i <= n; ++i ) {
			scanf("%s",tmp);
			switch ( 0[tmp] ) {
				case '0': break ;
				case 'L': b[i] = -oo; 
						  break ;
				default:  sscanf(tmp,"%d",&b[i]); 
						  j = i+b[i];
						  assert( onboard(j) );
						  adj[j][deg[j]++] = i;
						  break ;
			}
		}
		for ( t = IDLE; t <= ACTIVE; ++t )
			for ( i = ST; i <= END2; ++i )
				for ( k = 0; k <= T; p[t][i][k++] = +oo );
		for ( p[ACTIVE][ST][0] = 1.00, w = 0, k = 0; k <= T; w += calc_z(ACTIVE,END1,k)+calc_z(ACTIVE,END2,k), ++k );
		if ( w < 0.5 ) printf("Bet against. %.4lf\n",w);
		else if ( w > 0.5 ) printf("Bet for. %.4lf\n",w);
		else puts("Push. 0.5000");
	}
    return 0;
}


