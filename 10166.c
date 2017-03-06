/*
 * 10166. Travel
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
#define T (1<<11)
#define oo 0xfffffffful

unsigned int min( unsigned int x, unsigned int y ) {
	return x < y ? x : y;
}

unsigned int max( unsigned int x, unsigned int y ) {
	return x < y ? y : x;
}

int conv( char *s ) {
	int x = s[0]-'0',y = s[1]-'0',z=s[2]-'0',t=s[3]-'0';
	return (10*x+y)*60+10*z+t;
}

typedef struct {
	int x,t;
	unsigned int *p;
} edge;

int cmp( const void *a, const void *b ) {
	edge *A = (edge *)a,
		 *B = (edge *)b;
	if ( A->x == B->x )
		return A->t-B->t;
	return A->x-B->x;
}

int n,ts,m,len[N];
char buff[0x400],*ptr,cname[N][0x20];
unsigned int z[N][T];
edge e[N*N];

int find( char *s ) {
	int i;
	for ( i = 0; i < n; ++i )
		if ( strcmp(s,cname[i]) == 0 )
			return i+1;
	return 0;
}



int main() {
	int i,j,k,l,t,src,dst,pi,pt,st,
		bad,good,mid;
	char tmp[0x400],kello[0x400],
		 src_city[0x400],dst_city[0x400];
	edge fake;
	unsigned int w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( scanf("%d",&n) && n ) {
		for ( i = 0; i < n; scanf("%s",cname[i]), ++i );
		m = 0, e[m++].x = -1, e[m++].x = n;
		for ( scanf("%d",&k), l = 0; l < k; ++l ) {
			for ( pi = -1, scanf("%d",len+l), t = 0; t < len[l]; ++t, pi = i, pt = conv(kello) ) {
				scanf("%s %s",kello,tmp);
				i = find(tmp)-1;
				assert( i >= 0 );
				if ( pi >= 0 ) 
					e[m].x = i, e[m].t = conv(kello), e[m].p = &z[pi][pt], ++m;
			}
		}
		qsort(e,m,sizeof *e,cmp);
		scanf("%s %s %s",kello,src_city,dst_city);
		src = find(src_city)-1, dst = find(dst_city)-1, st = conv(kello);
		assert( src >= 0 ); assert( dst >= 0 );
		for ( t = 0; t <= st; ++t )
			for ( i = 0; i < n; ++i )
				z[i][t] = +oo;
		for ( t = st; t <= 24*60; ++t )
			z[src][t] = t;
		for ( t = st+1; t <= 60*24; ++t )
			for ( i = 0; i < n; ++i ) {
				if ( i == src ) continue ;
				z[i][t] = (t?z[i][t-1]:+oo);
				bad = 0, good = m-1, fake.x = i, fake.t = t;
				for(;bad+1<good;cmp(e+(mid=(good+bad)/2),&fake)<0?(bad=mid):(good=mid));
				assert( cmp(e+good,&fake) >= 0 );
				assert( cmp(e+bad,&fake) < 0 );
				for ( k = good; k < m && 0 == cmp(e+k,&fake); ++k ) 
					if ( z[i][t]==+oo||(*(e[k].p)<+oo&&*(e[k].p)>z[i][t]))
						z[i][t] = *(e[k].p);
			}
		for ( w = +oo, t = st; t <= 60*24; ++t )
			if ( z[dst][t] < +oo ) {
				w = z[dst][pt = t];
				goto nx;
			}
		nx: if ( w < +oo )
				printf("%02d%02d %02d%02d\n",(int)(w/60),(int)(w%60),pt/60,pt%60);
			else puts("No connection");
	}
	return 0;
}
