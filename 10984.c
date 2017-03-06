/*
 * 10984. Double NP-Hard
 * status: Accepted
 * TOPIC: bipartite matching, minimum vertex cover, maxmimum independent set, priority queue
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define N 0x400
enum { S, T };
enum { WHITE, BLACK };
#define oo (1 << 29)

int min( int x, int y ) { if ( x < y ) return x; return y; }
int max( int x, int y ) { if ( x < y ) return y; return x; }

int ts,cs,g[N][N],yes,bip,n,m,a[2],id[N],q[N],head,tail,cnt,indep,cover,used[2][N],aid[2][N],
    adj[2][N][N],deg[2][N],seen[N],mate[2][N],visited[N],indeed,c[2],ok,*qtr,out[N],e[2][N],*ptr[2],
    heap[2*N],pos[N],Cnt,d[N],mvc[N],*pmvc;
char color[N],covered[N];

void push( int x ) {
    int i,j;
    if ( pos[x] < 0 )
        pos[heap[Cnt] = x]=Cnt,++Cnt;
    for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] < d[heap[j]] || d[heap[i]]==d[heap[j]]&&heap[i]>heap[j]; bubble );
}

int pop() {
    int i,j,x = *heap;
    if ( (pos[x]=-1,--Cnt) )
        pos[heap[0]=heap[Cnt]]=0;
    for ( j = 0; (i=j,j<<=1,++j) < Cnt; bubble ) {
        if ( j < Cnt-1 && (d[heap[j]]<d[heap[j+1]]||d[heap[j]]==d[heap[j+1]]&&heap[j+1]<heap[j]) ) ++j;
        if ( d[heap[i]] > d[heap[j]] || d[heap[i]]==d[heap[j]]&&heap[i]<heap[j] ) break ;
    }
    return x;
}

void dfs( int x, int c ) {
    int y;
    assert( seen[x] != yes );
    for ( seen[x] = yes, color[x] = c, y = 0; y < n && bip; ++y )
        if ( g[x][y] == yes ) {
            if ( seen[y] == yes && color[y] == c ) {
                bip = 0;
                return ;
            }
            if ( seen[y] != yes )
                dfs(y,c^1);
        }
}

int alt_path( int x ) {
    int i,y;
    if ( visited[x] == indeed )
        return 0;
    for ( visited[x] = indeed, i = 0; i < deg[S][x]; ++i )
        if ( mate[T][y=adj[S][x][i]]==-1 || alt_path(mate[T][y]) ) {
            mate[T][mate[S][x] = y] = x;
            return 1;
        }
    return 0;
}

void floodfill( int t, int x ) {
    int i;
    if ( used[t][x]==indeed ) return ;
    for ( used[t][x]=indeed, ++c[t], *ptr[t]++ = x, i = 0; i < deg[t][x]; floodfill(t^1,adj[t][x][i++]) );
}

int cmp( const void *a, const void *b ) {
    int *x = (int *)a,
        *y = (int *)b;
    if ( *x < *y ) return -1;
    if ( *x == *y )  return 0;
    return 1;
}

int is_less( int *a, int *b, int n ) {
    int i;
    for ( i = 0; i < n; ++i )
        if ( a[i] != b[i] ) 
            return a[i] < b[i];
    return 0;
}

int maxmatch() {
    int i,j,k,t,x,y,flag,low,high;

    for ( ok = 1, cnt = 0, head = tail = 0, x = 0; x < a[S]; ++x )
        q[tail]=x,++cnt,tail=((tail+1)&(N-1));
    do {
        for ( flag = 0, ++indeed, k = cnt; k--; ) {
            x = q[head], --cnt, head = ((head+1)&(N-1));
            if ( alt_path(x) )
                flag = 1;
            else q[tail] = x, tail=((tail+1)&(N-1)), ++cnt;
        }
    }while(flag);

    if ( (a[S]-cnt) != (n>>1) )
        return 0;

    /*
    for ( Cnt = 0, x = 0; x < n; ++x ) {
        d[x] = deg[color[x]][id[x]], pos[x] = -1, covered[x] = 0;
        if ( mate[color[x]][id[x]] >= 0 ) push(x);
    }
    for ( ++indeed, pmvc = mvc; Cnt; ) {
        x = pop();
        if ( pmvc-mvc < a[S]-cnt )
            covered[*pmvc++ = x] = 1;
        for ( visited[x]=indeed, i = 0; i < deg[color[x]][id[x]]; ++i ) {
            j = adj[color[x]][id[x]][i], --d[y = aid[color[x]^1][j]];
            if ( mate[color[x]^1][j] != -1 && visited[x] != indeed )
                push(y);
        }
    }
    assert( pmvc-mvc == a[S]-cnt );
    */
    for ( pmvc = mvc, i = 0; i < n; ++i )
        if ( color[0] == color[i] )
            *pmvc++ = i;
    return 1;
}

int main() {
    int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m) && printf("Case #%d: ",++cs) && ++yes;) {
        for ( k = 0; k < m && 2 == scanf("%d %d",&i,&j); ++k )
            --i, --j, g[i][j] = g[j][i] = yes;
        memset(color,WHITE,sizeof color);
        for ( bip = ((n&1)^1), i = 0; i < n && bip; ++i )
            if ( seen[i] != yes )
                dfs(i,WHITE);
        if ( !bip ) {
            puts("Impossible");
            continue ;
        }
        for ( a[S] = a[T] = 0, i = 0; i < n; ++i )
            deg[color[i]][id[i]=a[color[i]]++] = 0, aid[color[i]][a[color[i]]-1] = i;
        for ( i = 0; i < n; ++i )
            for ( j = 0; j < n; ++j )
                if ( g[i][j] == yes ) {
                    assert( color[i] != color[j] );
                    adj[color[i]][id[i]][deg[color[i]][id[i]]++] = id[j];
                }
        for ( k = S; k <= T; ++k )
            for ( i = 0; i < a[k]; mate[k][i++] = -1 );
        if ( !maxmatch() )
            puts("Impossible");
        else {
            printf("%ld\n",pmvc-mvc);
            for ( i = 0; i < pmvc-mvc; ++i )
                if ( i ) printf(" %d",mvc[i]+1);
                else printf("%d",mvc[i]+1);
            putchar('\n');
        }
    }
    return 0;
}

