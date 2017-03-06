/*
 * 325. Identifying Legal Pascal Constants
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

char buff[0x400],*ptr,*qtr,legal_char[256],ok;

int q7() {
	if ( isdigit(*ptr) )
		return ++ptr, q7();
	if ( !*ptr )
		return 1;
	return 0;
}

int q6() {
	if ( isdigit(*ptr) )
		return ++ptr, q7();
	return 0;
}

int q3() {
	if ( *ptr == '+'||*ptr == '-' )
		return ++ptr, q6();
	if ( isdigit(*ptr) )
		return ++ptr, q7();
	return 0;
}

int q5() {
	if ( isdigit(*ptr) )
		return ++ptr, q5();
	if ( *ptr == 'e'||*ptr == 'E' )
		return ++ptr, q3();
	if ( !*ptr )
		return 1;
	return 0;
}

int q4() {
	if ( isdigit(*ptr) )
		return ++ptr, q5();
	return 0;
}

int q2() {
	if ( isdigit(*ptr) )
		return ++ptr, q2();
	if ( *ptr == '.' )
		return ++ptr, q4();
	if ( *ptr == 'e'||*ptr == 'E' )
		return ++ptr, q3();
	return 0;
}

int q1() {
	if ( isdigit(*ptr) )
		return ++ptr, q2();
	return 0;
}

int q0() {
	if ( *ptr == '+'||*ptr=='-' ) 
		return ++ptr, q1();
	if ( isdigit(*ptr) ) 
		return ++ptr, q2();
	if ( *ptr == 'e'||*ptr == 'E' )
		return ++ptr, q3();
	return 0;
}

int main() {
	int i,j,k,cnt;
	char *pch,tmp[0x400],*hold;
	double val;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; ++i ) legal_char[i] = 1;
	legal_char['.'] = legal_char['E'] = legal_char['e'] = legal_char['+'] = legal_char['-'] = 1;
	for(;1==scanf("%[^\n]\n",buff)&&!(0[buff]=='*'&&1[buff]=='\0');) {
		for ( ptr = buff; *ptr && isspace(*ptr); ++ptr );
		if ( !*ptr ) goto FAIL;
		for ( qtr = ptr+1; *qtr; ++qtr );
		for ( --qtr; qtr > ptr && isspace(*qtr); --qtr );
		*++qtr = '\0', hold = ptr;
		if ( !q0() ) goto FAIL;
		OK: printf("%s is legal.\n",hold);
		continue ;
		FAIL: printf("%s is illegal.\n",hold);
		continue ;
	}
	return 0;
}
