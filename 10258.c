/*
 * 10258. Contest Scoreboard
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
#define N 0x80
#define M 0x10
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

int g[N][M],yes,pen[N],inc[N][M],id[N],solved[N],is[N],v[N],n;
char buff[0x400],*ptr;

int main() {
	int i,j,k,ts,t,pr,tm,cs = 0;
	char s[0x40];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts), getchar(), FG; ts-- && ++yes && ++cs; ) {
		if(cs>1)putchar('\n');
		memset(pen,0,sizeof(pen));
		memset(inc,0,sizeof(inc));
		memset(solved,0,sizeof(solved));
		for (;FG && 4 == sscanf(buff,"%d %d %d %s",&t,&pr,&tm,s) && (is[t] = yes);) {
			if ( (*s != 'C' && *s != 'I')||(g[t][pr]==yes) ) 
				continue ;
			if ( *s == 'C' ) {
				g[t][pr] = yes, ++solved[t];
				pen[t] += (tm+inc[t][pr]);
				continue ;
			}
			assert( *s == 'I' );
			inc[t][pr] += 20;
		}
		for ( n = 0, i = 1; i <= 100; ++i )
			if ( is[i] == yes && (v[n++] = i) );
		for ( j = 1;j;)
			for ( j = 0, i = 0; i < n-1; ++i ) {
				if ( solved[v[i]]>solved[v[i+1]] ) 
					continue ;
				if ( solved[v[i]] == solved[v[i+1]] ) {
					if ( pen[v[i]] == pen[v[i+1]] ) {
						if ( v[i] > v[i+1] )
							++j, xchg(v[i],v[i+1]);
					}
					else if ( pen[v[i]] < pen[v[i+1]] ) {
						++j, xchg(v[i],v[i+1]);
					}
				}
				else
					++j, xchg(v[i],v[i+1]);
			}
		for ( i = 0; i < n; ++i )
			printf("%d %d %d\n",v[i],solved[v[i]],pen[v[i]]);
	}
	return 0;
}
