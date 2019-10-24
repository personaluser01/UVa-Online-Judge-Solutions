#include <iostream>
#include <set>
#include <cassert>
#include <map>
#define L(u) ((u) & (~(u)+1ull))
using namespace std;
using state= uint64_t;
using u64= uint64_t;
using t_bounding_box= u64;
#define BIT(k)   (1ull<<(k))
#define TST(u,i) (((u)>>(i))&1ull)
#define MAXK     (6)
#define N 0x400
#define MASK(k) (BIT(k)-1ull)
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#define oo (0xffffffffffffffffull)

unordered_set<state> configurations[MAXK+1];
int dx[]= {0,1,0,-1}, dy[]= {1,0,-1,0}, id[MAXK+1][MAXK][MAXK];
unsigned char ix[MAXK+1][MAXK*MAXK+1], iy[MAXK+1][MAXK*MAXK+1]; //TODO fill with 0xff
unordered_map<u64,char> which;
unordered_map<state,t_bounding_box> mbb[MAXK+1];
const t_bounding_box empty_box= +oo;

unsigned char get_wall( int i, int j, int k ) {
    unsigned char wall= 0;
    if ( i == 0 )
        wall|= BIT(0);
    if ( j == 0 )
        wall|= BIT(1);
    if ( i == k-1 )
        wall|= BIT(2);
    if ( j == k-1 )
        wall|= BIT(3);
    return wall;
}

t_bounding_box encode_bounding_box( u64 lx, u64 ly, u64 ux, u64 uy ) {
    return lx | (ly << 10) | (ux << 20) | (uy << 30);
}

t_bounding_box update_bounding_box( t_bounding_box b, int i, int j ) {
    if ( b == +oo )
        return encode_bounding_box(i,j,i,j);
    int lx= (b&MASK(10)), ly= (b>>10)&MASK(10),
        ux= (b>>20)&MASK(10), uy= (b>>30);
    lx= min(i,lx), ly= min(j,ly);
    ux= max(i,ux), uy= max(j,uy);
    return encode_bounding_box(lx,ly,ux,uy);
}

void dfs( const int k, int len, unsigned char touched_walls, state u ) {
    if ( len == k ) {
        if ( 3 == (touched_walls&3) and not configurations[k].count(u) )
            configurations[k].insert(u);
        return ;
    }
    assert( len < k );
    for ( auto v= u; v; v&= ~L(v) )
    for ( int w= which[L(v)], i= ix[k][w], j= iy[k][w], l= 0; l < 4; ++l )
        if ( auto ni= i+dx[l]; 0 <= ni and ni < k )
            if ( auto nj= j+dy[l]; 0 <= nj and nj < k )
                if ( auto t= id[k][ni][nj]; not TST(u,t) )
                    dfs(k, len + 1,
                            touched_walls|get_wall(ni,nj,k),
                            u|BIT(t)
                       );
}

void precompute( int K ) {
    static bool seen[MAXK+1]= {false};
    assert( 1 <= K and K <= MAXK );
    if ( not seen[K] ) {
        int i,j,k;
        for ( k= 0, i= 0; i < K; ++i )
            for ( j= 0; j < K; id[K][i][j]= k, ix[K][k]= i, iy[K][k]= j, ++k, ++j ) ;
        assert( k == K*K );
        seen[K]= true;
        for ( i= 0; i < K; ++i )
            for ( j= 0; j < K; ++j )
                dfs(K,1,get_wall(i,j,K),BIT(id[K][i][j]));
    }
}

int m,n,K;
char g[N][N];
u64 z[N][N],mask,M;

bool visited[N][N];

void floodfill( int x, int y, t_bounding_box &bb ) {
    assert( not visited[x][y] );
    visited[x][y]= true, bb= update_bounding_box(bb,x,y);
    for ( int l= 0; l < 4; ++l )
        if ( auto nx= x+dx[l]; 0 <= nx and nx < m+2*K )
            if ( auto ny= y+dy[l]; 0 <= ny and ny < n+2*K )
                if ( g[nx][ny] == '#' and not visited[nx][ny] )
                    floodfill(nx,ny,bb);

}

bool intersection_exists( int ni, int nj, int i, int j, int a, int b, int c, int d ) {
    return not(i < a or c < ni or j < b or d < nj);
}

bool inside_wall( int i, int j, int K ) {
    int ni= i-K+1, nj= j-K+1;
    return not intersection_exists(ni,nj,i,j,K,K,m+K-1,n+K-1);
}


int main() {
    int i,j,k,l,ts,cs= 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif

    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    for ( i= 0; i < MAXK*MAXK+1; which[BIT(i)]= i, ++i ) ;
    for ( K= 1; K <= MAXK; ++K ) {
        precompute(K);
        //cout << "t(" << K << ") = " << configurations[K].size() << endl;
        cout << "configurations[" << K << "]= {";
        bool flag= true;
        for ( auto x: configurations[K] )
            if ( flag )  {
                cout << x;
                flag= false;
            }
            else cout << "," << x;
        cout << "};\n";
    }

    return 0;
}

