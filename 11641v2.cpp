/*
 * TOPIC: bitmasks, DP, bounding box, state normalization, brute force, polymino, very neat
 * status: Accepted
 */
#include <iostream>
#include <set>
#include <cassert>
#include <map>
using namespace std;
using state= uint64_t;
using u64= uint64_t;
using t_bounding_box= u64;
using i64= int64_t;
#define BIT(k)   (1ull<<(k))
#define L(u) ((u) & (~(u)+1ull))
#define TST(u,i) (((u)>>(i))&1ull)
#define MAXK     (6)
#define N (0x450)
#define MASK(k) (BIT(k)-1ull)
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#define oo (0xffffffffffffffffull)
#include <vector>
#define numrows (m+2*K)
#define numcols (n+2*K)
#define SH 11

/**
 * global constants
 */
const t_bounding_box empty_box= +oo;
unordered_set<state> configurations[MAXK+1];
unordered_map<u64,char> which;
unordered_map<state,t_bounding_box> mbb[MAXK+1];
int dx[]= {0,1,0,-1},
    dy[]= {1,0,-1,0},
    id[MAXK+1][MAXK][MAXK];
char ix[MAXK+1][MAXK*MAXK+1],
     iy[MAXK+1][MAXK*MAXK+1];

/**
 * case-dependent global variables
 */
int m,n,K;
char g[N][N];

namespace bb_manager {
#define unpack_values(b) int lx= (b&MASK(SH)), ly= ((b>>SH)&MASK(SH)), ux= ((b>>(2*SH))&MASK(SH)), uy= (b>>(3*SH))
    t_bounding_box encode_bounding_box(u64 lx, u64 ly, u64 ux, u64 uy) { return lx|(ly<<SH)|(ux<<(2*SH))|(uy<<(3*SH)); }
    t_bounding_box update_bounding_box(t_bounding_box b, int i, int j) {
        if (b == +oo)
            return encode_bounding_box(i, j, i, j);
        unpack_values(b);
        lx = min(i, lx), ly = min(j, ly);
        ux = max(i, ux), uy = max(j, uy);
        return encode_bounding_box(lx, ly, ux, uy);
    }
    i64 get_width( t_bounding_box b ) {
        unpack_values(b);
        return ux-lx+1;
    }
    i64 get_height( t_bounding_box b ) {
        unpack_values(b);
        return uy-ly+1;
    }
    t_bounding_box inflate( t_bounding_box b, int shift ) {
        assert( b < +oo );
        unpack_values(b);
        lx= max(K,lx-shift+1), ly= max(K,ly-shift+1);
        ux= min(m+K-1,ux+shift-1), uy= min(n+K-1,uy+shift-1);
        return encode_bounding_box(lx,ly,ux,uy);
    }
    i64 pack( t_bounding_box b, int m, int n ) {
        return max((i64)0,(m-get_width(b)+1))*max((i64)0,(n-get_height(b)+1));
    }
};

namespace helpers {
    bool visited[N][N];
    void init_dfs() {
        for ( int i= 0; i < numrows; ++i )
            for ( int j= 0; j < numcols; ++j )
                visited[i][j]= false ;
    }
    void precompute( int K ) {
        assert(1 <= K and K <= MAXK);
        int i, j, k;
        for (k = 0, i = 0; i < K; ++i)
            for (j = 0; j < K; id[K][i][j] = k, ix[K][k] = i, iy[K][k] = j, ++k, ++j);
        assert(k == K * K);
    }
    void floodfill(int x, int y, t_bounding_box &bb) {
        if ( visited[x][y] ) return ;
        visited[x][y] = true, bb = bb_manager::update_bounding_box(bb, x, y);
        for (int l = 0; l < 4; ++l)
            if (auto nx = x + dx[l]; K <= nx and nx < m+K )
                if (auto ny = y + dy[l]; K <= ny and ny < n+K )
                    if (g[nx][ny] == '#' and not visited[nx][ny])
                        floodfill(nx, ny, bb);

    }
    void display( state u, int K ) {
        for ( int k= 0, i= 0; i < K; ++i, putchar('\n') )
            for ( int j= 0; j < K; ++j, ++k )
                if ( TST(u,k) )
                    putchar('#');
                else putchar(' ');
    }
};

