/*
 * 1238. Free Parenthesis
 * TOPIC: dp, sets
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#define SH 3000
#define N 0x20
#define Q ((SH+SH)+0x80)
#define L(u) ((u)&((~(u))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET(i,j,k) (e[i][j][(k)>>6]|=BIT((k)&63))
typedef unsigned long long u64;

char s[0x400],buff[0x400],op[0x20],*ptr,which[BIT(21)];
int M,m,n,c[N],sig[N];
u64 e[N][N][Q>>6];

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

int main() {
	int i,j,k,o,t,l,x,y,T;
	u64 u,v;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)]=i, ++i );
	for ( ;1 == scanf("%[^\n]\n",buff) && 0[buff]!='#'; ) {
		for ( n = 0, ptr = s, m = 0, j = 0; buff[j]; s[m++]=(buff[j]==' '?--m:buff[j]), ++j );
		if ( (s[m]='\0',s[0] != '-' && s[0] != '+') )
			sscanf(ptr,"%[0-9]%n",buff,&j), c[n++] = atoi(buff), ptr += j;
		for (;2==sscanf(ptr,"%[-+]%[0-9]%n",op,buff,&j);ptr+=j,sig[n]=0[op]=='-'?-1:1,c[n++]=atoi(buff));
		for ( M = 0, i = 0; i < n; M += c[i++] );
		for ( M = Q, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( l = 0; l < M/64; e[i][j][l++] = 0 );
		for ( k = 1, i = 0; (j=i+k-1) < n; SET(i,j,SH+c[i]), ++i );
		for ( k = 2; k <= n; ++k )
			for ( i = 0; (j=i+k-1) < n; ++i ) 
				for ( t = i; t <= j-1; ++t )
					for ( l = 0; l < M/64; ++l )
						for ( u = e[i][t][l]; u && (x=who(L(u))) >= 0; u &= ~L(u) )
							for ( o = 0; o < M/64; ++o )
								for ( v = e[t+1][j][o]; v && (y=who(L(v))) >= 0; v &= ~L(v) ) {
									T = SH+(64*l+x-SH)+sig[t+1]*(64*o+y-SH);
									assert( T >= 0 );
									SET(i,j,T);
								}
		for ( k = 0, i = 0; i < M/64; ++i )
			for ( u = e[0][n-1][i]; u && (x=who(L(u))) >= 0; ++k, u &= ~L(u) );
		printf("%d\n",k);
	}
	return 0;
}

