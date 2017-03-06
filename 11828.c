/*
 * 11828. Palindrome Again
 * status: Accepted
 * TOPIC: DP, Generating Functions (not needed), lazy DP, palindromes, prefix sums
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 0x400
#define K 0x400
#define MOD 1000000000LL
typedef long long i64;
typedef unsigned long long u64;
#define oo 0xffffffffffffffffull
#define DBG 0

u64 z[2][N/2][K],w,prefix[N/2][K];
char s[N];
int n,m;

u64 calc_z( const int t, int l, int k ) {
    if ( k < 0 ) return 0;
    if ( z[t][l][k] < +oo )
        return z[t][l][k];
    if ( k > 2*l )
        return z[t][l][k] = 0;
    assert( k <= 2*l );
    /* printf("%d %d %d\n",t,l,k);*/
    assert( l >= 1 );
    if ( t ) {
        if ( l == 1 ) {
            if ( k == 0 )
                return z[t][l][k] = 0;
            if ( k == 1 )
                return z[t][l][k] = 2;
            if ( k == 2 )
                return z[t][l][k] = 24;
            assert( 0 );
        }
        assert( l >= 2 );
        return z[t][l][k] = (24*calc_z(t,l-1,k-2)+2*calc_z(t,l-1,k-1))%MOD;
    }
    else {
        if ( l == 1 ) {
            if ( k == 0 )
                return z[t][l][k] = 1;
            if ( k == 1 )
                return z[t][l][k] = 0;
            if ( k == 2 )
                return z[t][l][k] = 25;
            assert( 0 );
        }
        assert( l >= 2 );
        return z[t][l][k] = (25*calc_z(t,l-1,k-2)+calc_z(t,l-1,k))%MOD;
    }
}

int main() {
    u64 ww,u;
    int i,j,k,l,t,par[2],cs = 0,ts,ch;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    memset(z,0xffull,sizeof z);
    for ( n = 1; n <= 500; ++n )
        for ( prefix[n][0] = 0, k = 1; k < K; ++k )
            prefix[n][k] = ((prefix[n][k-1]+calc_z(1,n,k))%MOD);
    for ( scanf("%d",&ts); ts-- && 3 == scanf("%d %d %s",&n,&m,s+1); ) {
        assert( strlen(s+1) == n );
        for ( i = 1; i <= n; ++i )
            if ( isupper(s[i]) )
                s[i] = tolower(s[i]);
        if ( m >= n ) m = n;
        assert( m <= n );
        for ( par[0]=par[1] = 0, i = 1, j = n; i < j; ++i, --j ) 
            if ( s[i] != s[j] ) ++par[1];
            else ++par[0];
        printf("Case %d: ",++cs), w = 0;
        if ( n == 1 ) {
            if ( m == 0 )
                puts("1");
            else puts("26");
            continue ;
        }
        if ( i == j ) {
            assert( (n&1) );
            assert( 2*par[0]+2*par[1]+1 == n );
            if ( par[0] && par[1] ) {
                for ( k = 0; k <= m; ++k )
                    w += (calc_z(0,par[0],k)*prefix[par[1]][m-k])%MOD, w %= MOD;
                for ( u = 0, k = 0; k <= m-1; ++k )
                    u += (calc_z(0,par[0],k)*prefix[par[1]][m-1-k])%MOD, u %= MOD;
                for ( k = 0; k < 25; ++k )
                    w += u, w %= MOD;
            }
            else if ( par[0] ) {
                for ( k = 0; k <= m; ++k )
                    w += (calc_z(0,par[0],k))%MOD, w %= MOD;
                for ( u = 0, k = 0; k <= m-1; ++k )
                    u += (calc_z(0,par[0],k))%MOD, u %= MOD;
                for ( k = 0; k < 25; ++k )
                    w += u, w %= MOD;
            }
            else if ( par[1] ) {
                for ( k = 0; k <= m; ++k )
                    w += calc_z(1,par[1],m-k)%MOD, w %= MOD;
                for ( u = 0, k = 0; k <= m-1; ++k )
                    u += calc_z(1,par[1],m-1-k), u %= MOD;
                for ( k = 0; k < 25; ++k )
                    w += u, w %= MOD;
            }
            else {
                assert( n == 1 );
                for ( ch = 'a'; ch <= 'z'; ++ch )
                    if ( ch != s[1] && 1 <= m )
                        ++w, w %= MOD;
            }
#if DBG
            for ( ww = 0, k = 0; k <= m; ++k ) 
                for ( i = 0; i <= k; ++i )
                    ww += calc_z(0,par[0],i)*calc_z(1,par[1],k-i), ww %= MOD;
            for ( k = 0; k <= m-1; ++k )
                for ( i = 0; i <= k; ++i )
                    ww += 25*calc_z(0,par[0],i)*calc_z(1,par[1],k-i), ww %= MOD;
#endif
        }
        else {
#if DBG
            for ( ww = 0, k = 0; k <= m; ++k ) 
                for ( i = 0; i <= k; ++i )
                    ww += calc_z(0,par[0],i)*calc_z(1,par[1],k-i), ww %= MOD;
#endif
            if ( par[0] && par[1] ) {
                for ( k = 0; k <= m; ++k )
                    w += (calc_z(0,par[0],k)*prefix[par[1]][m-k])%MOD, w %= MOD;
            }
            else if ( par[0] ) {
                for ( k = 0; k <= m; ++k )
                    w += (calc_z(0,par[0],k))%MOD, w %= MOD;
            }
            else if ( par[1] ) {
                for ( k = 0; k <= m; ++k )
                    w += calc_z(1,par[1],m-k)%MOD, w %= MOD;
            }
            else {
                assert( 0 );
            }
        }
#if DBG
        printf("%llu %llu\n",w,ww);
#else
        printf("%llu\n",w);
#endif
    }
    return 0;
}

