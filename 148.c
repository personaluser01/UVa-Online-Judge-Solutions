/*
 * 148. Anagram Checker
 * status: Accepted
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2048
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define A 26

char buff[0x400],*ptr,str[N][0x400],*qtr;
unsigned char cnt[N][A],cur[A+1],T[A+1];
unsigned int msk[N],u;
int sol[N],*tail,n;

int equal( unsigned char *a, unsigned char *b ) {
	int i;
	for ( i = 0; i < A; ++i )
		if ( a[i] != b[i] )
			return 0;
	return 1;
}

void f( int k ) {
	int i,j,l;
	unsigned char tmp[A];
	T[A] = cur[A] = '\0';
	if ( equal(cur,T) ) {
		printf("%s",buff);
		for ( printf("%s",str[sol[0]]), i = 1; i < tail-sol; ++i ) 
			printf(" %s",str[sol[i]]);
		putchar('\n');
		return ;
	}
	for ( j = 0; j < A; ++j )
		tmp[j] = cur[j];
	for ( i = k; i < n; ++i ) {
		if ( (msk[i]|u) != u )
			continue ;
		for ( j = 0; j < A; ++j )
			if ( (cur[j]+=cnt[i][j]) > T[j] ) 
				goto nx;
		*tail++ = i, f(i+1), --tail;
		nx: 
		for ( l = 0; l < A; ++l )
			cur[l] = tmp[l];
	}
}

int in_dict( char *w ) {
	int i,j,k;
	if ( strcmp(w,str[0]) < 0 )
		return 0;
	if ( strcmp(w,str[n-1]) > 0 )
		return 0;
	if ( strcmp(w,str[n-1]) == 0 )
		return 1;

	for ( i = 0, j = n-1; i+1 < j; ) {
		k = (i+j)/2;
		if ( strcmp(w,str[k]) >= 0 )
			i = k;
		else j = k;
	}
	if ( strcmp(w,str[i]) == 0 )
		return 1;
	if ( strcmp(w,str[j]) == 0 )
		return 1;
	return 0;
}

int main() {
	int i,j,k,t,l,m;
	char wrd[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( FG ) {
		for ( n = 0; *ptr != '#'; FG, *qtr = '\0', ++n )
			for ( memset(cnt[n],0,sizeof(cnt[n])), msk[n] = 0, qtr = str[n]; *ptr && *ptr != '\n'; ) {
				assert( isupper(*ptr) );
				msk[n] |= (1UL << (*ptr-'A'));
				++cnt[n][*ptr-'A'], *qtr++ = *ptr++;
			}
		while ( FG && *ptr != '#' ) {
			for ( i = 0; i < A; T[i++] = 0 );
			for ( m = 0; 1 == sscanf(ptr+m,"%s%n",wrd,&k); m += k )
				if ( !in_dict(wrd) ) 
					goto lx;
			continue ;
			lx:
			for ( u = 0, qtr = ptr; *qtr && *qtr != '\n'; ++qtr )
				if ( isupper(*ptr) ) {
					u |= (1UL << (*qtr-'A'));
					++T[*qtr-'A'];
				}
			*qtr++ = ' ', *qtr++ = '=', *qtr++ = ' ', *qtr = '\0';
			tail = sol, memset(cur,0,sizeof(cur)), f(0);
		}
	}
	return 0;
}

