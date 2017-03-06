/*
 * 309. FORCAL
 * TOPIC: parsing, medium, excellent interview question, careful implementation, iron logic
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FG (ptr = fgets(buff,sizeof buff,stdin))

int isReserved( char *a, int len ) {
	char ch[8];
	int i;
	if ( len >= 6 ) return 0;
	for ( i = 0; i < len; ++i )
		ch[i] = tolower(a[i]);
	ch[i] = '\0';
	return strcmp(ch,"write") == 0 ||\
		   strcmp(ch,"read") == 0 || \
		   strcmp(ch,"begin") == 0 ||\
		   strcmp(ch,"end") == 0;
}

int isLiteral( char *a, int len ) {
	int i;
	if ( len >= 9 ) return 0;
	for ( i = 0; i < len; ++i )
		if ( !isdigit(a[i]) )
			return 0;
	return 1;
}

int isIdentifier( char *a, int len ) {
	int i;
	if ( len >= 33 ) return 0;
	for ( i = 0; i < len; ++i )
		if ( !isdigit(a[i]) )
			return 1;
	return 0;
}

int al[256];
char buff[1<<21],*ptr,out[1<<21],*qtr;
char *badWord = "TOKEN ERROR";

int isEmpty( char *p ) {
	while ( p && *p && *p == ' ' ) ++p;
	return !p || !*p || *p == '\n';
}

int main() {
	int i,j,k,ok;
	char word[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	al['('] = al[')'] = al[';'] = al[','] = al['+'] = al['-'] = 1;
	for ( ;FG; *qtr = '\0', puts(out) ) {
		ok = 1, qtr = out;
		do {
			next:
			if ( !ok ) continue ;
			for ( ;*ptr == ' '; ++ptr );
			if ( !*ptr || *ptr == '\n' ) continue ;
			if ( *ptr == '-' && *(ptr+1) == '-' ) continue ;
			if ( al[*ptr] ) {
				*qtr++ = *ptr++, *qtr++ = '\n';
				goto next;
			}
			if ( 1 == sscanf(ptr,"%[A-Za-z0-9_]%n",word,&j) ) {
				k = strlen(word);
				if ( k >= 33 ) {
					ok = 0;
					continue ;
				}
				if ( isReserved(word,j) || isIdentifier(word,j) || isLiteral(word,j) ) {
					for ( i = 0; word[i]; *qtr++ = word[i++] );
					*qtr++ = '\n', ptr += j;
					goto next;
				}
				ok = 0;
			}
			else if ( *ptr == ':' && *(ptr+1) == '=' ) {
				*qtr++ = ':', *qtr++ = '=', *qtr++ = '\n', ptr += 2;
				goto next;
			}
			else ok = 0;
		} while ( !isEmpty(FG) );
		if ( !ok ) {
			for ( ptr = badWord; *ptr; *qtr++ = *ptr++ );
			*qtr++ = '\n';
		}
	}
	return 0;
}

