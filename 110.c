/*
 * 110. Meta-Loopless Sort
 * 	status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 16
#define M (720*8)
#define DH 4
#define xchg(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
#define DBG(x) (1)

char max( char x, char y ) {
	if ( x < y )
		return y;
	return x;
}

int n,cnt,SHIFT;
char head[N];

void printout() {
	int i,j,k = 0;
	DBG(printf("%*scnt = %d, SHIFT = %d, curline = %d\n",SHIFT,"",++cnt,SHIFT,curline));
	printf("%*swriteln(",SHIFT,"");
	DBG(printf("%*sstill here in printout()\n",SHIFT,""));
	for ( i = 0; i < n-1; k += j ) 
		printf("%c,",head[i++]);
	printf("%c)\n",head[n-1]);
	DBG(printf("%*sOK\n",SHIFT,""));
}

void rec( char cursor, char arrow ) {
	DBG(printf("%*scursor = %d, arrow = %d, n = %d\n",SHIFT,"",cursor,arrow,n));
	assert( cursor+1 <= arrow );
	assert( arrow <= n+1 );
	assert( cursor >= 0 );
	if ( cursor == n ) {
		printout();
		return ;
	}
	if ( cursor == 0 ) {
		rec(arrow,arrow+1);
		return ;
	}
	assert( cursor > 0 );
	printf("%*sif %c < %c then\n",SHIFT,"",head[cursor-1],head[cursor]);
	DBG(printf("%*sRecursive call 1\n",SHIFT,""));
	SHIFT += DH, rec(max(cursor+1,arrow),arrow+1), SHIFT -= DH;
	DBG(printf("%*sSuccess\n",SHIFT,""));
	printf("%*selse\n",SHIFT,"");
	assert( cursor > 0 );
	assert( cursor < n );
	xchg(head[cursor],head[cursor-1]);
	DBG(printf("%*sRecursive call 2\n",SHIFT,""));
	SHIFT += DH, rec(cursor-1,arrow), SHIFT -= DH;
	DBG(printf("%*sSuccess\n",SHIFT,""));
	xchg(head[cursor],head[cursor-1]);
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		printf("program sort(input,output);\n");
		printf("var \n");
		for ( k = 0, i = 0; i < n-1; ++i )
			printf("%c,",i+'a'), k += j;
		printf("%c : integer;\n",i+'a');
		printf("begin\n");
		k = 0, j = printf("%*sreadln(",DH,""),k += j;
		for ( i = 0; i < n-1; ++i )
			printf("%c,",i+'a'), k += j;
		printf("%c);\n",i+'a');
		for ( i = 0; i < n; ++i ) head[i] = 'a'+i;
		SHIFT = DH, rec(1,2);
		puts("end.");
		if ( ts ) putchar('\n');
	}
	return 0;
}
