/**
 * 11270. Tiling Dominoes
 * TOPIC: combinatorics, bitmasks, DP, precalc
 * status:
 */
#include <bits/stdc++.h>
using namespace std;
#define N 101
#define BIT(k) (1ull<<(k))
#define MASK(k) (BIT(k)-1ull)
using u64= uint64_t;
#define oo (numeric_limits<u64>::max())

u64 z[N][1<<11];

u64 calc( int m, int n ) {
    assert( m <= n );
    if ( (m*n)&1 ) return 0ull;
    unsigned int u,v,w,q,base;
    int i,j,k;
    memset(z,0,sizeof z);
    z[0][MASK(m)]= 1;
    for ( j= 1; j <= n; ++j ) {
        for ( z[j][0]= z[j-1][MASK(m)], u= 1; u < BIT(m); ++u ) {
            for ( z[j][u]= 0, v= u; ; v= (v-1)&u ) {
                for ( q= u, w= MASK(m), i= 0; i < m; ++i )
                    if ( v & BIT(i) ) {
                        w^= BIT(i), q^= BIT(i);
                    }
                for ( i= 0; i < m; ) {
                    if ( not(q&BIT(i)) ) { ++i; continue; }
                    if ( i+1 == m or not(q&BIT(i+1)) ) goto nx;
                    i+= 2;
                }
                assert( z[j][u] < +oo-z[j-1][w] );
                z[j][u]+= z[j-1][w];
                nx:
                if ( not v ) break ;
            }
        }
    }
    return z[n][MASK(m)];
}

u64 s[N][N];

