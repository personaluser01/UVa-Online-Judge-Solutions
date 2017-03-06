/*
 * 10017. The Never Ending Towers of Hanoi
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 256
enum { A, B, C };
#define D (display(A), display(B), display(C), putchar('\n'))

i64 m,n,cs,*top[3],stack[3][N];
char nm[3][2] = {"A","B","C"};

void display( int t ) {
	int i;
	printf("%s=>",nm[t]);
	if ( top[t] == stack[t] ) {
		putchar('\n');
		return ;
	}
	for ( printf("  "), i = 1; i <= top[t]-stack[t]; printf(" %lld",stack[t][i++]) );
	putchar('\n');
}

void rec( int a, int b, int c, i64 n, i64 *m ) {
	if ( !*m ) return ;
	assert( *m >= 1 );
	if ( n == 1 ) {
		--(*m), *++top[c] = *top[a]--, D;
		return ;
	}
	rec(a,c,b,n-1,m);
	if ( *m ) 
		--(*m), *++top[c] = *top[a]--, D;
	rec(b,a,c,n-1,m);
}

int main() {
	i64 i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%lld %lld",&n,&m) && (m||n); ) {
		printf("Problem #%lld\n\n",++cs);
		for ( i = 0; i < 3; top[i] = stack[i], ++i );
		for ( i = n; i; *++top[A] = i-- );
		D; rec(A,B,C,n,&m);
	}
	return 0;
}
