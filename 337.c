/*
 * 337. Interpreting Control Sequences
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
#define N 16
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
enum{OVERWHITE,INSERT};

char g[N][N],buff[0x400],*ptr;
int ts,n = 10,m,md,x,y,t;

int read_command( char *ch, int *is_cmd ) {
	if ( !*ptr||*ptr == '\n' )
		return 0;
	if ( *ptr == '^' ) {
		assert( *(ptr+1)&&*(ptr+1)!='\n' );
		*is_cmd = (*ch = *(ptr+1)) != '^';
		ptr += 2;
		return 1;
	}
	*is_cmd = 0, *ch = *ptr++;
	return 1;
}

void print( int t, char ch ) {
	int j;
	for ( j = n-1; t == INSERT && j > y; --j )
		g[x][j] = g[x][j-1];
	g[x][y] = ch;
	if ( y < n-1 ) ++y;
}

int main() {
	int i,j,k,is_cmd;
	char ch;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;1 == sscanf(FG,"%d",&m) && m && printf("Case %d\n",++ts);) {
		memset(g,' ',sizeof(g));
		for ( x = y = 0, t = OVERWHITE, i = 0; i < m; ++i ) {
			for ( FG; read_command(&ch,&is_cmd); ) {
				if ( !is_cmd ) { print(t,ch); continue; }
				switch ( ch ) {
					case 'b': y = 0; break ;
					case 'c': memset(g,' ',sizeof(g)); break ;
					case 'd': if ( x < n-1 ) ++x; break ;
					case 'e': for ( j = y; j < n; ++j ) g[x][j] = ' ';
								break ;
					case 'h': x = y = 0; break ;
					case 'i': t = INSERT; break ;
					case 'l': if ( y ) --y; break ;
					case 'o': t = OVERWHITE; break ;
					case 'r': if ( y < n-1 ) ++y; break ;
					case 'u': if ( x ) --x; break ;
					case '^': print(t,ch); break ;
					default: assert( isdigit(ch) );
							 x = ch-'0', y = *ptr++-'0';
							 break ;
				}
			}
		}
		puts("+----------+");
		for ( i = 0; i < n; ++i, puts("|") ) 
			for ( putchar('|'), j = 0; j < n; putchar(g[i][j++]) );
		puts("+----------+");
	}
	return 0;
}
