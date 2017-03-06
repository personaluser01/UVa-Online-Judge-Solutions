/*
 * 11889. Benefit
 * status: Accepted
 * TOPIC: lcm,sieve,primes,factorisation
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;
typedef long long i64;
#define M 10000

int ts,n,m,deg[2][M],len[2];
bool isprime[M];
map<i64,int> s[2];
i64 p[M],A,B,C,q[2][M];

i64 pw( i64 x, i64 n ) {
    i64 ax = 1LL;
    for(;n; n>>=1, x *= x)
        if ( n&1 ) ax *= x;
    return ax;
}

void factorise( i64 n, i64 *pr, int *deg, int *len ) {
    int i;
    for(*len=0,i=0;i<m&&p[i]<=n;++i)
        if ( !(n%p[i]) )
            for ( pr[(*len)++] = p[i], deg[(*len)-1] = 0; !(n%p[i]); ++deg[(*len)-1], n /= p[i] );
    if ( n > 1 )
        pr[(*len)++] = n, deg[*len-1] = 1;
}

int main() {
    i64 i,j,k,a,c;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( isprime[2]=true, i=3; i<M; i+=2 ) isprime[i]=true;
    for ( i = 3; i < M; i += 2 )
        if ( isprime[i] )
            for ( j = i+i; j < M; j += i )
                isprime[j] = false;
    for ( i = 0; i < M; ++i )
        if ( isprime[i] )
            p[m++] = i;
    for ( scanf("%d",&ts); ts-- && 2 == scanf("%lld %lld",&A,&C); ) {
        factorise(A,q[0],deg[0],len), factorise(C,q[1],deg[1],len+1), B = 1;
        for ( i = 0; i < 2; ++i ) 
            for ( s[i].clear(), j = 0; j < len[i]; ++j )
                s[i][q[i][j]] = deg[i][j];
        bool ok = true;
        for ( map<i64,int>::iterator it = s[0].begin(); it != s[0].end() && ok; ++it )
            if ( s[1].find(it->first) == s[1].end() || s[1][it->first] < it->second )
                ok = false;
        if ( !ok ) {
            puts("NO SOLUTION");
            continue ;
        }
        for ( map<i64,int>::iterator it = s[1].begin(); it != s[1].end(); ++it ) 
            if ( s[0].find(it->first) == s[0].end() || s[0][it->first] < it->second )
                B *= pw(it->first,it->second);
        printf("%lld\n",B);
    }
    return 0;
}

