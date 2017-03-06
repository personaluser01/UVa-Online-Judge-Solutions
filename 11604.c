/*
 * 11604. General Sultan
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
#define  N     0x80
#define  V(ch) ((ch)-'0')
#define  M(k)  ((1UL << (k))-1UL)
#define L 21
#define Q (N*L)
#define oo 0xfffffffful
#define enc(x,l) ((x)|((l)<<7))

int cs,ts,n,ok;
unsigned int u[N],d[N][L],q[Q],*head,*tail;
char name[0x100],s[N][0x100],len[N];

int main() {
	int i,j,k,x,y;
	unsigned int v,w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n)&&n;printf("Case #%d: %s\n",++cs,ok?"Not ambiguous.":"Ambiguous.")) {
		for ( ok = 1, i = 0; i < n; ++i ) 
			for ( scanf("%s %s",name,s[i]), u[i] = 0, len[i] = strlen(s[i]), j = 0; j < len[i]; ++j )
				if ( V(s[i][j]) )
					u[i] |= (1UL << j);
		for ( i = 0; i < n && ok; ++i )
			for ( j = i+1; j < n && ok; ++j )
				if (u[i]==u[j]&&len[i]==len[j]&&(ok=0));
		if ( ok ) {
			for ( i = 0; i < n; ++i )
				for ( k = 0; k < L; ++k )
					d[i][k] = +oo;
			head = tail = q;
			for ( i = 0; i < n; ++i )
				d[i][len[i]] = 0, *tail++ = enc(i,len[i]);
			for(;head<tail && ok;)
				for (x=(v=*head++)&M(7),k=(v>>7),y=0;y<n && ok;++y)
					if( len[y] < k ) {
						if ( ((u[x]>>(len[x]-k))&M(len[y]))^u[y] )
							continue ;
						if ( d[x][k-len[y]] > d[x][k]+1 )
							d[x][k-len[y]] = d[x][k]+1, *tail++ = enc(x,k-len[y]);
					}
					else if ( len[y] > k ) {
						if ( ((u[x]>>(len[x]-k)))^(u[y]&M(k)) )
							continue ;
						if ( d[y][len[y]-k] > d[x][k]+1 )
							d[y][len[y]-k] = d[x][k]+1, *tail++ = enc(y,len[y]-k);
					}
					else {
						if ( x == y && k == len[x] )
							continue ;
						if ( ((u[x]>>(len[x]-k))^u[y]) )
							continue ;
						if ( d[y][0] > d[x][k]+1 )
							d[y][0] = d[x][k]+1, *tail++ = enc(y,0), ok = 0;
					}
			for ( i = 0; i < n && ok; ++i )
				if ( d[i][0] >= 1 && d[i][0] < +oo && (ok = 0) );
		}
	}
	return 0;
}

