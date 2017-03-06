/*
 * 1293. Symbolic Derivation
 * TOPIC: grammars, parsing, recursion
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LEN 0x400

typedef struct cell {
	struct cell *left,*right;
	char op,s[0x10];
} cell;

cell pool[1<<21],*ptr = pool;
char buff[LEN],*qtr,out[LEN],*str;

cell *init() {
	cell *x = ptr++;
	x->left=x->right=NULL,x->op=0[x->s]='\0';
	return x;
};

cell *expr();

void read_num( char *s ) {
	if ( *qtr == '-' || *qtr == '+' ) *s++ = *qtr++;
	for (;*qtr && (*qtr=='.'||isdigit(*qtr)); *s++ = *qtr++ );
	*s = '\0';
};

cell *f00() {
	cell *x=init();
	int k;
	switch ( *qtr ) {
		case '(': x->op = '['; /* original parenthesis need to be preserved */
				  ++qtr, x->left = expr();
				  assert( *qtr++ == ')' );
				  break ;
		case 'x': x->op = *qtr++; break ;
		case 'l': x->op = *qtr++;
				  assert( *qtr++ == 'n' );
				  if ( *qtr == '(' ) ++qtr;
				  x->left = expr();
				  if ( *qtr == ')' ) ++qtr;
				  break ;
		default:  x->op='n', read_num(x->s); break ;
	};
	return x;
};

cell *f01( cell *left ) {
	cell *x;
	if ( *qtr=='*' || *qtr=='/' ) {
		x=init(),x->op=*qtr++,x->left=left,x->right=f00();
		return f01(x);
	};
	return left;
};

cell *f02( cell *left ) {
	cell *x;
	if ( *qtr=='+' || *qtr=='-' ) {
		x=init(),x->op=*qtr++,x->left=left,x->right=f01(f00());
		return f02(x);
	};
	return left;
};

cell *expr() { return f02(f01(f00())); };

void write_as_is( const cell *x ) {
	if ( !x ) return ;
	switch ( x->op ) {
		case 'x': *str++ = 'x'; break ;
		case 'l': *str++='l',*str++='n',*str++='(',write_as_is(x->left),*str++=')'; break ;
		case 'n': str += sprintf(str,"%s",x->s); break ;
		case '[': *str++ = '(',write_as_is(x->left),*str++ = ')'; break ;
		default:  write_as_is(x->left), *str++ = x->op, write_as_is(x->right);
				  break ;
	};
};

void diff( const cell *x ) {
	if ( !x ) return ;
	switch ( x->op ) {
		case 'x': *str++ = '1'; break ;
		case 'l': *str++ = '(', diff(x->left), *str++ = ')';
				  *str++ = '/';
				  *str++='(',write_as_is(x->left),*str++=')';
				  break ;
		case 'n': *str++ = '0'; break ;
		case '[': *str++='(',diff(x->left),*str++=')'; break ;
		default:  switch ( x->op ) {
					 case '*': *str++ = '(';
							   diff(x->left);
							   *str++='*';
							   if ( x->right->op == '+' || x->right->op == '-' ) *str++ = '(';
							   write_as_is(x->right);
							   if ( x->right->op == '+' || x->right->op == '-' ) *str++ = ')';
							   *str++ = '+';
							   if ( x->left->op == '+' || x->left->op == '-' ) *str++ = '(';
							   write_as_is(x->left);
							   if ( x->left->op == '+' || x->left->op == '-' ) *str++ = ')';
							   *str++='*';
							   diff(x->right);
							   *str++ = ')';
							   break ;
					 case '/':  *str++ = '(';
							   	diff(x->left),*str++='*';
								if ( x->right->op == '+' || x->right->op == '-' ) *str++ = '(';
							   	write_as_is(x->right);
								if ( x->right->op == '+' || x->right->op == '-' ) *str++ = ')';
							  		 *str++ = '-';
								if ( x->left->op == '+' || x->left->op == '-' ) *str++ = '(';
							   	write_as_is(x->left);
								if ( x->left->op == '+' || x->left->op == '-' ) *str++ = ')';
								*str++='*';
							   	diff(x->right);
							    *str++ = ')';
							    *str++ = '/';
								if ( x->right->op == '+' || x->right->op == '-' ) *str++ = '(';
							    write_as_is(x->right);
								if ( x->right->op == '+' || x->right->op == '-' ) *str++ = ')';
							    *str++ = '^', *str++ = '2';
							    break ;
					 default:  diff(x->left),*str++=x->op,diff(x->right);
							   break ;
				  };
				  break ;
	};
};

void pri( char *p ) {
	int i,banned=0,k=strlen(p),j;
	if ( p[0] == '\0' ) { puts(""); return ; }
	for ( i = 0; p[i]; ++i ) {
		if ( p[i] == '+' ) {
			if ( p[i+1] == '-' ) continue ;
			if ( banned ) continue ;
			putchar(p[i]), banned = 0;
		}
		else if ( p[i] == '-' ) {
			if ( p[i+1] == '+' ) 
				banned = 1;
			putchar('-');
		}
		else putchar(p[i]), banned = 0;
	}
	putchar('\n');
};

int main() {
	cell *root;
#ifndef ONLINE_JUDGE
	freopen("e.dat","r",stdin);
#endif
	for (;qtr=fgets(buff,sizeof buff,stdin);ptr=pool,str=out,diff(expr()),*str='\0',pri(out));
	return 0;
};

