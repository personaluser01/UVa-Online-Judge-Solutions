/*
 * 12145. Bases
 * TOPIC: maths, number bases, recursion, good lesson
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <vector>
#include <cfloat>
#define tol 1e-13
#define Q (1<<21)
#define oo (DBL_MAX-0x400)
#include <set>

typedef long long int pt;
typedef long long i64;

using namespace std;

bool isprime[Q];
i64 *pr;
int K;

void sieve() {
	int i,j,k;
	for ( isprime[2] = true, i = 3; i < Q; isprime[i] = true, i += 2 );
	for ( i = 3; i < Q; i += 2 )
		for ( j = i+i; isprime[i] && j < Q; isprime[j] = false, j += i );
	for ( K = 0, i = 0; i < Q; ++i )
		if ( isprime[i] ) ++K;
	pr = new i64[K];
	for ( k = 0, i = 0; i < Q; ++i )
		if ( isprime[i] ) pr[k++] = i;
	assert( k == K );
};

void signature( vector<pair<i64,int> > &vec, i64 n ) {
	int i,j,k;
	for ( vec.clear(), i = 0; i < Q && pr[i]*pr[i] <= n; ++i ) {
		for ( j = 0; 0 == (n%pr[i]); n /= pr[i], ++j );
		if ( j ) vec.push_back(make_pair(pr[i],j));
	}
	if ( n > 0 ) vec.push_back(make_pair(n,1));
};

void gen_divisors( set<i64> &d, vector<pair<i64,int> > &vec, int idx, i64 cur ) {
	if ( idx == vec.size() ) d.insert(cur);
	else {
		i64 ax = 1LL;
		for ( int i = 0; i <= vec[idx].second; gen_divisors(d,vec,idx+1,cur*ax), ++i, ax *= vec[idx].first );
	}
};

class poly {
	public:
	pt *c;
	int n;
	poly( int n ) { this->c = new pt[this->n = n+1]; for ( int i = 0; i < this->n; c[i++] = 0 ); }
	~poly() { delete c; };
	pt operator [] ( int i ) const { return c[i]; }
	poly ( i64 x, bool flag ) {
		if ( x == 0 ) {
			c = new pt[this->n = 1];
			0[c] = 0;
			return ;
		}
		int k = (int)(log(x)/log(10.00)+0.5)+4,i = 0;
		c = new pt[this->n = k];
		do c[i++] = (x%10); while ( x/=10 );
		for ( ;i < this->n; c[i++] = 0 );
	};
	int get_deg() const {
		int k;
		for ( k = this->n-1; k >= 0 && fabs(c[k]) < tol; --k );
		return max(k,0);
	};
	bool is_zero() {
		int i;
		for ( i = get_deg(); i >= 0 && fabs(c[i])<tol; --i );
		return i<0;
	};
	pt operator () ( pt t ) const {
		int m = get_deg();
		pt res = 0;
		assert( m==0&&fabs(c[m])<tol || fabs(c[m])>=tol );
		if ( fabs(t-oo) < tol ) {
			return c[m]<0?-oo:+oo;
		}
		else if ( fabs(t+oo) < tol ) {
			if ( m&1 )
				return c[m]<0?+oo:-oo;
			else return c[m]<0?-oo:+oo;
		}
		for ( int i = m; i >= 0; res *= t, res += c[i--] );
		return res;
	};
	poly *add( poly *p ) {
		poly *r = new poly(max(this->n,p->n));
		int i;
		for ( i = 0; i < this->n && i < p->n; ++i )
			r->c[i] = c[i]+(*p)[i];
		for ( ;i < this->n; r->c[i] += c[i], ++i );
		for ( ;i < p->n; r->c[i] += (*p)[i], ++i );
		return r;
	};
	poly *sub( poly *p ) {
		poly *r = new poly(max(this->n,p->n));
		int i;
		for ( i = 0; i < this->n && i < p->n; ++i )
			r->c[i] = c[i]-(*p)[i];
		for ( ;i < this->n; r->c[i] += c[i], ++i );
		for ( ;i < p->n; r->c[i] -= (*p)[i], ++i );
		return r;
	};
	poly *mult( poly *p ) {
		poly *r = new poly(p->n+this->n+4);
		for ( int i = 0; i < this->n; ++i )
			for ( int j = 0; j < p->n; ++j )
				r->c[i+j] += c[i]*(*p)[j];
		return r;
	};
};

bool check( const poly &c, i64 x ) {
	pt acc = 0;
	for ( int i = 0; i < c.n; ++i ) 
		if ( (acc=acc/x+c[i])%x )
			return false ;
	return !(acc%x);
};

poly operator + ( const poly a, const poly b ) {
	poly p = poly(max(a.n,b.n));
	int i;
	for ( i = 0; i < a.n && i < b.n; p.c[i] = a[i]+b[i], ++i );
	for (;i<a.n; p.c[i]+=a[i],++i );
	for (;i<b.n; p.c[i]+=b[i],++i );
	return p;
};
poly operator - ( const poly a, const poly b ) {
	poly p = poly(max(a.n,b.n));
	int i;
	for ( i = 0; i < a.n && i < b.n; p.c[i] = a[i]-b[i], ++i );
	for (;i<a.n; p.c[i]+=a[i],++i );
	for (;i<b.n; p.c[i]-=b[i],++i );
	return p;
};
poly operator * ( const poly a, const poly b ) {
	poly p = poly(a.n+b.n+2);
	for ( int i = 0; i < a.n; ++i )
		for ( int j = 0; j < b.n; ++j )
			p.c[i+j] += a[i]*b[j];
	return p;
};

poly operator ~ ( const poly &a ) {
	poly p = poly(a.n-1);
	for ( int i = 1; i < a.n; p.c[i-1] = i*a[i], ++i );
	return p;
};

long double root_in( const poly &c, long double l, long double r ) {
	long double L = c(l), R = c(r), low, high, mid, x[2] = {0};
	int t;
	if ( L > 0 && R > 0 || L < 0 && R < 0 ) return +oo;
	if ( fabs(L) < tol ) return l;
	if ( fabs(R) < tol ) return r;
	/*
	poly g = ~c;
	for ( x[t=0] = (2*l+r)/3.00, x[t^1] = (l+2*r)/3.00; fabs(x[1]-x[0])>=tol; )
		t^=1,x[t]=x[t^1]-c(x[t^1])/g(x[t^1]);
	if ( fabs(c(x[t])) < tol )
		return (x[t]+x[t^1])/2;
	*/
	if ( L < 0 ) {
		assert( L < 0 && R > 0 );
		for ( low=l, high=r; fabs(high-low)>=tol; c(mid=(low+high)/2)<0?(low=mid):(high=mid) );
	}
	else {
		assert( L > 0 && R < 0 );
		for ( low=l, high=r; fabs(high-low)>=tol; c(mid=(low+high)/2)>0?(low=mid):(high=mid) );
	}
	return (low+high)/2;
};

