#include <bits/stdc++.h>
using namespace std;
#define N 0x80
#define MAXE (0x1000)
#define MAXK (9)
#define NONE (-1)
#define pb push_back

struct edge {
    int x,y;
    int other( int x ) {
        if ( this->x == x )
            return y;
        return this->x;
    }
};

int m,n,nxt[MAXE],lst[N],to[MAXE],seen[N],yes,E,d[N],
    anc[N][MAXK],K,clique_no[MAXE],cl,g[N][N],numedges;
edge e[MAXE];
vector<vector<int>> cliques;
vector<int> adj[N];

void add_arc( int x, int y, int id ) { g[x][y]= g[y][x]= id; }

int main() {
    int i,j,k,x,y;
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    for ( ;(cin >> n >> m) and (n or m) and ++yes; ) {
        memset(g,0,sizeof g);
        for ( k= 0; k < m; ++k )
            cin >> i >> j, add_arc(i,j,k+1);
        for ( numedges= 0, i= 0; i < n; ++i )
            for ( j= i+1; j < n; ++j )
                if ( g[i][j] )
                    clique_no[numedges]= NONE, e[numedges++]= {i,j};
        for ( cliques.clear(), k= 0; k < numedges; ++k, ++cl )
            if ( clique_no[k] == NONE ) {
                vector<int> c;
                for ( c.pb(e[k].x), c.pb(e[k].y), clique_no[k]= cl, x= 0; x < n; ++x ) {
                    if ( x == e[k].x or x == e[k].y ) continue ;
                    for ( i= 0; i < c.size(); ++i )
                        if ( x != c[i] and (not g[x][c[i]] or clique_no[g[x][c[i]]] != NONE) )
                            goto nx;
                    for ( c.pb(x), i= 0; i < c[i]; ++i )
                        if ( x != c[i] )
                            clique_no[g[x][c[i]]]= cl;
                    nx:;
                }
                cliques.pb(move(c));
            }
        for ( i= 0; i < cliques.size(); ++i )
            for ( j= 0; j < cliques[i].size(); ++j ) {
                adj[cliques[i][j]].pb(i);
                if ( adj[cliques[i][j]].size() >= 3 )
                    goto BAD;
            }

        BAD: cout << "NO" << endl;
    }
    return 0;
}
