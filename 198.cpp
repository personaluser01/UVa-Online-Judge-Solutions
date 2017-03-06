/*
 * 198. Peter's Calculator
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cctype>
#include <map>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define skip_spaces for(;*ptr && *ptr != '\n' && isspace(*ptr); ++ptr )
#define get_word(s) for ( s = ""; *ptr && *ptr != '\n' && !isspace(*ptr) && isalnum(*ptr); s += *ptr++ )
#define clean_up for(map<string,cell*>::iterator it=m.begin();it!=m.end();it->second=NULL,++it)
#define oo (1 << 29)
#include <set>
typedef long long i64;

enum { L, R };
using namespace std;

map<string,int> vars;
map<string,string> defs;
set<string> is_being_processed;
char *ptr,buff[0x200];

int is_assignment( char *ptr ) {
	for ( ;*ptr && *ptr != '\n'; ++ptr )
		if ( *ptr == ':' && *(ptr+1) == '=' )
			return 1;
	return 0;
}

char *qtr[0x200],
	 str[0x200][0x200];
bool ok;

typedef struct cell {
	cell *nx[2];
	char op;
	i64 value;
	bool is_var;
	string *var_name;
} cell;

map<string,cell*> m;

cell *init_cell() {
	cell *x = (cell *)malloc(sizeof *x);
	x->nx[L] = x->nx[R] = NULL, x->is_var = false;
	x->value = +oo, x->var_name = NULL;
	return x;
}

i64 get_number( const int t ) {
	i64 x = 0;
	assert( isdigit(*qtr[t]) );
	for ( ;*qtr[t] && *qtr[t] != '\n' && isdigit(*qtr[t]); )
		x = 10*x  + (*qtr[t]++ - '0');
	return x;
}

cell *nil_cell;
cell *expr( const int t, cell *x, char op );

cell *eval_variable( const int t, string var_name ) {
	// printf("Request to evaluate %s\n",var_name.c_str());
	if ( defs.find(var_name) == defs.end() ||\
		is_being_processed.find(var_name) != is_being_processed.end() ) {
		ok = false;
		return NULL;
	}
	if ( m[var_name] == NULL ) {
		sprintf(qtr[t] = str[t],"%s",defs[var_name].c_str());
		is_being_processed.insert(var_name);
		m[var_name] = expr(t,NULL,'#');
		is_being_processed.erase(var_name);
	}
	// printf("Success %s\n",var_name.c_str());
	return m[var_name];
}

cell *f1( const int t ) {
	cell *z;

	if ( *qtr[t] == '(' ) {
		++qtr[t];
		z = expr(t,NULL,'#');
		assert( *qtr[t]++ == ')' );
		return z;
	}
	z = init_cell();
	if ( isdigit(*qtr[t]) || *qtr[t] == '+' || *qtr[t] == '-' ) {
		char op = *qtr[t];
		if ( !isdigit(*qtr[t]) )
			++qtr[t];
		assert( isdigit(*qtr[t]) );
		z->value = get_number(t);
		if ( op == '-' )
			z->value = -z->value;
		// printf("Read value %lld\n",z->value);
		return z;
	}
	assert( isalpha(*qtr[t]) );
	string s;
	for ( s = ""; *qtr[t] && *qtr[t] != '\n' && isalnum(*qtr[t]); s += *qtr[t]++ );
	assert( z );
	z->is_var = true, z->var_name = &s;
	// printf("Var %s\n",s.c_str());
	z->nx[L] = eval_variable(t+1,s);
	return z;
}

cell *f2( const int t, cell *left, char op ) {
	cell *z = init_cell();
	z->nx[L] = left, z->op = op, z->nx[R] = f1(t);
	if ( *qtr[t] == '*' ) 
		return f2(t,z,*qtr[t]++);
	return z;
}

cell *expr( const int t, cell *left, char op ) {
	cell *z = init_cell();
	z->nx[L] = left, z->op = op, z->nx[R] = f2(t,NULL,'#');
	if ( *qtr[t] == '+' || *qtr[t] == '-' ) 
		return expr(t, z, *qtr[t]++ );
	return z;
}

i64 F( cell *x ) {

	if ( !ok || !x ) return +oo;

	if ( x->value < +oo )
		return x->value;

	if ( x->is_var ) 
		return x->value = F(x->nx[L]);

	if ( !x->nx[R] )
		return x->value = F(x->nx[L]);
	if ( !x->nx[L] )
		return x->value = F(x->nx[R]);
	i64 left = F(x->nx[L]),
		right = F(x->nx[R]);
	if ( x->op == '+' )  
		return x->value = left+right;
	if ( x->op == '-' ) 
		return x->value = left-right;
	if ( x->op == '*' )
		return x->value = left*right;
}

int main() {
	string a,b,s;
	i64 val;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	nil_cell = init_cell(), nil_cell->value = 0;
	while ( FG ) {
		skip_spaces;
		get_word(s);
		if ( s == "PRINT" ) {
			skip_spaces;
			get_word(a);
			ok = true;
			eval_variable(0,a);
			if ( !ok ) {
				clean_up;
				puts("UNDEF");
			}
			else {
				printf("%lld\n",F(m[a]));
			}
			is_being_processed.clear();
			continue ;
		}
		if ( s == "RESET" ) {
			m.clear(), defs.clear();
			// is_being_processed.clear();
			continue ;
		}
		if ( is_assignment(ptr) ) {
			for ( ;*ptr && *ptr != '\n' && *ptr != ':'; ++ptr );
			assert( *++ptr == '=' );
			++ptr;
			skip_spaces;
			for( a = ""; *ptr && *ptr != '\n'; ++ptr )
				if ( !isspace(*ptr) )
					a += *ptr;
			defs[s] = a, m[s] = NULL;
			// printf("Assignment %s := %s\n",s.c_str(),a.c_str());
			clean_up;
			is_being_processed.clear();
		}
	}
	return 0;
}