int main() {
    int i,j,k;
    int m,n;
#ifndef ONLINE_JUDGE
    freopen("11270.in","r",stdin);
#endif
    s[1][2]= 1llu;
    s[1][4]= 1llu;
    s[1][6]= 1llu;
    s[1][8]= 1llu;
    s[1][10]= 1llu;
    s[1][12]= 1llu;
    s[1][14]= 1llu;
    s[1][16]= 1llu;
    s[1][18]= 1llu;
    s[1][20]= 1llu;
    s[1][22]= 1llu;
    s[1][24]= 1llu;
    s[1][26]= 1llu;
    s[1][28]= 1llu;
    s[1][30]= 1llu;
    s[1][32]= 1llu;
    s[1][34]= 1llu;
    s[1][36]= 1llu;
    s[1][38]= 1llu;
    s[1][40]= 1llu;
    s[1][42]= 1llu;
    s[1][44]= 1llu;
    s[1][46]= 1llu;
    s[1][48]= 1llu;
    s[1][50]= 1llu;
    s[1][52]= 1llu;
    s[1][54]= 1llu;
    s[1][56]= 1llu;
    s[1][58]= 1llu;
    s[1][60]= 1llu;
    s[1][62]= 1llu;
    s[1][64]= 1llu;
    s[1][66]= 1llu;
    s[1][68]= 1llu;
    s[1][70]= 1llu;
    s[1][72]= 1llu;
    s[1][74]= 1llu;
    s[1][76]= 1llu;
    s[1][78]= 1llu;
    s[1][80]= 1llu;
    s[1][82]= 1llu;
    s[1][84]= 1llu;
    s[1][86]= 1llu;
    s[1][88]= 1llu;
    s[1][90]= 1llu;
    s[1][92]= 1llu;
    s[1][94]= 1llu;
    s[1][96]= 1llu;
    s[1][98]= 1llu;
    s[1][100]= 1llu;
    s[2][2]= 2llu;
    s[2][3]= 3llu;
    s[2][4]= 5llu;
    s[2][5]= 8llu;
    s[2][6]= 13llu;
    s[2][7]= 21llu;
    s[2][8]= 34llu;
    s[2][9]= 55llu;
    s[2][10]= 89llu;
    s[2][11]= 144llu;
    s[2][12]= 233llu;
    s[2][13]= 377llu;
    s[2][14]= 610llu;
    s[2][15]= 987llu;
    s[2][16]= 1597llu;
    s[2][17]= 2584llu;
    s[2][18]= 4181llu;
    s[2][19]= 6765llu;
    s[2][20]= 10946llu;
    s[2][21]= 17711llu;
    s[2][22]= 28657llu;
    s[2][23]= 46368llu;
    s[2][24]= 75025llu;
    s[2][25]= 121393llu;
    s[2][26]= 196418llu;
    s[2][27]= 317811llu;
    s[2][28]= 514229llu;
    s[2][29]= 832040llu;
    s[2][30]= 1346269llu;
    s[2][31]= 2178309llu;
    s[2][32]= 3524578llu;
    s[2][33]= 5702887llu;
    s[2][34]= 9227465llu;
    s[2][35]= 14930352llu;
    s[2][36]= 24157817llu;
    s[2][37]= 39088169llu;
    s[2][38]= 63245986llu;
    s[2][39]= 102334155llu;
    s[2][40]= 165580141llu;
    s[2][41]= 267914296llu;
    s[2][42]= 433494437llu;
    s[2][43]= 701408733llu;
    s[2][44]= 1134903170llu;
    s[2][45]= 1836311903llu;
    s[2][46]= 2971215073llu;
    s[2][47]= 4807526976llu;
    s[2][48]= 7778742049llu;
    s[2][49]= 12586269025llu;
    s[2][50]= 20365011074llu;
    s[3][4]= 11llu;
    s[3][6]= 41llu;
    s[3][8]= 153llu;
    s[3][10]= 571llu;
    s[3][12]= 2131llu;
    s[3][14]= 7953llu;
    s[3][16]= 29681llu;
    s[3][18]= 110771llu;
    s[3][20]= 413403llu;
    s[3][22]= 1542841llu;
    s[3][24]= 5757961llu;
    s[3][26]= 21489003llu;
    s[3][28]= 80198051llu;
    s[3][30]= 299303201llu;
    s[3][32]= 1117014753llu;
    s[4][4]= 36llu;
    s[4][5]= 95llu;
    s[4][6]= 281llu;
    s[4][7]= 781llu;
    s[4][8]= 2245llu;
    s[4][9]= 6336llu;
    s[4][10]= 18061llu;
    s[4][11]= 51205llu;
    s[4][12]= 145601llu;
    s[4][13]= 413351llu;
    s[4][14]= 1174500llu;
    s[4][15]= 3335651llu;
    s[4][16]= 9475901llu;
    s[4][17]= 26915305llu;
    s[4][18]= 76455961llu;
    s[4][19]= 217172736llu;
    s[4][20]= 616891945llu;
    s[4][21]= 1752296281llu;
    s[4][22]= 4977472781llu;
    s[4][23]= 14138673395llu;
    s[4][24]= 40161441636llu;
    s[4][25]= 114079985111llu;
    s[5][6]= 1183llu;
    s[5][8]= 14824llu;
    s[5][10]= 185921llu;
    s[5][12]= 2332097llu;
    s[5][14]= 29253160llu;
    s[5][16]= 366944287llu;
    s[5][18]= 4602858719llu;
    s[5][20]= 57737128904llu;
    s[6][6]= 6728llu;
    s[6][7]= 31529llu;
    s[6][8]= 167089llu;
    s[6][9]= 817991llu;
    s[6][10]= 4213133llu;
    s[6][11]= 21001799llu;
    s[6][12]= 106912793llu;
    s[6][13]= 536948224llu;
    s[6][14]= 2720246633llu;
    s[6][15]= 13704300553llu;
    s[6][16]= 69289288909llu;
    s[7][8]= 1292697llu;
    s[7][10]= 53175517llu;
    s[7][12]= 2188978117llu;
    s[7][14]= 90124167441llu;
    s[8][8]= 12988816llu;
    s[8][9]= 108435745llu;
    s[8][10]= 1031151241llu;
    s[8][11]= 8940739824llu;
    s[8][12]= 82741005829llu;
    s[9][10]= 14479521761llu;
    s[10][10]= 258584046368llu;
    /*
    for ( k= 0, m= 1; m < N; ++m )
        for ( n= m; m*n < N; ++n, ++k ) {
            if ( (m*n) & 1 ) continue ;
            cout << "s[" << m << "][" << n << "]= " << calc(m,n) << "llu;\n";
        }
        */

    while ( cin >> m >> n ) {
        if ( m > n ) swap(m,n);
        if ( m == 0 ) {
            cout << 0 << endl;
            continue ;
        }
        cout << s[m][n] << endl;
    }
    return 0;
}