bool find_roots( const poly &c, long double *x, int &k ) {
	int m = c.get_deg(),l,i;
	long double *xx = new long double[m+2],r;
	if ( m == 1 ) {
		0[x] = (-c[0]+0.00)/c[1], k = 1;
		return true ;
	}
	assert( m >= 2 );
	if ( !find_roots(~c,xx+1,l) ) return false ;
	for ( k = 0, xx[0] = -oo, xx[l+1] = +oo, i = 0; i <= l; ++i ) {
		if ( (x[k]=root_in(c,xx[i],xx[i+1])) < +oo ) ++k;
	}
	delete xx;
	return k>0;
};

class Parser {
	char buff[0x400];
	int cur;
		public:
	Parser( string s ) {
		int n = strlen(s.c_str());
		buff[n] = '$', cur = 0;
		for ( int i = 0; i < n; ++i ) buff[i] = s[i];
	};
	struct cell {
		cell *son[2];
		char op;
		i64 B;
		cell() { op='$', son[0]=son[1]=NULL; };
		cell( char ch ) { op = ch, son[0]=son[1]=NULL; };
		cell( i64 B, char ch ) { this->B=B, op=ch, son[0]=son[1]=NULL; };
	};
	cell *root;
	cell *f00() {
		cell *x = NULL;
		if ( '0'<=buff[cur]&&buff[cur]<='9' ) {
			i64 res = 0;
			for (;'0'<=buff[cur]&&buff[cur]<='9'; res*=10, res+=buff[cur++]-'0' );
			x = new cell(res,'$');
		}
		return x;
	};
	cell *f01( cell *left ) {
		if ( buff[cur] == '*' ) {
			cell *x = new cell(buff[cur++]);
			x->son[0] = left, x->son[1] = f00();
			return f01(x);
		}
		return left;
	};
	cell *f02( cell *left ) {
		if ( buff[cur] == '+' ) {
			cell *x = new cell(buff[cur++]);
			x->son[0] = left, x->son[1] = f01(f00());
			return f02(x);
		}
		return left;
	}
	cell *expr() { return f02(f01(f00())); };
	poly *eval( const cell *c ) {
		assert( c );
		if ( c->op == '+' )
			return eval(c->son[0])->add(eval(c->son[1]));
		if ( c->op == '*' )
			return eval(c->son[0])->mult(eval(c->son[1]));
		return new poly(c->B,true);
	};
	void finalize() {
		root = expr();
		assert( buff[cur] == '$' );
	};
	poly *yield() {
		finalize();
		return eval(root);
	};
	void destroy( cell *x ) {
		if ( !x ) return ;
		if ( x->son[0] ) destroy(x->son[0]);
		if ( x->son[1] ) destroy(x->son[1]);
		delete x;
	}
	~Parser() {
		destroy(root);
	};
};