namespace grid_manager {
    bool intersection_exists(int ni, int nj, int i, int j, int a, int b, int c, int d) {
        return not(i < a or c < ni or j < b or d < nj);
    }
    bool inside_wall(int i, int j) {
        return not intersection_exists(i,j,i,j,K,K,m+K-1,n+K-1);
    }

    bool block_inside_wall(int i, int j) {
        int pi= i-K+1, pj= j-K+1;
        return not intersection_exists(pi,pj,i,j,K,K,m+K-1,n+K-1);
    }
};

namespace engine {

    bool seen[N][N];
    u64 z[N][N],mask,M;

    void init_engine() { memset(seen,0,sizeof seen); }

    void dp() {
        int i,j;
        for (mask = M = MASK(K * K), i = 0; i < K; ++i)
            mask &= ~BIT(id[K][i][0]);
        for (i = 0; i < numrows; ++i) {
            //for ( j= 0; j < K; z[i][j++]= M ) ;
            for (j = 0; j < numcols; ++j) {
                if ( grid_manager::block_inside_wall(i,j) ) {
                    z[i][j] = M;
                    continue;
                }
                z[i][j] = (z[i - 1][j] >> K) | ((z[i][j - 1] & mask) >> 1);
                if (g[i][j] == '#')
                    z[i][j] |= BIT(id[K][K - 1][K - 1]);
            }
        }
    }

    i64 number_of_intersections( t_bounding_box container, state pattern ) {
        i64 res= 0;
        unpack_values(container);
        int w= bb_manager::get_width(mbb[K][pattern]),
            h= bb_manager::get_height(mbb[K][pattern]);
        //cout << "Counting intersections for: " << endl;
        //helpers::display(pattern,K);
        //cout << "Bounding box: [" << lx << ", " << ux << "]x[" << ly << ", " << uy << "]\n";
        for ( int x= lx; x <= ux; ++x )
            for ( int y= ly; y <= uy; ++y ) {
                if ( not(K <= x and x+w-1 < m+K and K <= y and y+h-1 < n+K) )
                    continue ;
                if ( seen[x][y] ) continue ;
                seen[x][y]= true ;
                int nx= x+K-1, ny= y+K-1;
                assert( nx < numrows and ny < numcols );
                if ( (z[nx][ny] & pattern) ) {
                    //cout << "intersection with block anchored at " << nx << "," << ny << "when trying to place " << x << "," << y << endl;
                    ++res;
                }
            }
        return res;
    }
};


