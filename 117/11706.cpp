/**
 * 11706: Party Night
 * TOPIC: cliques, greedy, coloring, bfs, one of the best
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define N (0x80)
#define MAXE (0x400)
enum { W, B, NONE };

int m,n,color[N][N],g[N][N],yes;
set<int> adj[N];
bool ok;

void pack_greedily( int newcomer, set<int> &candidates, set<int> &clique, const int clr ) {
    assert( candidates.count(newcomer) );
    assert( not clique.count(newcomer) );
    for ( auto z: clique ) {
        assert( g[newcomer][z] == yes );
        if ( color[newcomer][z] != NONE and color[newcomer][z] != clr ) {
            ok= false ;
            return ;
        }
        color[newcomer][z]= color[z][newcomer]= clr;
    }
    clique.insert(newcomer);
    set<int> new_candidates;
    set_intersection(begin(candidates),end(candidates),begin(adj[newcomer]),end(adj[newcomer]),
            inserter(new_candidates,begin(new_candidates)));
    assert( not new_candidates.count(newcomer) );
    if ( new_candidates.empty() )
        return ;
    pack_greedily(*new_candidates.begin(),new_candidates,clique,clr);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int i,j,k,x,y;
    for ( ;(cin >> n >> m) and (n or m) and ++yes; ) {
        for ( i= 0; i < n; adj[i++].clear() ) ;
        for ( i= 0; i < n; ++i )
            for ( j= 0; j < n; ++j )
                color[i][j]= NONE;
        for ( k= 0; k < m; ++k )
            cin >> i >> j, g[i][j]= g[j][i]= yes, adj[i].insert(j), adj[j].insert(i);
        for ( i= 0; i < n and adj[i].empty(); ++i ) ;
        if ( i == n ) {
            cout << "YES\n";
            continue ;
        }
        ok= true;
        queue<tuple<int,int,int>> q;
        for ( q.push(make_tuple(i,*adj[i].begin(),W)); not q.empty(); ) {
            auto tpl= q.front(); q.pop();
            x= get<0>(tpl), y= get<1>(tpl), k= get<2>(tpl);
            if ( color[x][y] != NONE and color[x][y] == (k^1) ) {
                ok= false ;
                goto TOO_BAD;
            }
            if ( color[x][y] == k )
                continue ;
            assert( color[x][y] == NONE );
            assert( g[x][y] == yes );
            set<int> candidates= adj[x], clique= {x};
            pack_greedily(y,candidates,clique,k);
            if ( not ok ) break ;
            for ( auto z: clique )
                for ( auto nz: adj[z] ) {
                    if (color[z][nz] == NONE) {
                        q.push(make_tuple(z,nz,k^1));
                    }
                    else {
                        if ( clique.count(nz) ) continue ;
                        if ( color[z][nz] == k ) {
                            ok= false ;
                            goto TOO_BAD;
                        }
                    }
                }
        }
        if ( ok ) {
            cout << "YES\n";
            continue ;
        }
        TOO_BAD: cout << "NO\n";
    }
    return 0;
}
