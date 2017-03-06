*
 * 10484. Divisibility of Factors
 * status: Accepted
 * TOPIC: divisibility, prime factorisation, sieve, combinatorics, product rule
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
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
#define N 0x80

i64 n,d,p[1 << 16],m;
u64 f[N];
bool isprime[1 << 16];
char deg[1 << 16],b[1 << 16];
vector<pair<i64,int> > u,v;

void factorize( i64 n, vector<pair<i64,int> > &u ) {
    int i,j,k;
    for ( u.clear(), i = 0; i < m && p[i] <= n; ++i )
        if ( !(n%p[i]) ) {
            for ( k = 0; !(n%p[i]); n /= p[i], ++k );
            u.push_back(make_pair(p[i],k));
        }
    if ( n > 1 )
        u.push_back(make_pair(n,1));
}

int main() {
    i64 i,j,k,ax;
    bool ok;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    f[0] = 1ULL;
    for ( u64 t = 1; t <= 20; ++t ) f[t] = t*f[t-1];
    for ( i = 3; i < (1 << 16); i += 2 ) isprime[i] = true;
    for ( isprime[2] = true, i = 3; i < (1 << 16); i += 2 )
        if ( isprime[i] )
            for ( j = i+i; j < (1 << 16); j += i )
                isprime[j] = false;
    for ( i = 0; i < (1 << 16); ++i )
        if ( isprime[i] )
            p[m++] = i;
    for ( ;2 == scanf("%lld %lld",&n,&d); ) {
        if ( n == 0 && d == 0 ) break ;
        if ( d < 0 ) d = -d;
        for ( i = 0; i < m && p[i] <= n; ++i )
            for ( deg[i] = 0, k = n, ax = p[i]; ax <= n; ax *= p[i] )
                deg[i] += (n/ax);
        for ( v.clear(), j = 0; j < i; ++j )
            v.push_back(make_pair(p[j],deg[j]));
        factorize(d,u);
        if ( u.size() > v.size() ) {
            puts("0");
            continue ;
        }
        for ( ok = true, ax = 1LL, i = 0, j = 0; i < (int)v.size() && j < (int)u.size() && ok; ) {
            for ( ;i < (int)v.size() && v[i].first < u[j].first; ++i )
                ax *= (v[i].second+1);
            if ( i == (int)v.size() || v[i].first != u[j].first || v[i].second < u[j].second ) {
                ok = false, ax = 0;
                break ;
            }
            ax *= (v[i].second-u[j].second+1), ++i, ++j;
        }
        if ( j < (int)u.size() ) {
            puts("0");
            continue ;
        }
        for (;ok && i < (int)v.size(); ++i )
            ax *= (v[i].second+1);
        printf("%lld\n",ax);
    }
    return 0;
}

