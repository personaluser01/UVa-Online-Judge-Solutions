/*
 * 327. Evaluating Simple C Expressions
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
#define A 26
#define L (1 << 16)

char buff[L],*ptr;
int a[A],before[A],after[A],is[A],yes,n,inc[A],dec[A];

void skip_space() { for (;*ptr && isspace(*ptr); ++ptr ); }

void remove_spaces() {
	char tmp[L],*qtr = tmp;
	for ( ;*ptr && *ptr != '\n'; ++ptr  )
		if ( !isspace(*ptr) )
			*qtr++ = *ptr;
	for ( *qtr = '\0', ptr = buff+1, qtr = tmp; *qtr;  *ptr++ = *qtr++ );
	*ptr = (char)0, ptr = buff+1;
	if ( 1[buff] != '+' && 1[buff] != '-' )
		0[buff] = '+', ptr = buff;
}

int empty( char *s ) {
	while ( *s && *s != '\n' )
		if ( !isspace(*s++) )
			return 0;
	return 1;
}

int main() {
	int i,j,k,cnt,x,y;
	char op[0x400],ch[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( FG && ++yes ) {
		if ( empty(buff) ) continue ;
		printf("Expression: %s",ptr);
		for ( i = 0; i < A; ++i ) a[i] = 1+i;
		remove_spaces();
		n = strlen(ptr);
		for ( i = 0; i < n; ++i )
			if ( islower(ptr[i]) )
				is[ptr[i]-'a'] = yes;
		for ( i = 0; i < n-1; ++i )
			if ( ptr[i] == '+' && ptr[i+1] == '+' ) {
				if ( i >= 1 && islower(ptr[i-1]) ) {
					after[ptr[i-1]-'a'] = yes, inc[ptr[i-1]-'a'] = yes;
					ptr[i] = ptr[i+1] = ' ';
				}
				else if ( i < n-2 && islower(ptr[i+2]) ) {
					before[ptr[i+2]-'a'] = yes, inc[ptr[i+2]-'a'] = yes;
					ptr[i] = ptr[i+1] = ' ';
				}
			}
			else if ( ptr[i] == '-' && ptr[i+1] == '-' ) {
				if ( i >= 1 && islower(ptr[i-1]) )  {
					after[ptr[i-1]-'a'] = yes, dec[ptr[i-1]-'a'] = yes;
					ptr[i] = ptr[i+1] = ' ';
				}
				else if ( i < n-2 && islower(ptr[i+2]) ) {
					before[ptr[i+2]-'a'] = yes, dec[ptr[i+2]-'a'] = yes;
					ptr[i] = ptr[i+1] = ' ';
				}
			}
		for ( i = 0; i < A; ++i )
			if ( is[i] == yes && before[i] == yes ) {
				if ( inc[i] == yes )
					++a[i];
				else --a[i];
			}
		remove_spaces();
		for ( cnt = 0, j = 0; 2 == sscanf(ptr+cnt,"%1[+-]%1[a-z]%n",op,ch,&k); (j+=((*op=='+')?a[*ch-'a']:-a[*ch-'a'])),cnt+=k );
		printf("    value = %d\n",j);
		for ( i = 0; i < A; ++i )
			if ( is[i] == yes && after[i] == yes ) {
				if ( inc[i] == yes )
					++a[i];
				else --a[i];
			}
		for ( i = 0; i < A; ++i )
			if ( is[i] == yes )
				printf("    %c = %d\n",i+'a',a[i]);
	}
	return 0;
}

