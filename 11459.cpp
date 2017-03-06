/*
 * 11459. Snakes and Ladders
 * status: Accepted
 * TOPIC: simulation, easy
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
#define N (1 << 21)

int m,n,rolls,pos[N],x[0x80],y[0x80],
    Goto[16][16];

int main() {
    int i,j,k,l,t,ts,np;
    bool gameover;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = 0; i < 100; ++i )
        x[i] = i/10, y[i] = i%10;
    for ( scanf("%d",&ts); ts--; ) {
        scanf("%d %d %d",&n,&m,&rolls);
        for ( i = 0; i < 10; ++i )
            for ( j = 0; j < 10; ++j )
                Goto[i][j] = i*10+j;
        for ( k = 0; k < m; ++k ) 
            scanf("%d %d",&l,&t), --l, --t, Goto[l/10][l%10] = t;
        for ( i = 0; i < n; ++i ) pos[i] = 0;
        for ( gameover = false, i = 0; rolls-- && 1==scanf("%d",&k); ++i, i %= n ) {
            if ( gameover ) continue ;
            np = min(pos[i]+k,99);
            pos[i] = Goto[x[np]][y[np]];
            if ( pos[i] == 99 ) 
                gameover = true;
        }
        for ( i = 0; i < n; ++i )
            printf("Position of player %d is %d.\n",i+1,pos[i]+1);
    }
    return 0;
}

