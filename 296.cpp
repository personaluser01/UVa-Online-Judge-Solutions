/*
 * 296. Safebreaker
 * status: Accepted
 * TOPIC: simulation, medium
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

struct Guess {
    int x,y;
    string c;
};

bool consitent( Guess *g, int n, string code ) {
        int i,j,k,u,v,x = 0,y = 0,
            cnt[10] = {0},
            a[10] = {0},
            b[10] = {0};
        for ( j = 0; j < 10; ++j )
            cnt[j] = 0;
        for ( j = 0; j < 4; ++j )
            ++cnt[code[j]-'0'];
        for ( i = 0; i < n; ++i ) {
            x = 0; y = 0; u = 0;
            for ( j = 0; j < 10; ++j ) 
                { a[j] = 0; b[j] = 0; }
            for ( j = 0; j < 4; ++j ) {
                if ( code[j] == g[i].c[j] ) {
                    ++x;
                    ++a[g[i].c[j]-'0'];
                    u |= (1 << j);
                }
                else ++b[g[i].c[j]-'0'];
            }
            if ( x != g[i].x )
                return false;
            for ( j = 0; j < 10; ++j )
                y += min(cnt[j]-a[j],b[j]);
            if ( y != g[i].y )
                return false;
        }
        return true;
}

string code[10000];

int main() {
    int i,j,n,k,ts;
    Guess g[0x400];
    char tmp[0x400];
    bool multiple;
    string soln;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = 0; i <= 9999; ++i ) {
        for ( code[i] = "", k = i, j = 0; j < 4; ++j ) {
            tmp[3-j] = (k%10)+'0', k /= 10;
        }
        code[i] = string(tmp);
    }
    for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
        for ( i = 0; i < n; ++i ) {
            scanf("%s %d/%d",tmp,&g[i].x,&g[i].y);
            g[i].c = string(tmp);
        }
        for ( multiple = false, soln = string(""), i = 0; i <= 9999 && !multiple; ++i ) {
            if ( !consitent(g,n,code[i]) )
                continue ;
            if ( soln.size() == 0 )
                soln = string(code[i]);
            else multiple = true;
        }
        if ( multiple )
            puts("indeterminate");
        else if ( soln.size() )
            puts(soln.c_str());
        else puts("impossible");
    }
    return 0;
}

