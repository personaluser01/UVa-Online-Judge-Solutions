/*
 * 10039. Railroads
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define T 1001
#define L 101
#define Z (1 << 11)
#define oo 0xfffffffful

typedef struct { int city, t; } station;

int n,id[N];
station s[T*L];
int curr,conns[T],trains,cnt[N][Z];
station *lst[T],**List[N][Z],**ptr[N][Z],**qtr[N][Z];
char cname[N][0x400];
unsigned int z[N][Z];

int find_city( char *s ) {
	int i,j,k;
	if ( strcmp(s,cname[id[0]]) == 0 )
		return id[0];
	if ( strcmp(s,cname[id[0]]) < 0 || strcmp(s,cname[id[n-1]]) > 0 )
		return -1;
	assert( strcmp(s,cname[id[0]]) > 0 );
	for ( i = 0, j = n-1; i+1 < j; ) {
		k = (i+j)/2;
		if ( strcmp(s,cname[id[k]]) > 0 )
			i = k;
		else j = k;
	}
	if ( strcmp(s,cname[id[j]]) != 0 )
		return -1;
	return id[j];
}

int conv( char *tm ) {
	return (10*(tm[0]-'0')+(tm[1]-'0'))*60+(tm[2]-'0')*10+(tm[3]-'0');
}

int main() {
	int i,j,k,l,t,src,dst,ts,cs = 0,tt,nt,arr,mi,flag,x,y;
	char from[0x400],to[0x400],tm[0x400],tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Scenario %d\n",++cs) && scanf("%d",&n); putchar('\n') ) {
		for ( i = 0; i < n; scanf("%s",cname[i]), id[i] = i, ++i );
		for (j=1;j;)
			for ( i = j = 0; i < n-1; ++i )
				if ( strcmp(cname[id[i]],cname[id[i+1]]) > 0 )
					++j, k = id[i], id[i] = id[i+1], id[i+1] = k;
		for ( i = 0; i < n; ++i )
			for ( k = 0; k <= 1440; ++k )
				cnt[i][k] = 0;
		for ( curr = 0, scanf("%d",&trains), k = 0; k < trains; ++k ) 
			for ( scanf("%d",conns+k), lst[k] = s+curr, l = 0; l < conns[k]; ++l )  {
				scanf("%s %s",tm,tmp);
				if ( (s[curr].city=find_city(tmp)) == -1 ) {
					assert( 0 );
					continue ;
				}
				s[curr++].t=conv(tm);
				++cnt[s[curr-1].city][s[curr-1].t];
			}
		for ( i = 0; i < n; ++i )
			for ( k = 0; k <= 1440; ++k )
				if ( cnt[i][k] )
					ptr[i][k] = List[i][k] = (station **)malloc((cnt[i][k]+1)*sizeof *List[i][k]);
		for ( k = 0; k < trains; ++k )
			for ( l = 0; l < conns[k]; ++l ) {
				tt = (lst[k]+l)->t, x = (lst[k]+l)->city;
				if ( l ) *ptr[x][tt]++ = lst[k]+l-1;
			}
		scanf("%s %s %s",tm,from,to), t = conv(tm);
		src = find_city(from), dst = find_city(to);
		if ( src == -1 || dst == -1 ) {
			puts("No connection");
			continue ;
		}
		for ( i = 0; i < n; ++i )
			for ( k = 0; k <= 1440; z[i][k++] = +oo );
		for ( k = 0; k < trains; ++k )
			for ( l = 0; l < conns[k]; ++l )
				if ( (lst[k]+l)->city == src && (lst[k]+l)->t >= t )
					z[src][(lst[k]+l)->t] = (lst[k]+l)->t;
		for ( k = t; k <= 1440; ++k )
			for ( x = 0; x < n; ++x ) {
				if ( k > 0 && z[x][k-1] < +oo && (z[x][k] == +oo||z[x][k-1] > z[x][k]) )
					z[x][k] = z[x][k-1];
				if ( cnt[x][k] ) {
					for ( qtr[x][k] = List[x][k]; qtr[x][k] < ptr[x][k]; ++qtr[x][k] ) {
						tt = (*qtr[x][k])->t, y = (*qtr[x][k])->city;
						if ( z[y][tt] == +oo )
							continue ;
						if ( (z[x][k] == +oo||z[y][tt] > z[x][k]) )
							z[x][k] = z[y][tt];
					}
				}
			}

		for ( mi = (1 << 29), arr = (1 << 29), k = t; k <= 1440; ++k )
			if ( z[dst][k] < +oo ) {
				if ( arr > k )
					mi = z[dst][k], arr = k;
				else if ( k == arr && z[dst][k] > mi )
					mi = z[dst][k];
			}
		if ( mi == (1 << 29) ) 
			puts("No connection");
		else {
			printf("Departure %02d%02d %s\n",mi/60,mi%60,cname[src]);
			printf("Arrival   %02d%02d %s\n",arr/60,arr%60,cname[dst]);
		}
		for ( i = 0; i < n; ++i )
			for ( k = 0; k <= 1440; ++k )
				if ( cnt[i][k] )
					free(List[i][k]), cnt[i][k] = 0;
	}
	return 0;
}
