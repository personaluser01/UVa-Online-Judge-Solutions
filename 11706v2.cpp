#include <bits/stdc++.h>
#define N (0x400)
#define NONE (-1)
#define MAXE (1 << 21)
#define MAXK (12)
#define pb push_back
using namespace std;
enum { WHITE, BLACK, GRAY };

bool ok;

class graph {
private:
    int g[N][N],yes{0},n,K,d[N],id[N][N],idx{0},color[MAXE],anc[N][MAXK],dfs_color[N];
    bool seen[N];
    set<int> adj[N];
    vector<pair<int,int>> edges;
    int up( int x, unsigned int u ) const {
        for ( int k= 0; u; u >>= 1, ++k )
            if ( u & 1 )
                x= anc[x][k];
        return x;
    }
    int lca( int x, int y ) const {
        if ( d[x] > d[y] )
            return lca(up(x,d[x]-d[y]),y);
        if ( d[x] < d[y] )
            return lca(y,x);
        if ( x == y )
            return x;
        for ( int k= K-1; k; --k ) {
            assert( x != y );
            assert( anc[x][k] == anc[y][k] );
            if ( anc[x][k-1] != anc[y][k-1] )
                x= anc[x][k-1], y= anc[y][k-1];
        }
        return anc[x][0];
    }
    bool are_connected( int x, int y ) const {
        return g[x][y] == yes;
    }
    bool dfs( int x, int clr ) {
        assert( dfs_color[x] == WHITE );
        dfs_color[x]= GRAY, color[x]= clr;
        for ( auto y: adj[x] ) {
            if ( dfs_color[y] == WHITE ) {
                if (not dfs(y, clr ^ 1))
                    return false;
            }
            else {
                if ( color[y] == clr )
                    return false ;
            }
        }
        dfs_color[x]= BLACK;
        return true ;
    }
public:
    size_t size() const { return n; }
    bool has_odd_cycle() {
        int x,k;
        queue<int> q;
        for ( int src= 0; src < n; ++src ) {
            if ( seen[src] ) continue ;
            for (seen[src] = true, q.push(src), d[src] = 0; not q.empty();) {
                x = q.front(), q.pop();
                for (auto y: get_adj(x)) {
                    if (seen[y]) {
                        auto z = lca(x, y);
                        auto path_length = d[x] + d[y] - 2 * d[z] + 1;
                        if (path_length & 1)
                            return true;
                        continue;
                    }
                    for (d[y] = d[x] + 1, q.push(y), seen[y] = true, anc[y][0] = x, k = 1;
                         k < K and anc[y][k - 1] != NONE; anc[y][k] = anc[anc[y][k - 1]][k - 1], ++k);
                }
            }
        }
        return false ;
    }
    bool has_odd_cycle_dfs() {
        for ( int x= 0; x < n; dfs_color[x++]= WHITE ) ;
        for ( int src= 0; src < n; ++src )
            if ( dfs_color[src] == WHITE ) {
                if ( not dfs(src,WHITE) )
                    return true;
            }
        return false;
    }
    int color_of( int x, int y ) {
        assert( are_connected(x,y) );
        return color[id[x][y]];
    }
    void paint( int x, int y, int c ) {
        assert( are_connected(x,y) );
        color[id[x][y]]= c;
    }
    graph() {
        memset(g,0,sizeof g);
    }
    void init( int nn ) {
        ++yes, idx= 0, this->n= nn, edges.clear();
        for ( int x= 0; x < n; seen[x]= false, adj[x++].clear() ) ;
        for ( K= 0; (1 << K) <= this->n; ++K ) ;
        for ( int x= 0; x < n; ++x )
            for ( int k= 0; k < K; anc[x][k++]= NONE ) ;
    }
    void add_arc( int x, int y ) {
        assert( x != y );
        g[x][y]= g[y][x]= yes;
    }
    void pack() {
        for ( int x= 0; x < n; ++x )
            for ( int y= x+1; y < n; ++y )
                if ( are_connected(x,y) ) {
                    color[id[x][y] = id[y][x] = idx++]= NONE;
                    adj[x].insert(y), adj[y].insert(x);
                    edges.emplace_back(x,y);
                }
    }
    const set<int>& get_adj( int x ) const {
        return adj[x];
    }
    const vector<pair<int,int>> &get_edges() const {
        return edges;
    }
};

ostream &operator << ( ostream &os, const graph &g ) {
    os << "n= " << g.size() << '\n';
    for ( int x= 0; x < g.size(); ++x ) {
        os << x << ":" << '\n';
        for ( auto y: g.get_adj(x) )
            os << " " << y;
        os << '\n';
    }
    return os;
}

