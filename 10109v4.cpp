/*
 * 10109. Solving Systems of Linear Equations
 * status: Accepted
 */
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string.h>
#define N 64
typedef long long i64;
using namespace std;

typedef pair<i64,i64> frac;
bool no_solution,inf_solutions;

void pr( frac &c ) {
	printf("%lld / %lld\n",c.first,c.second);
}

int is_zero( frac &a ) {
	assert( a.second );
	return a.first == 0;
}

i64 Abs( i64 x ) { if ( x < 0 ) return -x; return x; }

i64 gcd( i64 x, i64 y ) {
	if ( !y ) return x;
	return gcd(y,x%y);
}

void add_frac( frac &a, frac &b, frac &c ) {
	frac tmp;
	i64 
		m = gcd(Abs(a.second*b.second),gcd(Abs(a.first*b.second),Abs(a.second*b.first))),
		s = (a.first*b.second)/m + (a.second*b.first)/m,
		t = (a.second*b.second)/m,
		d = gcd(Abs(s),Abs(t));
	tmp.first = s/d, tmp.second = t/d;
	c = tmp;
}

void mult_frac( frac &a, frac &b, frac &c ) {
	frac tmp;
	if(is_zero(a)||is_zero(b)) {
		c.first = 0, c.second = 1;
		return ;
	}
	i64 s = gcd(Abs(a.first),Abs(b.second)),
		t = gcd(Abs(a.second),Abs(b.first)),
		m = (a.first/s)*(b.first/t),
		n = (a.second/t)*(b.second/s),
		d = gcd(Abs(m),Abs(n));
	tmp.first = m/d, tmp.second = n/d;
	c = tmp;
}

void Negate( frac &b ) { b.first = -b.first; }
void recip( frac &a ) { 
	assert( !is_zero(a) );
	swap(a.first,a.second);
	if ( a.second < 0 )
		a.second = -a.second, a.first = -a.first;
}

void subtr( frac &a, frac &b, frac &c ) {
	frac tmp,d;
	d = b, Negate(d), add_frac(a,d,tmp), c = tmp;
}

void div_frac( frac &a, frac &b, frac &c ) {
	frac tmp,d;
	assert( !is_zero(b) );
	d = b, recip(d), mult_frac(a,d,tmp), c = tmp;
}

void read_frac( frac &a ) {
	i64 m = 0, n = 0,d;
	int ch,sign = 1;
	for (;(ch = getchar()) != EOF && ch != '-' && ch != '+' && !isdigit(ch); );
	if ( ch == '-' || ch == '+' ) {
		sign = -1;
	}
	else m = ch-'0';
	for(;(ch = getchar()) != EOF && isdigit(ch); m = 10*m + ch-'0' );
	if ( ch == '/' ) {
		ch = getchar();
		if ( ch == '-' || ch == '+' ) {
			if ( ch == '-' ) sign = -sign;
		}
		else {
			assert( isdigit(ch) );
			n = ch-'0';
		}
		for (; (ch = getchar()) != EOF && isdigit(ch); n = 10*n + ch-'0');
		d = gcd(Abs(m),Abs(n));
		a.first = sign*(m / d), a.second = n / d;
		if ( !a.second ) {
			no_solution = true;
		}
		return ;
	}
	a.first = sign*m, a.second = 1;
}

frac A[N][N],B[N];
int m,n,free_vars;


bool find_pivot( int k, int &row, int &col ) {
	int i,j;
	for ( i = k; i < m; ++i )
		for ( j = k; j < n; ++j )
			if ( !is_zero(A[i][j]) ) {
				row = i, col = j;
				return true;
			}
	return false;
}

frac x[N];
int id[N];

void gaussian() {
	int i,j,k,row,col;
	frac cf,s,tmp;

	if ( no_solution ) return ;
	for ( i = 0; i < n; ++i ) id[i] = i;
	for ( k = 0; k < m && k < n; ++k ) {
		if ( !find_pivot(k,row,col) ) {
			for ( i = k; i < m; ++i )
				if ( !is_zero(B[i]) ) {
					no_solution = true;
					return ;
				}
			free_vars = n-k, inf_solutions = true;
			return ;
		}
		assert( !is_zero(A[row][col]) );
		for ( j = 0; j < n; ++j ) swap(A[k][j],A[row][j]);
		swap(id[k],id[col]);
		for ( i = 0; i < m; ++i ) swap(A[i][k],A[i][col]);
		swap(B[k],B[row]);
		assert( !is_zero(A[k][k]) );
		for ( j = k+1; j < n; ++j )
			div_frac(A[k][j],A[k][k],A[k][j]);
		div_frac(B[k],A[k][k],B[k]);
		A[k][k].first = 1, A[k][k].second = 1;
		// assert( A[k][k].first == 1 && A[k][k].second == 1 );
		for ( i = k+1; i < m; mult_frac(B[k],cf,tmp), subtr(B[i],tmp,B[i]), ++i )
			for ( cf = A[i][k], j = k; j < n; ++j )
				mult_frac(A[k][j],cf,tmp), subtr(A[i][j],tmp,A[i][j]);
	}

	if ( m > n ) {
		for ( i = n; i < m; ++i )
			if ( !is_zero(B[i]) ) {
				no_solution = true;
				return ;
			}
	}

	if ( n > m ) {
		free_vars = n-m, inf_solutions = true;
		return ;
	}

	// assert( n == m );
	assert( m >= n );
	assert( !is_zero(A[n-1][n-1]) );

	div_frac(B[n-1],A[n-1][n-1],x[id[n-1]]);
	for ( i = n-2; i >= 0; --i ) {
		s.first = 0, s.second = 1;
		for ( j = i+1; j < n; ++j )
			mult_frac(A[i][j],x[id[j]],tmp), add_frac(s,tmp,s);
		subtr(B[i],s,tmp), div_frac(tmp,A[i][i],x[id[i]]);
	}
}

int main() {
	int i,j,k,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&ts) && ts ) {
		scanf("%d %d",&n,&m);
		if ( cs++ ) putchar('\n');
		printf("Solution for Matrix System # %d\n",ts);
		inf_solutions = no_solution = false;
		for ( i = 0; i < m; read_frac(B[i++]) ) 
			for ( j = 0; j < n; read_frac(A[i][j++]) );
		gaussian();
		if ( no_solution ) {
			puts("No Solution.");
			continue ;
		}
		if ( inf_solutions ) {
			printf("Infinitely many solutions containing %d arbitrary constants.\n",free_vars);
			continue ;
		}
		for ( i = 0; i < n; ++i ) {
			printf("x[%d] = %lld",1+i,x[i].first);
			if ( x[i].second != 1 ) {
				if ( x[i].first == 0 ) {
					putchar('\n');
					continue ;
				}
				printf("/%lld\n",x[i].second);
			}
			else putchar('\n');
		}
	}
	return 0;
}