bool is_int( long double t ) {
	i64 b = (i64)(t), u = b+1;
	return fabs(b-t)<tol || fabs(u-t)<tol;
};

i64 to_int( long double t ) {
	i64 b = (i64)(t), u = b+1;
	return fabs(b-t)<tol?b:u;
};

int main() {
	int i,j,k,l,t;
	char buff[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sieve(); fgets(buff,sizeof buff,stdin); ) {
		string left = "", right = "";
		char out[0x400],*ptr = out;
		for ( i = 0; buff[i] != '=' && buff[i] != '\0' && buff[i] != '\n'; ++i )
			if ( isdigit(buff[i]) || buff[i] == '+' || buff[i] == '*' )
				*ptr++ = buff[i];
		assert( buff[i] == '=' );
		*ptr = '\0', left = string(out);
		for ( ptr = out, ++i; buff[i] != '\0' && buff[i] != '\n'; ++i )
			if ( isdigit(buff[i]) || buff[i] == '+' || buff[i] == '*' )
				*ptr++ = buff[i];
		*ptr = '\0', right = string(out);
		if ( left == "" && right == "" ) break ;
		char largest = '1';
		for ( i = 0; buff[i] != '\n' && buff[i] != '\0'; ++i )
			if ( isdigit(buff[i]) )
				largest = max(largest,buff[i]);
		Parser *L = new Parser(left), *R = new Parser(right);
		poly *x = L->yield(), *y = R->yield(), *z = x->sub(y);
		if ( z->is_zero() ) {
			int T = largest-'0';
			printf("%d+\n",++T);
			continue ;
		}
		if ( (k=z->get_deg()) == 0 ) {
			puts("*");
			continue ;
		}
		/*
		long double *rt = new long double[k+1], ro;
		if ( find_roots(*z,rt,l) ) {
			vector<i64> vec;
			for ( i = 0; i < l; ++i ) {
				if ( !is_int(rt[i]) || rt[i] <= largest-'0' ) 
					continue ;
				vec.push_back(to_int(rt[i]));
			}
			if ( vec.size() ) {
				for ( i = 0; i < vec.size(); ++i ) {
					if ( i ) putchar(' ');
					printf("%lld",vec[i]);
				}
				puts("");
			}
			else puts("*");
		}
		else puts("*");
		*/
		for ( k = 0, i = 0; i < z->n && (*z)[i] == 0; ++k, ++i );
		set<i64> divisors;
		vector<pair<i64,int> > vec;
		vector<i64> u;
		u.clear(), vec.clear();
		assert( z->c[k] );
		signature(vec,z->c[k]<0?-z->c[k]:z->c[k]);
		gen_divisors(divisors,vec,0,1LL);
		assert( divisors.count(z->c[k]<0?-z->c[k]:z->c[k]) );
		for ( set<i64>::iterator it = divisors.begin(); it != divisors.end(); ++it ) {
			if ( *it > largest-'0' && check(*z,*it) ) 
				u.push_back(*it);
		}
		if ( !u.size() )
			puts("*");
		else {
			for ( i = 0; i < (int)u.size(); ++i ) {
				if ( i ) putchar(' ');
				printf("%lld",u[i]);
			}
			putchar('\n');
		}
	}
	return 0;
}

