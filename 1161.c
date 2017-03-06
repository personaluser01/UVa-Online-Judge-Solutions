/*
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
#include <map>
#define N (1 << 8)
using namespace std;
typedef unsigned long long u64;

u64 conv( char *s ) {
    u64 u = 0;
    for ( int i = 0; s[i]; i |= ((u64)(s[i]-'A'))<<(4*i) );
    return u;
}

int tconv( char *s ) {
    int hh = ((int)(s[0]-'0'))*10 + ((int)(s[1]-'0')),
        mm = ((int)(s[2]-'0'))*10 + ((int)(s[3]-'0'));
    return hh*60+mm;
}

int n,V;
map<u64,int> m;

int ins( char *tmp ) {
    u64 u = conv(tmp);
    if ( m.find(u) == m.end() )
        return m[u] = V++;
    return m[u];
}

int main() {
    int i,j,k,l,t,t0,t1,connections;
    char tmp[0x40];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for(;1 == scanf("%d",&n); ) {
        V = 0, m.clear(), scanf("%s",tmp), m[conv(tmp)] = V++, scanf("%s",tmp), m[conv(tmp)] = V++;
        scanf("%s",tmp), t0 = tconv(tmp), scanf("%s",tmp), t1 = tconv(tmp);
        for(scanf("%d",&connections);connections--;){
            scanf("%s",tmp), i = ins(tmp), scanf("%s",tmp), j = ins(tmp);
            scanf("%d %s",&k,tmp), l = tconv(tmp), scanf("%s",tmp), t = tconv(tmp);
            assert( l <= t );
            if ( t > t1 ) continue ;
        }
    }
    return 0;
}

