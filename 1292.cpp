/*
 * 1292. Strategic Game
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define N (1 << 11)
#define oo 0xfffffffful
using namespace std;

int n,seen[N],yes;
unsigned int z[N][2];
vector<int> adj[N],v[N];

unsigned int 
calc_z( int x, int t ) {
    int i,y;
    unsigned int w;
    if ( z[x][t] < +oo )
        return z[x][t];
    if ( v[x].size() == 0 ) 
        return z[x][t] = t;
    for ( w = 1, i = 0; t && i < (int)v[x].size(); ++i )
        w += min(calc_z(y=v[x][i],0),calc_z(y=v[x][i],1));
    if ( t ) return z[x][t] = w;
    for ( w = 0, i = 0; !t && i < (int)v[x].size(); ++i )
        w += calc_z(y=v[x][i],1);
    return z[x][t] = w;
}

void dfs( int x ) {
    int i,y;
    assert( seen[x]!=yes );
    for ( seen[x] = yes, i = 0; i < (int)adj[x].size(); ++i )
        if ( seen[y=adj[x][i]] != yes )
            dfs(y),v[x].push_back(y);
}

int main() {
    int i,j,k,l,t;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( ;1 == scanf("%d",&n) && ++yes; dfs(0), printf("%u\n",min(calc_z(0,0),calc_z(0,1))) ) {
        for ( i = 0; i < n; adj[i].clear(), v[i].clear(), ++i );
        for ( t = 0; t < n; z[t][0]=z[t][1]=+oo, ++t )
            for ( scanf("%d:(%d)",&i,&k), l = 0; l < k; ++l ) {
                assert( 1 == scanf("%d",&j) );
                adj[i].push_back(j), adj[j].push_back(i);
            }
    }
    return 0;
}

