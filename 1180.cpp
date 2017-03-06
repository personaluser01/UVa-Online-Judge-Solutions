/*
 * 1180. Perfect Numbers
 * TOPIC: sieve, sum of divisors
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
typedef long long i64;
using namespace std;
#define N 63
#define Q (1<<21)

i64 p,deg[N],m[Q];
bool isprime[Q];
char s[1 << 21],*ptr;

i64 g( i64 x, i64 n ) {
	i64 ax = 1LL;
	for (;n;n>>=1,x*=x)
		if ( n&1 ) ax *= x;
	return ax;
}

bool f( i64 p ) { 
	if ( p >= 20 ) return false;
	return m[deg[p]-1] == deg[p]; 
}

int main() {
	i64 i,j,k,l,t,ts;
	int jj;
	for ( deg[0]=1, i = 1; i < N; deg[i] = (deg[i-1]<<1), ++i );
	for ( isprime[2]=true, i = 3; i < Q; isprime[i]=true, i += 2 );
	for ( i = 0; i < Q; m[i++] = 1LL );
	for ( i = 2; i < Q; ++i )
		if ( isprime[i] ) 
			for ( j = i+i, m[i] += i; j < Q; m[j] *= (g(i,l+1)-1)/(i-1), isprime[j]=false, j += i ) 
				for ( k = j, l = 0; !(k%i); k /= i, ++l );
	for ( scanf("%lld %s",&ts,s), ptr=s, s[strlen(s)]=','; ts-- && 1 == sscanf(ptr,"%lld,%n",&p,&jj); ptr += jj, puts(f(p)?"Yes":"No") );
	return 0;
}

