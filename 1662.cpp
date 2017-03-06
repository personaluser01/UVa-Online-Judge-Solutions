/*
 * 1662. Brackets Removal
 * TOPIC: grammars, parsing
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define is_var(x) ('a'<=(x)->op&&(x)->op<='z')
#define LEN (1<<12)
enum { L, R };
using namespace std;

char buff[LEN],*ptr,st[LEN],*top;
int n;

struct cell {
	cell *son[2];
	char op,sign;
	cell() { this->op = '\0'; };
	cell( char op, char sign ) { 
		this->op = op, this->sign = sign; 
		son[L] = son[R] = NULL;
	}
};

cell *expr();

cell *f02() {
	cell *x;
	int sign = 1;
	if ( *ptr == '-' || *ptr == '+' ) 
		if ( *ptr++ == '-' ) sign = -1;
	if ( *ptr == '(' ) {
		++ptr, x = expr();
		assert( *ptr++ == ')' );
		return x;
	}
	if ( 'a'<=*ptr && *ptr<='z' ) 
		return new cell(*ptr++,sign);
	return NULL;
};

cell *f01( cell *left ) {
	cell *x;
	if ( *ptr == '*' || *ptr == '/' ) {
		x = new cell(*ptr++,1);
		x->son[L] = left, x->son[R] = f02();
		return f01(x);
	}
	return left;
};

cell *f00( cell *left ) {
	cell *x;
	if ( *ptr == '-' || *ptr == '+' ) {
		x = new cell(*ptr++,1);
		x->son[L] = left, x->son[R] = f01(f02());
		return f00(x);
	}
	return left;
};

cell *expr() { return f00(f01(f02())); }

cell *root;

void f(cell *);

void g( cell *x ) {
	if ( is_var(x) ) { *++top = x->op; return ; }
	switch ( x->op ) {
		case '+': g(x->son[L]), *++top = '-', *++top = '(', f(x->son[R]), *++top = ')'; return ;
		case '-': g(x->son[L]), *++top = '+', *++top = '(', f(x->son[R]), *++top = ')'; return ;
		default: f(x); return ;
	}
}

void h( cell *x ) {
	if ( is_var(x) ) { *++top = x->op; return ; }
	switch ( x->op ) {
		case '*': if ( is_var(x->son[L]) || x->son[L]->op == '*' || x->son[L]->op == '/' ) 
						h(x->son[L]);
				  else *++top = '(', f(x->son[L]), *++top = ')';
				  *++top = '/', *++top = '(', f(x->son[R]), *++top = ')';
				  return ;
		case '/': if ( is_var(x->son[L]) || x->son[L]->op == '*' || x->son[L]->op == '/' ) 
						h(x->son[L]);
				  else *++top = '(', f(x->son[L]), *++top = ')';
				  *++top = '*', *++top = '(', f(x->son[R]), *++top = ')';
				  return ;
		default: f(x); return ;
	}
}

void f( cell *x ) {
	assert( x );
	if ( is_var(x) ) { *++top = x->op; return ; }
	switch ( x->op ) {
		case '+': f(x->son[L]), *++top = '+', f(x->son[R]); return ;
		case '-': if ( is_var(x->son[R]) || x->son[R]->op == '*' || x->son[R]->op == '/' ) {
						f(x->son[L]), *++top = '-', f(x->son[R]);
						return ;
				  }
				  f(x->son[L]), *++top = '-', g(x->son[R]); return ;
		case '*': if ( is_var(x->son[L]) || x->son[L]->op == '*' || x->son[L]->op == '/' ) {
						f(x->son[L]), *++top = '*';
						if ( is_var(x->son[R]) || x->son[R]->op == '*' || x->son[R]->op == '/' ) 
							f(x->son[R]);
						else *++top = '(', f(x->son[R]), *++top = ')';
						return ;
				  }
				  *++top = '(', f(x->son[L]), *++top = ')', *++top = '*';
				  if ( is_var(x->son[R]) || x->son[R]->op == '*' || x->son[R]->op == '/' ) 
						f(x->son[R]);
				  else *++top = '(', f(x->son[R]), *++top = ')';
				  return ;
		case '/': if ( is_var(x->son[L]) || x->son[L]->op == '*' || x->son[L]->op == '/' ) {
						 f(x->son[L]), *++top = '/';
						 if ( is_var(x->son[R]) || x->son[R]->op == '*' || x->son[R]->op == '/' )
								h(x->son[R]);
						 else *++top = '(', f(x->son[R]), *++top = ')';
						 return ;
				  }
				  *++top = '(', f(x->son[L]), *++top = ')', *++top = '/';
				  if ( is_var(x->son[R]) || x->son[R]->op == '*' || x->son[R]->op == '/' )
						 h(x->son[R]);
				  else *++top = '(', f(x->son[R]), *++top = ')';
				  return ;
	}
}

int main() {
	bool flag;
	int i;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;fgets(buff,sizeof buff,stdin);) {
		for ( n = 0; buff[n] && buff[n] != '\n'; ++n );
		buff[n] = '\0', ptr = buff, root = expr();
		do {
			top = st, f(root), *++top = '\0';
			flag = strcmp(st+1,buff) != 0;
			for ( n = 0, i = 1; i <= top-st; buff[n++] = st[i++] );
			ptr = buff, buff[n] = '\0';
			root = expr();
		} while ( flag );
		puts(st+1);
	}
	return 0;
}

