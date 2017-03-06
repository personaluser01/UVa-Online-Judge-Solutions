/*
 * 159. Word Corsses
 * KEYWORDS: Beginner
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo (1 << 29)

int max( int x, int y ) {
	if ( x < y ) return y;
	return x;
}

int min( int x, int y ) {
	if ( x < y ) return x;
	return y;
}

char w[4][32],len[4],g[0x200][0x200];
int ts,height,width,row,col,bt[16],p,q,r,s;

int ok( unsigned int u, int *ii, int *jj, int *a, int *b ) {
	int i,k[2],j;
	for ( j = 0, i = 0; i < 4; ++i )
		if ( u & (1<<i) )
			k[j++] = i;
	assert( j == 2 );
	for ( i = 0; i < len[k[0]]; ++i )
		for ( j = 0; j < len[k[1]]; ++j )
			if ( w[k[0]][i] == w[k[1]][j] ) {
				*ii = i, *jj = j;
				*a = k[0], *b = k[1];
				return 1;
			}
	return 0;
}

void update( int x, int y ) {
	p = min(p,x), q = min(q,y);
	r = max(r,x), s = max(s,y);
}

int prefix[0x400][0x400];

int main() {
	unsigned int u;
	int k[2],i,j,ni[2],nj[2],
		a,b,c,d,x,y,cnt;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( u = 0; u < 16; ++u )
		bt[u] = bt[u>>1] + (u&1);
	while ( 4 == scanf("%s %s %s %s\n",w[0],w[1],w[2],w[3]) ) {
		for ( i = 0; i < 4; ++i )
			len[i] = strlen(w[i]);
		if ( ts++ ) putchar('\n');
		p = q = +oo, r = s = -oo;
		for ( u = 3; u <= 3; ++u ) {
			if ( bt[u] == 2 && ok(u,ni,nj,&a,&b) && ok((~u)&0xfu,ni+1,nj+1,&c,&d) ) {
				w[a][ni[0]] = tolower(w[a][ni[0]]);
				w[b][nj[0]] = tolower(w[b][nj[0]]);
				w[c][ni[1]] = tolower(w[c][ni[1]]);
				w[d][nj[1]] = tolower(w[d][nj[1]]);
				x = 100, y = 0;
				memset(g,'#',sizeof(g));
				for ( i = y; i < y+len[a]; ++i ) {
					g[x][i] = w[a][i-y];
					update(x,i);
				}
				for ( j = 0; j < 3; ++j )
					g[x][i++] = ' ';
				for ( j = 0; j < len[c]; ++j ) {
					g[x][i++] = w[c][j];
					update(x,i-1);
				}
				x = 100-nj[0];
				for ( i = x; i < x+len[b]; ++i ) {
					g[i][ni[0]] = w[b][i-x];
					update(i,ni[0]);
				}
				x = 100-nj[1];
				for ( i = x; i < x+len[d]; ++i ) {
					g[i][ni[1]+len[a]+3] = w[d][i-x];
					update(i,ni[1]+len[a]+3);
				}
				memset(prefix,0,sizeof(prefix));
				for ( i = p; i <= r; ++i ) {
					for ( j = q; j <= s; ++j ) {
						prefix[i][j] = isalpha(g[i][j]) ? 1 : 0;
						if ( j ) prefix[i][j] += prefix[i][j-1];
					}
				}
				for ( i = p; i <= r; ++i ) {
					for ( cnt = 0, j = q; j <= s; ++j )
						if ( g[i][j] != '#' ) {
							if ( islower(g[i][j]) )
								g[i][j] = toupper(g[i][j]);
							putchar(g[i][j]);
							if ( isalpha(g[i][j]) && ++cnt == prefix[i][s] ) {
								putchar('\n');
								goto nx;
							}
						}
						else putchar(' ');
					nx: continue;
				}
				goto next;
			}
		}
		puts("Unable to make two crosses");
		next:;
	}
	return 0;
}

