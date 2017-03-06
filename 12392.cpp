/*
 * 12393. Guess the Numbers
 * TOPIC: backtracking, parsing
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define N 0x10
enum { L, R };
using namespace std;
typedef long long i64;

char buff[0x400],*ptr;
set<char> s;

struct cell {
	struct cell *son[2];
	char op,var;
	cell( char OP, char VAR) { op = OP, var = VAR, son[L]=son[R]=NULL; };
	cell() { op=var='\0',son[L]=son[R]=NULL; };
};

cell *expr();

cell *f00() {
	cell *x;
	if ( 'a' <= *ptr && *ptr <= 'z' ) {
		s.insert(*ptr);
		return new cell('\0',*ptr++);
	}
	if ( *ptr == '(' ) {
		++ptr, x = expr();
		assert( *ptr++ == ')' );
		return x;
	}
	return NULL;
};

cell *f01( cell *left ) {
	cell *x;
	if ( *ptr == '*' ) {
		x = new cell(*ptr++,'\0');
		x->son[L] = left, x->son[R] = f00();
		return f01(x);
	}
	return left;
}

cell *f02( cell *left ) {
	cell *x;
	if ( *ptr == '+' || *ptr == '-' ) {
		x = new cell(*ptr++,'\0');
		x->son[L] = left, x->son[R] = f01(f00());
		return f02(x);
	}
	return left;
}

cell *expr() { return f02(f01(f00())); };

int n;
i64 c[N],value,val[26];
cell *root;

i64 eval( cell *x ) {
	if ( x->var ) 
		return val[x->var-'a'];
	assert( x->op );
	if ( x->op == '*' )
		return eval(x->son[L])*eval(x->son[R]);
	if ( x->op == '+' )
		return eval(x->son[L])+eval(x->son[R]);
	return eval(x->son[L])-eval(x->son[R]);
}

int main() {
	int i,j,k;
	bool ok;
	vector<char> v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( ptr = fgets(buff,sizeof buff,stdin) ) {
		sscanf(ptr,"%d%n",&n,&j);
		if ( n == 0 ) break ;
		for ( ptr += j, i = 0; i < n; sscanf(ptr,"%lld%n",&c[i++],&j), ptr += j );
		assert( 1 == sscanf(ptr,"%lld",&value) );
		ptr = fgets(buff,sizeof buff,stdin);
		s.clear(), root = expr(), v.clear();
		assert( *ptr == '\n' || *ptr == '\0' );
		for ( set<char>::iterator it = s.begin(); it != s.end(); v.push_back(*it++) );
		assert( v.size() == n );
		sort(v.begin(),v.end()), ok = false;
		assert( s.size() == n );
		do {
			for ( i = 0; i < (int)v.size(); val[v[i]-'a'] = c[i], ++i );
			if ( eval(root) == value ) { ok = true; break; };
		} while ( next_permutation(v.begin(),v.end()) );
		puts(ok?"YES":"NO");
	}
	return 0;
}

