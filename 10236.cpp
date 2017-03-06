/*
 * 10236. Fibonacci Primes
 * TOPIC: maths, logs, precision
 * status: Accepted
 */
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define BIT(k) (1ULL<<((k)))
#define SET(a,k) (a[(k)>>3] |= BIT((k)&7))
#define CLR(a,k) (a[(k)>>3] &= ~BIT((k)&7))
#define TST(a,k) (a[(k)>>3] & BIT((k)&7))
#define Q (1<<21)
#include <math.h>
#define N 22017
#define tol 1e-10
#include <vector>
#define M (1<<21)
using namespace std;
typedef long long i64;

unsigned char isprime[Q];
int p[Q],m,n;
const long double a = (sqrt(5.00)+1)/2, h = log(5.00)/log(10.00)/2, g = log(a)/log(10.00);
long double L,H,r;
vector<int> vec;
vector<i64> u;
i64 ans;
long double fib[M];

void fb() {
	bool flag = false ;
	int i,j,k;
	for ( fib[1] = fib[2] = 1, i = 3; i < M; ++i ) {
		if ( flag ) {
			fib[i] = fib[i-1]+fib[i-2]/10, flag = false ;
		}
		else {
			fib[i] = fib[i-1]+fib[i-2];
		}
		if ( fib[i] > 1e9 )
			fib[i] /= 10, flag = true ;
	}
}

int main() {
	int i,j,k,len;
	long double val;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( SET(isprime,2), i = 3; i < Q; i += 2 ) SET(isprime,i);
	for ( i = 3; i < Q; i += 2 )
		for ( j = i+i; j < Q && TST(isprime,i); j += i )
			CLR(isprime,j);
	for ( m = 0, i = 2; i < Q; ++i )
		if ( TST(isprime,i) )
			p[m++] = i;
	for ( vec.push_back(4), i = 0; i < m; vec.push_back(p[i++]) );
	sort(vec.begin(),vec.end());
	i64 x,y,z;
	for ( u.push_back(2), x = 1, y = 2, i = 4; (z=x+y) < 2000000000LL; ++i, x=y, y=z ) 
		if ( TST(isprime,i) || i == 4 ) u.push_back(z);
	fb();
	for ( ;1==scanf("%d",&n); ) {
		if ( n <= u.size() ) {
			for ( ans = u[n-1]; ans >= 1000000000L; ans /= 10 );
			printf("%lld\n",ans);
			continue ;
		}
		printf("%lld\n",(i64)(fib[vec[n]]-tol));
		/*
		n = vec[n];
		L = n*g-h-9, H = n*g-h-10;
		k = (int)(floor(L));
		x = (i64)(n*g-h-k);
		val = n*g-h-k-x;
		if ( !(n&1) )
			val = pow(10.00,val+(1e-12));
		else 
			val = pow(10.00,val-(1e-12));
		char s[0x40],out[0x40],*ptr = out;
		sprintf(s,"%.12Lf",val);
		for ( i = 0; s[i] != '.'; ++i );
		for ( j = 0; j < i; *ptr++ = s[j++] );
		for ( len = i; len <= 10 && x > 0; ++len, --x )
			*ptr++ = s[len+1];
		*ptr = '\0';
		for ( i = 0; i < 9 && out[i]; ++i )
			putchar(out[i]);
		puts("");
		*/
	}
	return 0;
}