int main() {
    int i,j,k,l,ts,cs= 0;
    i64 ans;

#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif

    //cin.tie(nullptr), ios_base::sync_with_stdio(false);

    for ( i= 0; i < MAXK*MAXK+1; which[BIT(i)]= i, ++i ) ;

    configurations[1]= {1};
    configurations[2]= {5,3};
    configurations[3]= {73,26,19,25,11,7};
    configurations[4]= {116,306,71,275,547,785,54,15,23,51,561,802,99,305,39,113,4369,114,562};
    configurations[5]= {1252,3268,7300,236,33890,35906,68674,7234,6242,484,3170,482,2274,1126,230,1082401,391,271,6211,199,1250,2119,47,488,2147,3107,4291,33827,1063,103,4321,2150,1123,4231,110,31,2243,7201,4322,451,229,3266,67651,2276,143,1249,100418,167,3169,33889,3142,2273,4324,67682,3139,99361,79,6241,67681,481,35873,227,68641};
    configurations[6]= {2000,5064,13192,9160,29448,532932,12740,49604,20932,29060,33732,5060,9156,4556,16844,17043650,790722,17051778,17571970,1851652,50864258,1843330,1077508,790721,33543,25026,536769,1581187,1073283,1992,274625,17567809,266689,4549,207,20929,25028,1065347,12737,548995,33667,532867,16837,9091,266438,17283,17348,28806,1799,1585217,16655,984,8398,5058,287,4295,24839,1923,16775,274499,1585282,49415,8652,12359,335,811268,783,794755,28865,8645,549057,266692,29444,462,12486,266311,34091138,532678,8643,50597953,17352,274820,839,549058,17043523,291076,274563,28739,907,476,536643,972,12430,591,795010,553220,1551,536707,9154,455,5057,28996,12483,17159,24963,4423,266435,4175,29058,1988,1065223,8391,4550,49601,399,794818,16835,9153,970,1065412,532615,34087043,794758,4547,24771,222,33736,20930,12684,532675,57475,16711,17051713,790595,24711,795012,61700,33729,655,34087106,17043649,12423,965,25025,8646,28866,532929,536770,290946,8583,28803,17345,1985,28940,969,290881,1065409,34349186,461,1090785345,4302,8335,57537,49539,1073345,13188,1581249,903,34087105,95,798785,553025,794817,61505,1077313,33730,28993,798850,1839169,34345025,543,12675,536710,1055,718,12678,553090,966,16838,24774,57538,274566,61960,963,28934,33295,12738,532930,13186,536962,274818,536964,266690,159,17346,1986,63,49602,34091073,1065410,274626,1073346,1581250,811138,61570,1077378};

    /*
    for ( k= 1; k <= MAXK; ++k )
        cout << "g(" << k << ") = " << configurations[k].size() << endl;*/
    /**
     * precomputing the bounding boxes for each configuration
     */
    for ( k= 1; k <= MAXK; ++k ) {
        helpers::precompute(k);
        for ( auto u: configurations[k] ) {
            t_bounding_box bb= empty_box;
            for ( auto v= u; v; v&= ~L(v) ) {
                auto t= which[L(v)];
                bb= bb_manager::update_bounding_box(bb,ix[k][t],iy[k][t]);
            }
            assert( bb < +oo );
            mbb[k][u]= bb;
        }
    }

    /**
     * processing the test cases
     */
    for ( cin>>ts; ts--; ) {
        cin>>m>>n>>K;
        // fill everything with rocks initially
        for ( i= 0; i < numrows; ++i )
            for ( j= 0; j < numcols; g[i][j++]= '#' ) ;
        // clear the inner space
        for ( i= K; i < m+K; ++i )
            for ( j= K; j < n+K; ++j )
                g[i][j]= '.';
        // fill in the rocks from the test case
        for ( cin>>l; l--; (cin>>i>>j), g[(--i)+K][(--j)+K]= '#' ) ;

        /*
        for ( i= 0; i < numrows; ++i, putchar('\n'))
            for (j= 0; j < numcols; ++j )
                putchar(g[i][j]);
         */

        // find a connected component, and inflate its bounding box
        // by K on all sides
        vector<t_bounding_box> connected_components;
        helpers::init_dfs();
        for ( i= K; i < m+K; ++i )
            for ( j= K; j < n+K; ++j )
                if ( g[i][j] == '#' ) {
                    t_bounding_box bb= empty_box;
                    helpers::floodfill(i, j, bb);
                    if ( bb < +oo )
                        connected_components.emplace_back(bb_manager::inflate(bb,K));
                }

        //cout << "# of connected components: " << connected_components.size() << endl;
        // finally, for each connected component and each configuration
        // count how many times we cannot place the configuration
        // within the inflated bounding box of the connected component
        ans= 0, engine::init_engine(), engine::dp();
        for ( auto conf: configurations[K] ) {
            auto a= bb_manager::pack(mbb[K][conf],m,n);
            ans+= a;
            engine::init_engine();
            for ( auto cc: connected_components ) {
                auto b= engine::number_of_intersections(cc, conf);
                /*helpers::display(conf,K);
                cout << "The number of intersections: " << b << endl;*/
                ans -= b;
            }
        }

        cout << "Case " << ++cs << ": " << ans << endl;
    }
    return 0;
}