map<int,set<int>> participation;

// invariant: "clique" contains the current clique
// "candidates" consists of all the nodes "x" such that "x" is adjacent to all "y" <- "clique"
// the problem is that the nodes inside "candidates" are not guaranteed
// to be connected to each other
// that is why the idea is to take the first element of "candidates"
// add it to "clique", and then filter out the "candidates"
// by leaving only "y"'s neighbours
// also, the invariant is that the edges between the nodes in "clique"
// are already colored
void greedy( graph &g, set<int> candidates, set<int> &clique, const int color ) {
    if ( candidates.empty() ) return ;
    auto it = candidates.begin();
    auto y= *it; candidates.erase(it);
    for ( auto z: clique ) {
        if ( g.color_of(z,y) != NONE and g.color_of(z,y) != color ) {
            ok= false;
            return ;
        }
        g.paint(z, y, color);
        participation[z].insert(color), participation[y].insert(color);
    }
    assert( not clique.count(y) );
    clique.insert(y);
    set<int> filtered;
    set_intersection(begin(candidates),end(candidates),begin(g.get_adj(y)),end(g.get_adj(y)),inserter(filtered,filtered.begin()));
    greedy(g,move(filtered),clique,color);
}

graph G,condensed;
vector<set<int>> cliques;
set<int> adj[N];

size_t intersection_size( const set<int> &a, const set<int> &b ) {
    vector<int> common;
    set_intersection(begin(a),end(a),begin(b),end(b),back_inserter(common));
    return common.size();
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    int i,j,k,n,m;
    for ( ;cin >> n >> m; ) {
        for ( ok= true, i= 0; i < n; adj[i++].clear() ) ;
        participation.clear();
        for ( G.init(n), k= 0; k < m; ++k )
            cin >> i >> j, G.add_arc(i,j);
        G.pack(), cliques.clear();
        bool first_ever= true;
        for ( bool changes= true; changes;) {
            changes= false;
            for ( const auto[x, y]: G.get_edges() ) {
                if ( G.color_of(x, y) == NONE and (first_ever or (participation.count(x) or participation.count(y))) ) {
                    if ( participation.count(x) and participation[x].size() >= 2 )
                        goto TOO_BAD;
                    if ( participation.count(y) and participation[y].size() >= 2 )
                        goto TOO_BAD;
                    if ( participation.count(x) and participation.count(y) )
                        goto TOO_BAD;
                    int this_color= first_ever?
                            WHITE :
                            (participation.count(x)?(*participation[x].begin())^1:(*participation[y].begin()^1));
                    first_ever= false, changes= true;
                    auto ax = G.get_adj(x), ay = G.get_adj(y);
                    set<int> clique = {x, y}, candidates;
                    participation[x].insert(this_color), participation[y].insert(this_color);
                    set_intersection(
                            begin(ax), end(ax), begin(ay), end(ay),
                            inserter(candidates, candidates.begin())
                    );
                    G.paint(x, y, this_color);
                    greedy(G, move(candidates), clique, cliques.size());
                    cliques.pb(move(clique));
                    if (not ok) goto TOO_BAD;
                }
            }
        }
        /*
        cerr << "cliques: " << cliques.size() << " in total" << endl;
        for ( i= 0; i < cliques.size(); ++i ) {
            for ( auto x: cliques[i] )
                cerr << x << ", ";
            cerr << endl;
        }
        */
        if ( not ok ) goto TOO_BAD;
        for ( i= 0; i < cliques.size(); ++i )
            for ( auto x: cliques[i] ) {
                adj[x].insert(i);
                if ( adj[x].size() >= 3 )
                    goto TOO_BAD;
            }
        for ( i= 0; i < cliques.size(); ++i )
            for ( j= i+1; j < cliques.size(); ++j )
                if ( intersection_size(cliques[i],cliques[j]) >= 2 )
                    goto TOO_BAD;
        condensed.init(cliques.size());
        for ( int x= 0; x < n; ++x ) {
            if ( adj[x].size() <= 1 )
                continue ;
            assert( adj[x].size() == 2 );
            auto it= adj[x].begin(), jt= next(it);
            condensed.add_arc(*it,*jt);
        }
        condensed.pack();
        //cerr << condensed;
        if ( condensed.has_odd_cycle_dfs() )
            goto TOO_BAD;
        cout << "YES" << endl;
        continue ;
        TOO_BAD: cout << "NO" << endl;
    }
    return 0;
}

