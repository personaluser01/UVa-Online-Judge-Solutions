/*
 * 1062. Containers
 * status: Accepted
 * TOPIC: Dilworth's theorem, partial orders
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define NX(x) (((x)+1)&((N)-1))
enum{S=0,T=1};

int n,mate[2][N+N],seen[2][N+N],yes[2],q[N+N],head,tail,cnt,adj[2][N+N][N+N],deg[2][N+N];
char s[N];

int alt_path( int x ) {
    int i,y;
    if ( seen[S][x] == yes[S] ) return 0;
    for ( seen[S][x] = yes[S], i = 0; i < deg[S][x]; ++i ) 
        if (mate[T][y=adj[S][x][i]]==-1||alt_path(mate[T][y])) {
            mate[T][mate[S][x] = y] = x;
            return 1;
        }
    return 0;
}

void bpm() {
    int i,j,k,x,y,flag;

    for ( i = S; i <= T; ++i )
        for ( x = 0; x < n; ++x ) {
            assert( i*n+x < N+N );
            mate[i][i*n+x] = -1;
        }
    for ( head=tail=cnt=0, x=0; x<n; (q[tail]=x++),(tail=NX(tail)),++cnt );
    do {
        for ( flag = 0, k = cnt; k--; ) {
            (x=q[head]),(head=NX(head)),--cnt;
            if ( ++yes[S] && alt_path(x) ) flag = 1;
            else (q[tail]=x),(tail=NX(tail)),++cnt;
        }
    }while(flag);
    /*
    for ( i = 0; i < n; ++i )
        printf("%d mate[%d] = %d %d\n",deg[S][i], i,mate[S][i],mate[T][i+n]);
        */
}

void traverse( int x ) {
    int y;
    if ( seen[S][x] == yes[S] ) return ;
    seen[S][x] = yes[S];
    if ( (y=mate[S][x]) == -1 ) return ;
    assert( y >= n );
    traverse(y-n);
}

int main() {
    int i,j,k,cs = 0,t;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( ;1 == scanf("%s",s) && strcmp(s,"end"); ) {
        n = strlen(s);
        for ( t = S; t <= T; ++t )
            for ( i = 0; i < n; deg[t][t*n+i] = 0, ++i );
        for ( i = 0; i < n; ++i ) 
            for ( j = i+1; j < n; ++j ) 
                if ( s[i] >= s[j] ) 
                    adj[S][i][deg[S][i]++]=(j+n),adj[T][j+n][deg[T][j+n]++]=i;
        for ( bpm(), k = 0, ++yes[S], i = 0; i < n; ++i )
            if ( seen[S][i] != yes[S] )
                traverse(i), ++k;
        printf("Case %d: %d\n",++cs,k);
    }
    return 0;
}

