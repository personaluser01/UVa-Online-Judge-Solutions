/*
 * 10855. Rotated Square
 * status: Accepted
 * TOPIC: rolling hash
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
#include <set>
#include <map>
#include <queue>
#define N (1 << SH)
#define SH (7)
#define BIT(k) (1ULL << (k))
#define MASK(k) (BIT(k)-1ULL)
#define enc(x,y) ((x)|((y)<<SH))
using namespace std;
typedef unsigned long long u64;
typedef long long i64;
#define MOD ((1LL << 31)-1ll)
#define FILL(x) (memset(x,0,sizeof x))

int m,n,h;
char g[N][N],p[N][N];
i64 M[] = {13,1499,2393,2251},iM[4],deg[4][N*N],ideg[4][N*N];

struct quad { i64 x[4]; };
bool operator < ( const quad &a, const quad &b ) {
    for ( int i = 0; i < 4; ++i )
        if ( a.x[i] != b.x[i] )
            return a.x[i] < b.x[i];
    return false;
}
bool operator == ( const quad &a, const quad &b ) {
    for ( int i = 0; i < 4; ++i )
        if ( a.x[i] != b.x[i] )
            return false;
    return true;
}

quad col[N][N],box[N][N];
map<quad,int> s;

void rotate() {
    char t[N][N];
    int i,j,k,ii,jj;
    for ( jj = m-1, i = 0; i < m; ++i, --jj )
        for ( ii = 0, j = 0; j < m; ++j, ++ii )
            t[ii][jj] = p[i][j];
    for ( i = 0; i < m; ++i )
        for ( j = 0; j < m; ++j )
            p[i][j] = t[i][j];
}

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
    if ( !y ) { *a = 1, *b = 0, *d = x; return; }
    ext_euclid(y,x%y,b,a,d);
    *b -= (x/y)*(*a);
}

i64 inv( i64 x, i64 M ) {
    i64 a,b,d;
    ext_euclid(x,M,&a,&b,&d);
    while ( a < 0 ) a += M;
    return a%M;
}

void norm( i64 &a ) {
    while ( a < MOD ) a+=MOD;
    a %= MOD;
}

int main() {
    int i,j,k,l,t;
    u64 u,v;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = 0; i < 4; ++i ) {
        iM[i] = inv(M[i],MOD);
        assert( ((iM[i]*M[i]) % MOD) == 1 );
        for ( ideg[i][0] = deg[i][0] = 1LL, j = 1; j < N*N; ++j ) {
            deg[i][j] = deg[i][j-1]*M[i], norm(deg[i][j]);
            ideg[i][j] = ideg[i][j-1]*iM[i], norm(ideg[i][j]);
        }
    }
    for (;2 == scanf("%d %d",&n,&m) && (m||n);) {
       for ( i = 0; i < n; scanf("%s",g[i++]) );
       for ( i = 0; i < m; scanf("%s",p[i++]) );
       for ( u = v = 0, i = 0; i < n; ++i )
           for ( j = 0; j < n; ++j )
               u |= (1ULL<<(g[i][j]-'A'));
       for ( i = 0; i < m; ++i )
           for ( j = 0; j < m; ++j )
               v |= (1ULL<<(p[i][j]-'A'));
       if ( v&(v^u) ) {
           puts("0 0 0 0");
           continue ;
       }

       for ( j = 0; j < n; ++j ) {
           for ( FILL(col[j][m-1].x), l = 0; l < 4; ++l )
               for ( k = 0; k < m; ++k )
                   col[j][m-1].x[l] += deg[l][k]*(g[k][j]-'A'), col[j][m-1].x[l] %= MOD;
           for ( i = m; i < n; ++i )
               for ( l = 0; l < 4; ++l ) {
                   col[j][i].x[l] = col[j][i-1].x[l];
                   col[j][i].x[l] -= (g[i-m][j]-'A'), col[j][i].x[l] *= iM[l], col[j][i].x[l] %= MOD;
                   col[j][i].x[l] += deg[l][m-1]*(g[i][j]-'A'), col[j][i].x[l] %= MOD;
                   norm(col[j][i].x[l]);
               }
       }

       for ( s.clear(), i = 0; i+m-1 < n; ++i ) {
           for ( FILL(box[i][0].x), j = 0; j < m; ++j )
               for ( l = 0; l < 4; ++l )
                   box[i][0].x[l] += col[j][i+m-1].x[l]*deg[l][m*j], box[i][0].x[l] %= MOD, norm(box[i][0].x[l]);
           for ( j = 1; j+m-1 < n; ++j )
               for ( l = 0; l < 4; ++l ) {
                   box[i][j].x[l] = box[i][j-1].x[l];
                   box[i][j].x[l] -= col[j-1][i+m-1].x[l], box[i][j].x[l] += MOD, box[i][j].x[l] %= MOD;
                   box[i][j].x[l] *= ideg[l][m], box[i][j].x[l] %= MOD;
                   box[i][j].x[l] += deg[l][m*(m-1)]*col[j+m-1][i+m-1].x[l], box[i][j].x[l] %= MOD;
                   norm(box[i][j].x[l]);
               }
           for ( j = 0; j+m-1 < n; ++j ) {
               // printf("HASH %lld %lld %lld %lld\n",box[i][j].x[0],box[i][j].x[1],box[i][j].x[2],box[i][j].x[3]);
               if ( s.find(box[i][j])==s.end() )
                   s[box[i][j]] = 1;
               else ++s[box[i][j]];
           }
       }

       for ( i = 0; i < 4; ++i, rotate() ) {
           quad e[N],hc;
           for ( j = 0; j < m; ++j )
               for ( FILL(e[j].x), l = 0; l < 4; ++l )
                   for ( k = 0; k < m; ++k )
                       e[j].x[l] += deg[l][k]*(p[k][j]-'A'), e[j].x[l] %= MOD, norm(e[j].x[l]);
           for ( FILL(hc.x), j = 0; j < m; ++j )
               for ( l = 0; l < 4; ++l )
                   hc.x[l] += deg[l][m*j]*e[j].x[l], hc.x[l] %= MOD, norm(hc.x[l]);
           // printf("[THIS] %lld %lld %lld %lld, res ",hc.x[0],hc.x[1],hc.x[2],hc.x[3]);
           if ( i ) putchar(' ');
           if ( s.find(hc) == s.end() )
               putchar('0');
           else
               printf("%d",s[hc]);
           /*
           puts("");
           for ( l = 0; l < m; ++l )
               puts(p[l]);
            */
       }
       putchar('\n');
    }
    return 0;
}

