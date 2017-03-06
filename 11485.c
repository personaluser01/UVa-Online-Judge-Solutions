/*
 * 11485. Extreme Discrete Simulation
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 0x80
#define B 10
typedef long long i64;
#include <ctype.h>
#define F(i) (idx[i] && !a[i])
typedef unsigned long long u64;

int n,x[N],a[B],m;
u64 C[N][N],ax,s,w,deg[N][9];

int Rint() {
	int c;
	for(;(c = getchar()) != '.';);
	return getchar()-'0';
}

int main() {
	int i,j,k,idx[B],p[N];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(i=0;i<N;C[i++][0]=1);
	for(i=1;i<N;++i)
		for(j=1;j<=i;++j)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	for ( i = 1; i < N; ++i )
		for ( k = 1, deg[i][0] = 1ULL; k <= 8; ++k )
			deg[i][k] = deg[i][k-1]*((u64)i);
	deg[0][0] = 1LL;
	for(;1 == scanf("%d",&n) && n;) {
		memset(a,0,sizeof(a)), w = 0;
		for(i=0;i<n;++a[x[i++] = Rint()]);
		for ( idx[0] = 0; idx[0] <= 8; ++idx[0] )
		for ( idx[1] = 0; !F(0) && idx[1]+idx[0] <= 8; ++idx[1] )
		for(idx[2]=0,p[2]=idx[0]+idx[1];!F(1) && idx[2]+p[2]<=8;++idx[2])
		for(idx[3]=0,p[3]=p[2]+idx[2];!F(2) && idx[3]+p[3]<=8;++idx[3])
		for ( idx[4] = 0, p[4] = p[3]+idx[3]; !F(3) && idx[4]+p[4] <= 8; ++idx[4] )
		for ( idx[5] = 0, p[5] = p[4]+idx[4]; !F(4) && idx[5]+p[5] <= 8; ++idx[5] )
		for ( idx[6] = 0, p[6] = p[5]+idx[5]; !F(5) && idx[6]+p[6] <= 8; ++idx[6] )
		for ( idx[7] = 0, p[7] = p[6]+idx[6]; !F(6) && idx[7]+p[7] <= 8; ++idx[7] )
		for ( idx[8] = 0, p[8] = p[7]+idx[7]; !F(7) && idx[8]+p[8] <= 8; ++idx[8] ) {
			if ( F(8) )
				continue ;
			idx[9] = 8-p[8]-idx[8], s = 0;
			if ( F(9) )
				continue ;
			assert( idx[0]+idx[1]+idx[2]+idx[3]+idx[4]+idx[5]+idx[6]+idx[7]+idx[8]+idx[9] == 8 );
			for ( i = 1; i <= 9; ++i )
				s += i*idx[i];
			for ( m = 8, ax = 1ULL, i = 0; i <= 9; ++i ) {
				if ( !idx[i] ) continue ;
				ax *= C[m][idx[i]];
				ax *= deg[a[i]][idx[i]];
				m -= idx[i];
			}
			assert( !m );
			w += (s/10)*ax;
		}
		printf("%llu\n",w);
	}
	return 0;
}

