/*
 * TOPIC: bitmasks, DP, bounding box, state normalization, brute force
 * status:
 */
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

/*
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
*/

t_bounding_box encode_bounding_box( u64 lx, u64 ly, u64 ux, u64 uy ) {
    return lx | (ly << 10) | (ux << 20) | (uy << 30);
}

t_bounding_box update_bounding_box( t_bounding_box b, int i, int j ) {
    if ( b == +oo )
        return encode_bounding_box(i,j,i,j);
    int lx= (b&MASK(10)), ly= (b>>10)&MASK(10),
        ux= (b>>20)&MASK(10), uy= (u>>30);
    lx= min(i,lx), ly= min(j,ly);
    ux= max(i,ux), uy= max(j,uy);
    return encode_bounding_box(lx,ly,ux,uy);
}

/*
void dfs( const int k, int len, unsigned char touched_walls, state u, t_bounding_box bb ) {
    if ( len == k ) {
        if ( 3 == (touched_walls&3) and not configurations[k].count(u) )
            configurations[k].insert(u), mbb[u]= bb;
        return ;
    }
    assert( len < k );
    for ( auto v= u; v; v&= ~L(v) )
    for ( int w= which[L(v)], i= ix[k][w], j= iy[k][w], l= 0; l < 4; ++l )
        if ( auto ni= i+dx[l]; i <= ni and ni < k )
            if ( auto nj= j+dy[l]; 0 <= nj and nj < k )
                if ( auto t= id[k][ni][nj]; not TST(u,t) )
                    dfs(k, len + 1,
                            touched_walls|get_wall(ni,nj,k),
                            u|BIT(t),
                            update_bounding_box(bb,ni,nj)
                       );
}
 */


void precompute( int K ) {
    static bool seen[MAXK+1]= {false};
    assert( 1 <= K and K <= MAXK );
    if ( not seen[K] ) {
        int i,j,k;
        for ( k= 0, i= 0; i < K; ++i )
            for ( j= 0; j < K; id[K][i][j]= k, ix[K][k]= i, iy[K][k]= j, ++k, ++j ) ;
        assert( k == K*K );
        seen[K]= true;
        /*
        for ( i= 0; i < K; ++i )
            for ( j= 0; j < K; ++j )
                dfs(K,1,get_wall(i,j,K),BIT(id[K][i][j]));*/
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
    configurations[1]= {1};
    configurations[2]= {3,5};
    configurations[3]= {7,11,19,25,26,73};
    configurations[4]= {15,23,39,51,54,71,99,113,114,116,275,305,306,547,561,562,785,802,4369};
    configurations[5]= {31,47,79,103,110,143,167,199,227,230,236,271,391,451,481,482,484,488,1063,1123,1126,
                        1249,1250,1252,2119,2147,2150,2243,2273,2274,2276,3107,3139,3142,3169,3170,3266,3268,
                        4231,4291,4321,4322,4324,6211,6241,6242,7201,7234,7300,33827,33889,33890,35873,35906,
                        67651,67681,67682,68641,68674,99361,100418,1082401};
    configurations[6]= {63,95,159,207,222,287,335,399,455,462,476,543,591,655,718,783,839,903,963,
                        966,972,984,1055,1551,1799,1923,1985,1986,1988,1992,2000,4175,4295,4302,4423,
                        4547,4550,4556,5057,5058,5060,5064,8335,8391,8398,8583,8643,8646,8652,9091,9153,
                        9154,9156,9160,12359,12423,12430,12483,12486,12675,12678,12684,12737,12738,12740,
                        13186,13188,13192,16655,16711,16775,16835,16838,16844,17159,17283,17345,17346,17348,
                        17352,20929,20930,20932,24711,24771,24774,24839,24963,25025,25026,25028,28739,28803,
                        28806,28865,28866,28934,28940,29058,29060,29444,29448,33295,33543,33667,33729,33730,
                        33732,33736,49415,49539,49601,49602,49604,57475,57537,57538,61505,61570,61700,61960,
                        266311,266435,266438,266689,266690,266692,274499,274563,274566,274625,274626,274818,
                        274820,290881,290946,291076,532615,532675,532678,532867,532929,532930,532932,536643,
                        536707,536710,536769,536770,536962,536964,548995,549057,549058,553025,553090,553220,
                        790595,790721,790722,794755,794758,794817,794818,795010,795012,798785,798850,811138,
                        811268,1065223,1065347,1065409,1065410,1065412,1073283,1073345,1073346,1077313,
                        1077378,1077508,1581187,1581249,1581250,1585217,1585282,1839169,1843330,1851652,
                        17043523,17043649,17043650,17051713,17051778,17567809,17571970,34087043,34087105,
                        34087106,34091073,34091138,34345025,34349186,50597953,50864258,1090785345};
    for ( i= 0; i < MAXK*MAXK+1; which[BIT(i)]= i, ++i ) ;
    /**
     * precomputing the bounding boxes for each configuration
     */
    for ( k= 1; k <= MAXK; ++k ) {
        for ( auto u: configurations[k] ) {
            t_bounding_box bb= empty_box;
            for ( auto v= u; v; v&= ~L(v) ) {
                auto t= which[L(v)];
                bb= update_bounding_box(bb,ix[k][t],iy[k][t]);
            }
            mbb[k][u]= bb;
        }
    }
    /*
    for ( K= 1; K <= MAXK; ++K ) {
        precompute(K);
        cout << "configurations[" << K << "]= {";
        bool flag= true;
        for ( auto x: configurations[K] )
            if ( flag )  {
                cout << x;
                flag= false;
            }
            else cout << "," << x;
        cout << "}\n";
    }
    */

    for ( cin>>ts; ts--; ) {
        cin>>m>>n>>K;
        precompute(K);
        for ( i= 0; i < m+2*K; ++i )
            for ( j= 0; j < n+2*K; g[i][j++]= '#' ) ;
        for ( i= K; i < m+K; ++i )
            for ( j= K; j < n+K; ++j )
                g[i][j]= '.';
        for ( cin>>l; l--; (cin>>i>>j), g[(--i)+K][(--j)+K]= '#' ) ;
        memset(visited,0,sizeof visited);
        for ( i= 0; i < m+2*K; ++i )
            for ( j= 0; j < n+2*K; ++j )
                if ( not visited[i][j] and g[i][j] == '#' ) {
                    t_bounding_box bb= empty_box;
                    floodfill(i, j, bb);
                }
        for ( mask= M= MASK(K*K), i= 0; i < K; ++i )
            mask&= ~BIT(id[K][i][0]);
        for ( i= 0; i < m+2*K; ++i ) {
            //for ( j= 0; j < K; z[i][j++]= M ) ;
            for ( j = 0; j < n + 2 * K; ++j) {
                if ( inside_wall(i,j,K) ) {
                    z[i][j]= M;
                    continue ;
                }
                z[i][j]= (z[i-1][j]>>K)|((z[i][j-1]&mask)>>1);
                if (g[i][j] == '#')
                    z[i][j]|= BIT(id[K][K-1][K-1]);
            }
        }
        int ans= 0;
        for ( const auto x: configurations[K] )
            for ( i= K; i < m+2*K; ++i )
                for ( j= K; j < n+2*K; ++j )
                    if ( 0 == (x & z[i][j]) )
                        ++ans;
        cout << "Case " << ++cs << ": " << ans << endl;
    }
    return 0;
}

