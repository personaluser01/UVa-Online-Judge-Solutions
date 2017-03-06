/*
 * 11126. Relaxed Golf
 * NOTES: Columns contain <= 5 cards, i.e. 3 bits, 21 bits overall
 * 		  The draw pile contains <= 16 card, i.e. 5 bits
 * 		  Which column -- or draw pile -- was used in the last move, 8 possibilities, i.e. 3 bits
 * 		  Overall: 21+5+3 == 29 bits
 * 		  status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T (6LL*6LL*6LL*6LL*6LL*6LL*6LL)
#define Q (T*17LL*8LL)
#define TST(a,k) (a[(k)>>3]&BIT((k)&7))
#define BIT(k) (1ULL<<(k))
#define CLR(a,k) (a[(k)>>3] &= ~BIT((k)&7))
#define SET(a,k) (a[(k)>>3]|=BIT((k)&7))
typedef long long i64;

int ts,cs,c[7][5],draw[18],
	valid_move[13][13];
unsigned char z[(Q>>3)+8],seen[(Q>>3)+8];

unsigned int encode( char *col, char d, char m ) {
	unsigned int u = 0;
	int i;
	for ( i = 6; i >= 0; u = 6*u+((unsigned int)col[i--]) );
	return ((unsigned int)m)*T*17+((unsigned int)d)*T+u;
}

int f( unsigned int u ) {
	char col[7],top_card,i,j,idx,d;
	unsigned int v;

	if ( TST(seen,u) ) return TST(z,u);

	SET(seen,u);
	v = u%T, idx = u/(T*17), d = (((i64)u)-((i64)v)-idx*T*17)/T;

	if ( !d && !v ) return SET(z,u);

	for( i = 0; i <= 6; col[i++] = (v%6), v /= 6 );
	top_card = (idx<=6)?c[idx][col[idx]]:draw[d];

	for ( i = 0; i <= 6; ++i )
		if ( col[i] && valid_move[c[i][col[i]-1]][top_card] ) {
			--col[i];
			if ( f(encode(col,d,i)) ) return SET(z,u);
			++col[i];
		}
	if ( d && f(encode(col,d-1,7)) )
		return SET(z,u);
	return 0;
}

int isdig[256];

int getnum() {
	int n = 0,ch;
	while ( (ch = getchar()) != EOF && !isdig[ch] );
	for ( n = ch-'0'; (ch = getchar()) != EOF && isdig[ch];)
		n = (n<<1)+(n<<3)+ch-'0';
	return n;
}

int main() {
	int i,j,k,l,t;
	i64 x,y,r;
	char col[] = {5,5,5,5,5,5,5,5};
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; ++i ) isdig[i] = 1;
	/*
	printf("%lf\n",sizeof(z)/1024.0/1024);
	printf("%lf\n",sizeof(seen)/1024.0/1024);
	*/
	for ( i = 0; i < 13; ++i )
		for ( j = 0; j < 13; ++j )
			if ( (i-j+13)%13 == 1||(i-j+13)%13 == 12 ) 
				valid_move[i][j] = 1;
	for( ts = getnum();ts--;) {
		for ( i = 0; i < 5; ++i )
			for ( j = 0; j < 7; ++j )
				c[j][i] = getnum()-1;
		for ( i = 0; i < 17; ++i )
			draw[i] = getnum()-1;
		memset(z,0,sizeof(z)), memset(seen,0,sizeof(seen));
		printf("Case #%d: %s\n",++cs,f(encode(col,16,7))?"Yes":"No");
	}
	return 0;
}

