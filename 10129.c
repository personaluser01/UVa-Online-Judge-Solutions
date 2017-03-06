/*
 * 10129. Play on Words
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100100
#define A 26
#define DBG(x) (1)

int n,deg[2][A],seen[A],yes,queue[A],*tail,*head,m,cnt[A];
char adj[2][A][N];

int main() {
	int i,j,k,u,v,src,snk,s,t,ts,c,l;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("words.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d",&n) && ++yes; ) {
		for ( i = 0; i < A; ++i )
			src = snk = cnt[i] = deg[0][i] = deg[1][i] = 0;
		for ( i = 0; i < n; ++i ) {
			scanf("%s",tmp);
			j = tmp[0]-'a', k = tmp[strlen(tmp)-1]-'a';
			++cnt[j], ++cnt[k];
			adj[0][j][deg[0][j]++] = k;
			adj[1][k][deg[1][k]++] = j;
			s = t = j;
		}
		for ( m = 0, i = 0; i < A; ++i ) {
			if ( !cnt[i] ) continue ;
			++m;
			if ( abs(deg[0][i]-deg[1][i]) >= 2 )
				goto nx;
			if ( deg[0][i]-deg[1][i] == 1 && ++src && (s = i) );
			if ( deg[0][i]-deg[1][i] == -1 && ++snk && (t = i) );
		}
		if ( !(snk==0&&src==0 || src==1&&snk==1) )
			goto nx;
		for ( l = 0; l <= 1; ++l ) {
			for ( c = 0,head=tail=queue,seen[*tail++=(l?t:s)]=++yes; head<tail;)
				for ( i = *head++,++c,k = 0; k < deg[l][i]; ++k )
					if ( seen[j = adj[l][i][k]] != yes )
						seen[*tail++ = j] = yes;
			if ( c != m ) goto nx;
		}
		ok: puts("Ordering is possible.");
			continue ;
		nx: puts("The door cannot be opened."); 
	}
	return 0;
}
