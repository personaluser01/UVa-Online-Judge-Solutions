/*
 * 1661. Equation
 * TOPIC: infix/postfix, stacks, parsing, grammars, linear equations, algebra
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
enum { L, R };
using namespace std;
#define oo (1LL << 43)
typedef long long i64;

i64 GCD( i64 x, i64 y ) { return (!y)?x:GCD(y,x%y); }

struct Pair {
	i64 k,b;
	Pair() {};
	Pair( i64 k, i64 b ) { this->k = k, this->b = b; };
	i64 gcd() const { return GCD(this->k,this->b); };
	bool is_constant() const { return k == 0; };
	bool is_zero() const { return k == 0 && b == 0; };
	void operator += ( const Pair &q ) {
		this->k += q.k;
		this->b += q.b;
	};
	void operator -= ( const Pair &q ) {
		this->k -= q.k;
		this->b -= q.b;
	};
	void operator *= ( const Pair &q ) {
		this->k = this->k*q.b + this->b*q.k;
		this->b = this->b*q.b;
	};
	void operator /= ( const i64 &q ) {
		this->k /= q, this->b /= q;
	};
	void negate() { this->k = -this->k, this->b = -this->b; };
	string to_string() {
		char A[0x20],B[0x20];
		sprintf(A,"%lld",k), sprintf(B,"%lld",b);
		if ( k == 0 ) 
			return string(B);
		return string(A)+"X+"+string(B);
	};
};

Pair operator + ( const Pair &p, const Pair &q ) { Pair r = p; r+=q; return r; };
Pair operator - ( const Pair &p, const Pair &q ) { Pair r = p; r-=q; return r; };
Pair operator * ( const Pair &p, const Pair &q ) { Pair r = p; r*=q; return r; };
Pair operator / ( const Pair &p, const i64 &q ) { Pair r = p; r/=q; return r; };

i64 ggcd( const Pair &p, const Pair &q ) { return GCD(p.gcd(),q.gcd()); };

struct Frac {
	Pair m,n;
	bool is_constant() const { return m.is_constant() && n.is_constant(); }
	Frac() { this->m = *(new Pair(0,0)), this->n = *(new Pair(0,1)); };
	Frac( Pair m, Pair n ) { this->m = m, this->n = n; };
	void negate() { this->m.negate(); };
	string to_string() {
		return m.to_string()+"/"+n.to_string();
	};
	Frac operator += ( const Frac &other ) {
		Pair M = this->m*other.n + this->n*other.m,
			 N = this->n*other.n;
		i64 d = ggcd(M,N);
		M /= d, N /= d;
		this->m = M, this->n = N;
	};
	Frac operator -= ( const Frac &other ) {
		Pair M = this->m*other.n - this->n*other.m,
			 N = this->n*other.n;
		i64 d = ggcd(M,N);
		M /= d, N /= d;
		this->m = M, this->n = N;
	};
	Frac operator *= ( const Frac &other ) {
		Pair M = this->m*other.m,
			 N = this->n*other.n;
		i64 d = ggcd(M,N);
		M /= d, N /= d;
		this->m = M, this->n = N;
	};
	Frac operator /= ( const Frac &other ) {
		Pair M = this->m*other.n,
			 N = this->n*other.m;
		i64 d = ggcd(M,N);
		M /= d, N /= d;
		this->m = M, this->n = N;
	};
};

Frac operator + ( const Frac &p, const Frac &q ) { Frac r = p; r += q; return r; };
Frac operator - ( const Frac &p, const Frac &q ) { Frac r = p; r -= q; return r; };
Frac operator * ( const Frac &p, const Frac &q ) { Frac r = p; r *= q; return r; };
Frac operator / ( const Frac &p, const Frac &q ) { Frac r = p; r /= q; return r; };

struct Cell {
	char op;
	Frac *val;
	Cell *son[2];
	bool has_x;
	Cell() { this->son[L] = this->son[R] = NULL; this->val = NULL; this->op = '$'; this->has_x = false; };
};

char buff[0x400],*ptr;
Pair ONE = *(new Pair(0,1));

Cell *expr();

Cell *f02() {
	Cell *x;
	i64 k=0,sign=1;
	// printf("Entering with %c\n",*ptr);
	if ( *ptr == '-' || *ptr == '+' ) {
		if ( *ptr == '-' ) sign = -1;
		++ptr;
	}
	if ( *ptr == '(' ) {
		++ptr, x = expr();
		assert( *ptr++ == ')' );
		if ( sign == -1 ) x->val->negate();
		return x;
	}
	assert( *ptr );
	if ( *ptr == 'X' ) {
		++ptr;
		x = new Cell(), x->val = new Frac(*(new Pair(sign,0)),ONE);
		return x;
	}
	assert( '0' <= *ptr && *ptr <= '9' );
	for ( ;*ptr && '0' <= *ptr && *ptr <= '9'; k = 10*k + (*ptr++-'0') );
	x = new Cell(), x->val = new Frac(*(new Pair(0,sign*k)),ONE);
	return x;
};

Cell *f01( Cell *left ) {
	Cell *x;
	if ( *ptr == '*' || *ptr == '/' ) {
		x = new Cell(), x->op = *ptr++, x->son[L] = left, x->son[R] = f02();
		return f01(x);
	}
	return left;
};

Cell *f00( Cell *left ) {
	Cell *x;
	if ( *ptr == '+' || *ptr == '-' ) {
		x = new Cell(), x->op = *ptr++, x->son[L] = left, x->son[R] = f01(f02());
		return f00(x);
	}
	return left;
}

Cell *expr() { return f00(f01(f02())); };

Frac eval( Cell *x ) {
	assert( x );
	if ( x->op == '$' ) {
		return *(x->val);
	}
	assert( !x->val );
	switch ( x->op ) {
		case '+': return eval(x->son[L])+eval(x->son[R]);
		case '-': return eval(x->son[L])-eval(x->son[R]);
		case '*': return eval(x->son[L])*eval(x->son[R]);
		case '/': return eval(x->son[L])/eval(x->son[R]);
		default: assert(0);
	}
}

Frac ZERO = *(new Frac(*(new Pair(0,0)),*(new Pair(0,1))));

Frac evall( Cell *x, bool *ok ) {
	Frac r;
	assert( x );
	if ( x->op == '$' ) {
		return *(x->val);
	}
	assert( !x->val );
	switch ( x->op ) {
		case '+': return evall(x->son[L],ok)+evall(x->son[R],ok);
		case '-': return evall(x->son[L],ok)-evall(x->son[R],ok);
		case '*': return evall(x->son[L],ok)*evall(x->son[R],ok);
		case '/': r = evall(x->son[R],ok);
				  if ( !ok ) return ZERO;
				  if ( r.m.k == 0 && r.m.b == 0 ) {
						 *ok = false; 
						 return ZERO;
				  }
				  return evall(x->son[L],ok)/r;
		default: assert(0);
	}
}

char tmp[0x400],a[0x400];
string st[0x400],*top;

int main() {
	int i,j,k,n;
	string p,q;
	Cell *root;
	Frac res;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( fgets(tmp,sizeof tmp,stdin) ) {
		for ( n = 0; tmp[n] && tmp[n] != '\n'; ++n );
		for ( tmp[n] = '\0', ptr=tmp, top=st; 1 == sscanf(ptr,"%s%n",a,&j); ptr += j ) {
			if ( 1[a] ) { *++top = string(a); continue ; }
			switch ( 0[a] ) {
				case '+': q = *top--, p = *top--, *++top = "("+p+"+"+q+")";
						  break ;
				case '-': q = *top--, p = *top--, *++top = "("+p+"-"+q+")";
						  break ;
				case '*': q = *top--, p = *top--, *++top = "("+p+"*"+q+")";
						  break ;
				case '/': q = *top--, p = *top--, *++top = "("+p+"/"+q+")";
						  break ;
				default: *++top = string(a);
						 break ;
			}
		}
		assert( top-st == 1 );
		for ( ptr = buff, p = *top--, i = 0; i < p.size(); buff[i] = p[i], ++i );
		buff[i] = '\0', root = expr(), res = eval(root);
		if ( res.m.is_constant() ) {
			if ( res.m.is_zero() ) {
				puts("MULTIPLE");
				continue ;
			}
			puts("NONE");
			continue ;
		}
		Pair M = res.m;
		i64 up = -M.b, down = M.k, g = GCD(up,down);
		up /= g, down /= g;
		if ( down < 0 ) up = -up, down = -down;
		Frac t = *(new Frac(*(new Pair(0,up)),*(new Pair(0,down))));
		for ( n = 0, i = 0, p.replace(p.find("X"),1,"("+t.to_string()+")"); i < p.size(); buff[n++] = p[i++] );
		buff[n] = '\0', ptr = buff, root = expr();
		bool ok = true ;
		// printf("Going to check %s\n",t.to_string().c_str());
		evall(root,&ok);
		if ( ok ) printf("X = %lld/%lld\n",up,down);
		else puts("NONE");
	};
	return 0;
};

